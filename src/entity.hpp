#pragma once

namespace Engine {
class Entity {
 public:
  using Id = unsigned int;

 public:
  const Id id;

 public:
  Entity() : id{current_max_id++} {}

 private:
  inline static Id current_max_id = 0;
};
}  // namespace Engine
