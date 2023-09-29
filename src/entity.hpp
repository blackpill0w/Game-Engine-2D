#pragma once

namespace Engine {

class Entity {
 public:
  using Id = unsigned int;

 public:
  Entity() : m_id{current_max_id++} {}
  Entity::Id get_id() const { return m_id; };

 protected:
  inline static Id current_max_id = 0;
  Id m_id;
};

}  // namespace Engine
