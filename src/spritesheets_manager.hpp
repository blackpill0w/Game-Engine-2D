#pragma once

#include <string>
#include <vector>
#include <optional>
#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "./entity.hpp"

namespace Engine {

using SpriteCoordinates = sf::Rect<uint16_t>;

class Spritesheet {
 public:
  Spritesheet(const sf::Texture &txtr);

 public:
  Entity entity;
  sf::Texture txtr;
};

/**
  A class that stores all of the spritesheets, and claasifies their sprites by animation
  state.
*/
class SpritesheetsManager {
 public:
  SpritesheetsManager();

  bool is_valid_spritesheet_id(const Entity::Id id) const;

  bool is_valid_animation_state(const Entity::Id id, const size_t ani_state) const;

  bool is_valid_sprite(const Entity::Id id, const size_t ani_state,
                                   const size_t idx) const;

  std::optional<size_t> number_of_animation_states(const Entity::Id id) const;

  std::optional<size_t> animation_state_sprites_number(const Entity::Id id,
                                                       const size_t ani_state) const;

  std::optional<SpriteCoordinates> get_sprite_coordinates(const Entity::Id id,
                                                          const size_t ani_state,
                                                          const size_t idx) const;

  /**
    Load a spritesheet from an image file and extract sprites from it.
    Each sprite in the sheet *must* have the same size `sprite_size`.
    Each line in the spritesheet defines a separate state (Idle, Walk...) which are
    just unsigned ints starting from 0.
    # Return
    `std::nullopt` is returned if:
     - the file doesn't exist
     - the file is of invalid or unsupported type
     - the `size` equal to or less than 0 or is bigger than the spritesheet
  */
  std::optional<Entity::Id> load_spritesheet(const std::string &filename,
                                             const sf::Vector2u sprite_size);
  /**
     Bind a drawable entities to a spritesheet.
     # Return
     `std::nullopt` if `id` doesn't refer to an existing spritesheet.
  */
  bool bind_entity(const Entity::Id entity_id, const Entity::Id spritesheet_id);

 public:
  const Entity entity;

 private:
  /**
    Load a spritesheet from a file and add it to `m_spritesheets`.
  */
  std::optional<Entity::Id> add_spritesheet(const std::string &filename);

  /**
    Split spritesheets, a vector of sprites for each animation state.
    # Return
    Return `std::nullopt` if the `size` equal to or less than 0
    or is bigger than the spritesheet.
   */
  std::optional<std::vector<std::vector<SpriteCoordinates>>> split_spritesheet(
      const Spritesheet &ss, const sf::Vector2u size) const;

 private:
  std::vector<Spritesheet> m_spritesheets;
  /**
    Store sprites of a spritesheet, grouped by animation state (which is a line in the
    spritesheet).
  */
  std::unordered_map<Entity::Id, std::vector<std::vector<SpriteCoordinates>>> m_sprites;
  /**
     Store drawable entities and spritesheets pairs.
   */
  std::unordered_map<Entity::Id, std::vector<Entity::Id>> m_bound_entities;
};
}  // namespace Engine
