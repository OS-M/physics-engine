#include "polygon.h"

Polygon::Polygon(std::vector<Point> points) : points_(std::move(points)) {
  this->AddScanPoints();
}

Polygon::Polygon(const Point& point, double width, double height) {
  if (Math::IsNegative(width) || Math::IsNegative(height)) {
    qWarning() << "Negative height or width";
    return;
  }
  points_.push_back(point);
  points_.push_back(point + Point(width, 0.));
  points_.push_back(point + Point(width, height));
  points_.push_back(point + Point(0., height));
  this->AddScanPoints();
}

Polygon::Polygon(const Point& point1, const Point& point2) :
    Polygon(point1, point2.X() - point1.X(), point2.Y() - point1.Y()) {
  this->AddScanPoints();
}

bool Polygon::Contains(const Point& point) const {
  for (int i = 0; i < this->Size(); i++) {
    if (this->GetSide(i).Contains(point)) {
      return true;
    }
  }
  int l = 1;
  int r = this->Size() - 2;
  while (l < r) {
    int mid = (l + r + 1) / 2;
    if (Point(points_.at(0), points_.at(mid)).IsRightTurn(Point(points_.at(mid),
                                                                point))) {
      l = mid;
    } else {
      r = mid - 1;
    }
  }
  if (l + 1 >= this->Size()) {
    return false;
  }
  if (Point(points_.at(0),
            points_.at(l)).IsRightTurn(Point(points_.at(l),
                                             point)) &&
      !Point(points_.at(0),
             points_.at(l + 1)).IsRightTurn(Point(points_.at(l + 1),
                                                  point))) {
    return Point(points_.at(l), points_.at(l + 1)).IsRightTurn(
            Point(points_.at(l + 1), point));
  }
  return false;
}

Segment Polygon::GetSide(int index) const {
  if (!Math::IsInBounds(index, 0, this->Size() - 1)) {
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

Polygon Polygon::Rotated(const Point& center, double angle) const {
  auto points = points_;
  for (auto& point : points) {
    point = point.Rotated(center, angle);
  }
  return Polygon::FromRawPoints(points);
}

std::vector<Point> Polygon::Points() const {
  return points_;
}

std::vector<Point> Polygon::Intersected(const Line& line) const {
  std::vector<Point> answer;
  for (int i = 0; i < this->Size(); i++) {
    auto points = this->GetSide(i).Intersected(line);
    answer.insert(answer.end(), points.begin(), points.end());
  }
  return answer;
}

std::vector<Point> Polygon::Intersected(const Polygon& polygon) const {
  std::vector<Point> answer;
  for (const auto& point : polygon.points_) {
    if (this->Contains(point)) {
      answer.push_back(point);
    }
  }
  return answer;
}

std::vector<Point> Polygon::Intersected(const Circle& circle) const {
  std::vector<Point> answer;
  for (int i = 0; i < this->Size(); i++) {
    auto points = circle.Intersected(this->GetSide(i));
    answer.insert(answer.end(), points.begin(), points.end());
  }
  return answer;
}

void Polygon::Shift(const Point& shift) {
  for (int i = 0; i < this->Size(); i++) {
    points_[i] += shift;
  }
}

void Polygon::AddScanPoints() {
  std::vector<Point> points;
  for (int i = 0; i + 1 < points_.size(); i++) {
    points.push_back(points_[i]);
    points.push_back((points_[i] + points_[i + 1]) / 2.);
  }
  if (!points_.empty()) {
    points.push_back(points_.back());
    points.push_back((points_[0] + points_.back()) / 2.);
  }
  points_ = points;
}

Polygon Polygon::FromRawPoints(std::vector<Point> points) {
  Polygon result;
  result.points_ = std::move(points);
  return result;
}
