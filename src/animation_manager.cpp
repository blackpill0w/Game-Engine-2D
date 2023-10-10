#include "./animation_manager.hpp"

#include <cassert>

#include "./engine.hpp"

namespace Engine {
AnimationManager::AnimationManager(Engine *parent) : m_parent{parent} {
  assert(m_parent != nullptr);
  m_anim_data.reserve(32);
}

bool AnimationManager::bind_entity(const Entity::Id id, const Entity::Id ss_id) {
  if (not m_parent->spritesheets_manager.is_valid_spritesheet_id(ss_id) or
      not m_parent->world.is_valid_entity(id)) {
    return false;
  }
  if (not m_anim_data.contains(id)) {
    m_anim_data[id] = AnimationData{};
  }
  m_anim_data[id].spritesheet_id = ss_id;
  m_anim_data[id].ani_state = 2;
  m_anim_data[id].sprite_num = 2;
  // TODO: move this to the rendering engine
  //m_parent->world.get_character(id)->sprite.setTexture(
  //    m_parent->spritesheets_manager.get_spritesheet(id)->txtr);

  return true;
}

bool AnimationManager::set_animation_state(const Entity::Id id, const std::size_t ani_state) {
  if (not m_anim_data.contains(id)) {
    return false;
  }
  const auto num_ani_states =
      m_parent->spritesheets_manager.animation_states_num(m_anim_data.at(id).spritesheet_id);
  if (not num_ani_states.has_value() or ani_state >= num_ani_states) {
    return false;
  }
  m_anim_data[id].ani_state = ani_state;

  // TODO: move this to the rendering engine
  const auto ss_coords = m_parent->spritesheets_manager.get_sprite_coordinates(id, ani_state, 0);
  if (not ss_coords) {
    return false;
  }
  // TODO: get rid of this conversion
  const sf::IntRect coords{int(ss_coords->left), int(ss_coords->top), int(ss_coords->width),
                           int(ss_coords->height)};
  m_parent->world.get_character(id)->sprite.setTextureRect(coords);

  return true;
}

void AnimationManager::update() {
  auto &ss_manager = m_parent->spritesheets_manager;
  for (auto &[id, anim_data] : m_anim_data) {
    anim_data.sprite_num += anim_data.anim_speed;
    auto max_sprite_num =
        ss_manager.animation_state_sprites_num(anim_data.spritesheet_id, anim_data.ani_state);
    if (anim_data.sprite_num >= max_sprite_num) {
      anim_data.sprite_num = 0.f;
    }
    // TODO: move this to the rendering engine
    const auto* ss = m_parent->spritesheets_manager.get_spritesheet(anim_data.spritesheet_id);
    const auto ss_coords = m_parent->spritesheets_manager.get_sprite_coordinates(
        anim_data.spritesheet_id, anim_data.ani_state, std::size_t(anim_data.sprite_num));
    assert(ss_coords.has_value());

    // TODO: get rid of this conversion
    const sf::IntRect coords{int(ss_coords->left), int(ss_coords->top), int(ss_coords->width),
                             int(ss_coords->height)};
    m_parent->world.get_character(id)->sprite.setTexture(ss->txtr);
    m_parent->world.get_character(id)->sprite.setTextureRect(coords);
  }
}
}  // namespace Engine