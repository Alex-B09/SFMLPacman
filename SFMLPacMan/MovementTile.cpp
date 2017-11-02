#include "MovementTile.h"
#include "GameMap.h"
#include <cmath>

#include <iostream>

using AvailableMovements = Movement::AvailableMovements;
using Position = Movement::Position;
using PossibleMovement = Movement::PossibleMovement;
using TileInformation = Movement::TileInformation;
using TilePosition = Movement::TilePosition;
using Neighbors = Movement::Neighbors;
using NeighborPositions = Movement::NeighborPositions;
using MapElement = Movement::MapElement;


//-----------------------------------------------------------------
// internal function definition -- port to header file if needed

enum RelativeTilePosition
{
    INNER,
    HORIZONTAL,
    VERTICAL
};

// Get the relative placement of a position within a tile
RelativeTilePosition GetRelativeTilePosition(const Position POSITION,
                                             const TileInformation INFORMATION);

Position GetCenterOfTile(const Position POSITION,
                         const TileInformation INFORMATION);

//-----------------------------------------------------------------


Position GetCenterOfTile(const Position POSITION,
                       const TileInformation INFORMATION)
{
    auto tile = Movement::GetTile(POSITION, INFORMATION);
    return Movement::GetPostion(tile, INFORMATION);
}

// Get the relative placement of a position within a tile
RelativeTilePosition GetRelativeTilePosition(const Position POSITION,
                                             const TileInformation INFORMATION)
{
    RelativeTilePosition relativePosition;

    const float CENTER_RADIUS = 0.35f;
    auto TILE_WIDTH = INFORMATION.x;
    auto TILE_HEIGHT = INFORMATION.y;

    const Position DIFFERENCE = GetCenterOfTile(POSITION, INFORMATION) - POSITION;
    const float HEIGHT_CENTER_RADIUS = CENTER_RADIUS * TILE_HEIGHT;
    const float WIDTH_CENTER_RADIUS = CENTER_RADIUS * TILE_WIDTH;

    bool withinInnerVertical = std::abs(DIFFERENCE.x) < WIDTH_CENTER_RADIUS;
    bool withinInnerHorizontal = std::abs(DIFFERENCE.y) < HEIGHT_CENTER_RADIUS;


    if (withinInnerVertical && withinInnerHorizontal)
    {
        relativePosition = RelativeTilePosition::INNER;
    }
    else if (withinInnerVertical)
    {
        relativePosition = RelativeTilePosition::VERTICAL;
    }
    else
    {
        relativePosition = RelativeTilePosition::HORIZONTAL;
    }

    return relativePosition;
}


Position Movement::GetNextPosition(const Position CURRENT_POSITION,
                                   const float VELOCITY,
                                   const PossibleMovement MOVEMENT,
                                   const TileInformation INFORMATION, 
                                   const Neighbors NEIGHBORS)
{
    Position newPosition = CURRENT_POSITION;
    auto center = GetCenterOfTile(CURRENT_POSITION, INFORMATION);
    
    std::vector<PossibleMovement> movements;


    if (MOVEMENT == PossibleMovement::DOWN)
    {

        newPosition.y += VELOCITY;
        newPosition.x = center.x;

        if (newPosition.y > center.y &&
            NEIGHBORS[NeighborPositions::NEIGHBOR_BOTTOM] == MapElement::WALL)
        {
            newPosition.y = center.y;
        }
    }
    else if (MOVEMENT == PossibleMovement::UP)
    {
        newPosition.y -= VELOCITY;
        newPosition.x = center.x;

        if (newPosition.y < center.y &&
            NEIGHBORS[NeighborPositions::NEIGHBOR_TOP] == MapElement::WALL)
        {
            newPosition.y = center.y;
        }
    }
    else if (MOVEMENT == PossibleMovement::LEFT)
    {
        newPosition.x -= VELOCITY;
        newPosition.y = center.y;

        if (newPosition.x < center.x 
            && NEIGHBORS[NeighborPositions::NEIGHBOR_LEFT] == MapElement::WALL)
        {
            newPosition.x = center.x;
        }
    }
    else if (MOVEMENT == PossibleMovement::RIGHT)
    {
        newPosition.x += VELOCITY;
        newPosition.y = center.y;

        if (newPosition.x > center.x 
            && NEIGHBORS[NeighborPositions::NEIGHBOR_RIGHT] == MapElement::WALL)
        {
            newPosition.x = center.x;
        }
    }

    return newPosition;
}

AvailableMovements Movement::GetPossibleMovement(const Position POSITION, 
                                                 const TileInformation INFORMATION,
                                                 Neighbors neighbors)
{
    AvailableMovements movements;

    auto tileCenter = GetCenterOfTile(POSITION, INFORMATION);
    auto positionDifferences = POSITION - tileCenter;
    auto relativePosition = GetRelativeTilePosition(POSITION, INFORMATION);
    
    float epsilon = 0.0001f; // i dont want to use std::numerics_limit....

    if (relativePosition == RelativeTilePosition::INNER)
    {
        if (positionDifferences.y > epsilon
            || neighbors[NeighborPositions::NEIGHBOR_TOP] != MapElement::WALL)
        {
            movements.push_back(PossibleMovement::UP);
        }

        // is on top of the center OR the bottom neighbor is ok
        if (positionDifferences.y < -epsilon
            || neighbors[NeighborPositions::NEIGHBOR_BOTTOM] != MapElement::WALL) // is on top of center
        {
            movements.push_back(PossibleMovement::DOWN);
        }

        // at right or the left neighbor is ok
        if (positionDifferences.x > epsilon
            || neighbors[NeighborPositions::NEIGHBOR_LEFT] != MapElement::WALL)
        {
            movements.push_back(PossibleMovement::LEFT);
        }

        // at left or the right neighbor is ok
        if (positionDifferences.x < -epsilon
            || neighbors[NeighborPositions::NEIGHBOR_RIGHT] != MapElement::WALL)
        {
            movements.push_back(PossibleMovement::RIGHT);
        }
    }
    else if (relativePosition == RelativeTilePosition::HORIZONTAL)
    {
        movements.push_back(PossibleMovement::RIGHT); movements.push_back(PossibleMovement::RIGHT);
        movements.push_back(PossibleMovement::RIGHT); movements.push_back(PossibleMovement::LEFT);
    }
    else if (relativePosition == RelativeTilePosition::VERTICAL)
    {
        movements.push_back(PossibleMovement::RIGHT); movements.push_back(PossibleMovement::UP);
        movements.push_back(PossibleMovement::RIGHT); movements.push_back(PossibleMovement::DOWN);
    }

    return movements;
}

Position Movement::GetPostion(const TilePosition TILE,
                              const TileInformation INFORMATION)
{
    // the 0.5f is to align to the center of the tile
    float rowPosition = (TILE.y + 0.5f) * INFORMATION.y;
    float columnPosition = (TILE.x + 0.5f) * INFORMATION.x;
    
    return {columnPosition, rowPosition};
}

TilePosition Movement::GetTile(const Position POSITION,
                               const TileInformation INFORMATION)
{
    int rowTile = static_cast<int>(POSITION.y / INFORMATION.y);
    int colTile = static_cast<int>(POSITION.x / INFORMATION.x);
    
    return TilePosition(colTile, rowTile);
}

Position Movement::GetTileRightBorder(const TilePosition TILE,
                                      const TileInformation INFORMATION)
{
    // there is a better way to write that function but it involves
    // copy-paste the GetPosition function and work a bit with it.

    auto position = GetPostion(TILE, INFORMATION);

    // shift the x position by half of a tileWidth
    position.x += (0.5f * INFORMATION.x);
    
    return position;
}
