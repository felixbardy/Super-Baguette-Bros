#include "World.h"

Segment::Segment()
{
}

Segment::Segment(Platform* platforms, Animation* animations)
{
}

Segment::~Segment()
{
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
    
    delete [] segments;
    delete [] platforms;
    delete nPlatforms;
}

void World::testRegression()
{
    // TODO Implémenter le test de régression de World
}