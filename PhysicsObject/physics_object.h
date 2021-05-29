#ifndef PHYSICS_OBJECT_H_
#define PHYSICS_OBJECT_H_

#include <QPainter>

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

  virtual Rectangle GetBoundingRect() const = 0;
  virtual Circle GetBoundingCircle() const = 0;

 private:
  Point position_;
  double resiliency_{0.};
};

#endif  // PHYSICS_OBJECT_H_
