#include "segment.h"

Segment::Segment(const Point& point1, const Point& point2) :
    point1_(point1), point2_(point2), line_(point1, point2) {}

double Segment::Length() const {
  return (point2_ - point1_).Length();
}

bool Segment::Contains(const Point& point) const {
  if (!line_.Contains(point)) {
    return false;
  }
  return Math::IsInBounds(point.X(),
                          Math::Min(point1_.X(), point2_.X()),
                          Math::Max(point1_.X(), point2_.X())) &&
      Math::IsInBounds(point.Y(),
                       Math::Min(point1_.Y(), point2_.Y()),
                       Math::Max(point1_.Y(), point2_.Y()));
}

std::vector<Point> Segment::Intersects(const Line& line) const {
  std::vector<Point> points;
  for (const auto& point : line_.Intersects(line)) {
    if (this->Contains(point)) {
      points.push_back(point);
    }
  }
  return points;
}

std::vector<Point> Segment::Intersects(const Segment& segment) const {
  std::vector<Point> points;
  for (const auto& point : this->Intersects(segment.GetLine())) {
    if (segment.Contains(point)) {
      points.push_back(point);
    }
  }
  return points;
}

Line Segment::GetLine() const {
  return line_;
}

Point Segment::Middle() const {
  return Point(point1_ + point2_) / 2.;
}

Point Segment::Vector() const {
  return point2_ - point1_;
}
