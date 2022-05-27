#include "pod.hpp"
#include "game.hpp"
#include <SFML/System/Vector2.hpp>


Decision::Decision(sf::Vector2f target, float power) 
{
    target_ = target;
    power_ = power;
};


Pod::Pod(sf::Vector2f pos, float angle, sf::Vector2f vel) 
{
    pos_ = pos;
    angle_ = angle;
    vel_ = vel;
};


Decision Pod::getDecision(Game gameSnapshot, sf::RenderWindow* pwindow) const 
{
    if (!manualPod_)  // Commande automatique
    {
        if (version_ == 1)
        {
            if (nextCP_ == 0)
            {
                sf::Vector2f target = gameSnapshot.finalCP_.getPosition();   
                target = verifAngle(target,pos_,angle_,ROTA_MAX); 
                float pow = power(target, pos_, angle_, POW_MAX);
                
                return Decision(target, pow);        
            } 
            else
            {
                sf::Vector2f target = gameSnapshot.otherCPs_[nextCP_-1.f].getPosition();
                target = verifAngle(target,pos_,angle_,ROTA_MAX);
                float pow = power(target, pos_, angle_, POW_MAX);
                return Decision(target, pow);
            }
        }
        else // Version 2
        {
            if (nextCP_ == 0)
            {
                sf::Vector2f target = gameSnapshot.finalCP_.getPosition();   
                target = verifAngle(target,pos_,angle_,ROTA_MAX);             
                
                return Decision(target, 100);        
            } 
            else
            {
                sf::Vector2f target = gameSnapshot.otherCPs_[nextCP_-1.f].getPosition();
                target = verifAngle(target,pos_,angle_,ROTA_MAX);
                
                return Decision(target, 100);
            }
        }
        

    }
    
    else // Commande manuelle
    {
        sf::Vector2i targeti = sf::Mouse::getPosition(*pwindow);
        sf::Vector2f targetf = {float(targeti.x)*10, float(targeti.y)*10};

        targetf = verifAngle(targetf,pos_,angle_,ROTA_MAX); 
        return Decision(targetf, 100);
    }

    // Si theta est supérieur a thetamax, on redéfinit la cible !
    
}; 

