#include <cmath>
#include "utils.hpp"
#include <stdlib.h>
#include <stdbool.h>

void setOriginToCenter(sf::Sprite &myObject){
    auto bounds = myObject.getGlobalBounds();
    myObject.setOrigin(bounds.width/2.f, bounds.height/2.f);
}

void setOriginToCenterShape(sf::Shape &myObject){
    auto bounds = myObject.getGlobalBounds();
    myObject.setOrigin(bounds.width/2.f, bounds.height/2.f);
}

void scaleToMaxSize(sf::Sprite &Sprite, float H, float W){
    auto bounds = Sprite.getGlobalBounds();
    float rapport_h = H/bounds.height;
    float rapport_w = W/bounds.width;
    if (rapport_h < rapport_w){ //On multiplie par le rapport L/l le plus petit
        Sprite.setScale(rapport_h,rapport_h); //On multiplie largeur et longueur par H/h
    }
    else {
        Sprite.setScale(rapport_w,rapport_w); 
    }
}

void scaleToMinSize(sf::Sprite &Sprite, float H, float W){
    auto bounds = Sprite.getGlobalBounds();
    float rapport_h = H/bounds.height;
    float rapport_w = W/bounds.width;
    if (rapport_h > rapport_w){//On multiplie par le rapport L/l le plus grand
        Sprite.setScale(rapport_h,rapport_h); //On multiplie largeur et longueur par H/h
    }
    else {
        Sprite.setScale(rapport_w,rapport_w);
    }
}

void setTextCenterPosition(sf::Text &txt, sf::Vector2f center)
{   
    sf::Vector2f offset;
    offset.x = txt.getPosition().x - txt.getGlobalBounds().left - txt.getGlobalBounds().width/2.;
    offset.y = txt.getPosition().y - txt.getGlobalBounds().top - txt.getGlobalBounds().height/2.;

    txt.setPosition(center + offset);
}

void scaleByRadius(sf::Sprite &sp, int radius)
{
    double scalingFactor = 2*radius/std::sqrt(sp.getTextureRect().width*sp.getTextureRect().width + sp.getTextureRect().height*sp.getTextureRect().height);
    sp.scale(scalingFactor, scalingFactor);
}

float norm(sf::Vector2f u){
    return sqrt(pow(u.x,2) + pow(u.y,2));
}

float arg(sf::Vector2f u){
    if (u.x == 0) return u.y/abs(u.y)*M_PI/2; // + ou - pi/2 en fonction du signe de y
    else if (u.x < 0 && u.y >= 0) return atan(u.y/u.x)+M_PI;
    else if (u.x < 0 && u.y < 0) return atan(u.y/u.x)-M_PI; // On veut rester dans l'intervalle ]-pi,pi]
    else return atan(u.y/u.x);
}

std::vector<sf::Vector2f> coord_CP(int nbCP){

    std::vector<sf::Vector2f> Coord_CP;

    if (nbCP == 9)
        nbCP = rand()%7 + 2;
        
    Coord_CP.reserve(nbCP+1);

    
    for (int i=0; i<nbCP+1; ++i)
    {
        bool collision;
        float x;
        float y;
        do{
            x = rand()%14801 + 500; // x de manière aléatoire
            y = rand()%7801 + 500; // y de manière aléatoire
            collision = false;
            
            // Verification d'une éventuelle superposition des CPs
            for(int j=0; j<i; ++j){
                if (norm(sf::Vector2f(x,y)-Coord_CP[j])<1200)
                {   collision = true;
                    printf("collision btw %d and %d\n",i,j);
                }    
            }
        } while (collision);
        
        // S'il n'y a pas de superposition, on ajoute les coordonnees du CP
        Coord_CP.emplace_back(sf::Vector2f(x,y));
    }
    return Coord_CP;
}



sf::Vector2f verifAngle(sf::Vector2f target, sf::Vector2f pos, float angle, float thetaMax)
{
    sf::Vector2f C = target-pos;
    
    if (abs(arg(C)-angle)<thetaMax)
        return target;   
    else
    {
        int n = -1;
        float k = angle - arg(C) + 2*n*M_PI;
        while ((k <= -M_PI || k > M_PI) && n<2)
        {
            n = n+1;
            k = angle - arg(C) + 2*n*M_PI;
        }

        float alpha;
        if (0<=k && k<=M_PI) alpha = k - thetaMax; // > 0
        else alpha = k + thetaMax; // < 0

        sf::Vector2f CPrime = sf::Vector2f(C.x*cos(alpha)-C.y*sin(alpha), C.x*sin(alpha)+C.y*cos(alpha));
        return CPrime + pos;
    }
} 

float power(sf::Vector2f target , sf::Vector2f pos, float angle, float powMax )
{
    float theta = abs(arg(target-pos)-angle);
    if (theta > M_PI) theta = 2*M_PI - theta ; // On veut un angle modulo pi, un angle aigu
    
    float pow = (M_PI-theta)/M_PI*powMax;
    //if (pow < 2) return 2;
    //else return pow;
    return pow;
}
