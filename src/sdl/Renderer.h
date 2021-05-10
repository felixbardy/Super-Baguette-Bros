#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "core/World.h"

/** \class GraphicRenderer Renderer.h "src/sdl/Renderer.h"
 * \brief La classe se chargeant de l'affichage
 * 
 * La classe se charge de l'affichage du jeu sur une fenêtre déjà créée.<br>
 * Côté utilisateur, seul GraphicRenderer::renderWorld() est accessible et a une importance.
 * 
 **/
class GraphicRenderer
{
private:
    World* world;               ///< Pointeur vers le monde à afficher
    SDL_Window* window;         ///< Fenêtre SDL
    SDL_Renderer* renderer;     ///< Renderer SDL
    SDL_Texture* sprite_sheet;  ///< Texture du sprite_sheet
    TTF_Font* font;             ///< La police à utiliser
    int unit_size;              ///< Le rapport pixels / unité de distance
    int camera_offset;          ///< Le décalage actuel de la caméra en x

    /// Renvoie les coordonées sur l'écran à partir des coordonées dans le monde
    /// \param pos Les coordonées à convertir
    Vec2f worldToScreen(Vec2f pos) const;

    /** \brief Dessine le joueur
     * \param game_ticks Le tick actuel, pour faire fonctionner les animations qui bouclent
     * \param player_inputs Le masque d'actions actuel du joueur
     **/
    void drawPlayer(Uint32 game_ticks, uint16_t player_inputs);
public:
    /** \brief Constructeur de GraphicRenderer
     * \param world Pointeur vers le monde à afficher
     * \param window La fenêtre SDL utilisée
     * \param renderer Le renderer SDL sur lequel dessiner
     * \param sprite_sheet Le spritesheet à utiliser, converti en texture
     * \param font La police d'écriture à utiliser 
     **/
    GraphicRenderer(World* world, SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* sprite_sheet, TTF_Font* font);
    ~GraphicRenderer();

    /** \brief La fonction d'affichage du monde
     * \param game_ticks Le tick actuel, pour faire fonctionner les animations qui bouclent
     * \param player_input Le masque d'actions actuel du joueur
     **/
    void renderWorld(Uint32 game_ticks, uint16_t player_input);
};


#endif //RENDERER_H