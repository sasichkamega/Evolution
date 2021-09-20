#pragma once
#include <memory>

class Entity;

class Turf {
public:
  const size_t x;
  const size_t y;
  std::weak_ptr<Entity> entity;
  Turf(int x, int y);
};