#include "math.h"

namespace Math {

bool IsEqual(double lhs, double rhs, double epsilon) {
  return std::fabs(lhs - rhs) <= epsilon;
}

bool IsZero(double number) {
  return IsEqual(number, 0.);
}

bool IsNotEqual(double lhs, double rhs, double epsilon) {
  return !IsEqual(lhs, rhs, epsilon);
}

bool IsLess(double lhs, double rhs, double epsilon) {
  return (lhs + epsilon <= rhs);
}

bool IsLessOrEqual(double lhs, double rhs, double epsilon) {
  return IsLess(lhs, rhs, epsilon) || IsEqual(lhs, rhs, epsilon);
}

bool IsMore(double lhs, double rhs, double epsilon) {
  return (lhs - epsilon >= rhs);
}

bool IsMoreOrEqual(double lhs, double rhs, double epsilon) {
  return IsMore(lhs, rhs, epsilon) || IsEqual(lhs, rhs, epsilon);
}

bool IsInBounds(double number, double bound1, double bound2, double epsilon) {
  return IsLessOrEqual(bound1, number, epsilon) &&
      IsLessOrEqual(number, bound2, epsilon);
}

bool IsInBounds(int number, int bound1, int bound2) {
  return (bound1 <= number) && (number <= bound2);
}

double Min(double lhs, double rhs, double epsilon) {
  if (IsLess(lhs, rhs, epsilon)) {
    return lhs;
  }
  return rhs;
}

double Max(double lhs, double rhs, double epsilon) {
  if (IsMore(lhs, rhs, epsilon)) {
    return lhs;
  }
  return rhs;
}

bool IsNegative(double number, double epsilon) {
  return IsLess(number, 0, epsilon);
}

bool IsPositive(double number, double epsilon) {
  return IsMore(number, 0, epsilon);
}

}  // namespace Math

