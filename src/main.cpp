#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <math.h>
#include "utils.hpp"
#include "CheckPoint.hpp"
#include "game.hpp"
#include "menu.hpp"



int main()
{

    int width_screen = 1600;
    int height_screen = 900;
    sf::RenderWindow window(sf::VideoMode(width_screen, height_screen), "Star Citizen Race");
    sf::View myview(sf::FloatRect(0,0,16000,9000));
    window.setView(myview);

    int gameMode = 0;
    int nbCP = 0;
    int manualPlayer = 0;

    sf::Event event;

    while (window.isOpen())
    {   
        if (gameMode == 0){
            Menu open_menu = Menu();
            
            while (gameMode == 0){

                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                    {
                        gameMode = -1;
                        window.close();
                    } 

                    if (event.type == sf::Event::MouseButtonPressed) 
                    {
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            int x = event.mouseButton.x;
                            int y = event.mouseButton.y;
                            
                            //Bouton Play
                            if (118<x && x<484 && 600<y && y<902)
                            {
                                manualPlayer = open_menu.manualPlayer_;
                                nbCP = open_menu.nbCP_;
                                gameMode = 1;
                            }    
                            
                            // +/- Boutons
                            else if (178<x && x<206 && 416<y && y<488)
                            {
                                if (open_menu.nbCP_> 2)
                                    open_menu.nbCP_ -=1;
                            }
                            else if (470<x && x<490 && 426<y && y<488)
                            {
                                if (open_menu.nbCP_< 9)
                                    open_menu.nbCP_ +=1;
                            }
                            
                            
                        
                        }
                    }   
                }

               
                open_menu.param_nbCP();

                window.clear();
                
                window.draw(open_menu);
                
                window.display();

            }
        }

        if (gameMode == 1){

            //Initialisation des variables temporelles
            float fps = 60;
            sf::Time refreshTime = sf::microseconds(1e6/fps);
            sf::Clock globalClock;
            sf::Clock refreshClock;
            sf::Time physicsTime = sf::Time::Zero;
            
            // Création des positions aléatoires des CPs
            std::vector<sf::Vector2f> Coord_CP = coord_CP(nbCP);
            
            Game gameSnapshot = Game(Coord_CP);
            gameSnapshot.addPod(manualPlayer);
            gameSnapshot.initDecompte();
                              
            while (gameMode == 1){
                
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                    {
                        gameMode = -1;
                        window.close();
                    }
                    if (event.type == sf::Event::KeyPressed)
                    {
                        if (event.key.code == sf::Keyboard::Escape)    
                            gameMode = 0;

                    }
                    if (event.type == sf::Event::MouseButtonPressed)
                    {    
                        if (event.mouseButton.button == sf::Mouse::Left)
                            {
                                int x = event.mouseButton.x;
                                int y = event.mouseButton.y;
                                printf("x = %d, y = %d\n", x, y);
                            }
                    }
                }

                //Si on a dépasse le refreshTime depuis la dernière frame
                if (refreshClock.getElapsedTime() >= refreshTime)
                {
                    refreshClock.restart();
                    sf::Time frameTime = globalClock.getElapsedTime();
                    gameSnapshot.decompteTime_ = frameTime;


                    if (frameTime > physicsTime && frameTime.asMilliseconds() > 3000)
                    { 
                        gameSnapshot.updateGraphics(physicsTime);
                        gameSnapshot.updatePhysics(&window);
                        physicsTime += PHYSICS_TIME_STEP;
                        frameTime = globalClock.getElapsedTime();
                    }
                    else 
                        gameSnapshot.updateGraphics(frameTime);
                    
                    window.clear();
                    //
                    window.draw(gameSnapshot);
                    //
                    window.display();
                }
            }
        }
    }

    return 0;
}