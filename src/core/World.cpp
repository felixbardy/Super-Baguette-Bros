#include "World.h"

Segment::Segment() 
{
    platforms = nullptr;
    nPlatforms = 0;
    animations = nullptr;
    nAnimations = 0;
}

Segment::Segment(Platform* platforms, int nPlatforms,  Animation* animations, int nAnimations)
: platforms(platforms), nPlatforms(nPlatforms), animations(animations), nAnimations(nAnimations)
{

}

Segment::~Segment()
{
    if (platforms != nullptr){
        delete[] platforms;
        platforms = nullptr;
    }
    if (animations != nullptr){
        delete[] animations;
        animations = nullptr;
    }
}


void Segment::testRegression()
{
    //TODO Implémenter le test de régression de Segment
}


World::World(/* args */)
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

    delete nPlatforms;
}

void World::testRegression()
{
    // TODO Implémenter le test de régression de World
}

const Platform** World::getPlatforms() const
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