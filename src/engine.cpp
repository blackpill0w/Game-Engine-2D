#include "./engine.hpp"

namespace e2d {

Engine::Engine()
    : input_manager{},
      spritesheets_manager{},
      world{},
      animation_manager{this},
      physics_engine{this},
      win{sf::VideoMode{500, 500}, "Engine Demo"} {
  input_manager.bind(std::make_unique<CloseWindowEvent>(), [&] { win.close(); });
}

void Engine::run() {
  win.setFramerateLimit(60);
  while (win.isOpen()) {
    input_manager.update(win);
    physics_engine.update();
    animation_manager.update();
    const auto chars = world.get_characters();

    win.clear();
    for (auto entt_id : chars) {
      win.draw(world.get_character(entt_id)->sprite);
    }
    win.display();
  }
}

}  // namespace e2d
