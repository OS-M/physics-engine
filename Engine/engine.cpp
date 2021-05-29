#include "engine.h"

Engine::Engine(int tickrate, const QSizeF& world_size) :
    world_size_(world_size) {
  ticker_.start(1000 / tickrate);
  delta_time_measurer_.start();
  objects_ = std::make_shared<std::vector<std::shared_ptr<PhysicsObject>>>();
  QObject::connect(&ticker_, &QTimer::timeout,
                   [this]() {
                     this->OnTick();
                   });
}

void Engine::OnTick() {
  double delta_time = delta_time_measurer_.restart();
  delta_time /= 1000.;

  this->PrepareTick(delta_time);
  this->ProcessGravity(delta_time);
  this->SetVelocities(delta_time);
  this->SetPositions(delta_time);
}

void Engine::PrepareTick(double delta_time) {
  for (const auto& object : *objects_) {
    object->SetForce(Point());
  }
}

void Engine::ProcessGravity(double delta_time) {
  for (const auto& object : *objects_) {
    object->GetMutableForce() += gravity_force_;
  }
}

void Engine::SetVelocities(double delta_time) {
  for (const auto& object : *objects_) {
    object->GetMutableVelocity() +=
        object->GetForce() * delta_time / object->GetMass();
  }
}

void Engine::SetPositions(double delta_time) {
  for (const auto& object : *objects_) {
    object->Shift(object->GetVelocity() * delta_time);
  }
}

void Engine::AddObject(const std::shared_ptr<PhysicsObject>& physics_object) {
  objects_->push_back(physics_object);
}

QSizeF Engine::GetWorldSize() const {
  return world_size_;
}

std::shared_ptr<std::vector<std::shared_ptr<PhysicsObject>>> Engine::GetObjects() {
  return objects_;
}
