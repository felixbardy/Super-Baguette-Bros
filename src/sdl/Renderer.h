#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "core/World.h"

/// TODO Réfléchir à coder un gestionnaire de spritesheets pour simplifier l'affichage dans Renderer

class GraphicRenderer
{
private:
    World* world;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* sprite_sheet;
    int unit_size;
    int camera_offset;

    Vec2f worldToScreen(Vec2f pos) const;

    void drawPlayer(Uint32 game_ticks, uint16_t player_inputs);
public:
    GraphicRenderer(World* world, SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* sprite_sheet);
    ~GraphicRenderer();

    void renderWorld(Uint32 game_ticks, uint16_t player_input);
};


#endif //RENDERER_H