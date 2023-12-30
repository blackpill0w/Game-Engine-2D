#include "./engine.hpp"

#include <fmt/core.h>

namespace e2d {

Engine::Engine()
    : input_manager{},
      spritesheets_manager{},
      world{this},
      animation_manager{this},
      physics_engine{this} {}

void Engine::run() {
  sf::RenderWindow win{sf::VideoMode{500, 500}, "Engine Demo"};

  input_manager.bind(std::make_unique<CloseWindowEvent>(), [&] { win.close(); });

  win.setFramerateLimit(60);
  while (win.isOpen()) {
    input_manager.update(win);
    physics_engine.update();
    animation_manager.update();
    const auto chars = world.get_characters();
    const auto tiles = world.get_static_tiles();
    win.clear();
    for (auto &[id, s] : world.m_static_tiles) {
      win.draw(s.sprite);
    }
    for (auto entt_id : chars) {
      win.draw(world.get_character(entt_id)->sprite);
    }
    win.display();
  }
}

}  // namespace e2d
