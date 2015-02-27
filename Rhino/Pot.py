import rhinoscript as rs

# get all user data
diameterTop = rs.userinterface.GetInteger("Diameter Top", 180)
diameterBottom = rs.userinterface.GetInteger("Diameter Bottom", 120)
totalHeight = rs.userinterface.GetInteger("Height", 170)
thickness = rs.userinterface.GetInteger("Thickness", 5)

# calculate stuff from user data
diameterMiddle = ((diameterTop - diameterBottom) * 0.8) + diameterBottom
middleHeight = totalHeight * 0.4

# radiuses
radiusTop = diameterTop / 2
radiusMiddle = diameterMiddle / 2
radiusBottom = diameterBottom / 2

# draw hull outline
bottomOuterLine = rs.curve.AddLine([0, 0, 0], [radiusBottom, 0, 0])
bottomInnerLine = rs.curve.AddLine([0, 0, thickness], [radiusBottom - thickness, 0, thickness])
outerHullLine = rs.curve.AddArc3Pt([radiusBottom, 0, 0], [radiusTop, 0, totalHeight], [radiusMiddle, 0, middleHeight])
innerHullLine = rs.curve.AddArc3Pt([radiusBottom - thickness, 0, thickness], [radiusTop - thickness, 0, totalHeight],
                                   [radiusMiddle - thickness, 0, middleHeight])
topEdgeLine = rs.curve.AddLine([radiusTop, 0, totalHeight], [radiusTop - thickness, 0, totalHeight])
hullLine = rs.curve.JoinCurves([bottomOuterLine, outerHullLine, topEdgeLine, innerHullLine, bottomInnerLine], True)

# create rail
railLine = rs.curve.AddCircle([0, 0, 0], radiusBottom)

# sweep hull
hullSurface = rs.surface.AddRevSrf(hullLine, [[0, 0, 0], [0, 0, thickness]])

# remove remaining curves
rs.object.DeleteObjects([hullLine, railLine])
