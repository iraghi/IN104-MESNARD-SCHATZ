#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>


class Menu : public sf::Drawable
{
    public :
    Menu();
    
    int nbCP_;
    int manualPlayer_;
    void param_nbCP();
    void param_caseYesNo();

    private :
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    sf::Texture backgroundTexture_;
    sf::Sprite backgroundSprite_;
    
    sf::Text nbCPText_;
    sf::Font nbCPFont_;

    sf::Sprite caseYesNoSprite_;
    sf::Texture caseYesNoTexture_;

};

#endif