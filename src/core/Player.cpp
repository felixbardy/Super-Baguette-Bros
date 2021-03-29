#include "Player.h"

Player::Player(/* args */)
: current_input(0)
{
    in_air = false;
    jumping = false;
}

Player::~Player()
{
}


void Player::moveleft(Vec2f& pos)
{
    pos.x = pos.x - 0.15;
}

void Player::moveright(Vec2f& pos)
{
    pos.x = pos.x + 0.15;
}

void Player::jump(Vec2f& pos)
{
    if (!in_air)
        pos.y = pos.y + 0.15;
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

bool Player::checkInput(uint16_t mask)
{
    return (bool)(current_input & mask);
}

void Player::clearAllInputs()
{
    current_input = 0;
}

void Player::testRegression()
{
    //TODO Implémenter le test de régression de Player
}
