#include "./world.hpp"

#include <sstream>
#include <filesystem>
#include <cctype>
#include <fmt/core.h>
#include <tinyxml2.h>

#include "./engine.hpp"

namespace fs = std::filesystem;

namespace e2d {

World::World(Engine *parent) : m_parent{parent}, m_characters{}, m_static_tiles{} {
  m_characters.reserve(32);
}

const std::vector<Entity::Id> World::get_characters() const {
  std::vector<Entity::Id> res{};
  res.reserve(m_characters.size());
  for (const auto &[id, c] : m_characters)
    res.push_back(id);
  return res;
}

const std::vector<Entity::Id> World::get_static_tiles() const {
  std::vector<Entity::Id> res{};
  res.reserve(m_static_tiles.size());
  for (const auto &[id, c] : m_static_tiles)
    res.push_back(id);
  return res;
}
Entity::Id World::new_character() {
  Sprite c{};
  const auto id = c.ntt.id;
  m_characters.emplace(id, std::move(c));
  return id;
}

bool World::is_valid_entity(const Entity::Id id) const { return m_characters.contains(id); }

Sprite *World::get_character(const Entity::Id id) {
  return m_characters.contains(id) ? &m_characters.at(id) : nullptr;
}

Sprite *World::get_static_tile(const Entity::Id id) {
  return m_characters.contains(id) ? &m_characters.at(id) : nullptr;
}

bool World::load_tiled_map(const std::string &filename, const Entity::Id txtr_id) {
  if (not fs::exists(filename) or not fs::is_regular_file(filename))
    return false;
  tinyxml2::XMLDocument map_file{};
  const auto err = map_file.LoadFile(filename.c_str());
  if (tinyxml2::XML_SUCCESS != err) {
    fmt::println(stderr, "ERROR: There was an error parsing the map file `{}`, here is some info:",
                 filename);
    fmt::println(stderr, "\t- Error code: {}", size_t(err));
    fmt::println(stderr, "\t- Error line number: {}", map_file.ErrorLineNum());
    fmt::println(stderr, "\t- Error string: {}", map_file.ErrorStr());
    return false;
  }
  const auto *map          = map_file.FirstChildElement("map");
  const auto *tileset_info = map->FirstChildElement("tileset");
  if (tileset_info == nullptr) {
    fmt::println(stderr, "ERROR: Couldn't find the <tileset> field.");
    exit(1);
  }
  const size_t fst_tile_id = tileset_info->Unsigned64Attribute("firstgid");

  for (auto *layer = map->FirstChildElement("layer"); layer != nullptr;
       layer       = layer->NextSiblingElement("layer")) {
    const auto *data_elem = layer->FirstChildElement("data");
    if (data_elem == nullptr) {
      fmt::println(stderr, "ERROR: Data node not found in <layer>.");
      fmt::println(stderr, "\t- Map file: {}", filename);
      fmt::println(stderr, "\t- Layer id: {}", layer->Unsigned64Attribute("id"));
      exit(1);
    }
    if (std::string("csv") != data_elem->Attribute("encoding")) {
      fmt::println("ERROR: Only CSV format is supported for maps.");
      exit(1);
    }

    const size_t tile_w = map->Unsigned64Attribute("tilewidth");
    const size_t tile_h = map->Unsigned64Attribute("tileheight");
    const Texture *txtr = this->m_parent->spritesheets_manager.get_spritesheet(txtr_id);
    size_t x = 0, y = 0;
    const char *c = data_elem->GetText();
    while (*c == ' ' || *c == '\n')
      c++;
    for (; *c != 0; c++) {
      if (*c == '\n') {
        ++y;
        x = 0;
      }
      else if (*c == ',')
        ++x;
      else if (std::isdigit(*c)) {
        size_t id = 0;
        // Parse the full number
        do {
          id *= 10;
          id += size_t(*c - '0');
          c++;
        } while (c && std::isdigit(*c));
        --c;
        if (id >= fst_tile_id) {
          id -= fst_tile_id;
          Sprite s{};
          s.sprite.setPosition(x * tile_w, y * tile_h);
          m_static_tiles.emplace(s.ntt.id, std::move(s));
          m_static_tiles.at(s.ntt.id).sprite.setTexture(txtr->txtr);
          const int mapx = (id % tile_w) * tile_w;
          const int mapy = id - id % tile_h;
          m_static_tiles.at(s.ntt.id).sprite.setTextureRect({mapx, mapy, int(tile_w), int(tile_h)});
        }
      }
    }
  }
  return true;
}

}  // namespace e2d
