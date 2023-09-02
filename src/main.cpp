#include <iostream>
#include "./engine.hpp"

int main() {
  Engine::Engine engine{};
  engine.input_manager.bind(
      std::make_unique<Engine::KeyEvent>(Engine::EventType::KeyPress, Engine::KeyEvent::Key::K),
      [&] {
        std::cout << "Hello,  Mr. K\n";
        std::cout.flush();
      });
  engine.run();
}
