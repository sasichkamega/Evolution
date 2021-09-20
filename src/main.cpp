#include <cstdlib> //getenv
#include <random>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/cfg/env.h>
#include "World.hpp"
#include "WorldRender.hpp"
#include "DummyEntity.hpp"

int main(int argc, char** argv) {

  spdlog::set_pattern("[%H:%M:%S][%^%l%$][%s:%#]: %v");
#ifndef NDEBUG
  spdlog::set_level(spdlog::level::trace);  
#endif
  if (std::getenv("SPDLOG_LEVEL")) {
    spdlog::cfg::load_env_levels();
  }
  try {
    World world(200,100);
    WorldRender render(world);

    std::random_device random_device;
    std::default_random_engine random_engine(random_device());
    for (size_t x = 0; x<200;++x) {
      for (size_t y = 0; y<100;++y) {
        world.move(std::make_shared<DummyEntity>(world, random_engine), x, y);
      }
    }

  
    while (!render.close) {
      render.render();
      world.update();
    }
  }
  catch(const std::exception& e) {
    SPDLOG_CRITICAL("{}", e.what());
  }
  
 
  
  
  return 0;
}
