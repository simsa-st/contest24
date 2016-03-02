#ifndef OBJECTS_CELL_H_
#define OBJECTS_CELL_H_

#include <SFML/Graphics.hpp>

struct Cell : public sf::Drawable, public sf::Transformable {
  bool vis_player = false;
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif  // OBJECTS_CELL_H_
