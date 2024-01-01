#include <fmt/core.h>
#include "./engine.hpp"

// Defined according to the spritesheet
enum class LauraAnimationStates { FacingUp = 0, FacingLeft, FacingDown, FacingRight };

int main() {
  e2d::Engine engine{};
  engine.input_manager.bind(
      std::make_unique<e2d::KeyEvent>(e2d::EventType::KeyPress, e2d::KeyEvent::Key::K),
      [&] { fmt::print("Hello, Mr. K"); });

  const auto laura_id = engine.world.new_character();
  auto laura_ss_id = engine.spritesheets_manager.load_spritesheet("../assets/laura.png", {64, 64});
  if (not laura_ss_id.has_value()) {
    fmt::print(stderr, "Couldn't load spritesheet");
    exit(1);
  }
  engine.world.get_character(laura_id)->sprite.setPosition(200.f, 200.f);
  engine.animation_manager.bind_entity(laura_id, *laura_ss_id);
  engine.animation_manager.set_animation_state(laura_id, size_t(LauraAnimationStates::FacingDown));

  const auto tileset_id =
      engine.spritesheets_manager.load_tiled_tileset("../maps/modern-city.tsx").value();
  engine.world.load_tiled_map("../maps/map1.tmx", tileset_id);

  engine.input_manager.bind(
      std::make_unique<e2d::KeyEvent>(e2d::EventType::KeyPress, e2d::KeyEvent::Key::G), [&] {
        engine.physics_engine.enable_gravity(laura_id, 2.f, 1.f);
        engine.physics_engine.set_gravity(laura_id, -10.f);
      });
  engine.input_manager.bind(
      std::make_unique<e2d::KeyEvent>(e2d::EventType::KeyPress, e2d::KeyEvent::Key::H),
      [&] { engine.physics_engine.disable_gravity(laura_id); });

  engine.input_manager.bind(
      std::make_unique<e2d::KeyEvent>(e2d::EventType::KeyPress, e2d::KeyEvent::Key::Right), [&] {
        engine.animation_manager.set_animation_state(laura_id,
                                                     size_t(LauraAnimationStates::FacingRight));
        engine.world.get_character(laura_id)->sprite.move(5.f, 0.f);
      });
  engine.input_manager.bind(
      std::make_unique<e2d::KeyEvent>(e2d::EventType::KeyPress, e2d::KeyEvent::Key::Left), [&] {
        engine.animation_manager.set_animation_state(laura_id,
                                                     size_t(LauraAnimationStates::FacingLeft));
        engine.world.get_character(laura_id)->sprite.move(-5.f, 0.f);
      });

  engine.input_manager.bind(
      std::make_unique<e2d::KeyEvent>(e2d::EventType::KeyPress, e2d::KeyEvent::Key::Up), [&] {
        engine.animation_manager.set_animation_state(laura_id,
                                                     size_t(LauraAnimationStates::FacingUp));
        engine.world.get_character(laura_id)->sprite.move(0.f, -5.f);
      });

  engine.input_manager.bind(
      std::make_unique<e2d::KeyEvent>(e2d::EventType::KeyPress, e2d::KeyEvent::Key::Down), [&] {
        engine.animation_manager.set_animation_state(laura_id,
                                                     size_t(LauraAnimationStates::FacingDown));
        engine.world.get_character(laura_id)->sprite.move(0.f, 5.f);
      });

  engine.run();
}
