import rhinoscript as rs

diameterTop = rs.userinterface.GetInteger("Diameter Top", 12)
diameterBottom = rs.userinterface.GetInteger("Diameter Bottom", 8)
diameterMiddle = ((diameterTop - diameterBottom) * 0.7) + diameterBottom

totalHeight = rs.userinterface.GetInteger("Height", 20)
middleHeight = totalHeight * 0.4

plane = rs.plane.WorldXYPlane()

bottom = rs.curve.AddCircle(plane, diameterBottom)
middle = rs.curve.AddCircle(plane, diameterMiddle)
top = rs.curve.AddCircle(plane, diameterTop)

rs.object.MoveObject(middle, [0, 0, middleHeight])
rs.object.MoveObject(top, [0, 0, totalHeight])

rs.surface.AddLoftSrf([bottom, middle, top])
