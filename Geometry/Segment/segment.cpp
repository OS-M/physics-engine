#include "segment.h"

Segment::Segment(const Point& point1, const Point& point2) :
    point1_(point1), point2_(point2), line_(point1, point2) {}

double Segment::Length() const {
  return this->Vector().Length();
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

std::vector<Point> Segment::Intersected(const Line& line) const {
  std::vector<Point> points;
  for (const auto& point : line_.Intersected(line)) {
    if (this->Contains(point)) {
      points.push_back(point);
    }
  }
  return points;
}

std::vector<Point> Segment::Intersected(const Segment& segment) const {
  std::vector<Point> points;
  for (const auto& point : this->Intersected(segment.GetLine())) {
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
  return Point(point1_, point2_);
}

QLineF Segment::ToQLineF() const {
  return QLineF(point1_.ToQPointF(), point2_.ToQPointF());
}

void Segment::Shift(const Point& shift) {
  *this = Segment(point1_ + shift, point2_ + shift);
}

double Segment::DistanceTo(const Point& point) const {
  double scalar1 = (point - point1_).DotProduct(point2_ - point1_);
  double scalar2 = (point - point2_).DotProduct(point1_ - point2_);
  if (Math::IsMoreOrEqual(scalar1 * scalar2, 0)) {
    return this->GetLine().DistanceTo(point);
  } else {
    return Math::Min(point.DistanceTo(point1_), point.DistanceTo(point2_));
  }
}
