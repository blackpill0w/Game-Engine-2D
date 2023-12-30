#pragma once

#include <SFML/Graphics.hpp>

#include "./input_manager.hpp"
#include "./spritesheets_manager.hpp"
#include "./world.hpp"
#include "./animation_manager.hpp"
#include "./physics_engine.hpp"

namespace e2d {
class Engine {
 public:
  //** Initialises the engine and its components.
  Engine();
  //** Creates the window, starts the game loop, and sets an event to handle closing the window.
  void run();

 public:
  InputManager input_manager;
  SpritesheetsManager spritesheets_manager;
  World world;
  AnimationManager animation_manager;
  PhysicsEngine physics_engine;
  // TODO: rendering engine
};
}  // namespace e2d
