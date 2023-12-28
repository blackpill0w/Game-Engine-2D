#include "./spritesheets_manager.hpp"

#include <iostream>
#include <algorithm>
#include <ranges>

using std::optional;
using std::vector;

namespace e2d {

SpritesheetsManager::SpritesheetsManager() : entity{}, m_spritesheets{}, m_sprites{} {
  m_spritesheets.reserve(32);
}

bool SpritesheetsManager::is_valid_spritesheet_id(const Entity::Id id) const {
  return std::ranges::any_of(m_spritesheets, [id](const Texture &x) { return x.ntt.id == id; });
}

bool SpritesheetsManager::is_valid_animation_state(const Entity::Id id,
                                                   const size_t ani_state) const {
  optional<size_t> ani_state_num = animation_states_num(id);
  return ani_state_num.has_value() and ani_state < ani_state_num;
}

bool SpritesheetsManager::is_valid_sprite(const Entity::Id id, const size_t ani_state,
                                          const size_t idx) const {
  return is_valid_animation_state(id, ani_state) and idx < m_sprites.at(id).at(ani_state).size();
}

const Texture *SpritesheetsManager::get_spritesheet(const Entity::Id id) const {
  if (! is_valid_spritesheet_id(id))
    return nullptr;
  const auto ss =
      std::ranges::find_if(m_spritesheets, [&](const Texture &txtr) { return txtr.ntt.id == id; });
  return &(*ss);
}

optional<Entity::Id> SpritesheetsManager::load_spritesheet(const std::string &filename,
                                                           const sf::Vector2u sprite_size) {
  if (! add_spritesheet(filename).has_value())
    return std::nullopt;

  auto ss_sprites = split_spritesheet(m_spritesheets.back(), sprite_size);
  if (! ss_sprites.has_value()) {
    m_spritesheets.pop_back();
    return std::nullopt;
  }
  m_sprites.emplace(m_spritesheets.back().ntt.id, std::move(*ss_sprites));

  return m_spritesheets.back().ntt.id;
}

optional<size_t> SpritesheetsManager::animation_states_num(const Entity::Id id) const {
  if (! is_valid_spritesheet_id(id))
    return std::nullopt;
  return m_sprites.at(id).size();
}

optional<size_t> SpritesheetsManager::animation_state_sprites_num(const Entity::Id id,
                                                                  const size_t ani_state) const {
  if (! is_valid_animation_state(id, ani_state))
    return std::nullopt;
  return m_sprites.at(id).at(ani_state).size();
}

optional<SpriteCoordinates> SpritesheetsManager::get_sprite_coordinates(const Entity::Id id,
                                                                        const size_t ani_state,
                                                                        const size_t idx) const {
  if (! is_valid_spritesheet_id(id))
    return std::nullopt;
  return m_sprites.at(id).at(ani_state).at(idx);
}

optional<Entity::Id> SpritesheetsManager::add_spritesheet(const std::string &filename) {
  Texture txtr{filename};
  if (! txtr.has_texture())
    return std::nullopt;
  m_spritesheets.emplace_back(std::move(txtr));

  return m_spritesheets.back().ntt.id;
}

optional<vector<vector<SpriteCoordinates>>> SpritesheetsManager::split_spritesheet(
    const Texture &ss, const sf::Vector2u size) const {
  if (size.x > ss.txtr.getSize().x || size.y > ss.txtr.getSize().y)
    return std::nullopt;

  vector<vector<SpriteCoordinates>> res{};
  res.reserve(32);
  for (size_t y = 0; y < ss.txtr.getSize().y; y += size.y) {
    res.emplace_back();
    res.back().reserve(size_t(ss.txtr.getSize().x / size.x));
    for (size_t x = 0; x < ss.txtr.getSize().x; x += size.x) {
      res.back().emplace_back(SpriteCoordinates(x, y, size.x, size.y));
    }
  }
  return res;
}

}  // namespace e2d
