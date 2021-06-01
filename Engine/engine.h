#ifndef ENGINE_H
#define ENGINE_H

#include <QTimer>
#include <QElapsedTimer>
#include <vector>
#include <memory>

#include "PhysicsObject/PolygonObject/polygon_object.h"
#include "Collisions/collisions.h"

class Engine {
 public:
  Engine(int tickrate, const QSizeF& world_size);

  void AddObject(const SharedObject& physics_object);
  QSizeF GetWorldSize() const;
  std::shared_ptr<std::vector<SharedObject>> GetObjects();
  const std::vector<CollidingPoint>& GetCollidingPoints() const;

  void OnTick();

 private:
  void PrepareTick(double delta_time);
  void ProcessForces(double delta_time);
  void SetVelocities(double delta_time);
  void SetPositions(double delta_time);
  void ProcessCollisions(double delta_time);
  void ProcessPressureForces(double delta_time);

  QSizeF world_size_;
  QTimer ticker_;
  QElapsedTimer delta_time_measurer_;
  std::shared_ptr<std::vector<SharedObject>> objects_;
  Point gravity_force_{0, 9.8};
  std::map<std::pair<SharedObject, SharedObject>, double> collide_depth_;
  std::vector<CollidingPoint> colliding_points_;
};

#endif //ENGINE_H
