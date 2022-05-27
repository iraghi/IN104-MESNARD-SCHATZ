#include <SFML/Graphics/CircleShape.hpp>
#include <cmath>
#include "game.hpp"
#include "CheckPoint.hpp"
#include "utils.hpp"



Game::Game(std::vector<sf::Vector2f> checkpointsPositions) : finalCP_(checkpointsPositions[0])
{
    otherCPs_.reserve(checkpointsPositions.size()-1);
    

    if (!backgroundTexture_.loadFromFile(IMAGES_PATH + "/background.png"))
    {
        printf("Texture error\n");
    }
    backgroundSprite_.setTexture(backgroundTexture_);
    setOriginToCenter(backgroundSprite_);
    scaleToMinSize(backgroundSprite_,HEIGHT_VIEW,WIDTH_VIEW);
    backgroundSprite_.setPosition(WIDTH_VIEW/2,HEIGHT_VIEW/2);

    for (unsigned int cpID = 1; cpID<checkpointsPositions.size(); cpID++)
    {
        otherCPs_.emplace_back(checkpointsPositions[cpID], cpID);
    }

    winner_ = "nobody";
}

void Game::addPod(int manualPlayer)
{
    int nb_pods = 2;
    
    podsSprites_.reserve(nb_pods);
    pods_.reserve(nb_pods);
    podsTextures_.reserve(nb_pods);
    
 
    Pod pod1 = Pod({13000,4000}, 0.f);
    sf::Texture podTexture1;
    sf::Sprite podSprite1;
    
    if (!podTexture1.loadFromFile("/home/ensta/IN104/projet/repository/Images/BSGCylon.png"))
    {
        printf("Texture error\n");
    }
    
    podsTextures_.emplace_back(podTexture1);
    pods_.emplace_back(pod1);
    podsSprites_.emplace_back(podSprite1);
    pods_[0].name_ = "BSGCylon";
    pods_[0].version_ = 1;
       
    Pod pod2 = Pod({13000,4000}, 0.f);
    sf::Texture podTexture2;
    sf::Sprite podSprite2;

    if (!podTexture2.loadFromFile("/home/ensta/IN104/projet/repository/Images/BSGViper.png"))
    {
        printf("Texture error\n");
    }

    podsTextures_.emplace_back(podTexture2);
    pods_.emplace_back(pod2);
    podsSprites_.emplace_back(podSprite2);
    pods_[1].name_ = "BSGViper"; 
    pods_[1].version_ = 2;   
    
    for (int i=0; i<nb_pods; i++){
        
        podsSprites_[i].setTexture(podsTextures_[i]);
        setOriginToCenter(podsSprites_[i]);
        scaleToMaxSize(podsSprites_[i], 800,800);

        pods_[i].nextCP_ = 1;
        pods_[i].lapCount_ = 1;
        pods_[i].manualPod_ = 0;
    }

    if (manualPlayer)
    {
        pods_[0].manualPod_ = 1;
    }
    
}

void Game::initDecompte()
{
    decompteSprites_.reserve(3);
    decompteTextures_.reserve(3);

    sf::Texture decompteTexture3;
    sf::Sprite decompteSprite3;
    
    if (!decompteTexture3.loadFromFile("/home/ensta/IN104/projet/repository/Images/3.png"))
        printf("Texture error\n");
    
    decompteTextures_.emplace_back(decompteTexture3);
    decompteSprites_.emplace_back(decompteSprite3);

    sf::Texture decompteTexture2;
    sf::Sprite decompteSprite2;
    
    if (!decompteTexture2.loadFromFile("/home/ensta/IN104/projet/repository/Images/2.png"))
        printf("Texture error\n");
    
    decompteTextures_.emplace_back(decompteTexture2);
    decompteSprites_.emplace_back(decompteSprite2);

    sf::Texture decompteTexture1;
    sf::Sprite decompteSprite1;
    
    if (!decompteTexture1.loadFromFile("/home/ensta/IN104/projet/repository/Images/1.png"))
        printf("Texture error\n");
    
    decompteTextures_.emplace_back(decompteTexture1);
    decompteSprites_.emplace_back(decompteSprite1);


    for (int i=0; i<3; i++){
        
        decompteSprites_[i].setTexture(decompteTextures_[i]);
        setOriginToCenter(decompteSprites_[i]);
        scaleToMaxSize(decompteSprites_[i], 4000,4000);
        decompteSprites_[i].setPosition(WIDTH_VIEW/2,HEIGHT_VIEW/2);
    }
}

void Game::updatePhysics(sf::RenderWindow* pwindow)
{
    
    for (Pod &pod : pods_){
        if (pod.lapCount_ <= NUMBER_OF_LAPS)
        {
            Decision d = pod.getDecision(*this, pwindow);

            float k = 0.85;
            pod.vel_ =  k * ( pod.vel_ + d.power_*(d.target_-pod.pos_)/norm(d.target_-pod.pos_) );
            pod.pos_ = pod.pos_ + pod.vel_;

            // Le pod ne doit pas sortir de l'ecran
            if (pod.pos_.x<400)pod.pos_.x = 400;
            if (pod.pos_.x>WIDTH_VIEW-400)pod.pos_.x = WIDTH_VIEW-400;
            if (pod.pos_.y<400)pod.pos_.y = 400;
            if (pod.pos_.y>HEIGHT_VIEW-400)pod.pos_.y = HEIGHT_VIEW-400;
            
            pod.angle_ = arg(pod.vel_);
                    

            if (norm(pod.pos_ - d.target_)<550){ //Le pod a atteint le CP
                //printf("Le pod %s a atteint le CkeckPoint numero %d.\n", pod.name_, pod.nextCP_);

                if (pod.nextCP_ == 0 && pod.lapCount_<= NUMBER_OF_LAPS){
                    pod.nextCP_ = 1;
                    pod.lapCount_ += 1;
                    if (pod.lapCount_ == NUMBER_OF_LAPS+1 && winner_.compare("nobody")==0 )
                    {
                        winner_ = pod.name_;
                        std::cout <<"winner is : " << winner_ << '\n';
                    }
                }
                
                else if (0 < pod.nextCP_ && pod.nextCP_ < otherCPs_.size()) pod.nextCP_ += 1;
                else pod.nextCP_ = 0; //FinalCP
            }
        }
    }

    physicsTime += PHYSICS_TIME_STEP;
    
    // On récupère la décision d'un pod avec getDecision puis on met à jour son angle et sa position puis sa vitesse. L'angle ne doit pas dépasser une valeur thetamax
    
}

void Game::updateGraphics(sf::Time frameTime)
{
    // Cette fonction met à jour la position des sprites en fonction d'un incrément de temps
    
    float k = (physicsTime - frameTime)/(frameTime-lastFrameTime); //Attention si k est proche de 0 ?
    
    /*float sec1  = physicsTime.asSeconds();
    float sec2 = frameTime.asSeconds();
    float sec3 = lastFrameTime.asSeconds();
    printf("k = %f\n", k);
    printf("physicsTime = %f, frameTime = %f, lastFrameTime = %f\n", sec1, sec2, sec3);
    */
    int nb_pods = podsSprites_.size();
    for (int i=0; i<nb_pods; ++i){
        if (pods_[i].lapCount_ <= NUMBER_OF_LAPS) // Si le pod n'a pas encore fini sa course
        {
            sf::Vector2f pos_sprite = podsSprites_[i].getPosition();

            if (k>1)  podsSprites_[i].setPosition( pos_sprite + (pods_[i].pos_ - pos_sprite)/k );
            else podsSprites_[i].setPosition(pods_[i].pos_);
            
            podsSprites_[i].setRotation(pods_[i].angle_*180.f/M_PI);
        }
    }

    lastFrameTime = frameTime;

}



void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    
        target.draw(backgroundSprite_, states);
        target.draw(finalCP_, states);

        for (const auto &cp : otherCPs_)
        {
            target.draw(cp,states);
        }
        
        if (decompteTime_.asMilliseconds() > 3000)
        {
            for (const auto &podSprite : podsSprites_)
            {   
                target.draw(podSprite, states); 
            }
        }

        //Affichage du decompte
        else if (decompteTime_.asMilliseconds() < 1000)
            target.draw(decompteSprites_[0],states);
        else if (decompteTime_.asMilliseconds() < 2000)
            target.draw(decompteSprites_[1],states);
        else if (decompteTime_.asMilliseconds() < 3000)
            target.draw(decompteSprites_[2],states);


}