#include "GameMap.h"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>


using std::string;
using MapElement = GameMap::MapElement;
using Position = GameMap::Position;
using TilePosition = GameMap::TilePosition;
using TileInformation = GameMap::TileInformation;
using PossibleMovement = GameMap::PossibleMovement;
using AvailableMovements = GameMap::AvailableMovements;
using Neighbors = GameMap::Neighbors;


GameMap::GameMap(sf::Sprite sprite)
    :m_sprite(sprite)
    , m_elements(NB_ELEMENTS_HEIGHT * NB_ELEMENTS_WIDHT)
{
    m_sprite.setPosition(0.0f, 0.0f);
    
    m_tileHeight = GetHeight() / static_cast<float>(NB_ELEMENTS_HEIGHT);
    m_tileWidth = GetWidth() / static_cast<float>(NB_ELEMENTS_WIDHT);

    LoadLayout("Ressources//mapComplete.txt");
}

void GameMap::Draw(sf::RenderWindow & window)
{
    window.draw(m_sprite);
    auto maxElement = NB_ELEMENTS_WIDHT * NB_ELEMENTS_HEIGHT;

    sf::RectangleShape shapeDots(sf::Vector2f(m_tileWidth / 4, m_tileHeight / 4));
    shapeDots.setFillColor(sf::Color(255, 255, 160));
    shapeDots.setOrigin(shapeDots.getLocalBounds().width / 2.f,
                        shapeDots.getLocalBounds().height / 2.f);

    sf::CircleShape shapePills(m_tileWidth / 3.2f);
    shapePills.setFillColor(sf::Color(255, 255, 160));
    shapePills.setOrigin(shapePills.getLocalBounds().width / 2.f,
                         shapePills.getLocalBounds().height / 2.f);

    for (int elementPosition = 0; elementPosition < maxElement; ++elementPosition)
    {
        auto elemType = m_elements[elementPosition];

        if (elemType == MapElement::DOT)
        {
            int tileHeightPosition = elementPosition / NB_ELEMENTS_WIDHT;
            int tileWidthPosition = elementPosition % NB_ELEMENTS_WIDHT;

            shapeDots.setPosition((tileWidthPosition + 0.5f) * m_tileWidth,
                                  (tileHeightPosition + 0.5f) * m_tileHeight);
                                
            window.draw(shapeDots);
        }
        else if (elemType == MapElement::PILL)
        {
            int tileHeightPosition = elementPosition / NB_ELEMENTS_WIDHT;
            int tileWidthPosition = elementPosition % NB_ELEMENTS_WIDHT;

            shapePills.setPosition((tileWidthPosition + 0.5f) * m_tileWidth,
                                  (tileHeightPosition + 0.5f) * m_tileHeight);

            window.draw(shapePills);
        }
    }
}

MapElement GameMap::GetMapElement(const TilePosition TILE) const
{
    return m_elements[TILE.y * NB_ELEMENTS_WIDHT + TILE.x];
}

int GameMap::GetHeight() const
{
    return static_cast<int>(m_sprite.getGlobalBounds().height);
}

int GameMap::GetWidth() const
{
    return static_cast<int>(m_sprite.getGlobalBounds().width);
}

TilePosition GameMap::GetStartingTile() const
{
    //  the "- cbegin()" is to get the current position of the element and not the iterator
    auto gridPosition = static_cast<int>(std::find(m_elements.cbegin(), m_elements.cend(), MapElement::STARTING_POSITION) - m_elements.cbegin());

    int rowPosition = gridPosition / NB_ELEMENTS_WIDHT;
    int columnPosition = gridPosition % NB_ELEMENTS_WIDHT;

    return {columnPosition, rowPosition};
}


void GameMap::LoadLayout(const string FILE_NAME)
{
    std::ifstream mapFile(FILE_NAME);
    
    // assert if the file is not open at this point
    assert(mapFile.is_open());

    // TODO I dont like it...must be redone later on...
    // maybe with cin and table addressing magic?
    size_t cptRow = 0;
    for (string line; std::getline(mapFile, line); ++cptRow)
    {
        size_t cptCol = 0;
        for (char elem : line)
        {
            m_elements[cptRow * NB_ELEMENTS_WIDHT + cptCol] = static_cast<MapElement>(atoi(&elem));
            ++cptCol;
        }
    }
}

Neighbors GameMap::GetNeighbors(const TilePosition TILE) const
{
    auto neighbors = Neighbors();
    auto topTile = TILE;
    topTile.y -= 1;
    neighbors.push_back(GetMapElement(topTile));

    // right
    auto rightTile = TILE;

    if (rightTile.x == 0)
    {
        neighbors.push_back(MapElement::WARP);
    }
    else
    {
        rightTile.x += 1;
        neighbors.push_back(GetMapElement(rightTile));
    }

    // bot
    auto botTile = TILE;
    botTile.y += 1;
    neighbors.push_back(GetMapElement(botTile));


    // left
    auto leftTile = TILE;
    if (leftTile.x == NB_ELEMENTS_WIDHT - 1)
    {
        neighbors.push_back(MapElement::WARP);
    }
    else
    {
        leftTile.x -= 1;
        neighbors.push_back(GetMapElement(leftTile));
    }

    return neighbors;
}

TileInformation GameMap::GetTileSize() const
{
    return {m_tileWidth, m_tileHeight};
}