#pragma once

#include <vector>
#include <utility>

#include <SFML/Graphics.hpp>

#include "./utils.hpp"
#include "./event.hpp"

namespace Engine {

using EventCallbackPair = std::pair<AbstractEvent, Callback>;

class InputManager {
 public:
  InputManager();
  void bind(const AbstractEvent &e, Callback f);
  void update(sf::Window& win);
protected:
  std::vector<EventCallbackPair> m_event_callback_pairs;
};

}  // namespace Engine
