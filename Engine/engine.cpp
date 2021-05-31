#include "engine.h"

#include <utility>
#include <set>

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
  delta_time /= 300.;

  this->PrepareTick(delta_time);
  this->ProcessGravity(delta_time);
  this->SetVelocities(delta_time);
  this->ProcessCollisions(delta_time);
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
  std::vector<CollidingPoint> colliding_points;
  std::map<std::shared_ptr<PhysicsObject>, int> count_of_collisions;
  for (int i = 0; i < objects_->size(); i++) {
    for (int j = i + 1; j < objects_->size(); j++) {
      auto object1 = objects_->at(i);
      auto object2 = objects_->at(j);
      if (object1->IsStatic() && object2->IsStatic()) {
        continue;
      }
      bool collided = false;
      for (auto point : object1->Points()) {
        if (object2->Contains(point)) {
          collided = true;
          double depth;
          auto normal = object2->GetDistanceToClosestSide(point, &depth);
          colliding_points.emplace_back(point,
                                        normal,
                                        depth,
                                        object1,
                                        object2);
        }
      }
      for (auto point : object2->Points()) {
        if (object1->Contains(point)) {
          collided = true;
          double depth;
          auto normal = object1->GetDistanceToClosestSide(point, &depth);
          colliding_points.emplace_back(point,
                                        normal,
                                        depth,
                                        object1,
                                        object2);
        }
      }
      if (collided) {
        count_of_collisions[object1]++;
        count_of_collisions[object2]++;
      }
    }
  }
  std::sort(colliding_points.begin(), colliding_points.end(), [](
      const CollidingPoint& point1, const CollidingPoint& point2) {
    return point1.depth > point2.depth;
  });
  std::set<std::pair<std::shared_ptr<PhysicsObject>,
                     std::shared_ptr<PhysicsObject>>> processed;
  for (const auto& colliding_point : colliding_points) {
    auto object1 = colliding_point.object1;
    auto object2 = colliding_point.object2;
    if (processed.find(std::make_pair(object1, object2)) != processed.end()) {
      continue;
    }

    auto normal = colliding_point.normal.Normalized();

    auto velocity1 = object1->GetVelocity();
    auto velocity2 = object2->GetVelocity();
    auto v_projection1 = velocity1.ProjectionOn(normal);
    auto v_projection2 = velocity2.ProjectionOn(normal);
    auto mass1 = object1->GetMass();
    auto mass2 = object2->GetMass();

    auto k = (object1->GetRecoveryFactor() + object2->GetRecoveryFactor()) / 2.;

    auto velocity_to_set1 = velocity1 - normal * v_projection1;
    auto scalar_v1 = velocity1.Length()
        - (1 + k) * mass2 * (velocity1.Length() - velocity2.Length())
            / (mass1 + mass2);
    velocity_to_set1 -= normal * scalar_v1;

    auto velocity_to_set2 = velocity2 - normal * v_projection2;
    auto scalar_v2 = velocity2.Length()
        + (1 + k) * mass1 * (velocity1.Length() - velocity2.Length())
            / (mass1 + mass2);
    velocity_to_set2 -= normal * scalar_v2;

    object1->SetVelocity(velocity_to_set1);
    object2->SetVelocity(velocity_to_set2);

    processed.emplace(object1, object2);
    processed.emplace(object2, object1);
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

Engine::CollidingPoint::CollidingPoint(Point point_, Point normal_,
                                       double depth_,
                                       std::shared_ptr<PhysicsObject> object1_,
                                       std::shared_ptr<PhysicsObject> object2_)
    : point(point_),
      normal(normal_),
      depth(depth_),
      object1(std::move(object1_)),
      object2(std::move(object2_)) {}
