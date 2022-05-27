#ifndef INC_GameLOGIC_H
#define INC_GameLOGIC_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <cmath>
#include "checkpoint.h"
#include "pod.h"

const unsigned int NUMBER_OF_LAPS = 3;
const float FRICTION_COEFF = 0.85;
const float ROTA_MAX = M_PI/10.;
const sf::Time PHYSICS_TIME_STEP = sf::milliseconds(100);
const std::string IMAGES_PATH = "./Images/";
const std::string FONT_PATH = "./";

struct GameInfos
{
    std::vector<Pod> pods;
    std::vector<sf::Vector2f> cpPositions;
};

class Game : public sf::Drawable
{
    public :
    Game(); // On crée un jeu avec 2 à 8 CP placés aléatoirement, jamais superposés
    Game(std::vector<sf::Vector2f> checkpointsPositions); //create a Game with predefined checkpoints positions

    void addPod(); // Apparence et décision des pods
    void updatePhysics();
    void updateGraphics(sf::Time frameTime); //Modifie l'apparence et la position des sprites en fonction du temps 

    private :
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Texture backgroundTexture_;
    sf::Sprite backgroundSprite_;

    std::vector<Pod> pods_;
    std::vector<sf::Texture> podsTextures_;
    std::vector<sf::Sprite> podsSprites_;

    FinalCheckPoint finalCP_;
    std::vector<CheckPoint> otherCPs_;

    sf::Time lastFrameTime;
    sf::Time physicsTime;   
};

#endif