#include "Player.h"

Player::Player()
: current_input(0)
{
    in_air = false;
    jumping = false;
    lives = 3;
    setWidth(1);
    setHeight(2);
}

Player::~Player()
{
}


void Player::moveLeft()
{
    move({-1,0});
}

void Player::moveRight()
{
    move({1,0});
}

void Player::jump()
{
    //if (!in_air)
    move({0,1});
    in_air = true;
}

void Player::fall()
{
	move({0, -0.5});
}

bool Player::isJumping()
{
    return jumping;
}

bool Player::isInAir()
{
    return in_air;
}


void Player::addInput(uint16_t mask)
{
    current_input |= mask;
}

void Player::clearInput(uint16_t mask)
{
    current_input &= ~mask;
}

bool Player::checkInput(uint16_t mask) const
{
    return (bool)(current_input & mask);
}

void Player::clearAllInputs()
{
    current_input = 0;
}

void Player::testRegression() const
{
    //TODO Implémenter le test de régression de Player
}

void Player::removeLife()
{
    lives--;
}

void Player::addLife()
{
    lives++;
}

int Player::checkLife() const
{
    return lives;
}
