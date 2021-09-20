#pragma once
#include <random>
#include "Entity.hpp"

class DummyEntity final : public Entity {
public:
  DummyEntity(World& world, std::default_random_engine&);
  void update() override;
private:
  std::default_random_engine& random_engine;
  std::uniform_int_distribution<int> uniform_dist = std::uniform_int_distribution<int>(-1,1);
};