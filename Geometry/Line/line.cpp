#include "line.h"

Line::Line(const Point& point1, const Point& point2) :
    point1_(point1), point2_(point2) {
  a_ = point2.Y() - point1.Y();
  b_ = point1.X() - point2.X();
  c_ = point2.X() * point1.Y() - point1.X() * point2.Y();
}

bool Line::Contains(const Point& point) const {
  return Math::IsZero(this->DistanceTo(point));
}

std::vector<Point> Line::Intersects(const Line& other) const {
  double a1 = a_;
  double b1 = b_;
  double c1 = c_;
  double a2 = other.a_;
  double b2 = other.b_;
  double c2 = other.c_;

  if (Math::IsZero(b2 * a1 - b1 * a2)) {
    return {};
  }

  double x = (b1 * c2 - b2 * c1) / (b2 * a1 - b1 * a2);
  double y;
  if (Math::IsNotEqual(b1, 0)) {
    y = -(a1 * x + c1) / b1;
  } else {
    y = -(a2 * x + c2) / b2;
  }
  return {{x, y}};
}

Line Line::Rotated(const Point& point, double angle) const {
  return Line(point1_.Rotated(point, angle),
              point2_.Rotated(point, angle));
}

Line Line::Normal() const {
  Line line(point1_, point2_);
  line.a_ = b_;
  line.b_ = -a_;
  line.c_ = c_;
  return line;
}

double Line::DistanceTo(const Point& point) const {
  return std::fabs(a_ * point.X() + b_ * point.Y() + c_)
      / sqrt(a_ * a_ + b_ * b_);
}

bool Line::IsOnRightSize(const Point& point) const {
  return (point2_ - point1_).IsRightTurn(point - point2_);
}

QLineF Line::ToQLineF() const {
  return QLineF(point1_.ToQPointF(), point2_.ToQPointF());
}
