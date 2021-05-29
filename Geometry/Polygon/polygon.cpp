#include "polygon.h"

Polygon::Polygon(std::vector<Point> points) : points_(std::move(points)) {}

Polygon::Polygon(const Point& point, double width, double height) {
  if (Math::IsNegative(width) || Math::IsNegative(height)) {
    qWarning() << "Negative height or width";
    return;
  }
  points_.push_back(point);
  points_.push_back(point + Point(width, 0.));
  points_.push_back(point + Point(width, height));
  points_.push_back(point + Point(0., height));
}

Polygon::Polygon(const Point& point1, const Point& point2) :
    Polygon(point1, point2.X() - point1.X(), point2.Y() - point1.Y()) {}

bool Polygon::Contains(const Point& point) const {
  int l = 1;
  int r = this->Size() - 2;
  while (l < r) {
    int mid = (l + r + 1) / 2;
    if (Point(points_.at(0),
              points_.at(mid)).IsRightTurn(Point(points_.at(mid),
                                                 point)) &&
        Point(points_.at(0),
              points_.at(mid + 1)).IsRightTurn(Point(points_.at(mid + 1),
                                                     point))) {
      l = mid;
    } else {
      r = mid - 1;
    }
  }
  return Point(points_.at(l), points_.at(l + 1)).IsRightTurn(Point(points_.at(
      l + 1), point));
}

Segment Polygon::GetSide(int index) const {
  if (!Math::IsInBounds(0, this->Size() - 1, index)) {
    qWarning() << "Index out of bounds";
    return Segment(Point(), Point());
  }
  return Segment(points_[index], points_[(index + 1) % this->Size()]);
}

int Polygon::Size() const {
  return points_.size();
}

QPolygonF Polygon::ToQPolygonF() const {
  QVector<QPointF> points;
  for (const auto& point : points_) {
    points.push_back(point.ToQPointF());
  }
  return QPolygonF(points);
}
