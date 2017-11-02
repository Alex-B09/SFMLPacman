#ifndef PACMAN_ANIMATION_H
#define PACMAN_ANIMATION_H

#include <vector>

#include <SFML/Graphics.hpp>

// NOTE
//  All the time is in seconds

class PacmanAnimation
{
public:
    using SpriteVector = std::vector<sf::Sprite>;

    const float SCALE = 0.7f;

private:
    SpriteVector m_sprites;
    float m_timeBetweenSprites;

    // this will be the cumulative time added at each draw. 
    // while timeBetweenSprite is the threshold, this is the acumulator that will reach the threshold
    float m_cumulativeTime;
    bool m_loopBack;
    SpriteVector::iterator m_currentSprite;

public:
    PacmanAnimation();
    PacmanAnimation(SpriteVector sprites, float timeBetweenSprites, bool loopable);
    ~PacmanAnimation();

    void Draw(sf::RenderWindow & window, sf::Vector2f position, float time);
    void ResetCycle();
};


#endif