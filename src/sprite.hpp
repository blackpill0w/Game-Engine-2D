#pragma once

#include <SFML/Graphics.hpp>

#include "./entity.hpp"

namespace e2d {

//** Simple wrapper for SFML
class Sprite {
 public:
  Sprite();

 public:
  Entity ntt;
  sf::Sprite sprite;
};

}  // namespace e2d
