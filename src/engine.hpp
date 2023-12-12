#pragma once

#include <SFML/Graphics.hpp>

#include "./input_manager.hpp"
#include "./spritesheets_manager.hpp"
#include "./world.hpp"
#include "./animation_manager.hpp"

namespace e2d {
class Engine {
 public:
  /**
    Initialises the engine and its components, and sets an event to handle closing the window.
  */
  Engine();
  void run();

 public:
  InputManager input_manager;
  SpritesheetsManager spritesheets_manager;
  World world;
  AnimationManager animation_manager;
  // TODO: rendering engine

 protected:
  sf::RenderWindow win;
};
}  // namespace e2d
