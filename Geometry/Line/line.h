#ifndef LINE_H
#define LINE_H

#include <vector>
#include "Geometry/Point/point.h"
#include "Math/math.h"
#include <QDebug>
#include <QLineF>

class Line {
 public:
  Line(const Point& point1, const Point& point2);
  Line(double a, double b, double c);

  bool Contains(const Point& point) const;
  std::vector<Point> Intersected(const Line& other) const;

  Line Rotated(const Point& point, double angle) const;
  Line Normal() const;
  double DistanceTo(const Point& point) const;
  bool IsOnRightSide(const Point& point) const;
  QLineF ToQLineF() const;
  Point Vector() const;

  void Shift(const Point& shift);

  double A() const;
  double B() const;
  double C() const;

 private:
  double a_;
  double b_;
  double c_;
  Point point1_;
  Point point2_;
};

#endif //LINE_H
