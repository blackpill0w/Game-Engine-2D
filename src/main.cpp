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

  const auto laura_id = engine.world.new_character();
  auto laura_ss_id    = engine.spritesheets_manager.load_spritesheet("../laura.png", {64, 64});
  if (not laura_ss_id.has_value()) {
    exit(1);
  }
  engine.animation_manager.bind_entity(laura_id, *laura_ss_id);
  engine.animation_manager.set_animation_state(laura_id, 1);

  engine.run();
}
