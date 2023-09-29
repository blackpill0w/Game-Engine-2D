#pragma once

#include <SFML/Graphics.hpp>
#include "./entity.hpp"

namespace Engine {

/*
  A class representing an `sf::Texture` as an entity.
 */
class Texture : public Entity {
 public:
  /*
    # Note:
    The class takes ownership of `txtr_`.
   */
  Texture(const sf::Texture &txtr_) : Entity{}, txtr{std::move(txtr_)} {}

 public:
  sf::Texture txtr;
};
}  // namespace Engine
