#include "./input_manager.hpp"

namespace Engine {

InputManager::InputManager() : m_event_callback_pairs{} {
  m_event_callback_pairs.reserve(16);
}

void InputManager::bind(const AbstractEvent &e, Callback f) {
  m_event_callback_pairs.push_back({e, f});
}

void InputManager::update(sf::Window &win) {
  sf::Event e;
  while (win.pollEvent(e)) {
    for (auto &[event, func_to_exec] : m_event_callback_pairs) {
      if (event.equals_sfml_event(e)) {
        func_to_exec();
      }
    }
  }
}

}  // namespace Engine
