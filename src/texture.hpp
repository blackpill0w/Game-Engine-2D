#pragma once

#include <SFML/Graphics.hpp>
#include "./entity.hpp"

namespace Engine {

/*
  A class representing an `sf::Texture` as an entity.
 */
class Texture {
 public:
  /*
    # Note:
    The class takes ownership of `txtr_`.
   */
  Texture(const sf::Texture &txtr_) : entity{}, txtr{std::move(txtr_)} {}

 public:
  Entity entity;
  sf::Texture txtr;
};
}  // namespace Engine
