#include "engine.h"

#include <utility>
#include <set>

Engine::Engine(int tickrate, const QSizeF& world_size) :
    world_size_(world_size) {
  ticker_.start(1000 / tickrate);
  delta_time_measurer_.start();
  objects_ = std::make_shared<std::vector<SharedObject>>();
  QObject::connect(&ticker_, &QTimer::timeout,
                   [this]() {
                     this->OnTick();
                   });
}

void Engine::OnTick() {
  double delta_time = delta_time_measurer_.restart();
  delta_time /= 300.;

  this->PrepareTick(delta_time);
  this->ProcessForces(delta_time);
  this->ProcessPressureForces(delta_time);
  this->SetVelocities(delta_time);
  this->ProcessCollisions(delta_time);
  this->SetPositions(delta_time);
}

void Engine::PrepareTick(double delta_time) {
  for (const auto& object : *objects_) {
    object->SetForce(Point());
  }
  colliding_points_.clear();
  for (int i = 0; i < objects_->size(); i++) {
    for (int j = i + 1; j < objects_->size(); j++) {
      auto object1 = objects_->at(i);
      auto object2 = objects_->at(j);
      if (object1->IsStatic() && object2->IsStatic()) {
        continue;
      }
      auto points = Collisions::GetCollisionPoints(object1, object2);
      colliding_points_.insert(colliding_points_.end(),
                               points.begin(), points.end());
    }
  }
  std::sort(colliding_points_.begin(), colliding_points_.end(), [](
      const CollidingPoint& point1, const CollidingPoint& point2) {
    return point1.depth > point2.depth;
  });
}

void Engine::ProcessForces(double delta_time) {
  for (const auto& object : *objects_) {
    object->GetMutableForce() +=
        (gravity_force_ + object->GetAdditionalForce()) * object->GetMass();
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

void Engine::ProcessCollisions(double delta_time) {
  std::map<std::pair<SharedObject, SharedObject>, double> depths;
  std::set<std::pair<SharedObject, SharedObject>> processed;
  for (const auto& colliding_point : colliding_points_) {
    auto object1 = colliding_point.object1;
    auto object2 = colliding_point.object2;
    if (processed.find(std::make_pair(object1, object2)) != processed.end()) {
      continue;
    }
    if (Math::IsLess(colliding_point.depth,
                     collide_depth_[std::make_pair(object1, object2)])) {
      continue;
    }
    depths[std::make_pair(object1, object2)] = colliding_point.depth;
    depths[std::make_pair(object2, object1)] = colliding_point.depth;
    auto normal = colliding_point.normal.Normalized();

    auto velocity1 = object1->GetVelocity();
    auto velocity2 = object2->GetVelocity();
    auto v_projection1 = velocity1.ProjectionOn(normal);
    auto v_projection2 = velocity2.ProjectionOn(normal);
    auto mass1 = object1->GetMass();
    auto mass2 = object2->GetMass();

    auto k = (object1->GetRecoveryFactor() + object2->GetRecoveryFactor()) / 2.;

    auto velocity_to_set1 = velocity1 - normal * v_projection1;
    auto scalar_v1 = v_projection1
        - (1 + k) * mass2 * (v_projection1 - v_projection2)
            / (mass1 + mass2);
    velocity_to_set1 += normal * scalar_v1;

    auto velocity_to_set2 = velocity2 - normal * v_projection2;
    auto scalar_v2 = v_projection2
        + (1 + k) * mass1 * (v_projection1 - v_projection2)
            / (mass1 + mass2);
    velocity_to_set2 += normal * scalar_v2;

    object1->SetVelocity(velocity_to_set1);
    object2->SetVelocity(velocity_to_set2);

    processed.emplace(object1, object2);
    processed.emplace(object2, object1);
  }
  collide_depth_ = depths;
}

void Engine::AddObject(const SharedObject& physics_object) {
  objects_->push_back(physics_object);
}

QSizeF Engine::GetWorldSize() const {
  return world_size_;
}

std::shared_ptr<std::vector<SharedObject>> Engine::GetObjects() {
  return objects_;
}

void Engine::ProcessPressureForces(double delta_time) {
  for (int iter = 0; iter < objects_->size(); iter++) {
    std::set<std::pair<SharedObject, SharedObject>> processed;
    for (const auto& colliding_point : colliding_points_) {
      auto object1 = colliding_point.object1;
      auto object2 = colliding_point.object2;
      if (processed.contains(std::make_pair(object1, object2))) {
        continue;
      }
      processed.emplace(object1, object2);
      processed.emplace(object2, object1);
      auto normal = colliding_point.normal;
      auto f1 = object1->GetForce();
      auto f2 = object2->GetForce();
      auto f1_projection = f1.ProjectionOn(normal);
      auto f2_projection = f2.ProjectionOn(normal);
      f2 += normal * f1_projection;
      f1 += normal * f2_projection;
      f1 -= normal * f1_projection;
      f2 -= normal * f2_projection;
      object1->SetForce(f1);
      object2->SetForce(f2);
    }
  }
}

const std::vector<CollidingPoint>& Engine::GetCollidingPoints() const {
  return colliding_points_;
}
