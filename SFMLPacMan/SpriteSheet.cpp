#include "SpritesSheet.h"

using Sprite = SpriteSheet::Sprite;

SpriteSheet::SpriteSheet(float scale)
:m_scale(scale)
{
    if (!m_texture.loadFromFile("Ressources/sprites.png"))
    {
        std::cout << "No go" << std::endl;
        // TODO assert here would be ok!
    }

    auto img = m_texture.copyToImage();
    img.createMaskFromColor(sf::Color::Black);
    m_transparentTexture.loadFromImage(img);

    m_mapTexture = TexturePosition{ 228, 0, 248, 223 };
    m_pacmanPositionsTexture[SmallRight] = TexturePosition{ 473, 1, 13, 12 };
    m_pacmanPositionsTexture[BigRight] = TexturePosition{ 457, 1, 13, 12 };

    m_pacmanPositionsTexture[SmallLeft] = TexturePosition{ 474, 17, 13, 12 };
    m_pacmanPositionsTexture[BigLeft] = TexturePosition{ 458, 17, 13, 12 };

    m_pacmanPositionsTexture[SmallUp] = TexturePosition{ 473, 34, 13, 12 };
    m_pacmanPositionsTexture[BigUp] = TexturePosition{ 457, 34, 12, 13 };

    m_pacmanPositionsTexture[SmallDown] = TexturePosition{ 473, 49, 13, 12 };
    m_pacmanPositionsTexture[BigDown] = TexturePosition{ 457, 49, 12, 13 };

    m_texture.setSmooth(true);
    m_transparentTexture.setSmooth(true);
}

Sprite SpriteSheet::GetPacman(SpriteSheet::PacmanPosition position)
{
    auto sprite = GetTransparentSprite(m_pacmanPositionsTexture[position], true);
    return sprite;
}

Sprite SpriteSheet::GetMap()
{
    return GetSprite(m_mapTexture, false);
}

Sprite SpriteSheet::GetSprite(TexturePosition position, bool centered)
{
    return GetSprite(m_texture, position, centered);
}

Sprite SpriteSheet::GetTransparentSprite(TexturePosition position, bool centered)
{
    return GetSprite(m_transparentTexture, position, centered);
}

Sprite SpriteSheet::GetSprite(sf::Texture & texture, TexturePosition position, bool centered)
{
    Sprite sprite;

    sprite.setTexture(texture);
    sprite.setTextureRect(position.GetRect());

    if (centered)
    {
        sprite.setOrigin(   sprite.getLocalBounds().width / 2.f,
                            sprite.getLocalBounds().height / 2.f);
    }

    sprite.scale(m_scale, m_scale);
    return sprite;
}