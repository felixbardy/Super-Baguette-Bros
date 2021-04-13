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

    // bool is_in_bounds(const Platform& platform);

    Vec2f worldToScreen(Vec2f pos);
public:
    GraphicRenderer(World* world, SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* sprite_sheet);
    ~GraphicRenderer();

    void renderWorld();
};


#endif //RENDERER_H