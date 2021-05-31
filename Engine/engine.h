#ifndef ENGINE_H
#define ENGINE_H

#include <QTimer>
#include <QElapsedTimer>
#include <vector>
#include <memory>

#include "PhysicsObject/PolygonObject/polygon_object.h"

class Engine {
 public:
  Engine(int tickrate, const QSizeF& world_size);

  void AddObject(const std::shared_ptr<PhysicsObject>& physics_object);
  QSizeF GetWorldSize() const;
  std::shared_ptr<std::vector<std::shared_ptr<PhysicsObject>>> GetObjects();

  void OnTick();

 private:
  void PrepareTick(double delta_time);
  void ProcessGravity(double delta_time);
  void SetVelocities(double delta_time);
  void SetPositions(double delta_time);
  void ProcessCollisions(double delta_time);

  QSizeF world_size_;
  QTimer ticker_;
  QElapsedTimer delta_time_measurer_;
  std::shared_ptr<std::vector<std::shared_ptr<PhysicsObject>>> objects_;
  Point gravity_force_{0, 9.8};
};

#endif //ENGINE_H
