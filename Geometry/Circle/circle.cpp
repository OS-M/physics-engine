#include "circle.h"

Circle::Circle(const Point& center, double radius)
    : center_(center), radius_(radius) {}

bool Circle::Contains(const Point& point) const {
  return Math::IsLessOrEqual(center_.DistanceTo(point), radius_);
}

std::vector<Point> Circle::Intersected(const Circle& other) const {
  // inspired by http://e-maxx.ru/algo/circles_intersection
  Circle circle1(Point(), radius_);
  Circle circle2(other.center_ - center_, other.radius_);
  auto x2 = circle2.center_.X();
  auto y2 = circle2.center_.Y();
  auto points = circle1.Intersected(
      Line(-2 * x2, -2 * y2,
           x2 * x2 + y2 * y2 + radius_ * radius_
               - circle2.radius_ * circle2.radius_));
  for (auto& point : points) {
    point = point + center_;
  }
  return points;
}

std::vector<Point> Circle::Intersected(const Line& line) const {
  double center_x = center_.X();
  double center_y = center_.Y();
  double r = radius_;

  double perp_a = line.Normal().A();
  double perp_b = line.Normal().B();
  double perp_c = line.Normal().C();

  if (Math::IsNotEqual(perp_a, 0)) {
    double temp_x = (-perp_b * center_y - perp_c) / perp_a;
    perp_c -= perp_a * (center_x - temp_x);
  } else {
    double temp_y = (-perp_a * center_x - perp_c) / perp_b;
    perp_c -= perp_b * (center_y - temp_y);
  }

  auto tangent_point = line.Intersected(Line(perp_a, perp_b, perp_c));
  if (tangent_point.empty()) {
    return {};
  }
  double distance_to_line = line.DistanceTo(center_);
  double segment_length =
      std::sqrt(std::fabs(r * r - distance_to_line * distance_to_line));
  double delta_y = segment_length * sin(atan(-line.A() / line.B()));
  double
      delta_x = sqrt(fabs(segment_length * segment_length - delta_y * delta_y));
  Point res1(tangent_point[0].X() + delta_x, tangent_point[0].Y() + delta_y);
  Point res2(tangent_point[0].X() - delta_x, tangent_point[0].Y() - delta_y);
  std::vector<Point> answer;
  if (this->Contains(res1) && line.Contains(res1)) {
    answer.push_back(res1);
  }
  if (this->Contains(res2) && line.Contains(res2)) {
    answer.push_back(res2);
  }
  return answer;
}

Point Circle::Center() const {
  return center_;
}

double Circle::Radius() const {
  return radius_;
}

double Circle::Diameter() const {
  return 2. * radius_;
}

std::vector<Point> Circle::Intersected(const Segment& segment) const {
  auto points = this->Intersected(segment.GetLine());
  std::vector<Point> answer;
  for (auto point : points) {
    if (segment.Contains(point)) {
      answer.push_back(point);
    }
  }
  return answer;
}

void Circle::Shift(const Point& shift) {
  center_ += shift;
}

bool Circle::Intersects(const Circle& other) const {
  return Math::IsLessOrEqual(center_.DistanceTo(other.center_),
                             this->Radius() + other.Radius());
}
