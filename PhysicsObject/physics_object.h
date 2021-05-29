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
  explicit PhysicsObject(const Point& position);

  virtual PhysicsObjectType GetType() const;

  virtual void Draw(QPainter* painter) const = 0;

  void SetPosition(const Point& position);
  Point GetPosition() const;

  void SetResiliency(double resiliency);
  double GetResiliency() const;

  void SetForce(const Point& force);
  Point GetForce() const;

  void SetVelocity(const Point& velocity);
  Point GetVelocity() const;

 private:
  Point position_;
  double resiliency_{0.};
  Point force_;
  Point velocity_;
};

#endif  // PHYSICS_OBJECT_H_
