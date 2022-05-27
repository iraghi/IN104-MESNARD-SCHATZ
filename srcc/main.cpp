#include <SFML/Graphics.hpp>
#include <utils.h>

int main()
{
    sf::RenderWindow window(sf::VideoMode(2160,1080), "Joumard & Ghislain jtm");
    // sf::CircleShape octagon(300.f, 8);
    // octagon.setFillColor(sf::Color(113,60,167,100));
    //  sf::CircleShape circle(200.f);
    // circle.setFillColor(sf::Color(255,0,0,200));
    // setOriginToCenter(circle);
    // setOriginToCenter(octagon);
    // circle.setPosition(500,500);
    // octagon.setPosition(500,500);
    sf::Texture background;
    sf::Texture FighterG;
    sf::Texture FighterY;
    background.loadFromFile("./Images/background.png");
    FighterG.loadFromFile("./Images/NMSFighterG.png");
    FighterY.loadFromFile("./Images/NMSFighterY.png");

    sf::Sprite sprite_B;
    sf::Sprite sprite_G;
    sf::Sprite sprite_Y;

    sprite_B.setTexture(background);
    sprite_G.setTexture(FighterG);
    sprite_Y.setTexture(FighterY);
    sprite_Y.setPosition(500,500);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sprite_Y.rotate(0.2);
        window.clear();
        // window.draw(octagon);
        // window.draw(circle);
    
        
        window.draw(sprite_B);
        window.draw(sprite_G);
        window.draw(sprite_Y);


        window.display();

    }

    return 0;
}

