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

# create outer hull
outerBottouterMiddleCircleircle = rs.curve.AddCircle([0, 0, 0], radiusBottom)
outerMiddleCircle = rs.curve.AddCircle([0, 0, middleHeight], radiusMiddle)
outerTopCircle = rs.curve.AddCircle([0, 0, totalHeight], radiusTop)
outerHullSurface = rs.surface.AddLoftSrf([outerBottouterMiddleCircleircle, outerMiddleCircle, outerTopCircle])

# create inner hull
innerBottomCircle = rs.curve.AddCircle([0, 0, thickness], radiusBottom - thickness)
innerMiddleCircle = rs.curve.AddCircle([0, 0, middleHeight], radiusMiddle - thickness)
innerTopCircle = rs.curve.AddCircle([0, 0, totalHeight], radiusTop - thickness)
innerHullSurface = rs.surface.AddLoftSrf([innerBottomCircle, innerMiddleCircle, innerTopCircle])

# create top edge
topEdgeSurface = rs.surface.AddPlanarSrf([outerTopCircle, innerTopCircle])

# create bottom surface
outerBottomSurface = rs.surface.AddPlanarSrf([outerBottouterMiddleCircleircle])
innerBottomSurface = rs.surface.AddPlanarSrf([innerBottomCircle])

# cleanup curves
rs.object.DeleteObjects([outerBottouterMiddleCircleircle, outerMiddleCircle, outerTopCircle])
rs.object.DeleteObjects([innerBottomCircle, innerMiddleCircle, innerTopCircle])

# join all surfaces
potSurface = rs.surface.JoinSurfaces([outerHullSurface, innerHullSurface, topEdgeSurface,
                                      outerBottomSurface, innerBottomSurface])

# cleanup surfaces
rs.object.DeleteObjects([outerHullSurface, innerHullSurface, topEdgeSurface,
                         outerBottomSurface, innerBottomSurface])
