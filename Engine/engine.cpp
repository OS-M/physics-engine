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

void Engine::ProcessCollisions(double delta_time) {
  std::unordered_map<std::shared_ptr<PhysicsObject>, Point> velocities_to_set;
  for (const auto& current_object : *objects_) {
    for (const auto& colliding_object : *objects_) {
      if (current_object == colliding_object) {
        continue;
      }
      std::vector<Point> colliding_points;
      for (auto point : current_object->Points()) {
        if (colliding_object->Contains(point)) {
          colliding_points.push_back(point);
        }
      }
      for (auto point : colliding_object->Points()) {
        if (current_object->Contains(point)) {
          colliding_points.push_back(point);
        }
      }

      Point colliding_point;
      Point normal;
      double max_distance = -1e9;
      for (auto point : colliding_points) {
        double distance;
        auto curr_normal =
            colliding_object->GetDistanceToClosestSide(point, &distance);
        if (distance > max_distance) {
          max_distance = distance;
          normal = curr_normal;
          colliding_point = point;
        }
      }
      normal = normal.Normalized();

      auto curr_velocity = current_object->GetVelocity();
      auto colliding_velocity = colliding_object->GetVelocity();
      auto curr_v_projection = curr_velocity.ProjectionOn(normal);
      auto colliding_v_projection = colliding_velocity.ProjectionOn(normal);

      auto velocity_to_set = curr_velocity - normal * curr_v_projection;
      double system_pulse = curr_velocity.Length() * current_object->GetMass() +
          colliding_velocity.Length() * colliding_object->GetMass();
      velocity_to_set +=
          normal * (system_pulse / (2. * current_object->GetMass());
    }
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
