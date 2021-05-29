#ifndef SEGMENT_H
#define SEGMENT_H

#include "Geometry/Point/point.h"
#include "Geometry/Line/line.h"
#include <QLineF>

class Segment {
 public:
  Segment(const Point& point1, const Point& point2);

  double Length() const;
  bool Contains(const Point& point) const;
  std::vector<Point> Intersects(const Line& line) const;
  std::vector<Point> Intersects(const Segment& segment) const;
  Point Middle() const;
  Line GetLine() const;
  Point Vector() const;
  QLineF ToQLineF() const;

 private:
  Point point1_;
  Point point2_;
  Line line_;
};

#endif //SEGMENT_H
