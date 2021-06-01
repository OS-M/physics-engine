#include "polygon_object.h"

PolygonObject::PolygonObject(const Point& position,
                             double width, double height) :
    polygon_(position, width, height) {}

PolygonObject::PolygonObject(std::vector<Point> points) :
    polygon_(std::move(points)) {}

void PolygonObject::Draw(QPainter* painter) const {
  painter->drawPolygon(this->ToQPolygonF());
  for (auto point : polygon_.Points()) {
    painter->drawEllipse(point.ToQPointF(), 1, 1);
  }
}

QPolygonF PolygonObject::ToQPolygonF() const {
  return polygon_.ToQPolygonF();
}

void PolygonObject::Rotate(const Point& center, double angle) {
  polygon_ = polygon_.Rotated(center, angle);
}

void PolygonObject::Shift(const Point& shift) {
  polygon_.Shift(shift);
}

PhysicsObjectType PolygonObject::GetType() const {
  return PhysicsObjectType::kPolygonObject;
}

std::vector<Point> PolygonObject::Points() const {
  return polygon_.Points();
}

bool PolygonObject::Contains(const Point& point) const {
  return polygon_.Contains(point);
}

Point PolygonObject::GetDistanceToClosestSide(const Point& point,
                                              double* const distance) const {
  *distance = 1e9;
  Point normal;
  for (int i = 0; i < polygon_.Size(); i++) {
    auto curr_distance = polygon_.GetSide(i).DistanceTo(point);
    if (curr_distance < *distance) {
      *distance = curr_distance;
      normal = polygon_.GetSide(i).Vector().Normal();
    }
  }
  return normal.Normalized();
}

const Polygon& PolygonObject::GetPolygon() const {
  return polygon_;
}

