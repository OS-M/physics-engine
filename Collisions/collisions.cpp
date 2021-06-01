#include "collisions.h"

CollidingPoint::CollidingPoint(Point point_, Point normal_,
                               double depth_,
                               SharedObject object1_,
                               SharedObject object2_)
    : point(point_),
      normal(normal_),
      depth(depth_),
      object1(std::move(object1_)),
      object2(std::move(object2_)) {}

std::vector<CollidingPoint> Collisions::GetCollisionPoints(
    SharedObject object1, SharedObject object2) {
  std::vector<CollidingPoint> points;
  if (object1->GetType() == PhysicsObjectType::kPolygonObject &&
      object2->GetType() == PhysicsObjectType::kPolygonObject) {
    for (auto point : object1->Points()) {
      if (object2->Contains(point)) {
        double depth;
        auto normal = object2->GetDistanceToClosestSide(point, &depth);
        points.emplace_back(point,
                            normal,
                            depth,
                            object1,
                            object2);
      }
    }
    for (auto point : object2->Points()) {
      if (object1->Contains(point)) {
        double depth;
        auto normal = object1->GetDistanceToClosestSide(point, &depth);
        points.emplace_back(point,
                            normal,
                            depth,
                            object1,
                            object2);
      }
    }
  }
  if (object1->GetType() == PhysicsObjectType::kPolygonObject) {
    object1.swap(object2);
  }
  if (object1->GetType() == PhysicsObjectType::kCircleObject &&
      object2->GetType() == PhysicsObjectType::kPolygonObject) {
    auto circle = std::dynamic_pointer_cast<CircleObject>(object1);
    auto polygon = std::dynamic_pointer_cast<PolygonObject>(object2);
    std::vector<Point> intersect_points;
    double depth = 1e9;
    for (int i = 0; i < polygon->GetPolygon().Size(); i++) {
      auto p = circle->Intersected(polygon->GetPolygon().GetSide(i));
      if (p.empty()) {
        continue;
      }
      intersect_points.insert(intersect_points.end(),
                              p.begin(), p.end());
      depth = Math::Min(depth,
                        circle->GetCircle().Radius() -
                        polygon->GetPolygon().GetSide(i).
                            DistanceTo(circle->GetCircle().Center()));
    }
    if (!intersect_points.empty()) {
      Point normal;
      for (auto point : intersect_points) {
        normal += Point(circle->GetCircle().Center(), point);
      }
      points.emplace_back(circle->GetCircle().Center() +
                              normal.Normalized() * circle->GetCircle().Radius(),
                          normal.Normalized(),
                          depth,
                          object1,
                          object2);
    }
  }
  if (object1->GetType() == PhysicsObjectType::kCircleObject &&
      object2->GetType() == PhysicsObjectType::kCircleObject) {
    auto circle1 = std::dynamic_pointer_cast<CircleObject>(object1);
    auto circle2 = std::dynamic_pointer_cast<CircleObject>(object2);
    if (circle1->Intersects(*circle2)) {
      auto intersect_points = circle1->Intersected(*circle2);
      Point normal = Point(circle1->GetCircle().Center(),
                           circle2->GetCircle().Center());
      auto depth = circle1->GetCollisionDepth(*circle2);
      points.emplace_back(circle1->GetCircle().Center() +
                              normal.Normalized() * circle1->GetCircle().Radius(),
                          normal.Normalized(),
                          depth,
                          object1,
                          object2);
    }
  }
  return points;
}
