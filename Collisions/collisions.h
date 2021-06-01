#ifndef COLLISIONS_H_
#define COLLISIONS_H_

#include "PhysicsObject/physics_object.h"
#include "PhysicsObject/PolygonObject/polygon_object.h"
#include "PhysicsObject/CircleObject/circle_object.h"

struct CollidingPoint {
  CollidingPoint(Point point,
                 Point normal,
                 double depth,
                 SharedObject object1,
                 SharedObject object2);
  Point point;
  Point normal;
  double depth;
  SharedObject object1;
  SharedObject object2;
};

namespace Collisions {

std::vector<CollidingPoint> GetCollisionPoints(SharedObject object1,
                                               SharedObject object2);

}  // namespace Collisions

#endif //  COLLISIONS_H_
