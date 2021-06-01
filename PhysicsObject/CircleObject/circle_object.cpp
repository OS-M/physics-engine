#include "circle_object.h"

CircleObject::CircleObject(const Point& center, double radius) :
    circle_(center, radius) {}

void CircleObject::Draw(QPainter* painter) const {
  painter->drawEllipse(circle_.Center().ToQPointF(),
                       circle_.Radius(),
                       circle_.Radius());
  painter->drawEllipse(circle_.Center().ToQPointF(), 1, 1);
}

void CircleObject::Shift(const Point& shift) {
  circle_.Shift(shift);
}

PhysicsObjectType CircleObject::GetType() const {
  return PhysicsObjectType::kCircleObject;
}

std::vector<Point> CircleObject::Points() const {
  return {};
}

bool CircleObject::Contains(const Point& point) const {
  return circle_.Contains(point);
}

Point CircleObject::GetDistanceToClosestSide(const Point& point,
                                             double* const distance) const {
  *distance = circle_.Radius() - circle_.Center().DistanceTo(point);
  Point normal(circle_.Center(), point);
  return normal.Normalized();
}

bool CircleObject::Intersects(const CircleObject& other) const {
  return circle_.Intersects(other.circle_);
}

std::vector<Point> CircleObject::Intersected(const CircleObject& other) const {
  return circle_.Intersected(other.circle_);
}

double CircleObject::GetCollisionDepth(const CircleObject& other) const {
  return circle_.Radius() + other.circle_.Radius() -
      circle_.Center().DistanceTo(other.circle_.Center());
}

std::vector<Point> CircleObject::Intersected(const Segment& segment) const {
  return circle_.Intersected(segment);
}

const Circle& CircleObject::GetCircle() const {
  return circle_;
}
