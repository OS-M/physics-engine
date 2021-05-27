#include "rectangle_object.h"

RectangleObject::RectangleObject(const Point& position,
                                 double width, double height) :
    PhysicsObject(position), width_(width), height_(height) {}

void RectangleObject::Draw(QPainter* painter) const {
  painter->drawRect(this->ToQRect());
}

Rectangle RectangleObject::GetBoundingRect() const {
  return Rectangle(this->GetPosition(),
                   Point(this->GetPosition().x() + width_,
                         this->GetPosition().y() + height_));
}

Circle RectangleObject::GetBoundingCircle() const {
  return Circle(this->GetBoundingRect()[0],
                this->GetBoundingRect()[2],
                CGAL::Orientation::CLOCKWISE);
}

QRectF RectangleObject::ToQRect() const {
  return QRectF(this->GetPosition().x(), this->GetPosition().y(),
                width_, height_);
}

Point RectangleObject::GetCenter() const {
  return CGAL::midpoint(this->GetBoundingRect()[0],
                        this->GetBoundingRect()[2]);
}
