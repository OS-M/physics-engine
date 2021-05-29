#ifndef FPOLYGON_H
#define FPOLYGON_H

#include <QDebug>
#include <QVector>
#include <QPolygonF>

#include <vector>
#include <utility>
#include "Geometry/Point/point.h"
#include "Geometry/Segment/segment.h"

class Polygon {
 public:
  explicit Polygon(std::vector<Point> points);
  Polygon(const Point& point, double width, double height);
  Polygon(const Point& point1, const Point& point2);

  bool Contains(const Point& point) const;
  Segment GetSide(int index) const;
  int Size() const;

  QPolygonF ToQPolygonF() const;

 private:
  std::vector<Point> points_;
};

#endif //POLYGON_H
