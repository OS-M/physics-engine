#ifndef POINT_H
#define POINT_H

#include <QPointF>
#include "Math/math.h"

class Point {
 public:
  Point() = default;
  Point(double x, double y);
  explicit Point(QPointF point_f);
  Point(const Point& point1, const Point& point2);

  Point operator+(const Point& other) const;
  void operator+=(const Point& other);
  Point operator-(const Point& other) const;
  void operator-=(const Point& other);
  Point operator*(double scalar) const;
  Point operator/(double scalar) const;
  bool operator==(const Point& other) const;
  bool operator<(const Point& other) const;

  double DistanceTo(const Point& point) const;
  double DotProduct(const Point& other) const;
  double Length() const;
  Point Normal() const;
  double AngleTo(const Point& point) const;
  double Angle() const;
  Point Normalized() const;
  bool IsRightTurn(const Point& point) const;

  void SetX(double x);
  double& MutableX();
  double X() const;

  void SetY(double y);
  double& MutableY();
  double Y() const;

  QPointF ToQPointF() const;

  Point Rotated(const Point& center, double angle) const;

 private:
  double x_{0.};
  double y_{0.};
};

#endif //POINT_H
