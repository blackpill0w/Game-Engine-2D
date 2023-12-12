#include "./input_manager.hpp"

namespace e2d {

InputManager::InputManager() : m_event_callback_pairs{} { m_event_callback_pairs.reserve(16); }

void InputManager::bind(std::unique_ptr<AbstractEvent> e, Callback f) {
  m_event_callback_pairs.push_back({std::move(e), f});
}

void InputManager::update(sf::Window &win) {
  sf::Event e;
  while (win.pollEvent(e)) {
    for (size_t i = 0; i < m_event_callback_pairs.size(); ++i) {
      if (m_event_callback_pairs[i].first->equals_sfml_event(e)) {
        m_event_callback_pairs[i].second();
      }
    }
  }
}

}  // namespace e2d
