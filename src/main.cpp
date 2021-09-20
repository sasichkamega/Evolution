#include <cstdlib> //getenv
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/cfg/env.h>
#include "World.hpp"
#include "WorldRender.hpp"



int main(int argc, char** argv) {
  spdlog::set_pattern("[%H:%M:%S][%^%l%$][%s:%#]: %v");
#ifndef NDEBUG
  spdlog::set_level(spdlog::level::trace);  
#endif
  if (std::getenv("SPDLOG_LEVEL")) {
    spdlog::cfg::load_env_levels();
  }

  World world(200,100);
  WorldRender render(world);
  for (size_t x = 0; x<200;++x) {
    for (size_t y = 0; y<100;++y) {
      world.move(std::make_shared<Wall>(), x, y);
    }
  }

  while (!render.close) {
    render.render();
    world.update();
  }
  
  
  return 0;
}
