#include <cmath>
#include "point.h"

Point::Point(double x, double y) : x_{x}, y_{y} {}

Point Point::operator+(const Point& other) const {
  return Point(x_ + other.x_, y_ + other.y_);
}

Point Point::operator-(const Point& other) const {
  return Point(x_ - other.x_, y_ - other.y_);
}

Point Point::operator*(double scalar) const {
  return Point(scalar * x_, scalar * y_);
}

Point Point::operator/(double scalar) const {
  return Point(x_ / scalar, y_ / scalar);
}

double Point::DistanceTo(const Point& point) const {
  return std::sqrt((x_ - point.x_) * (x_ - point.x_) +
      (y_ - point.y_) * (y_ - point.y_));
}

double Point::DotProduct(const Point& other) const {
  return x_ * other.x_ + y_ * other.y_;
}

double Point::Length() const {
  return std::sqrt(x_ * x_ + y_ * y_);
}

Point Point::GetNormal() const {
  return Point(y_, -x_);
}

double Point::AngleTo(const Point& point) const {
  return std::acos(point.DotProduct(*this) / (this->Length() * point.Length()));
}

double Point::Angle() const {
  return this->AngleTo(Point(1, 0));
}

Point Point::Normalized() const {
  return *this / this->Length();
}

double Point::X() const {
  return x_;
}

double Point::Y() const {
  return y_;
}

void Point::SetX(double x) {
  x_ = x;
}

void Point::SetY(double y) {
  y_ = y;
}

Point Point::Rotated(const Point& center, double angle) const {
  auto point = *this - center;
  return center
      + Point(point.X() * std::cos(angle) + point.Y() * std::sin(angle),
              -point.X() * std::sin(angle) + point.Y() * std::cos(angle));
}

bool Point::operator==(const Point& other) const {
  return Math::IsEqual(x_, other.x_) && Math::IsEqual(y_, other.y_);
}

bool Point::operator<(const Point& other) const {
  if (Math::IsEqual(x_, other.x_)) {
    return Math::IsLess(y_, other.y_);
  }
  return Math::IsLess(x_, other.x_);
}