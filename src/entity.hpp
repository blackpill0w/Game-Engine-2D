#pragma once

namespace Engine {

class Entity {
 public:
  using Id = unsigned int;

 public:
  Entity() : m_id{current_max_id++} {}
  Entity::Id get_id() const { return m_id; };

 public:
  static constexpr Id InvalidId = 0;

 protected:
  inline static Id current_max_id = 1;
  Id m_id;
};

}  // namespace Engine
