#pragma once
#include <memory>
#include <SFML/Graphics/Color.hpp>
#include "Turf.hpp"

class World;

enum class EntityType {
  invalid,
  mob,
  food,
  poison,
  wall
};

class Entity : public std::enable_shared_from_this<Entity> {
public:
  EntityType type = EntityType::invalid;
  sf::Color color = sf::Color::White;
  Turf* turf = nullptr;

  Entity(World&);
  virtual void update() {};
  virtual ~Entity() = default;
protected:
  World& world;
};

class Wall : public Entity {
public:
  inline Wall(World& world): Entity(world) {
    color = sf::Color(100,100,100);
    type = EntityType::wall;
  }
};