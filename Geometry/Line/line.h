#ifndef LINE_H
#define LINE_H

#include <vector>
#include "Geometry/Point/point.h"
#include "Math/math.h"
#include <QDebug>

class Line {
 public:
  Line(const Point& point1, const Point& point2);

  bool Contains(const Point& point) const;
  std::vector<Point> Intersects(const Line& other) const;
  Line Rotated(const Point& point, double angle) const;
  Line Normal() const;
  double DistanceTo(const Point& point) const;
  bool IsOnRightSize(const Point& point) const;

 private:
  double a_;
  double b_;
  double c_;
  Point point1_;
  Point point2_;
};

#endif //LINE_H
