#ifndef POINT_H
#define POINT_H

#include "Math/math.h"

class Point {
 public:
  Point() = default;
  Point(double x, double y);

  Point operator+(const Point& other) const;
  Point operator-(const Point& other) const;
  Point operator*(double scalar) const;
  Point operator/(double scalar) const;
  bool operator==(const Point& other) const;
  bool operator<(const Point& other) const;

  double DistanceTo(const Point& point) const;
  double DotProduct(const Point& other) const;
  double Length() const;
  Point GetNormal() const;
  double AngleTo(const Point& point) const;
  double Angle() const;
  Point Normalized() const;
  bool IsRightTurn(const Point& point) const;

  double X() const;
  void SetX(double x);
  double Y() const;
  void SetY(double y);

  Point Rotated(const Point& center, double angle) const;

 private:
  double x_{0.};
  double y_{0.};
};

#endif //POINT_H
