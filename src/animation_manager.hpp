#pragma once

#include <unordered_map>
#include <vector>

#include "./entity.hpp"

namespace e2d {

class Engine;

struct AnimationData {
  Entity::Id spritesheet_id = Entity::InvalidId;
  float anim_speed          = 0.2f;
  std::size_t ani_state     = 0;
  float sprite_num          = 0.f;
};

class AnimationManager {
 public:
  AnimationManager(Engine *parent);
  /**
     Bind a drawable entities to a spritesheet.
     # Return
     `false` if `spritesheet_id` or `id` are invalid.
   */
  bool bind_entity(const Entity::Id id, const Entity::Id spritesheet_id);
  bool set_animation_state(const Entity::Id id, const std::size_t ani_state);
  void update();

 protected:
  //** Store drawable entities and spritesheets pairs.
  std::unordered_map<Entity::Id, AnimationData> m_anim_data;
  Engine *m_parent;
};
}  // namespace e2d
