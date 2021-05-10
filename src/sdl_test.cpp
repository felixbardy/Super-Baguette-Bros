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
    if ( TTF_Init() == -1)
    {
        cout << "Failed to initialize SDL_TTF!" << endl;
        IMG_Quit();
        SDL_Quit();
        exit(1);
    }

    SDL_Window* window = SDL_CreateWindow(
        "Super baguette bros",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1080, 720,
        0
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Surface* sprite_sheet = IMG_Load("data/sprite-sheet.png");

    SDL_Texture* sprite_sheet_tex = SDL_CreateTextureFromSurface(renderer, sprite_sheet);

    TTF_Font* blocky_font = TTF_OpenFont("data/blocky.ttf", 24);
    if (blocky_font == NULL)
    {
        cout << "Failed to open font!" << endl;
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        exit(1);
    }

    SDL_SetRenderDrawColor(renderer, 168, 230, 255, 255);
    SDL_RenderClear(renderer);

    GraphicRenderer game_renderer(&world, window, renderer, sprite_sheet_tex, blocky_font);

    Uint32 ticks, game_ticks;
    Uint32 previous_game_tick = -1;

    uint16_t player_input = 0;
    int game_stop = 0;

    while (!quit && !game_stop)
    {
        ticks = SDL_GetTicks();
        game_ticks = ticks/17;

        //1• Récupérer les inputs et les mettre à jour le buffer d'inputs du joueur
        // SDL_PumpEvents() http://wiki.libsdl.org/SDL_PumpEvents
        // et const Uint8* SDL_GetKeyboardState(int* numkeys) http://wiki.libsdl.org/SDL_GetKeyboardState
        //Boucle d'évènements

        SDL_PumpEvents();
        const Uint8* keypressed = SDL_GetKeyboardState(NULL);

        if (keypressed[SDL_SCANCODE_SPACE])
            player_input |= Player::JUMP;
        
        if (keypressed[SDL_SCANCODE_W]) {
            player_input |= Player::JUMP;
            player_input |= Player::UP;
        }

        if (keypressed[SDL_SCANCODE_S])
            player_input |= Player::DOWN;
        
        if (keypressed[SDL_SCANCODE_A])
            player_input |= Player::LEFT;
        
        if (keypressed[SDL_SCANCODE_D])
            player_input |= Player::RIGHT;

        while (SDL_PollEvent(&event) != NULL)
        {
            if (event.type == SDL_QUIT) quit = true;
            else 
            if (event.type == SDL_KEYDOWN)
            {   //Si une touche est enfoncée
                //! Utiliser pour des contrôles occasionels comme mettre en pause ou quitter 
                switch (event.key.keysym.scancode)
                {
                    //Insérer les keybindings occasionnels
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
            game_stop = world.step();

            //2.3• Affichage
            game_renderer.renderWorld(game_ticks, player_input);

            player_input = 0;
        }

        previous_game_tick = game_ticks;
    }

    // Si on est sortis de la boucle après une défaite
    if ( game_stop == -1 )
    {
        SDL_Surface* end_screen = IMG_Load("data/gameover.png");
        SDL_Texture* end_screen_tex = SDL_CreateTextureFromSurface(renderer, end_screen);

        SDL_RenderCopy(renderer, end_screen_tex, NULL, NULL);

        SDL_RenderPresent(renderer);

        quit = false;
        while ( !quit )
        {
            SDL_PumpEvents();
            while (SDL_PollEvent(&event) != NULL)
            {
                if (event.type == SDL_QUIT) quit = true;
                else 
                if (event.type == SDL_KEYDOWN)
                {   //Si une touche est enfoncée
                    if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                    {
                            quit = true;
                    }
                }
            }
        }

        SDL_DestroyTexture(end_screen_tex);
        SDL_FreeSurface(end_screen);

    }

    // Si on est sortis de la boucle après une victoire
    if ( game_stop == 1 )
    {
        SDL_Surface* end_screen = IMG_Load("data/victory.png");
        SDL_Texture* end_screen_tex = SDL_CreateTextureFromSurface(renderer, end_screen);

        SDL_RenderCopy(renderer, end_screen_tex, NULL, NULL);

        SDL_RenderPresent(renderer);

        quit = false;
        while ( !quit )
        {
            SDL_PumpEvents();
            while (SDL_PollEvent(&event) != NULL)
            {
                if (event.type == SDL_QUIT) quit = true;
                else 
                if (event.type == SDL_KEYDOWN)
                {   //Si une touche est enfoncée
                    if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                    {
                            quit = true;
                    }
                }
            }
        }

        SDL_DestroyTexture(end_screen_tex);
        SDL_FreeSurface(end_screen);

    }

    // À la sortie du programme:

    //Détruire la texture
    SDL_DestroyTexture(sprite_sheet_tex);
    //Détruire la surface
    SDL_FreeSurface(sprite_sheet);
    //Fermer la police
    TTF_CloseFont(blocky_font);
    //Détruire le renderer
    SDL_DestroyRenderer(renderer);
    //Détruire la fenêtre
    SDL_DestroyWindow(window);
    //Fermer SDL, SDL_Image et SDL_ttf
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
