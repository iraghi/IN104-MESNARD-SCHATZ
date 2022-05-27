#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "CheckPoint.hpp"
#include "utils.hpp"
#include "game.hpp"

CheckPoint::CheckPoint(sf::Vector2f center, unsigned int id)
{
    // On consruit un cercle qui correspond au CP
    circle_ = sf::CircleShape(600);
    setOriginToCenterShape(circle_);
    circle_.setFillColor(sf::Color(0, 0, 0, 63));
    circle_.setOutlineColor(sf::Color(0, 0, 0));
    circle_.setOutlineThickness(-50.f);
    circle_.setPosition(center.x, center.y);
    
    if (!font_.loadFromFile(FONT_PATH + "/Fredoka-Bold.ttf")) 
    {
        printf("error");
    }   
    fillingText_.setFont(font_);
    fillingText_.setString(std::to_string(id));    
    fillingText_.setCharacterSize(500);
    fillingText_.setOutlineThickness(100);
    fillingText_.setFillColor(sf::Color::White);
    setTextCenterPosition(fillingText_, center);

};

void CheckPoint::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(circle_, states);
    target.draw(fillingText_);
};

sf::Vector2f CheckPoint::getPosition()
{
    return circle_.getPosition();
}

FinalCheckPoint::FinalCheckPoint(sf::Vector2f center)
{
    circle_ = sf::CircleShape(600);
    setOriginToCenterShape(circle_);
    circle_.setFillColor(sf::Color(255, 255, 255, 63));
    circle_.setOutlineColor(sf::Color(0, 0, 0));
    circle_.setOutlineThickness(-50.f);
    circle_.setPosition(center.x, center.y);

    if (!fillingTexture_.loadFromFile(IMAGES_PATH + "/checkeredFlag.png"))
    {
        printf("error");
    }
    fillingSprite_.setTexture(fillingTexture_);
    setOriginToCenter(fillingSprite_);
    scaleByRadius(fillingSprite_, 550);
    fillingSprite_.setPosition(center);

};

void FinalCheckPoint::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(circle_, states);
    target.draw(fillingSprite_, states);
};

sf::Vector2f FinalCheckPoint::getPosition()
{
    return circle_.getPosition();
}