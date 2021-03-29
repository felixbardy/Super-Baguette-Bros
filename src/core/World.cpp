#include "World.h"
#include <assert.h>

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

void World::step()
{
    // 3• On applique l'update physique:

    // 3.1• Si le joueur va à droite/gauche: incrémenter/décrémenter la position en x
    if (player.checkInput(Player::RIGHT)) player.moveRight();

    if (player.checkInput(Player::LEFT)) player.moveLeft();

    // 3.2• Si le joueur saute, on met in_air à true et on incrémente la position en y
    if (player.checkInput(Player::JUMP)) player.jump();
    // 3.3• Si le joueur ne saute pas, vérifier la présence d'une plateforme en dessous:
    else
    {
        // 3.3.1• Si il y a une plateforme, fixer la position du joueur à sa hauteur*

		for (int i = 0; i < *nPlatforms; i++)
		{
            if (player.superposition(*platforms[i]))
		        ;
	        // 3.3.1• Sinon, décrémenter la position en y
	        else 
            {
		        player.fall();
	        }
        }
	}

    player.clearAllInputs();
}