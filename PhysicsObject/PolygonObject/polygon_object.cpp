#include "polygon_object.h"

PolygonObject::PolygonObject(const Point& position,
                             double width, double height) :
    polygon_(position, width, height) {}

PolygonObject::PolygonObject(std::vector<Point> points) :
    polygon_(std::move(points)) {}

void PolygonObject::Draw(QPainter* painter) const {
  painter->drawPolygon(this->ToQPolygonF());
}

QPolygonF PolygonObject::ToQPolygonF() const {
  return polygon_.ToQPolygonF();
}

void PolygonObject::Rotate(const Point& center, double angle) {
  polygon_ = polygon_.Rotated(center, angle);
}
