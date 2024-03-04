#include "./input_manager.hpp"

namespace e2d {

InputManager::InputManager()
    : m_event_callback_pairs{},
      m_post_input_handling_callbacks{},
      m_while_pressed_key_callback_pairs{} {
  m_event_callback_pairs.reserve(16);
  m_post_input_handling_callbacks.reserve(16);
  m_while_pressed_key_callback_pairs.reserve(16);
}

void InputManager::bind(std::unique_ptr<AbstractEvent> e, Callback f) {
  // Assumes that window.setKeyRepeatEnabled(false);
  m_event_callback_pairs.push_back({std::move(e), f});
}

void InputManager::bind_key_while_pressed(const KeyEvent::Key k, const Callback f) {
  m_while_pressed_key_callback_pairs.push_back({k, f});
}

void InputManager::add_post_input_handling_callback(Callback f) {
  m_post_input_handling_callbacks.emplace_back(f);
}

void InputManager::update(sf::Window &win) {
  sf::Event e;
  while (win.pollEvent(e)) {
    for (const auto &[event, callback] : m_event_callback_pairs) {
      if (event->equals_sfml_event(e)) {
        callback();
      }
    }
  }
  for (const auto &f : m_post_input_handling_callbacks) {
    f();
  }
  for (const auto &[k, f] : m_while_pressed_key_callback_pairs) {
    if (sf::Keyboard::isKeyPressed(k)) {
      f();
    }
  };
}

}  // namespace e2d
