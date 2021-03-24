#include "console/ConsoleRenderer.h"

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
    Animation* animations = new Animation[0];

    segments[0] = Segment(platforms, 3, animations, 0);

    // Et on s'attaque au 2ème segment

    platforms = new Platform[3];
    platforms[0] = Platform({0,0}, 10, 1, 0);
    platforms[1] = Platform({10,5}, 10, 1, 0);
    platforms[2] = Platform({20,10}, 10, 1, 0);
    animations = new Animation[0];
    segments[1] = Segment(platforms, 3, animations, 0);

    // Segment 3
    platforms = new Platform[3];
    platforms[0] = Platform({0,0}, 10, 1, 0);
    platforms[1] = Platform({10,5}, 10, 1, 0);
    platforms[2] = Platform({20,10}, 10, 1, 0);
    animations = new Animation[0];
    segments[2] = Segment(platforms, 3, animations, 0);

    World w = World(segments, 3);
    ConsoleRenderer cr = ConsoleRenderer(&w, 20, 30, 1);

    cr.render();
    return 0;
}