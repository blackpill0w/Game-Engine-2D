#pragma once

#include <SFML/Graphics.hpp>

namespace Engine {

enum class EventType { Other, KeyPress, KeyRelease };

class AbstractEvent {
 public:
  EventType get_type() const { return m_type; }
  virtual bool equals_sfml_event(const sf::Event &e) const { return false; };

 protected:
  EventType m_type = EventType::Other;
};

class KeyEvent : public AbstractEvent {
 public:
  using Key = sf::Keyboard::Key;

 public:
  // TODO: turn these bools into flags
  KeyEvent(const EventType et, const Key k, const bool ctrl = false, const bool alt = false,
           const bool shift = false)
      : m_key{k}, m_ctrl{ctrl}, m_alt{alt}, m_shift{shift} {
    if (et != EventType::KeyPress and et != EventType::KeyRelease)
      abort();
    m_type = et;
  };

  bool equals_sfml_event(const sf::Event &e) const override {
    return e.type == sf::Event::KeyPressed and e.key.code == m_key and e.key.control == m_ctrl and
           e.key.alt == m_alt and e.key.shift == m_shift;
  }

 private:
  const Key m_key;
  const bool m_ctrl;
  const bool m_alt;
  const bool m_shift;
};

}  // namespace Engine
