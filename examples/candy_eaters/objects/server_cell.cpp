#include "server_cell.h"

void ServerCell::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  // apply the transform
  states.transform *= getTransform();

  sf::VertexArray vertices;
  vertices.setPrimitiveType(sf::LinesStrip);
  vertices.append(sf::Vector2f(0, 0));
  vertices.append(sf::Vector2f(0, 1));
  vertices.append(sf::Vector2f(1, 1));
  vertices.append(sf::Vector2f(1, 0));
  vertices.append(sf::Vector2f(0, 0));

  int candies_left = num_candies;
  for (int i = 0; i < 5 && candies_left; ++i) {
    for (int j = 0; j < 5 && candies_left; ++j) {
      sf::CircleShape money(0.1);
      money.setPosition(0.2 * j, 0.2 * i);
      money.setFillColor(sf::Color::Yellow);
      target.draw(money, states);
      --candies_left;
    }
  }

  for (int i = 0; i < (int)vis_players.size(); ++i) {
    if (vis_players[i]) {
      sf::RectangleShape player(sf::Vector2f(0.2, 0.2));
      player.setFillColor(sf::Color(50, 50, 255));
      player.setPosition(0.4, 0.4);
      target.draw(player, states);
    }
  }

  // draw the vertex array
  target.draw(vertices, states);
}
