#ifndef OBJECTS_CELL_H_
#define OBJECTS_CELL_H_

#include <SFML/Graphics.hpp>

struct Cell : public sf::Drawable, public sf::Transformable {
  int last_seen_candies;
  int last_turn_visited = 0;
  bool just_eating;

  bool vis_player;
  int now_turn;
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif  // OBJECTS_CELL_H_
