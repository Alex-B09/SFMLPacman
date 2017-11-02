#include "PacmanAnimation.h"
#include <iostream>

using std::cout;
using std::endl;

PacmanAnimation::PacmanAnimation()
{
}

PacmanAnimation::PacmanAnimation(SpriteVector sprites, float timeBetweenSprites, bool loopable)
: m_sprites(sprites)
, m_timeBetweenSprites(timeBetweenSprites)
, m_cumulativeTime(0.0f)
, m_loopBack(loopable)
{
    m_currentSprite = m_sprites.begin();
}

PacmanAnimation::~PacmanAnimation()
{
}

void PacmanAnimation::Draw( sf::RenderWindow & window, 
                            sf::Vector2f position, 
                            float time)
{
    float timeSinceLastChange = m_cumulativeTime + time;
    if (timeSinceLastChange >= m_timeBetweenSprites)
    {
        m_cumulativeTime = timeSinceLastChange - m_timeBetweenSprites;

        m_currentSprite++;

        if (m_currentSprite == m_sprites.end())
        {
            if (m_loopBack)
            {
                m_currentSprite = m_sprites.begin();
            }
            else
            {
                // step back to keep the last sprite
                m_currentSprite--; 
            }
        }
    }
    else
    {
        m_cumulativeTime = timeSinceLastChange;
    }

    auto sprite = (*m_currentSprite);
    sprite.setPosition(position);
    sprite.scale(SCALE, SCALE);
    window.draw(sprite);
}

void PacmanAnimation::ResetCycle()
{
    m_cumulativeTime = 0.0f;
    m_currentSprite = m_sprites.begin();
}