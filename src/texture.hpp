#pragma once

#include <SFML/Graphics.hpp>
#include "./entity.hpp"

namespace e2d {

/*
  A class representing an `sf::Texture` as an entity.
 */
class Texture : public Entity {
 public:
  /*
    # Note:
    The class takes ownership of `txtr_`.
   */
  Texture(const std::string &filename) : Entity{}, txtr{} { load_from_file(filename); }
  bool has_texture() const { return m_has_texture; }
  bool load_from_file(const std::string &filename) {
    if (txtr.loadFromFile(filename)) {
      m_has_texture = true;
    }
    return m_has_texture;
  }

 public:
  sf::Texture txtr;

 protected:
  bool m_has_texture = false;
};
}  // namespace e2d
