#include <chrono>
#include <iostream>
#include <algorithm>

#include "Game.h"
#include "Pacman.h"

#include "MovementTile.h"

// TODO delete when not needed
void Test12(sf::RenderWindow & window, float width, float height)
{
    float hDistance = height / 31;
    float wDistance = width / 28;

    for (int i = 0; i < 28; ++i)
    {
        auto currentWidth = (i + 1) * wDistance;
        sf::Vertex line [] =
        {
            sf::Vertex(sf::Vector2f(currentWidth, 0)),
            sf::Vertex(sf::Vector2f(currentWidth, height))
        };

        window.draw(line, 2, sf::Lines);
    }

    for (int i = 0; i < 31; ++i)
    {
        auto currentWidth = (i + 1) * hDistance;
        sf::Vertex line [] =
        {
            sf::Vertex(sf::Vector2f(0, currentWidth)),
            sf::Vertex(sf::Vector2f(width, currentWidth))
        };

        window.draw(line, 2, sf::Lines);
    }
}


Game::Game(float scale)
    : m_sheet(scale)
    , m_map(m_sheet.GetMap())
    , m_scale(scale)
    , m_height(m_map.GetHeight())
    , m_width(m_map.GetWidth())
{
    m_window.create(sf::VideoMode(m_width, m_height, 32), "Test1");
    m_window.setFramerateLimit(60);
}

void Game::GameLoop()
{
    auto tileInformation = m_map.GetTileSize();
    auto startringTile = m_map.GetStartingTile();
    auto startingPosition = Movement::GetTileRightBorder(startringTile, tileInformation);
    
    auto pacman = Pacman(m_sheet);
        
    pacman.SetPosition(startingPosition);

    std::cout   << "width : " << m_width << std::endl
                << "height : " << m_height << std::endl;

    bool exiting = false;
    Movement::PossibleMovement movement;

    sf::Clock clock;

    while (!exiting)
    {
        auto time = clock.restart().asSeconds();

        m_window.clear(sf::Color(0, 0, 0));
        m_map.Draw(m_window);

        sf::Event currentEvent;
        while (m_window.pollEvent(currentEvent))
        {
            if (currentEvent.type == sf::Event::Closed)
            {
                exiting = true;
            }
            else if (currentEvent.type == sf::Event::KeyPressed)
            {
                auto code = currentEvent.key.code;
                if (code == sf::Keyboard::Left)
                {
                    pacman.SetAnimation(Pacman::GoingLeft);
                    movement = Movement::PossibleMovement::LEFT;
                }
                else if (code == sf::Keyboard::Right)
                {
                    pacman.SetAnimation(Pacman::GoingRight);
                    movement = Movement::PossibleMovement::RIGHT;
                }
                else if (code == sf::Keyboard::Up)
                {
                    pacman.SetAnimation(Pacman::GoingUp);
                    movement = Movement::PossibleMovement::UP;
                }
                else if (code == sf::Keyboard::Down)
                {
                    pacman.SetAnimation(Pacman::GoingDown);
                    movement = Movement::PossibleMovement::DOWN;
                }
            }
        }

        auto neighbors = m_map.GetNeighbors(Movement::GetTile(pacman.GetPosition(), tileInformation));

        auto movements = Movement::GetPossibleMovement(pacman.GetPosition(), 
                                                       tileInformation, 
                                                       neighbors);

        if (std::find(movements.cbegin(), movements.cend(), movement) != movements.cend())
        {
            auto nextPosition = Movement::GetNextPosition(pacman.GetPosition(),
                                                          pacman.GetVelocity(time),
                                                          movement,
                                                          m_map.GetTileSize(),
                                                          neighbors);
            pacman.SetPosition(nextPosition);
        }

        pacman.Draw(m_window, time);
        
        // TODO remove
        //Test12(m_window, 
        //       static_cast<float>(m_map.GetWidth()), 
        //       static_cast<float>(m_map.GetHeight()));

        m_window.display();
    }
}
