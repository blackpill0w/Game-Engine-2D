# e2d
An *Engine of 2 Dimensions* (a 2D game engine) in C++20.

## Interface
This is probably how the engine is meant to be used:
```c++
/*
 Load spritesheet, each one has pictures of the same size.
 Each line in the spritesheet defines a state (Idle, Walk...) which are just ints
 starting from 0.
 (64, 64) is the size of each sprite.
*/
ss_id1 = engine.spritesheet_manager.load_spritesheet('/path/to/file1.png', (64, 64));
ss_id2 = engine.spritesheet_manager.load_spritesheet('/path/to/file2.png', (64, 64));

player_id = engine.world_manager.new_character();
// Make spritesheet active for an entity
// The first sprite in spritesheet is used by default (the one located at (0, 0))
engine.spritesheet_manager.bind_spritesheet(player_id, ss_id1);

// These depend on how your spritesheet is organised.
enum class PlayerAnimationState {
  Idle = 0,
  Walk = 1
};

engine.spritesheet_manager.set_entity_animation_state(player_id, PlayerAnimationState::Walk);
engine.input_manager.bind(KeyEvent{key='D', ctrl=true, alt=false}, [&](){
  engine.world_manager.get_character(player_id).move(x=-200, y=0);
});

engine.event_manager.bind(KeyEvent(key='p'), [&]() {
  // code for drawing a pause menu;
});

engine.input_manager.bind(MouseEvent{button="right"}, [&](){
	engine.pause();
});
```

# Build
Build using [CMake](https://cmake.org).

If it doesn't work, install the following libraries:
- [SFML](https://sfml-dev.org)
- [tinyxml2](https://github.com/leethomason/tinyxml2)
