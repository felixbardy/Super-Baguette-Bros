#include "Entity.h"

Entity::Entity() :
pos({0,0}),
width(0),
height(0),
angle(0)
{}

Entity::Entity(Vec2f pos, float width, float height, float angle)
{
    setPosition(pos);
    setWidth(width);
    setHeight(height);
    setAngle(angle);
}

Entity::~Entity()
{
}

void Entity::testRegression()
{
    //TODO Implémenter le test régression de Entity
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