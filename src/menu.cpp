#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "menu.hpp"
#include "utils.hpp"

const unsigned int WIDTH_VIEW = 16000;
const unsigned int HEIGHT_VIEW = 9000;

Menu::Menu()
{
    if (!backgroundTexture_.loadFromFile("./Images/Menu_bg.png"))
    {
        printf("error");
    } 
    backgroundSprite_.setTexture(backgroundTexture_);
    setOriginToCenter(backgroundSprite_);
    scaleToMinSize(backgroundSprite_,HEIGHT_VIEW,WIDTH_VIEW);
    backgroundSprite_.setPosition(WIDTH_VIEW/2,HEIGHT_VIEW/2);

    nbCP_ = 5;
    manualPlayer_ = 0;

    if (!nbCPFont_.loadFromFile("./Trispace.ttf"))
        printf("error");
    nbCPText_.setFont(nbCPFont_);
    nbCPText_.setFillColor(sf::Color::White);
    nbCPText_.setCharacterSize(300);

     

}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(backgroundSprite_, states);
    target.draw(nbCPText_);
    
}

void Menu::param_nbCP()
{
    if (nbCP_ == 9)
        nbCPText_.setString("random");
    else 
        nbCPText_.setString(std::to_string(nbCP_));
    
    setTextCenterPosition(nbCPText_,sf::Vector2f(3000.f, 4550.f));
}

