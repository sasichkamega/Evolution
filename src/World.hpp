#pragma once
#include <vector>
#include <set>
#include <memory>
#include "Entity.hpp"
#include "Turf.hpp"


class World {
public:
  const size_t size_x;
  const size_t size_y;
  std::set<std::shared_ptr<Entity>> entities;

  World(size_t size_x, size_t size_y);
  World() = delete;
  bool move(std::shared_ptr<Entity> entity, size_t x, size_t y);
  void destroy(std::shared_ptr<Entity> entity);
  std::shared_ptr<Entity> get_entity(size_t x, size_t y);
  void update();
private:
  std::set<std::shared_ptr<Entity>> to_destroy;
  std::vector<Turf> map;
  
  Turf& get_turf(size_t x, size_t y);
  World( const World& ) = delete;
  void operator=( const World& ) = delete;
};