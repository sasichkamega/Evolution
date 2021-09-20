#pragma once
#include "World.hpp"

#include <SFML/Graphics.hpp>

size_t cell_size = 5;
size_t cell_bound = cell_size/5;
size_t full_size = cell_size+cell_bound;

class WorldRender {
public:
  bool close = false;

  WorldRender(World& world): world(world) {
    window.create(sf::VideoMode(full_size*world.size_x+cell_bound, full_size*world.size_y+cell_bound), 
                  "Evolution",
                  sf::Style::Titlebar|sf::Style::Close);
    window.setFramerateLimit(60);

    rectangle.setSize(sf::Vector2f(cell_size,cell_size));
  }

  ~WorldRender() {
    window.close();
  }

  void render() {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        close = true;
      }
    }
    window.clear(sf::Color::Black);

    for (const std::shared_ptr<Entity>& p_entity : world.entities) {
      float x = p_entity->turf->x * full_size;
      float y = (world.size_y - p_entity->turf->y - 1) * full_size;
      x+=cell_bound;
      y+=cell_bound;
      rectangle.setPosition(x,y);
      rectangle.setFillColor(p_entity->color);
      window.draw(rectangle);
    }

    window.display();
  }

private:
  World& world;
  sf::RenderWindow window;
  sf::RectangleShape rectangle;

  WorldRender( const WorldRender& ) = delete;
  void operator=( const WorldRender& ) = delete;
};