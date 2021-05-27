#ifndef RECTANGLE_OBJECT_H_
#define RECTANGLE_OBJECT_H_

#include "PhysicsObject/physics_object.h"

class RectangleObject : public PhysicsObject {
 public:
  RectangleObject(const Point& position,
                  double width, double height);

  void Draw(QPainter* painter) const override;

  Rectangle GetBoundingRect() const override;
  Circle GetBoundingCircle() const override;

  Point GetCenter() const;

  QRectF ToQRect() const;

 private:
  double width_;
  double height_;
};

#endif  // RECTANGLE_OBJECT_H_
