#ifndef PACMAN_H
#define PACMAN_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "SpritesSheet.h"
#include "PacmanAnimation.h"

class Pacman
{
public:
    enum Animations
    {
        GoingUp,
        GoingDown,
        GoingLeft,
        GoingRight,
        Dying,
        NB_OF_ANIMATIONS
    };

private:
    using InternalAnimation = std::shared_ptr<PacmanAnimation>;

    // a better option would be to use vector
    // however, it would be a bit more complicated to align everything together
    InternalAnimation m_animations[NB_OF_ANIMATIONS];

    Animations m_currentAnimation;
    sf::Vector2f m_position;
    float m_scale;

    const float SPEED_PER_SECOND = 110.0f;

public:
    Pacman(SpriteSheet & sheet);

    void SetPosition(sf::Vector2f position);
    sf::Vector2f GetPosition() const;

    // the GetNextPosition will be use for the colisions
    sf::Vector2f GetNextPosition(float time) const;

    void SetAnimation(Animations animation);
    float GetVelocity(float time);
    
    void Draw(sf::RenderWindow & window, float time);
};

#endif