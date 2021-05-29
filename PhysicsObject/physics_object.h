#ifndef PHYSICS_OBJECT_H_
#define PHYSICS_OBJECT_H_

#include <QPainter>
#include <QMetaEnum>
#include "Geometry/Point/point.h"

namespace PhysicsObjectTypeWrapper {

Q_NAMESPACE

enum class PhysicsObjectType {
  kPhysicsObject,
  kStaticObject,

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

  void SetResiliency(double resiliency);
  double GetResiliency() const;

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

 private:
  bool static_{false};
  double resiliency_{0.};
  Point force_;
  Point velocity_;
  double mass_{1.};
};

#endif  // PHYSICS_OBJECT_H_
