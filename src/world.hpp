#pragma once

#include <unordered_map>
#include <vector>

#include "./sprite.hpp"

namespace e2d {

class Engine;

//** Not the actual position, TODO: docs
using SpritePosition = size_t;

class World {
 public:
  World(Engine *parent);
  const std::vector<Entity::Id> get_characters() const;
  const std::vector<Entity::Id> get_static_tiles() const;
  //** Creates a new character and return its id.
  Entity::Id new_character();
  bool is_valid_entity(Entity::Id id) const;
  Sprite *get_static_tile(const Entity::Id id);
  //** Returns `nullptr` if the character doesn't exist.
  Sprite *get_character(const Entity::Id id);
  Sprite *get_character_or_tile(const Entity::Id id);
  /**
     Load a map that was made by the <a href="https://www.mapeditor.org">Tiled</a> map editor.
     @param `filename` path (relative or absolute) to the map file (.tmx)
     @param `txtr_id` id of the corresponding map
  */
  bool load_tiled_map(const std::string &filename, const Entity::Id txtr_id);

  // protected:
  Engine *m_parent;
  std::unordered_map<Entity::Id, Sprite> m_characters;
  std::unordered_map<SpritePosition, Sprite> m_static_tiles;
};

}  // namespace e2d
