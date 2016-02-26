#include "cell.h"

#include <algorithm>
#include <glog/logging.h>

void Cell::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  // apply the transform
  states.transform *= getTransform();

  sf::RectangleShape cell(sf::Vector2f(1.0, 1.0));
  int turns_ago = now_turn - last_turn_visited;
  cell.setFillColor(sf::Color(0, std::max(0, 255 - turns_ago * 10), 0));
  target.draw(cell, states);

  sf::VertexArray vertices;
  vertices.setPrimitiveType(sf::LinesStrip);
  vertices.append(sf::Vector2f(0, 0));
  vertices.append(sf::Vector2f(0, 1));
  vertices.append(sf::Vector2f(1, 1));
  vertices.append(sf::Vector2f(1, 0));
  vertices.append(sf::Vector2f(0, 0));
  target.draw(vertices, states);

  int candies_left = last_seen_candies;
  for (int i = 0; i < 5 && candies_left; ++i) {
    for (int j = 0; j < 5 && candies_left; ++j) {
      sf::CircleShape money(0.1);
      money.setPosition(0.2 * j, 0.2 * i);
      if (candies_left == 1 && just_eating) {
        money.setFillColor(sf::Color(255, 0, 0));
      } else {
        money.setFillColor(sf::Color(255, 255, 0));
      }
      target.draw(money, states);
      --candies_left;
    }
  }

  if (vis_player) {
    sf::RectangleShape player(sf::Vector2f(0.2, 0.2));
    player.setFillColor(sf::Color(50, 50, 255));
    player.setPosition(0.4, 0.4);
    target.draw(player, states);
  }
  if (vis_future_player) {
    sf::RectangleShape player(sf::Vector2f(0.2, 0.2));
    player.setFillColor(sf::Color(255, 0, 0));
    player.setPosition(0.4, 0.4);
    target.draw(player, states);
  }
}
