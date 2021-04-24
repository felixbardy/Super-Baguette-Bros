#include "Entity.h"
#include <iostream>
#include <cassert>

using namespace std;

Entity::Entity() :
pos({0,0}),
vel({0,0}),
width(0),
height(0),
angle(0)
{}

Entity::Entity(Vec2f pos, float width, float height, float angle) :
vel({0,0})
{
    setPosition(pos);
    setWidth(width);
    setHeight(height);
    setAngle(angle);
}

Entity::~Entity()
{
}

void    Entity::testRegression()
{
    //TODO Implémenter le test régression de Entity
    cout << "Entity: constructeur par valeurs... ";
    
    Entity EntityTest({10.0,10.0}, 10.0, 10.0, 10.0);
    assert(EntityTest.pos.x == 10.0 && EntityTest.pos.y == 10.0);
    assert(EntityTest.width == 10.0);
    assert(EntityTest.height == 10.0);
    assert(EntityTest.angle == 10.0);

    cout << "OK" << endl;


    cout << "Entity: constructeur par défaut... ";

    Entity EntityTest2;
    Vec2f vecTest = EntityTest2.getPosition();
    assert(vecTest.x == 0 && vecTest.y == 0);
    assert(EntityTest2.getWidth() == 0);
    assert(EntityTest2.getHeight() == 0);
    assert(EntityTest2.getAngle() == 0);

    cout << "OK" << endl;

    cout << "Entity: velocity et angle...";

    EntityTest.setVelocity({10,10});
    vecTest = EntityTest.getVelocity();
    assert(vecTest.x == 10 && vecTest.y == 10);
    EntityTest.applyForce({5,5});
    assert(EntityTest.vel.x == 15 && EntityTest.vel.y == 15);
    EntityTest.setAngle(15);
    assert(EntityTest.getAngle() == 15);

    cout << "OK" << endl;


    cout << "Entity: move et superposition... ";

    assert(!(EntityTest.superposition(EntityTest2))); //lorsqu'il n'y a pas de superpositon
    EntityTest2.move({10,10});
    assert(EntityTest2.pos.x == 10 && EntityTest2.pos.y == 10);
    assert(EntityTest.superposition(EntityTest2)); //lorsqu'il y a superposition

    cout << "OK" << endl;


}

Vec2f   Entity::getPosition() const
{
    return pos;
}

void    Entity::setPosition(Vec2f newpos)
{
    pos = newpos;
}

Vec2f   Entity::getVelocity() const
{
    return vel;
}

void    Entity::setVelocity(Vec2f newvel)
{
    vel = newvel;
}

float   Entity::getAngle() const
{
    return angle;
}

void    Entity::setAngle(float newangle)
{
    angle = newangle;
}

float   Entity::getWidth() const
{
    return width;
}

void    Entity::setWidth(float newwidth)
{
    width = newwidth;
}

float   Entity::getHeight() const
{
    return height;
}

void    Entity::setHeight(float newheight)
{
    height = newheight;
}

Hitbox Entity::getHitbox() const
{
    return Hitbox(pos, width, height);
}


void    Entity::applyForce(Vec2f force)
{
    vel += force;
}

void    Entity::move(Vec2f offset)
{
    pos += offset;
}

void    Entity::rotate(float angle)
{
    this->angle += angle;
}

bool    Entity::superposition(Entity ent2)
{
    return !( // Vrai sauf si:
           ((ent2.pos.x + ent2.width) < pos.x)  // ent2 est complètement à gauche de this
        || ((pos.x + width) < ent2.pos.x)       // this est complètement à gauche de ent2
        || ((ent2.pos.y + ent2.height) < pos.y) // ent2 est complètement en dessous de this
        || ((pos.y + height) < ent2.pos.y)      // this est complètement en dessous de ent2
    );
}
