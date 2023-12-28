#pragma once

#include <unordered_map>
#include <functional>

#include "./entity.hpp"

namespace e2d {

class Engine;

enum class Direction { None, Right, Left, Up, Down };

struct EntityGravityData {
  float velocity;
  float increment_val;
  float max_velocity;
};

class PhysicsEngine {
 public:
  PhysicsEngine(Engine *parent);
  bool enable_gravity(const Entity::Id id, const float max_velocity, const float increment_val);
  bool set_gravity(const Entity::Id id, const float velocity);
  bool disable_gravity(const Entity::Id id);

  bool on_collision(const Entity::Id id, const std::function<void(const Direction dir)> callback);

  void update();

 protected:
  void apply_gravity();

 protected:
  // maximum velocity and increment value
  std::unordered_map<Entity::Id, EntityGravityData> m_gravity_data;
  std::unordered_map<Entity::Id, std::function<void(const Direction dir)>> m_collision_callbacks;
  Engine *m_parent;
};
}  // namespace e2d
