#include "World.h"

World::World(/* args */)
: platforms(nullptr), segments(nullptr), nPlatforms(nullptr)
{
}

World::~World()
{
    for (Animation* anim : animations)
        delete anim;

    if (platforms != nullptr)
        delete [] platforms;
    
    if (segments != nullptr)
        delete [] segments;

    if (nPlatforms != nullptr)
        delete [] nPlatforms;
}

void World::testRegression()
{
    // TODO Implémenter le test de régression de World
}

Platform** World::getPlatforms() const
{
    return platforms;
}

const int* World::getPlatformsSizes() const
{
    return nPlatforms;
}


const Player& World::getPlayer() const{
    return player;
}