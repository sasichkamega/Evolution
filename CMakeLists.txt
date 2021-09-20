cmake_minimum_required(VERSION 3.21)
project(Evolution VERSION 0.0.1 LANGUAGES CXX)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  option(EVOLUTION_USE_LIBCXX "Use libc++" ON)
else ()
  option(EVOLUTION_USE_LIBCXX "Use libc++" OFF)
endif()

add_compile_options(
  -Wall
  -Wextra
  -Wpedantic

  -Wcast-align
  -Wcast-qual
  -Wconversion
  -Wctor-dtor-privacy
  -Wenum-compare
  -Wfloat-equal
  -Wnon-virtual-dtor
  -Wold-style-cast
  -Woverloaded-virtual
  -Wredundant-decls
  -Wsign-conversion
  -Wsign-promo

  -Wno-unused-parameter
  -Wno-sign-conversion
  -Wno-implicit-int-float-conversion
  -Wno-unused-function
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

if (EVOLUTION_USE_LIBCXX)
  set(CMAKE_CXX_FLAGS "-stdlib=libc++ ${CMAKE_CXX_FLAGS}" CACHE STRING "" FORCE)
  set(CMAKE_EXE_LINKER_FLAGS "-stdlib=libc++ -lc++abi ${CMAKE_EXE_LINKER_FLAGS}" CACHE STRING "" FORCE)
endif()

message(STATUS "-- Start configure submodules")
message(STATUS "-- Configure SFML")
option(BUILD_SHARED_LIBS off)
option(SFML_BUILD_AUDIO off)
option(SFML_BUILD_NETWORK off)
add_subdirectory(third_party/SFML)

message(STATUS "-- Configure JSON")
option(JSON_BuildTests off)
option(JSON_Install off)
option(JSON_ImplicitConversions off)
add_subdirectory(third_party/json)

message(STATUS "-- Configure SDPLOG")
add_subdirectory(third_party/spdlog)
message(STATUS "-- End configure submodules")

add_executable(main
  src/main.cpp
  src/Turf.cpp
  src/World.cpp
)

target_compile_definitions(main PRIVATE SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE)

target_link_libraries(main PRIVATE sfml-system sfml-window sfml-graphics)
target_link_libraries(main PRIVATE spdlog::spdlog)
target_link_libraries(main PRIVATE nlohmann_json::nlohmann_json)
