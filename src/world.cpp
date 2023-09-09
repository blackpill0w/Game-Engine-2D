#include "./world.hpp"

namespace Engine {

World::World() : m_characters{} { m_characters.reserve(16); }

const std::vector<Character> &World::characters() const { return m_characters; }

Entity::Id World::new_character() {
  m_characters.emplace_back(Character());
  return m_characters.back().id;
}

}  // namespace Engine
