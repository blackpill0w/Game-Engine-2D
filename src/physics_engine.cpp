#include "./physics_engine.hpp"
#include "./engine.hpp"

namespace e2d {

PhysicsEngine::PhysicsEngine(Engine *parent) : m_parent{parent} {}

bool PhysicsEngine::enable_gravity(
    const Entity::Id id, const float max_velocity, const float increment_val
) {
  if (not m_parent->world.is_valid_entity(id)) {
    return false;
  }
  const EntityGravityData gravity_data{
      .velocity      = max_velocity,
      .increment_val = increment_val,
      .max_velocity  = max_velocity,
  };
  m_gravity_data[id] = std::move(gravity_data);
  return true;
}

bool PhysicsEngine::disable_gravity(const Entity::Id id) { return m_gravity_data.erase(id) != 0; }

bool PhysicsEngine::set_gravity(const Entity::Id id, const float velocity) {
  if (not m_gravity_data.contains(id) or velocity > m_gravity_data.at(id).velocity) {
    return false;
  }
  m_gravity_data.at(id).velocity = velocity;
  return true;
}

void PhysicsEngine::apply_gravity() {
  for (auto &[id, gravity_data] : m_gravity_data) {
    m_parent->world.get_character(id)->sprite.move(0, gravity_data.velocity);
    if (gravity_data.velocity - gravity_data.max_velocity <= 0.0005f) {
      gravity_data.velocity += gravity_data.increment_val;
    }
  }
}

void PhysicsEngine::update() { apply_gravity(); }

}  // namespace e2d
