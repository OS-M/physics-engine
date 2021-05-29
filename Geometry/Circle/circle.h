#ifndef CIRCLE_H
#define CIRCLE_H

#include "Geometry/Point/point.h"
#include "Geometry/Line/line.h"
#include "Geometry/Segment/segment.h"

class Circle {
 public:
  Circle(const Point& center, double radius);

  bool Contains(const Point& point) const;
  std::vector<Point> Intersected(const Circle& other) const;
  std::vector<Point> Intersected(const Line& line) const;
  std::vector<Point> Intersected(const Segment& segment) const;

  Point Center() const;
  double Radius() const;
  double Diameter() const;

 private:
  Point center_;
  double radius_;
};

#endif //CIRCLE_H
