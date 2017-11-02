#ifndef MOVEMENT_TILE_H
#define MOVEMENT_TILE_H

#include <functional>
#include <SFML/Graphics.hpp>
#include <vector>

// this class will implement the diffent possible directions
// given a position

// A movement tile can be described as such :
//
//      -------
//      -     -
//      -     -
//      -------
//
//  It is a simple tile in which the different entities can move on
//  The goal is to limit the possible movement of a sprite 
//  For that, it defines an "internal" tiles that covers a certain radius of 
//  the center
//
//      -----------------
//      -               -
//      -    -------    -
//      -    -     -    -
//      -    -  C  -    -
//      -    -     -    -
//      -    -------    -
//      -               -
//      -----------------
//  where C represents the center and the inner square is the inner tile
//  From the inner tile, a sprite will be able to move to all possible 
//  position that are available from that tile.
//  When the sprite is outside of the inner tile but within the movement tile,
//  is can only go back to the center or toward the direction it was going to.
//  For example, if the sprite is outside of the inner tile and bellow the 
//  center, it can only go up (toward the center) or continue down.


//  TODO maybe a class is not the right way to go 
//       A function seems more ok

// TODO for now, the game loop will create a new tile at every itteration
//      I still have to think of something here...

namespace Movement
{
    // -- definitions 

    using Position = sf::Vector2f;

    // the TileInformation contains the width/height of the tiles
    using TileInformation = sf::Vector2f;

    using TilePosition = sf::Vector2i;

    // class description
    enum PossibleMovement
    {
        LEFT,
        RIGHT,
        UP,
        DOWN,
        NB_POSSIBLE_MOVEMENTS
    };

    enum MapElement
    {
        WALL = 0,
        DOT = 1,
        FREE_WAY = 2,
        PILL = 3,
        STARTING_POSITION = 4,
        GATE = 5,
        PHANTOM_INCUBATOR = 6,
        WARP = 7
    };

    enum NeighborPositions
    {
        NEIGHBOR_TOP = 0,
        NEIGHBOR_RIGHT = 1,
        NEIGHBOR_BOTTOM = 2,
        NEIGHBOR_LEFT = 3,
        NEIGHBOR_NB_NEIBORS = 4,
    };

    // TODO check if array or vector... -- for return type, vector is better...
    using Neighbors = std::vector<MapElement>;
    using AvailableMovements = std::vector<PossibleMovement>;


    // -- function declarations
    Position GetNextPosition(const Position CURRENT_POSITION,
                             const float VELOCITY,
                             const PossibleMovement MOVEMENT,
                             const TileInformation INFORMATION,
                             const Neighbors NEIGHBORS);

    AvailableMovements GetPossibleMovement(const Position POSITION, 
                                           const TileInformation INFORMATION, 
                                           Neighbors neighbors);

    // returns the center position of the tile
    Position GetPostion(const TilePosition TILE, const TileInformation INFORMATION);
    TilePosition GetTile(const Position POSITION, const TileInformation INFORMATION);

    Position GetTileRightBorder(const TilePosition TILE, const TileInformation INFORMATION);
};

#endif