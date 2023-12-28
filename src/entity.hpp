#pragma once

namespace e2d {

class Entity {
 public:
  using Id = unsigned int;

  Entity() : id{current_max_id++} {}

  static constexpr Id InvalidId   = 0;
  inline static Id current_max_id = 1;
  const Id id;
};

}  // namespace e2d
