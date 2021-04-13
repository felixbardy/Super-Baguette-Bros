#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "core/World.h"
#include "sdl/Renderer.h"

int main()
{
    World world("data/levels/example_level.xml");

    bool quit = false;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window* window = SDL_CreateWindow(
        "Super baguette bros",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1920, 1080,
        0
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Surface* sprite_sheet = IMG_Load("data/sprite-sheet.png");

    SDL_Texture* sprite_sheet_tex = SDL_CreateTextureFromSurface(renderer, sprite_sheet);
    //TODO Définir une/des classe pour gérer le spritesheet (nécéssite une discussion)

    SDL_SetRenderDrawColor(renderer, 168, 230, 255, 255);
    SDL_RenderClear(renderer);

    GraphicRenderer game_renderer(&world, window, renderer, sprite_sheet_tex);

    Uint32 ticks, game_ticks;
    Uint32 previous_game_tick = -1;

    uint16_t player_input = 0;

    while (!quit)
    {
        ticks = SDL_GetTicks();
        game_ticks = ticks/17;

        //1• Récupérer les inputs et les mettre à jour le buffer d'inputs du joueur
        //FIXME Cette méthode n'est pas optimal pour du jeu en temps réel
        //TODO Convertir la lecture des inputs pour utiliser:
        // SDL_PumpEvents() http://wiki.libsdl.org/SDL_PumpEvents
        // et const Uint8* SDL_GetKeyboardState(int* numkeys) http://wiki.libsdl.org/SDL_GetKeyboardState
        //Boucle d'évènements
        while (SDL_PollEvent(&event) != NULL)
        {
            if (event.type == SDL_QUIT) quit = true;
            else 
            if (event.type == SDL_KEYDOWN)
            {   //Si une touche est enfoncée
                switch (event.key.keysym.scancode)
                {
                    case SDL_SCANCODE_SPACE:
                        player_input |= Player::JUMP;
                        break;
                        
                    case SDL_SCANCODE_W:
                        player_input |= Player::JUMP;
                        player_input |= Player::UP;
                        break;
                    
                    case SDL_SCANCODE_S:
                        player_input |= Player::DOWN;
                        break;
                    
                    case SDL_SCANCODE_A:
                        player_input |= Player::LEFT;
                        break;
                    
                    case SDL_SCANCODE_D:
                        player_input |= Player::RIGHT;
                        break;
                    
                    default:
                        break;
                }
            }
        }

        if (game_ticks == previous_game_tick)
        {
            //Ne rien faire
        }
        else //2• Mettre à jour l'image
        {
            //2.1• Passer les inputs à world
            world.setPlayerInputs(player_input);

            //2.2• Mettre à jour world
            world.step();

            //2.3• Affichage
            game_renderer.renderWorld(game_ticks, player_input);

            player_input = 0;
        }

        previous_game_tick = game_ticks;
    }

    // À la sortie du programme:

    //Détruire la texture
    SDL_DestroyTexture(sprite_sheet_tex);
    //Détruire la surface
    SDL_FreeSurface(sprite_sheet);
    //Détruire le renderer
    SDL_DestroyRenderer(renderer);
    //Détruire la fenêtre
    SDL_DestroyWindow(window);
    //Fermer SDL et SDL_Image
    IMG_Quit();
    SDL_Quit();

    return 0;
}