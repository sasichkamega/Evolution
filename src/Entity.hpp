#pragma once
#include <memory>
#include <SFML/Graphics/Color.hpp>
#include "Turf.hpp"

enum class EntityType {
  invalid,
  mob,
  food,
  poison,
  wall
};

class Entity {
public:
  EntityType type = EntityType::invalid;
  sf::Color color = sf::Color::White;
  Turf* turf = nullptr;

  virtual void update() {};
  virtual ~Entity() = default;
};

class Wall : public Entity {
public:
  inline Wall() {
    color = sf::Color(100,100,100);
    type = EntityType::wall;
  }
};