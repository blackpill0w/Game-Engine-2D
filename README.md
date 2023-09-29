# Game-Engine-2D
A 2D game engine in C++20.

## Interface

```c++
/*
 Load spritesheet, each one has pictures of the same size.
 Each line in the spritesheet defines a state (Idle, Walk...) which are just ints
 starting from 0.
*/
sh_id1 = engine.spritesheet_manager.load_spritesheet('/path/to/file1.png', (64, 64));
sh_id2 = engine.spritesheet_manager.load_spritesheet('/path/to/file2.png', (64, 64));

player_id = engine.world_manager.new_character();
// Make spritesheet active for an entity
// The first sprite in spritesheet is used by default (the one located at (0, 0))
engine.spritesheet_manager.bind_spritesheet(player_id, sh_id1);

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

# Dependenies
- [cmake](https://cmake.org)

If you're building without [nix](https://github.com/NixOS/nix),
cmake will try to download & compile the dependenies,
but I am not very good with it so it might fail :)

If it doesn't work, make sure you have these libraries installed:
- [SFML](https://sfml-dev.org)
- [JsonCpp](https://github.com/open-source-parsers/jsoncpp)
# Build
Run this from the root directory of the project.
```bash
mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_WITH_NIX=OFF .. && cmake --build .
```
## Note
If you have [nix](https://github.com/NixOS/nix) installed remove the `-DBUILD_WITH_NIX=OFF` option
and run `nix develop` before running cmake.
