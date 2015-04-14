import rhinoscript as rs

# get all user data
innerTopD = rs.userinterface.GetInteger("Inner Top Diameter", 140)
innerBottomD = rs.userinterface.GetInteger("Inner Bottom Diameter", 110)
outerBottomD = rs.userinterface.GetInteger("Outer Bottom Diameter", 105)
innerH = rs.userinterface.GetInteger("Inner Height", 140)

# pot values
thickness = 5
bellyRatio = 0.8
bellyPosition = 0.7

# ring values
ringOuterD = 50
ringInnerD = 25
ringAngle = 3.5
ringInset = -5
ringPosition = 0.7

# arduino inlet
arduinoH = 35
arduinoW = 60
arduinoL = 80


# GENERATE POT

# calculate stuff from user data
innerMiddleD = ((innerTopD - innerBottomD) * bellyRatio) + innerBottomD
innerMiddleY = innerH * bellyPosition
innerBottomY = thickness + arduinoH
totalY = innerBottomY + innerH
middleY = innerMiddleY + thickness

# radiuses
radiusTop = innerTopD / 2
radiusMiddle = innerMiddleD / 2
radiusBottom = innerBottomD / 2
radiusGround = outerBottomD / 2

# draw hull outline
bottomOuterLine = rs.curve.AddLine([0, 0, 0], [radiusGround, 0, 0])
bottomInnerLine = rs.curve.AddLine([0, 0, innerBottomY], [radiusBottom - thickness, 0, innerBottomY])
outerHullLine = rs.curve.AddArc3Pt([radiusGround, 0, 0], [radiusTop, 0, totalY], [radiusMiddle, 0, middleY])
innerHullLine = rs.curve.AddLine([radiusBottom - thickness, 0, innerBottomY], [radiusTop - thickness, 0, totalY])

topEdgeLine = rs.curve.AddArc3Pt([radiusTop, 0, totalY], [radiusTop - thickness, 0, totalY],
                                 [radiusTop - thickness / 2, 0, totalY + thickness / 2])
hullLine = rs.curve.JoinCurves([bottomOuterLine, outerHullLine, topEdgeLine, innerHullLine, bottomInnerLine], True)

# sweep hull
pot = rs.surface.AddRevSrf(hullLine, [[0, 0, 0], [0, 0, thickness]])

# remove remaining curves
rs.object.DeleteObject(hullLine)


# GENERATE RING EMBOSS

# create ring
outerRing = rs.surface.AddCylinder([0, 0, 0], radiusBottom, ringOuterD / 2)
innerRing = rs.surface.AddCylinder([0, 0, 0], radiusBottom, ringInnerD / 2)
ring = rs.surface.BooleanDifference(outerRing, innerRing)

# position ring
rs.object.RotateObject(ring, [0, 0, 0], 90 - ringAngle, [1, 0, 0])
rs.object.MoveObject(ring, [0, radiusMiddle + ringInset, totalY * ringPosition])

# cut out ring
pot = rs.surface.BooleanDifference(pot, ring)


# GENERATE ARDUINO INLET

# create arduino
arduino = rs.surface.AddBox([
    [0, 0, 0],
    [arduinoW, 0, 0],
    [arduinoW, arduinoL, 0],
    [0, arduinoL, 0],
    [0, 0, arduinoH],
    [arduinoW, 0, arduinoH],
    [arduinoW, arduinoL, arduinoH],
    [0, arduinoL, arduinoH]
])

# position arduino
rs.object.MoveObject(arduino, [arduinoW / -2, arduinoL / -2, 0])

# cut out arduino
pot = rs.surface.BooleanDifference(pot, arduino)
