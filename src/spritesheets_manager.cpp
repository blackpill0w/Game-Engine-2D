#include "./spritesheets_manager.hpp"

#include <algorithm>
#include <cmath>
#include <ranges>
#include <filesystem>

#include <fmt/core.h>
#include <tinyxml2.h>

namespace fs = std::filesystem;
using std::optional;
using std::vector;

namespace e2d {

SpritesheetsManager::SpritesheetsManager() : entity{}, m_spritesheets{}, m_sprites{} {
  m_spritesheets.reserve(32);
}

bool SpritesheetsManager::is_valid_spritesheet_id(const Entity::Id id) const {
  return std::ranges::any_of(m_spritesheets, [id](const Texture &x) { return x.ntt.id == id; });
}

bool SpritesheetsManager::is_valid_animation_state(const Entity::Id id, const size_t ani_state)
    const {
  optional<size_t> ani_state_num = animation_states_num(id);
  return ani_state_num.has_value() and ani_state < ani_state_num;
}

bool SpritesheetsManager::is_valid_sprite(
    const Entity::Id id, const size_t ani_state, const size_t idx
) const {
  return is_valid_animation_state(id, ani_state) and idx < m_sprites.at(id).at(ani_state).size();
}

const Texture *SpritesheetsManager::get_spritesheet(const Entity::Id id) const {
  if (not is_valid_spritesheet_id(id))
    return nullptr;
  const auto ss =
      std::ranges::find_if(m_spritesheets, [&](const Texture &txtr) { return txtr.ntt.id == id; });
  return &(*ss);
}

optional<Entity::Id> SpritesheetsManager::load_spritesheet(
    const std::string &filename, const sf::Vector2<size_t> sprite_size
) {
  if (not add_spritesheet(filename).has_value())
    return std::nullopt;

  auto ss_sprites = split_spritesheet(m_spritesheets.back(), sprite_size);
  if (not ss_sprites.has_value()) {
    m_spritesheets.pop_back();
    return std::nullopt;
  }
  m_sprites.emplace(m_spritesheets.back().ntt.id, std::move(*ss_sprites));

  return m_spritesheets.back().ntt.id;
}

optional<size_t> SpritesheetsManager::animation_states_num(const Entity::Id id) const {
  if (not is_valid_spritesheet_id(id))
    return std::nullopt;
  return m_sprites.at(id).size();
}

optional<size_t> SpritesheetsManager::animation_state_sprites_num(
    const Entity::Id id, const size_t ani_state
) const {
  if (not is_valid_animation_state(id, ani_state))
    return std::nullopt;
  return m_sprites.at(id).at(ani_state).size();
}

optional<SpriteCoordinates> SpritesheetsManager::get_sprite_at(
    const Entity::Id id, const size_t ani_state, const size_t idx
) const {
  if (not is_valid_spritesheet_id(id))
    return std::nullopt;
  return m_sprites.at(id).at(ani_state).at(idx);
}

optional<SpriteCoordinates> SpritesheetsManager::get_sprite_coordinates(
    const Entity::Id id, const size_t row, const size_t col
) const {
  return get_sprite_at(id, row, col);
}

optional<SpriteCoordinates> SpritesheetsManager::get_sprite_with_tiled_id(
    const Entity::Id id, const size_t tiled_id
) const {
  if (not is_valid_spritesheet_id(id))
    return std::nullopt;
  const size_t len = m_sprites.at(id).size();
  const size_t l   = size_t(floor(tiled_id / len));
  const size_t col = tiled_id % len;
  return m_sprites.at(id).at(l).at(col);
}

optional<Entity::Id> SpritesheetsManager::add_spritesheet(const std::string &filename) {
  Texture txtr{filename};
  if (not txtr.has_texture())
    return std::nullopt;
  m_spritesheets.emplace_back(std::move(txtr));

  return m_spritesheets.back().ntt.id;
}

optional<vector<vector<SpriteCoordinates>>> SpritesheetsManager::split_spritesheet(
    const Texture &ss, const sf::Vector2<size_t> size
) const {
  if (size.x > ss.txtr.getSize().x || size.y > ss.txtr.getSize().y)
    return std::nullopt;

  vector<vector<SpriteCoordinates>> res{};
  res.reserve(32);
  for (size_t y = 0; y < ss.txtr.getSize().y; y += size.y) {
    res.emplace_back();
    res.back().reserve(ss.txtr.getSize().x / size.x);
    for (size_t x = 0; x < ss.txtr.getSize().x; x += size.x) {
      res.back().emplace_back(SpriteCoordinates(x, y, size.x, size.y));
    }
  }
  return res;
}

std::optional<Entity::Id> SpritesheetsManager::load_tiled_tileset(const std::string &filename) {
  tinyxml2::XMLDocument tileset_tsx_file{};
  const auto err = tileset_tsx_file.LoadFile(filename.c_str());
  if (tinyxml2::XML_SUCCESS != err) {
    fmt::println(
        stderr, "ERROR: There was an error parsing the map file `{}`, here is some info:", filename
    );
    fmt::println(stderr, "\t- Error code: {}", size_t(err));
    fmt::println(stderr, "\t- Error line number: {}", tileset_tsx_file.ErrorLineNum());
    fmt::println(stderr, "\t- Error string: {}", tileset_tsx_file.ErrorStr());
    return std::nullopt;
  }
  const tinyxml2::XMLElement *tileset_info = tileset_tsx_file.FirstChildElement("tileset");
  if (tileset_info == nullptr) {
    fmt::println(stderr, "ERROR: tileset_info is null");
    exit(1);
  }
  const size_t tile_w = tileset_info->Unsigned64Attribute("tilewidth");
  const size_t tile_h = tileset_info->Unsigned64Attribute("tileheight");
  if (tile_w <= 0 or tile_h <= 0) {
    fmt::println(stderr, "ERROR: tile_w or tile_h is 0");
    return std::nullopt;
  }
  const tinyxml2::XMLElement *tileset_img = tileset_info->FirstChildElement("image");
  if (tileset_img == nullptr) {
    fmt::println(stderr, "ERROR: tileset_img is null");
    exit(1);
  }
  // Relative to the .tsx file
  const char *tileset_img_relative_path = tileset_img->Attribute("source");
  if (tileset_img_relative_path == nullptr) {
    fmt::println(stderr, "ERROR: tileset_img_relative_path is null");
    exit(1);
  }
  const fs::path tileset_tsx_file_parent_dir = fs::path(filename).parent_path();
  const std::string tileset_img_path =
      fmt::format("{}/{}", tileset_tsx_file_parent_dir.c_str(), tileset_img_relative_path);

  Texture txtr{tileset_img_path};
  if (not txtr.has_texture()) {
    fmt::println("Error: file does not exist or is of unsupported format `{}`", tileset_img_path);
    return std::nullopt;
  }
  m_spritesheets.emplace_back(std::move(txtr));
  m_sprites[m_spritesheets.back().ntt.id] =
      this->split_spritesheet(m_spritesheets.back(), {tile_w, tile_h}).value();

  return m_spritesheets.back().ntt.id;
}

}  // namespace e2d
