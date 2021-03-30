#ifndef CONSOLERENDERER_H
#define CONSOLERENDERER_H

#include <iostream>

#include "core/World.h"

class ConsoleRenderer
{
private:
    World* world;
    int image_height;
    int image_width;
    int camera_offset;
    float tile_width;
    char** image;

    /** \brief Remplit l'image avec le caractère donné
     * \param c Le caractère avec lequel remplir l'image
     **/
    void fill(char c);

    /** \brief Dessine une ligne sur l'image avec le caractère donné
     * \param sx Coordonnée x du 1er point
     * \param sy Coordonnée y du 1er point
     * \param ex Coordonnée x du 2ème point
     * \param ey Coordonnée y du 2ème point
     * \param c Le caractère utilisé pour dessiner la ligne
     **/
    void draw_line(int sx, int sy, int ex, int ey, char c);

    /** \brief Dessine un rectangle sur l'image avec le caractère donné
     * \param minx Coordonnée x du point en bas à gauche
     * \param miny Coordonnée y du point en bas à gauche
     * \param maxx Coordonnée x du point en haut à droite
     * \param maxy Coordonnée y du point en haut à droite
     * \param c Caractère utilisé pour dessiner le rectangle
     **/
    void draw_rectangle(int minx, int miny, int maxx, int maxy, char c);

    /** \brief Renvoie vrai si le point est dessinable, faux sinon
     * \param point Le point à vérifier
     **/
    bool is_in_bounds(Vec2f point);
public:
    /// Constructeur de ConsoleRenderer (world doit être initialisé au préalable)
    ConsoleRenderer(World* world, int width, int height, float scale);
    /// Destructeur de ConsoleRenderer (ne détruit pas World)
    ~ConsoleRenderer();

    /// Affiche le monde
    void render();
};





#endif //CONSOLERENDERER_H