#include "physics_object.h"

PhysicsObject::PhysicsObject(double mass) :
    mass_(mass) {}

PhysicsObjectType PhysicsObject::GetType() const {
  return PhysicsObjectType::kPhysicsObject;
}

double PhysicsObject::GetResiliency() const {
  return resiliency_;
}

void PhysicsObject::SetResiliency(double resiliency) {
  resiliency_ = resiliency;
}

Point PhysicsObject::GetForce() const {
  if (static_) {
    return Point();
  }
  return force_;
}

Point PhysicsObject::GetVelocity() const {
  if (static_) {
    return Point();
  }
  return velocity_;
}

void PhysicsObject::SetForce(const Point& force) {
  force_ = force;
}

void PhysicsObject::SetVelocity(const Point& velocity) {
  velocity_ = velocity;
}

Point& PhysicsObject::GetMutableForce() {
  return force_;
}

Point& PhysicsObject::GetMutableVelocity() {
  return velocity_;
}

void PhysicsObject::SetMass(double mass) {
  mass_ = mass;
}

double PhysicsObject::GetMass() const {
  return mass_;
}

bool PhysicsObject::IsStatic() const {
  return static_;
}

void PhysicsObject::SetStatic(bool is_static) {
  static_ = is_static;
}
