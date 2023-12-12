#include "./character.hpp"

namespace e2d {

Character::Character() : Entity{}, sprite{} {}

sf::Vector2f Character::get_position() const { return sprite.getPosition(); }

void Character::move(const float x_offset, const float y_offset) {
  sprite.move(x_offset, y_offset);
}

}  // namespace e2d
