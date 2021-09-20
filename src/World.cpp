#include <cassert>
#include "World.hpp"

World::World(size_t size_x, size_t size_y): size_x(size_x), size_y(size_y) {
  map.reserve(size_x*size_y);
  for (size_t x = 0; x < size_x; ++x) {
    for (size_t y = 0; y < size_y; ++y) {
      map.emplace_back(x,y);
    }
  }
}

Turf& World::get_turf(size_t x, size_t y) {
  return map.at(x*size_y+y);
}

bool World::move(std::shared_ptr<Entity> entity, size_t x, size_t y) {
  assert(entity != nullptr);
  assert(x < size_x);
  assert(y < size_y);

  Turf& new_turf = get_turf(x,y);
  if (new_turf.entity.lock()) {
    return false;
  }

  if (entity->turf) {
    entity->turf->entity.reset();
    entity->turf = nullptr;
  }
  entities.insert(entity);
  entity->turf = &new_turf;
  entity->turf->entity = entity;
  return true;
}

void World::destroy(std::shared_ptr<Entity> entity) {
  assert(entity != nullptr);
  if (entity->turf) {
    entity->turf->entity.reset();
    entity->turf = nullptr;
  }
  entities.erase(entity);
  to_destroy.insert(std::move(entity));
}

std::shared_ptr<Entity> World::get_entity(size_t x, size_t y) {
  return get_turf(x,y).entity.lock();
}

void World::update() {
  for(const std::shared_ptr<Entity>& entity : entities) {
    entity->update();
  }
  to_destroy.clear();
}