#ifndef INC_POD_H
#define INC_POD_H

#include <SFML/System.hpp>
#include <cmath>

struct GameInfos;

struct Decision
{
    Decision(sf::Vector2f target, float power);

    sf::Vector2f target_;
    float power_;
};

class Pod
{
    public :
    Pod(sf::Vector2f pos, float angle, sf::Vector2f vel = {0, 0});
    Decision getDecision(GameInfos gameInfos) const; 

    private :
    sf::Vector2f pos_, vel_; // Position et vitesse du pod
    float angle_; // L'angle mesuré en radian
    int nextCP_, lapCount_;
    
    friend class Game; // Permet au jeu de modifier les arguments privés du pod
};

#endif