#include "./engine.hpp"

namespace Engine {
Engine::Engine()
    : input_manager{}, spritesheets_manager{}, win{sf::VideoMode{500, 500}, "Engine Demo"} {
  input_manager.bind(std::make_unique<CloseWindowEvent>(), [&] { win.close(); });
}

void Engine::run() {
  while (win.isOpen()) {
    input_manager.update(win);

    win.clear();
    win.display();
  }
}

}  // namespace Engine
