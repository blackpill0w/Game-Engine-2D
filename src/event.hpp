#pragma once

#include <SFML/Graphics.hpp>

namespace Engine {

enum class EventType { Other, CloseWindow, KeyPress, KeyRelease };

class AbstractEvent {
 public:
  AbstractEvent(const EventType et) : m_type{et} {}
  virtual bool equals_sfml_event([[maybe_unused]] const sf::Event &e) const = 0;

 protected:
  const EventType m_type;
};

/**
   Represents a windows close event.
 */
class CloseWindowEvent : public AbstractEvent {
 public:
  CloseWindowEvent() : AbstractEvent{EventType::CloseWindow} {}
  bool equals_sfml_event(const sf::Event &e) const override { return e.type == sf::Event::Closed; }
};

/**
   Represents a key press or key release event, the engine aborts if `EventType et` is neither of
   those two.
 */
class KeyEvent : public AbstractEvent {
 public:
  using Key = sf::Keyboard::Key;

 public:
  // TODO: turn these bools into flags
  KeyEvent(const EventType et, const Key k, const bool ctrl = false, const bool alt = false,
           const bool shift = false)
      : AbstractEvent{et}, m_key{k}, m_ctrl{ctrl}, m_alt{alt}, m_shift{shift} {
    if (et != EventType::KeyPress and et != EventType::KeyRelease)
      abort();
  };

  bool equals_sfml_event(const sf::Event &e) const override {
    const bool press_event   = e.type == sf::Event::KeyPressed and m_type == EventType::KeyPress;
    const bool release_event = e.type == sf::Event::KeyReleased and m_type == EventType::KeyRelease;
    const bool correct_key_are_pressed = e.key.code == m_key and e.key.control == m_ctrl and
                                         e.key.alt == m_alt and e.key.shift == m_shift;
    return (press_event or release_event) and correct_key_are_pressed;
  }

 protected:
  const Key m_key;
  const bool m_ctrl;
  const bool m_alt;
  const bool m_shift;
};

}  // namespace Engine
