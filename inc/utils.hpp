#ifndef UTILS_HPP
#define UTILS_HPP

#include <SFML/Graphics.hpp>

void setOriginToCenter(sf::Sprite &myObject);

void setOriginToCenterShape(sf::Shape &myObject);

void scaleToMaxSize(sf::Sprite &Sprite, float maxwidth, float maxHeight);

void scaleToMinSize(sf::Sprite &Sprite, float maxwidth, float maxHeight);

void setTextCenterPosition(sf::Text &txt, sf::Vector2f center);

void scaleByRadius(sf::Sprite &sp, int radius);

float norm(sf::Vector2f u);

float arg(sf::Vector2f u);

std::vector<sf::Vector2f> coord_CP(int nbCP);

sf::Vector2f verifAngle(sf::Vector2f target, sf::Vector2f pos, float angle, float thetaMax);

float power(sf::Vector2f target , sf::Vector2f pos, float angle, float powMax );

#endif