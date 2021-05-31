#ifndef RECTANGLE_OBJECT_H_
#define RECTANGLE_OBJECT_H_

#include "PhysicsObject/physics_object.h"
#include "Geometry/Polygon/polygon.h"
#include <utility>

class PolygonObject : public PhysicsObject {
 public:
  PolygonObject(const Point& position,
                double width, double height);
  explicit PolygonObject(std::vector<Point> points);
  virtual ~PolygonObject() = default;

  virtual PhysicsObjectType GetType() const;

  void Shift(const Point& shift) override;
  void Draw(QPainter* painter) const override;
  void Rotate(const Point& center, double angle);
  QPolygonF ToQPolygonF() const;
  std::vector<Point> Points() const override;
  bool Contains(const Point& point) const;

  Point GetDistanceToClosestSide(const Point& point,
                                 double* distance) const override;

 private:
  Polygon polygon_;
};

#endif  // RECTANGLE_OBJECT_H_
