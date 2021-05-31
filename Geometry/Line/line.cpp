#include "line.h"

Line::Line(const Point& point1, const Point& point2) :
    point1_(point1), point2_(point2) {
  a_ = point2.Y() - point1.Y();
  b_ = point1.X() - point2.X();
  c_ = point2.X() * point1.Y() - point1.X() * point2.Y();
}

Line::Line(double a, double b, double c) : a_(a), b_(b), c_(c) {
  if (Math::IsZero(a) && Math::IsZero(b)) {
    qWarning() << "A and B are zero";
  }
}

bool Line::Contains(const Point& point) const {
  return Math::IsZero(this->DistanceTo(point));
}

std::vector<Point> Line::Intersected(const Line& other) const {
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
  if (Math::IsZero(point1_.DistanceTo(point2_)) {
    qWarning() << "Points are equal";
  }
  return Line(point1_.Rotated(point, angle),
              point2_.Rotated(point, angle));
}

Line Line::Normal() const {
  return Line(b_, -a_, c_);
}

double Line::DistanceTo(const Point& point) const {
  return std::fabs(a_ * point.X() + b_ * point.Y() + c_)
      / sqrt(a_ * a_ + b_ * b_);
}

bool Line::IsOnRightSide(const Point& point) const {
  if (Math::IsZero(point1_.DistanceTo(point2_)) {
    qWarning() << "Points are equal";
  }
  return (point2_ - point1_).IsRightTurn(point - point2_);
}

QLineF Line::ToQLineF() const {
  if (Math::IsZero(point1_.DistanceTo(point2_)) {
    qWarning() << "Points are equal";
  }
  return QLineF(point1_.ToQPointF(), point2_.ToQPointF());
}

double Line::A() const {
  return a_;
}

double Line::B() const {
  return b_;
}

double Line::C() const {
  return c_;
}

void Line::Shift(const Point& shift) {
  if (Math::IsZero(point1_.DistanceTo(point2_)) {
    qWarning() << "Points are equal";
  }
  *this = Line(point1_ + shift, point2_ + shift);
}

Point Line::Vector() const {
  return Point(point1_, point2_);
}
