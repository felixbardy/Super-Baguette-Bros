#include "Entity.h"

Entity::Entity() :
pos({0,0}),
width(0),
height(0),
angle(0)
{}

Entity::Entity(Vec2f pos, float width, float height, float angle)
{
}

Entity::~Entity()
{
}

Vec2f   Entity::getPosition() const
{
}

void    Entity::setPosition(Vec2f newpos)
{
}

Vec2f   Entity::getVelocity() const
{
}

void    Entity::setVelocity(Vec2f newvel)
{
}

float   Entity::getAngle() const
{
}

void    Entity::setAngle(float newangle)
{
}

float   Entity::getWidth() const
{
}

void    Entity::setWidth(float newwidth)
{
}

float   Entity::getHeight() const
{
}

void    Entity::setHeight(float newheight)
{
}

void    Entity::applyForce(Vec2f force)
{
}

void    Entity::move(Vec2f offset)
{
}

void    Entity::rotate(float angle)
{
}