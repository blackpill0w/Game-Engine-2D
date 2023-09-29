#pragma once

#include <unordered_map>
#include <vector>

#include "./character.hpp"

namespace Engine {

class World {
 public:
  World();
  const std::vector<Entity::Id> characters() const;
  /**
    Create a new character and return its id.
  */
  Entity::Id new_character();
  /**
    Return `nullptr` if the character doesn't exist.
  */
  Character* get_character(const Entity::Id id);

 protected:
  std::unordered_map<Entity::Id, Character> m_characters;
};

}  // namespace Engine
