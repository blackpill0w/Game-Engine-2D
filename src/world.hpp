#pragma once

#include <unordered_map>
#include <vector>

#include "./sprite.hpp"

namespace e2d {

class World {
 public:
  World();
  const std::vector<Entity::Id> get_characters() const;
  //** Creates a new character and return its id.
  Entity::Id new_character();
  bool is_valid_entity(Entity::Id id) const;
  //** Returns `nullptr` if the character doesn't exist.
  Sprite *get_character(const Entity::Id id);

 protected:
  std::unordered_map<Entity::Id, Sprite> m_characters;
  // TODO
};

}  // namespace e2d
