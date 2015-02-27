import rhinoscript as rs

# get all user data
innerTopDiameter = rs.userinterface.GetInteger("Inner Top Diameter", 180)
innerBottomDiameter = rs.userinterface.GetInteger("Inner Bottom Diameter", 120)
innerHeight = rs.userinterface.GetInteger("Inner Height", 170)

# pot values
thickness = 5
bellyRatio = 0.8
bellyPosition = 0.4

# ring values
ringOuterDiameter = 46
ringInnerDiameter = 30
ringAngle = 4
ringInset = thickness * 0.7
ringPosition = 0.7


# GENERATE POT

# calculate stuff from user data
innerMiddleDiameter = ((innerTopDiameter - innerBottomDiameter) * bellyRatio) + innerBottomDiameter
innerMiddleHeight = innerHeight * bellyPosition
totalHeight = innerHeight + thickness
middleHeight = innerMiddleHeight + thickness

# radiuses
radiusTop = innerTopDiameter / 2
radiusMiddle = innerMiddleDiameter / 2
radiusBottom = innerBottomDiameter / 2

# draw hull outline
bottomOuterLine = rs.curve.AddLine([0, 0, 0], [radiusBottom, 0, 0])
bottomInnerLine = rs.curve.AddLine([0, 0, thickness], [radiusBottom - thickness, 0, thickness])
outerHullLine = rs.curve.AddArc3Pt([radiusBottom, 0, 0], [radiusTop, 0, totalHeight], [radiusMiddle, 0, middleHeight])
innerHullLine = rs.curve.AddArc3Pt([radiusBottom - thickness, 0, thickness], [radiusTop - thickness, 0, totalHeight],
                                   [radiusMiddle - thickness, 0, middleHeight])

topEdgeLine = rs.curve.AddArc3Pt([radiusTop, 0, totalHeight], [radiusTop - thickness, 0, totalHeight],
                                 [radiusTop - thickness / 2, 0, totalHeight + thickness / 2])
hullLine = rs.curve.JoinCurves([bottomOuterLine, outerHullLine, topEdgeLine, innerHullLine, bottomInnerLine], True)

# create rail
railLine = rs.curve.AddCircle([0, 0, 0], radiusBottom)

# sweep hull
hullSurface = rs.surface.AddRevSrf(hullLine, [[0, 0, 0], [0, 0, thickness]])

# remove remaining curves
rs.object.DeleteObjects([hullLine, railLine])


# GENERATE RING EMBOSS

# create ring
outerRing = rs.surface.AddCylinder([0, 0, 0], thickness, ringOuterDiameter / 2)
innerRing = rs.surface.AddCylinder([0, 0, 0], thickness, ringInnerDiameter / 2)
ring = rs.surface.BooleanDifference(outerRing, innerRing)

# position ring
rs.object.RotateObject(ring, [0, 0, 0], 90 - ringAngle, [1, 0, 0])
rs.object.MoveObject(ring, [0, radiusMiddle + ringInset, totalHeight * ringPosition])

# cut out ring
pot = rs.surface.BooleanDifference(hullSurface, ring)
