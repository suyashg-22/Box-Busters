#if !defined(GAME_HPP)
#define GAME_HPP

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<iostream>
#include<vector> 
#include<ctime>
#include<sstream>

class Game {

    public: 
        Game();
        ~Game();
        void update();
        void render();

        void pollevents();

        //Accessors
        const bool running() const;
        const bool getendgame() const;



    private:
        void initvariables();
        void initwindows();
        void processinput();
        
        void initenemies();

        void updatemousepositions();

        void spawnenemies();
        void updateenemies();
        void renderenemies(sf::RenderTarget &target);
        
        void initfonts();

        void inittext();

        void updatetext();
        void rendertext(sf::RenderTarget &target);
    
    private:

        //window
        sf::RenderWindow * m_window;
        sf::VideoMode videomode;

        //event
        sf::Event event;

        //game object
        sf::RectangleShape enemy;
        std::vector<sf::RectangleShape>enemies;

        //mouse position
        sf::Vector2i mouseposwindow;
        sf::Vector2f mouseposview;

        //game logic
        int maxenemies;
        float EnemySpawnTimer;
        float EnemySpawnTimerMax;
        unsigned points;
        bool mouseheld;
        int health;
        bool endgame;
        unsigned int font_size;

        //resources
        sf::Font font;

        //text
        sf::Text uitext;
        

};


#endif // GAME_HPP;

