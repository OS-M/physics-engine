#ifndef CIRCLE_OBJECT_H_
#define CIRCLE_OBJECT_H_

#include "Geometry/Circle/circle.h"
#include "PhysicsObject/physics_object.h"
#include "Geometry/Polygon/polygon.h"
#include <utility>

class CircleObject : public PhysicsObject {
 public:
  CircleObject(const Point& center, double radius);
  virtual ~CircleObject() = default;

  PhysicsObjectType GetType() const override;

  void Shift(const Point& shift) override;
  void Draw(QPainter* painter) const override;
  std::vector<Point> Points() const override;
  bool Contains(const Point& point) const override;
  bool Intersects(const CircleObject& other) const;
  std::vector<Point> Intersected(const CircleObject& other) const;
  void Rotate(const Point& center, double angle) override {};
  double GetCollisionDepth(const CircleObject& other) const;

  const Circle& GetCircle() const;

  Point GetDistanceToClosestSide(const Point& point,
                                 double* distance) const override;
  std::vector<Point> Intersected(const Segment& segment) const;

 private:
  Circle circle_;
};

#endif  // CIRCLE_OBJECT_H_
