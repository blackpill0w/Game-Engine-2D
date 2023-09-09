#pragma once

#include <vector>

#include "./character.hpp"

namespace Engine {

class World {
 public:
  World();
  const std::vector<Character> &characters() const;
  Entity::Id new_character();

 protected:
  std::vector<Character> m_characters;
};

}  // namespace Engine
