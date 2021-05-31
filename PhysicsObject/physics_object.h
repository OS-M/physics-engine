#ifndef PHYSICS_OBJECT_H_
#define PHYSICS_OBJECT_H_

#include <QPainter>
#include <QMetaEnum>
#include "Geometry/Point/point.h"

namespace PhysicsObjectTypeWrapper {

Q_NAMESPACE

enum class PhysicsObjectType {
  kPhysicsObject,
  kPolygonObject,

  SIZE
};

Q_ENUM_NS(PhysicsObjectType)

}  // namespace WeaponTypeWrapper

using PhysicsObjectType = PhysicsObjectTypeWrapper::PhysicsObjectType;

Q_DECLARE_METATYPE(PhysicsObjectType)

class PhysicsObject {
 public:
  PhysicsObject() = default;
  explicit PhysicsObject(double mass);

  virtual PhysicsObjectType GetType() const;

  virtual void Draw(QPainter* painter) const = 0;

  virtual void Shift(const Point& shift) = 0;

  void SetRecoveryFactor(double resiliency);
  double GetRecoveryFactor() const;

  void SetForce(const Point& force);
  Point& GetMutableForce();
  Point GetForce() const;

  void SetVelocity(const Point& velocity);
  Point& GetMutableVelocity();
  Point GetVelocity() const;

  void SetMass(double mass);
  double GetMass() const;

  void SetStatic(bool is_static);
  bool IsStatic() const;

  virtual std::vector<Point> Points() const;
  virtual bool Contains(const Point& point) const = 0;
  // Returns normal to closest side
  virtual Point GetDistanceToClosestSide(const Point& point,
                                         double* distance) const = 0;

 private:
  bool static_{false};
  double recovery_factor_{0.6};
  Point force_;
  Point velocity_;
  double mass_{1.};
};

#endif  // PHYSICS_OBJECT_H_
