#pragma once

#include <SFML/Graphics.hpp>

#include "./entity.hpp"

namespace e2d {

class Character : public Entity {
 public:
  Character();
  sf::Vector2f get_position() const;
  /*
    Move the character by the given offset.
   */
  void move(const float x_offset, const float y_offset);

 public:
  sf::Sprite sprite;
};

}  // namespace e2d
