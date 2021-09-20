#include "DummyEntity.hpp"
#include "World.hpp"
#include "spdlog/spdlog.h"


DummyEntity::DummyEntity(World& world, std::default_random_engine& random): Entity(world), random_engine(random) {
  color = sf::Color::White;
  type = EntityType::mob;

}

void DummyEntity::update() {
  int x = static_cast<int>(turf->x) + uniform_dist(random_engine);
  int y = static_cast<int>(turf->y) + uniform_dist(random_engine);
  
  if (x < 0) {
    x = 0;
  } else if (x >= world.size_x) {
    x = world.size_x - 1;
  }
  if (y < 0) {
    y = 0;
  } else if (y >= world.size_y) {
    y = world.size_y - 1;
  }


  std::shared_ptr entity = world.get_entity(static_cast<size_t>(x), static_cast<size_t>(y));
  if (entity == shared_from_this()) {
    return;
  }
  if (entity) {
    world.destroy(entity);
  }
  world.move(shared_from_this(), static_cast<size_t>(x), static_cast<size_t>(y));

}