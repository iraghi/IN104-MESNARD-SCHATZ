#ifndef INC_UTILS_H
#define INC_UTILS_H

#include <SFML/Graphics.hpp>

void setOriginToCenter(sf::Sprite &object);
void setOriginToCenter(sf::Shape &object);

void scaleToMinSize(sf::Sprite &sp, double size_x, double size_y);
void scaleToMaxSize(sf::Sprite &sp, double size_x, double size_y);
void scaleByRadius(sf::Sprite &sp, int radius);

void setTextCenterPosition(sf::Text &txt, sf::Vector2f center);


#endif