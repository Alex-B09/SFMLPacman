#include <SFML/Graphics.hpp>

#include "GameMap.h"
#include "SpritesSheet.h"



class Game
{
    sf::RenderWindow m_window;
    SpriteSheet m_sheet;

    //sf::Sprite m_map;
    GameMap m_map;
    
    float m_scale;
    int m_width;
    int m_height;

public:
    Game(float scale = 1.0f);

    void GameLoop();

};