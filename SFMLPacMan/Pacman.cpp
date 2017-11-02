#include "Pacman.h"

#include <memory>

Pacman::Pacman(SpriteSheet & sheet)
{
    const float TIME_BETWEEN_ANIMATION = 0.1f;
    
    auto upAnimationSprites = { sheet.GetPacman(SpriteSheet::BigUp), sheet.GetPacman(SpriteSheet::SmallUp) };
    m_animations[GoingUp] = std::make_shared<PacmanAnimation>(  upAnimationSprites,
                                                                TIME_BETWEEN_ANIMATION,
                                                                true);

    auto downAnimationSprites = { sheet.GetPacman(SpriteSheet::BigDown), sheet.GetPacman(SpriteSheet::SmallDown) };
    m_animations[GoingDown] = std::make_shared<PacmanAnimation>(downAnimationSprites,
                                                                TIME_BETWEEN_ANIMATION,
                                                                true);

    auto leftAnimationSprites = { sheet.GetPacman(SpriteSheet::BigLeft), sheet.GetPacman(SpriteSheet::SmallLeft) };
    m_animations[GoingLeft] = std::make_shared<PacmanAnimation>(leftAnimationSprites,
                                                                TIME_BETWEEN_ANIMATION,
                                                                true);

    auto rightAnimationSprites = { sheet.GetPacman(SpriteSheet::BigRight), sheet.GetPacman(SpriteSheet::SmallRight) };
    m_animations[GoingRight] = std::make_shared<PacmanAnimation>(   rightAnimationSprites,
                                                                    TIME_BETWEEN_ANIMATION,
                                                                    true);
    // TODO dying

    m_currentAnimation = GoingLeft;
}

void Pacman::SetAnimation(Pacman::Animations animation)
{
    m_currentAnimation = animation;
}

void Pacman::SetPosition(sf::Vector2f position)
{
    m_position = position;
}

void Pacman::Draw(sf::RenderWindow & window, float time)
{
    m_animations[m_currentAnimation]->Draw(window, m_position, time);
}

float Pacman::GetVelocity(float time)
{
    return time * SPEED_PER_SECOND;
}

sf::Vector2f Pacman::GetPosition() const
{
    return m_position;
}

sf::Vector2f Pacman::GetNextPosition(float time) const
{
    float unitToAdvance = SPEED_PER_SECOND * time;
    sf::Vector2f displacement(0.0f, 0.0f);

    if (m_currentAnimation == Animations::GoingLeft)
    {
        displacement.x = -unitToAdvance;
    }
    else if (m_currentAnimation == Animations::GoingRight)
    {
        displacement.x = unitToAdvance;
    }
    else if (m_currentAnimation == Animations::GoingUp)
    {
        displacement.y = -unitToAdvance;
    }
    else if (m_currentAnimation == Animations::GoingDown)
    {
        displacement.y = unitToAdvance;
    }
    return m_position + displacement;
}