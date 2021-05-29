#ifndef POLYGON_H
#define POLYGON_H

#include <QDebug>
#include <QVector>
#include <QPolygonF>

#include <vector>
#include <utility>
#include "Geometry/Point/point.h"
#include "Geometry/Segment/segment.h"
#include "Geometry/Circle/circle.h"

class Polygon {
 public:
  Polygon() = default;
  explicit Polygon(std::vector<Point> points);
  Polygon(const Point& point, double width, double height);
  Polygon(const Point& point1, const Point& point2);

  bool Contains(const Point& point) const;
  Segment GetSide(int index) const;
  int Size() const;
  Polygon Rotated(const Point& center, double angle) const;

  std::vector<Point> Points() const;

  QPolygonF ToQPolygonF() const;

  std::vector<Point> Intersects(const Line& line) const;
  std::vector<Point> Intersects(const Polygon& polygon) const;
  std::vector<Point> Intersects(const Circle& circle) const;

 private:
  std::vector<Point> points_;
};

#endif //POLYGON_H
