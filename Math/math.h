#ifndef MATH_H_
#define MATH_H_

#include <cmath>

namespace Math {

const double kEps = 1e-6;
const double kPi = M_PI;

bool IsEqual(double lhs, double rhs, double epsilon = kEps);
bool IsZero(double number);
bool IsNotEqual(double lhs, double rhs, double epsilon = kEps);
bool IsLess(double lhs, double rhs, double epsilon = kEps);
bool IsLessOrEqual(double lhs, double rhs, double epsilon = kEps);
bool IsMore(double lhs, double rhs, double epsilon = kEps);
bool IsMoreOrEqual(double lhs, double rhs, double epsilon = kEps);
double Min(double lhs, double rhs, double epsilon = kEps);
double Max(double lhs, double rhs, double epsilon = kEps);
bool IsInBounds(double number, double bound1, double bound2,
                double epsilon = kEps);
bool IsInBounds(int number, int bound1, int bound2);
bool IsNegative(double number, double epsilon = kEps);
bool IsPositive(double number, double epsilon = kEps);

}  // namespace Math

#endif //  MATH_H_
