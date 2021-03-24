#include "World.h"

World::World()
: platforms(nullptr), segments(nullptr),
 nPlatforms(nullptr), last_loaded_segment(-1)
{
}

World::World(Segment* segments, int nSegments)
: segments(segments), nSegments(nSegments)
{
    nPlatforms = new int[3];
    //TODO Initialiser le joueur avec une position passée en paramètre
    player = Player();
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

void World::loadFirstSegments()
{
    //TODO Charger les 3 premiers segments
    Segment& first_segment = segments[0];
    
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