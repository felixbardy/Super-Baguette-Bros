#include "Player.h"
#include <cassert>
#include <iostream>

using namespace std;

Player::Player(/* args */)
: current_input(0)
{
    in_air = false;
    jumping = false;
    lives = 3;
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
    //TODO Mettre a jour lorsque player est finalisé

    cout << "Player: constructeur par défaut... ";

    Player p;
    assert(!p.isInAir());
    assert(!p.isJumping());
    assert(p.lives == 3);
    assert(p.current_input == 0);

    cout << "OK" << endl;


    cout << "Player: lives...";

    p.removeLife();
    assert(p.checkLife() == 2);
    p.addLife();
    assert(p.lives == 3);

    cout << "OK" << endl;


    cout << "Player: air et jump... ";

    p.jump();
    assert(p.in_air);

    cout << "OK" << endl;


    cout << "Player: inputs... ";

    assert(!p.checkInput(JUMP));
    p.addInput(JUMP);
    assert(p.checkInput(JUMP));
    p.clearInput(JUMP);
    assert(!p.checkInput(JUMP));

    assert(!p.checkInput(DOWN));
    p.addInput(DOWN);
    assert(p.checkInput(DOWN));

    assert(!p.checkInput(UP));
    p.addInput(UP);
    assert(p.checkInput(UP));

    assert(!p.checkInput(LEFT));
    p.addInput(LEFT);
    assert(p.checkInput(LEFT));

    assert(!p.checkInput(RIGHT));
    p.addInput(RIGHT);
    assert(p.checkInput(RIGHT));
    
    p.clearAllInputs();
    assert(!p.checkInput(DOWN));
    assert(!p.checkInput(UP));
    assert(!p.checkInput(LEFT));
    assert(!p.checkInput(RIGHT));

    cout << "OK" << endl;



}

void Player::removeLife()
{
    lives--;
}

void Player::addLife()
{
    lives++;
}

int Player::checkLife()
{
    return lives;
}
