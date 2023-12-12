cmake_minimum_required(VERSION 3.14)
project(e2d CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
string(CONCAT CMAKE_CXX_FLAGS
              "${CMAKE_CXX_FLAGS}"
              " -Wall -Wextra"
              " -Wfloat-conversion -Wsign-conversion"
              " -Wshadow -Wduplicated-cond"
              " -Wduplicated-branches -Wlogical-op"
              " -Wnull-dereference -Wuseless-cast"
              " -Wformat=2")

# SFML
add_subdirectory(deps/SFML-2.6.1)

# JsonCpp
set(JSONCPP_WITH_POST_BUILD_UNITTEST OFF)
set(JSONCPP_WITH_POST_BUILD_UNITTEST OFF)
set(JSONCPP_WITH_TESTS OFF)
#add_subdirectory(deps/jsoncpp)

add_library(e2d STATIC
  src/character.cpp
  src/input_manager.cpp
  src/spritesheets_manager.cpp
  src/world.cpp
  src/animation_manager.cpp
  src/engine.cpp)
target_link_libraries(e2d
  sfml-window sfml-graphics
)

add_executable(engine-demo
  src/main.cpp
)
target_link_libraries(engine-demo
  e2d)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Copy root/build/compile_commands.json to root/
if (EXISTS "${CMAKE_BINARY_DIR}/compile_commands.json")
  FILE(COPY ${CMAKE_BINARY_DIR}/compile_commands.json DESTINATION ${CMAKE_HOME_DIRECTORY})
endif()
