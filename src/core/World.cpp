#include "World.h"

World::World()
: platforms(nullptr), segments(nullptr),
 nPlatforms(nullptr), last_loaded_segment(-1)
{
}

World::World(Segment* segments, int nSegments)
: segments(segments), nSegments(nSegments)
{
    platforms = new Platform*[3];
    nPlatforms = new int[3];
    //TODO Initialiser le joueur avec une position passée en paramètre
    player = Player();

    loadFirstSegments();
}

World::~World()
{
    for (Animation* anim : animations)
        if (!anim->from_segment) delete anim;
    
    if (segments != nullptr)
        delete [] segments;

    if (platforms != nullptr)
        delete platforms;

    if (nPlatforms != nullptr)
        delete [] nPlatforms;
}

void World::loadFirstSegments()
{
    Segment* segment;
    Platform* new_platforms;
    Animation** new_animations;
    int platforms_size;
    int animations_size;

    for (int i = 0; i < 3; i++)
    {
        // On récupère les données du segment
        segment = &segments[i];
        segment->loadPlatforms(new_platforms, platforms_size);
        segment->loadAnimations(new_animations, animations_size);

        // On charge les plateformes dans World
        platforms[i] = new_platforms;
        nPlatforms[i] = platforms_size;

        // Et on charge les animations dans World
        for (int j = 0; j < animations_size; j++)
            animations.push_back(new_animations[j]);
    }
    
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

void World::setPlayerInputs(uint16_t input_mask)
{
    player.addInput(input_mask);
}