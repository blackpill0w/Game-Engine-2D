#include "./world.hpp"

namespace e2d {

World::World() : m_characters{} { m_characters.reserve(32); }

const std::vector<Entity::Id> World::get_characters() const {
  std::vector<Entity::Id> res{};
  res.reserve(m_characters.size());
  for (const auto &[id, c] : m_characters)
    res.push_back(id);
  return res;
}

Entity::Id World::new_character() {
  Sprite c{};
  const auto id    = c.ntt.id;
  m_characters.emplace(id, std::move(c));
  return id;
}

bool World::is_valid_entity(const Entity::Id id) const { return m_characters.contains(id); }

Sprite *World::get_character(const Entity::Id id) {
  return m_characters.contains(id) ? &m_characters.at(id) : nullptr;
}

}  // namespace e2d
