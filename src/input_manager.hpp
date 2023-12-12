#pragma once

#include <vector>
#include <memory>
#include <utility>

#include <SFML/Graphics.hpp>

#include "./utils.hpp"
#include "./event.hpp"

namespace e2d {

using EventCallbackPair = std::pair<std::unique_ptr<AbstractEvent>, Callback>;

class InputManager {
 public:
  InputManager();
  void bind(std::unique_ptr<AbstractEvent> e, Callback f);
  void update(sf::Window &win);

 protected:
  std::vector<EventCallbackPair> m_event_callback_pairs;
};

}  // namespace e2d
