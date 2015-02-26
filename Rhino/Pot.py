import math
import rhinoscriptsyntax as rs

diameterTop = rs.GetInteger("Diameter Top", 12)
diameterBottom = rs.GetInteger("Diameter Bottom", 8)
diameterMiddle = ((diameterTop - diameterBottom) * 0.7) + diameterBottom

totalHeight = rs.GetInteger("Height", 20)
middleHeight = totalHeight * 0.4

plane = rs.WorldXYPlane()

bottom = rs.AddCircle(plane, diameterBottom)
middle = rs.AddCircle(plane, diameterMiddle)
top = rs.AddCircle(plane, diameterTop)

rs.MoveObject(middle, [0, 0, middleHeight])
rs.MoveObject(top, [0, 0, totalHeight])

rs.AddLoftSrf([bottom, middle, top])
