#pragma once

#include <SFML/Graphics.hpp>
#include "./entity.hpp"

namespace Engine {
class Texture {
 public:
  Texture(const sf::Texture &txtr_) : entity{}, txtr{std::move(txtr_)} {}

 public:
  Entity entity;
  sf::Texture txtr;
};
}  // namespace Engine
