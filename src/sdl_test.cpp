#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "core/World.h"

int main()
{
    // Création d'une liste simple de 3 segments
    // On fait des segments de 30 de longueur
    Segment* segments = new Segment[3];

    // On créé 3 plateformes par segment
    Platform* platforms = new Platform[3];
    platforms[0] = Platform({0,0}, 10, 1, 0);
    platforms[1] = Platform({10,3}, 10, 1, 0);
    platforms[2] = Platform({20,6}, 10, 1, 0);

    // On ne fait pas d'animations pour l'instant
    Animation** animations = new Animation*[0];

    segments[0].setPlatforms(platforms, 3);
    segments[0].setAnimations(animations, 0);

    // Et on s'attaque au 2ème segment

    platforms = new Platform[3];
    platforms[0] = Platform({30,9}, 10, 1, 0);
    platforms[1] = Platform({40,6}, 10, 1, 0);
    platforms[2] = Platform({50,3}, 10, 1, 0);
    animations = new Animation*[0];

    segments[1].setPlatforms(platforms, 3);
    segments[1].setAnimations(animations, 0);

    // Segment 3
    platforms = new Platform[3];
    platforms[0] = Platform({60,2}, 10, 1, 0);
    platforms[1] = Platform({70,5}, 10, 1, 0);
    platforms[2] = Platform({80,8}, 10, 1, 0);
    animations = new Animation*[0];
    
    segments[2].setPlatforms(platforms, 3);
    segments[2].setAnimations(animations, 0);

    World w = World(segments, 3);

    return 0;
}