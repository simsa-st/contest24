#ifndef OBJECTS_SERVER_CELL_H_
#define OBJECTS_SERVER_CELL_H_

#include <vector>
#include <SFML/Graphics.hpp>

struct ServerCell : public sf::Drawable, public sf::Transformable {
  ServerCell() : ServerCell(0) {}
  ServerCell(int candies) : num_candies(candies) {}

  int num_candies;

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  // What players are on this cell.
  std::vector<bool> vis_players;
};

#endif  // OBJECTS_SERVER_CELL_H_
