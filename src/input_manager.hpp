#pragma once

#include <vector>
#include <memory>
#include <utility>

#include <SFML/Graphics.hpp>

#include "./utils.hpp"
#include "./event.hpp"

namespace e2d {

using EventCallbackPair = std::pair<std::unique_ptr<AbstractEvent>, Callback>;
  using KeyCallbackPair = std::pair<KeyEvent::Key, Callback>;

class InputManager {
 public:
  InputManager();
  void bind(std::unique_ptr<AbstractEvent> e, Callback f);
  void bind_key_while_pressed(KeyEvent::Key k, Callback f);
  void update(sf::Window &win);
  void add_post_input_handling_callback(Callback f);

 protected:
  std::vector<EventCallbackPair> m_event_callback_pairs;
  std::vector<Callback> m_post_input_handling_callbacks;
  std::vector<KeyCallbackPair> m_while_pressed_key_callback_pairs;
};

}  // namespace e2d
