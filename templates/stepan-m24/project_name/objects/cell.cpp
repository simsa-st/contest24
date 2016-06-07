#include "cell.h"

#include <algorithm>

void Cell::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  // apply the transform
  states.transform *= getTransform();

  sf::RectangleShape cell(sf::Vector2f(1.0, 1.0));
  cell.setFillColor(sf::Color::White);
  target.draw(cell, states);

  sf::VertexArray vertices;
  vertices.setPrimitiveType(sf::LinesStrip);
  sf::Vertex v;
  v.color = sf::Color::Black;
  v.position = sf::Vector2f(0, 0);
  vertices.append(v);
  v.position = sf::Vector2f(0, 1);
  vertices.append(v);
  v.position = sf::Vector2f(1, 1);
  vertices.append(v);
  v.position = sf::Vector2f(1, 0);
  vertices.append(v);
  v.position = sf::Vector2f(0, 0);
  vertices.append(v);
  target.draw(vertices, states);

  if (vis_player) {
    sf::RectangleShape player(sf::Vector2f(0.2, 0.2));
    player.setFillColor(sf::Color::Blue);
    player.setPosition(0.4, 0.4);
    target.draw(player, states);
  }
}
