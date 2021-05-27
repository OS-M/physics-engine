#include "physics_object.h"

PhysicsObject::PhysicsObject(const Point& position) :
    position_(position) {}

PhysicsObjectType PhysicsObject::GetType() const {
  return PhysicsObjectType::kPhysicsObject;
}

double PhysicsObject::GetResiliency() const {
  return resiliency_;
}

void PhysicsObject::SetResiliency(double resiliency) {
  resiliency_ = resiliency;
}

Point PhysicsObject::GetPosition() const {
  return position_;
}

void PhysicsObject::SetPosition(const Point& position) {
  position_ = position;
}
