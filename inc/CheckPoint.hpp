#ifndef CHECKPOINT_HPP
#define CHECKPOINT_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include "utils.hpp"


class CheckPoint : public sf::Drawable
{
    public :
    CheckPoint(sf::Vector2f center, unsigned int id); // On crée un CP avec ses coordonnées et son numéro 
    sf::Vector2f getPosition(); // Permet de retourner les coordonnées 2D du CP

    private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::CircleShape circle_;
    sf::Font font_;
    sf::Text fillingText_;
};

class FinalCheckPoint : public sf::Drawable
{
    public :
    FinalCheckPoint(sf::Vector2f center);
    sf::Vector2f getPosition();

    private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::CircleShape circle_;
    sf::Texture fillingTexture_;
    sf::Sprite fillingSprite_;
};


#endif