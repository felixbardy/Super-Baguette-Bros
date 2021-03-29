#include "console/ConsoleRenderer.h"
#include <cassert>

int main()
{
    // Création d'une liste simple de 3 segments
    // On fait des segments de 30 de longueur
    Segment* segments = new Segment[3];

    // On créé 3 plateformes par segment
    Platform* platforms = new Platform[3];
    platforms[0] = Platform({0,0}, 10, 1, 0);
    platforms[1] = Platform({10,5}, 10, 1, 0);
    platforms[2] = Platform({20,10}, 10, 1, 0);

    // On ne fait pas d'animations pour l'instant
    Animation** animations = new Animation*[0];

    segments[0].setPlatforms(platforms, 3);
    segments[0].setAnimations(animations, 0);

    // Et on s'attaque au 2ème segment

    platforms = new Platform[3];
    platforms[0] = Platform({30,0}, 10, 1, 0);
    platforms[1] = Platform({40,5}, 10, 1, 0);
    platforms[2] = Platform({50,10}, 10, 1, 0);
    animations = new Animation*[0];

    segments[1].setPlatforms(platforms, 3);
    segments[1].setAnimations(animations, 0);

    // Segment 3
    platforms = new Platform[3];
    platforms[0] = Platform({60,0}, 10, 1, 0);
    platforms[1] = Platform({70,5}, 10, 1, 0);
    platforms[2] = Platform({80,10}, 10, 1, 0);
    animations = new Animation*[0];
    
    segments[2].setPlatforms(platforms, 3);
    segments[2].setAnimations(animations, 0);

    World w = World(segments, 3);
    
    ConsoleRenderer cr = ConsoleRenderer(&w, 60, 20, 1);
    int offset = -1;
    while (offset != 0)
    {
        cr.render();
        cin >> offset;
        //FIXME Le Joueur est protégé en écriture: Ajouter les méthodes de contrôle dans World
        //w.getPlayer().move(Vec2f(offset,0));
    }
    
	return 0;
}