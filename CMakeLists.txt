cmake_minimum_required(VERSION 3.14)
project(engine-demo CXX)

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
find_package(SFML REQUIRED COMPONENTS window graphics)
#if (NOT SFML_FOUND)
#   include(FetchContent)
#   FetchContent_Declare(
#      SFML
#      GIT_REPOSITORY https://github.com/SFML/SFML.git
#      GIT_TAG 2.5.1
#   )
#   FetchContent_MakeAvailable(SFML)
#endif()

# JsonCpp
set(JSONCPP_WITH_POST_BUILD_UNITTEST OFF)
set(JSONCPP_WITH_POST_BUILD_UNITTEST OFF)
set(JSONCPP_WITH_TESTS OFF)
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
#if (NOT JSONCPP_FOUND)
#   include(FetchContent)
#   FetchContent_Declare(
#      JSONCPP
#      GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp.git
#      GIT_TAG 1.9.5
#   )
#   FetchContent_MakeAvailable(JSONCPP)
#endif()

add_executable(engine-demo
  src/main.cpp
  src/input_manager.cpp
  src/spritesheets_manager.cpp
  src/world.cpp
  src/character.cpp
  src/engine.cpp)
target_link_libraries(engine-demo
   sfml-window sfml-graphics
#   jsoncpp
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Copy root/build/compile_commands.json to root/
if (EXISTS "${CMAKE_BINARY_DIR}/compile_commands.json")
   FILE(COPY ${CMAKE_BINARY_DIR}/compile_commands.json DESTINATION ${CMAKE_HOME_DIRECTORY})
endif()
