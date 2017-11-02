#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H

#include <SFML/Graphics.hpp>


#include <iostream>

struct TexturePosition
{
    int posX;
    int posY;

    int height;
    int width;

    sf::IntRect GetRect()
    {
        return sf::IntRect(posX, posY, width, height);
    }
};


class SpriteSheet
{
public:
    using Sprite = sf::Sprite;

    enum PacmanPosition
    {
        FullCircle,
        SmallLeft,
        BigLeft,
        SmallRight,
        BigRight,
        SmallUp,
        BigUp,
        SmallDown,
        BigDown,
        NB_PACMAN_POSITIONS
    };

private:
    float m_scale;
    sf::Texture m_texture;
    sf::Texture m_transparentTexture;

    TexturePosition m_mapTexture;
    TexturePosition m_pacmanPositionsTexture[NB_PACMAN_POSITIONS];

public:
    SpriteSheet(float scale);
    
    Sprite GetMap();

    Sprite GetPacman(PacmanPosition position);


private:
    Sprite GetSprite(TexturePosition position, bool centered);
    Sprite GetSprite(sf::Texture & texture, TexturePosition position, bool centered);
    Sprite GetTransparentSprite(TexturePosition position, bool centered);

};


#endif