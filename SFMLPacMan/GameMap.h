#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "MovementTile.h"

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

class GameMap
{
public:
    // TODO check whether it is more convinient to use char instead of the enum
    //using mapElement = char;
    
    using Position = Movement::Position;
    using TilePosition = Movement::TilePosition;
    using TileInformation = Movement::TileInformation;
    using PossibleMovement = Movement::PossibleMovement;
    using AvailableMovements = Movement::AvailableMovements;
    using Neighbors = Movement::Neighbors;
    using MapElement = Movement::MapElement;

    enum
    {
        NB_ELEMENTS_HEIGHT = 31,
        NB_ELEMENTS_WIDHT = 28
    };


private:
    sf::Sprite m_sprite;
    std::vector<MapElement> m_elements;
    
    float m_tileHeight;
    float m_tileWidth;

public:
    GameMap(sf::Sprite);

    void Draw(sf::RenderWindow&);

    MapElement GetMapElement(const TilePosition TILE) const;
    Neighbors GetNeighbors(const TilePosition TILE) const;

    int GetHeight() const;
    int GetWidth() const;

    TilePosition GetStartingTile() const;
    TileInformation GetTileSize() const;

    void CollectPosition(const Position POSITION);

private:
    void LoadLayout(const std::string FILE_NAME);
};

#endif