#include "Player.h"

Player::Player(/* args */)
: current_input(0)
{
}

Player::~Player()
{
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