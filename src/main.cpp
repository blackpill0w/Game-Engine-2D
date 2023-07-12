#include <iostream>
#include <sstream>
#include <string>
#include "./spritesheets_manager.hpp"

int main() {
  Engine::SpritesheetsManager ss_manager{};
  auto print_cmds = []() {
    std::cout << "Commands\n"
              << "\th: print this"
              << "\tlss <path>:\t load spritesheet\n"
              << "\tis_valid_ss_id <id>\n"
              << "\tis_valid_ani_state <id> <ani_state>\n"
              << "\tis_valid_sprite <id> <ani_state> <idx>\n"
              << "\tn_ani_state <id>\n"
              << "\tn_sprites\n";
  };
  print_cmds();

  std::cout << std::boolalpha;
  while (true) {
    std::cout << "-> ";
    std::string input;
    std::getline(std::cin, input);
    std::stringstream ss{ input };

    std::string cmd;
    ss >> cmd;

    if (cmd == "h")
      print_cmds();
    else if (cmd == "lss") {
      std::string filepath;
      ss >> filepath;
      std::optional<Engine::Entity::Id> i = ss_manager.load_spritesheet(filepath, {54, 64});
      std::cout << (i.has_value() ? std::to_string(i.value()) : "null");
    }
    else if (cmd == "is_valid_ss_id") {
      size_t id;
      ss >> id;
      std::cout << ss_manager.is_valid_spritesheet_id(id);
    }
    else if (cmd == "is_valid_ani_state") {
      size_t id, ani_state;
      ss >> id >> ani_state;
      std::cout << ss_manager.is_valid_animation_state(id, ani_state);
    }
    else if (cmd == "is_valid_sprite") {
      size_t id, ani_state, idx;
      ss >> id >> ani_state >> idx;
      std::cout << ss_manager.is_valid_sprite(id, ani_state, id);
    }
  }
}
