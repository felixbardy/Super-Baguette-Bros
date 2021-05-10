#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
 
int main(int argc, char ** argv)
{
    bool quit = false;
    SDL_Event event;
 
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
 
    SDL_Window * window = SDL_CreateWindow("SDL2 Sprite Sheets",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Surface * image = IMG_Load("data/sprite-sheet.png");
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
 
    SDL_SetRenderDrawColor(renderer, 168, 230, 255, 255);
    SDL_RenderClear(renderer);


    while (!quit)
    {
        Uint32 ticks = SDL_GetTicks();
        //Uint32 seconds = ticks / 1000;
        Uint32 sprite = (ticks/150) % 3;

        SDL_Rect srcrect;
        SDL_Rect dstrect = { 50, 50, 33, 66 };
        bool direction; //! true = droite, false = gauche

        while (SDL_PollEvent(&event) != NULL)
        {
            if (event.type == SDL_QUIT) quit = true;  // Si l'utilisateur a clique sur la croix de fermeture
			else if (event.type == SDL_KEYDOWN)
            {              // Si une touche est enfoncee
				switch (event.key.keysym.scancode)
                {
                    //* Les keybindings sont à définir ici
                    //TODO: peut-etre mettre des fonctions de mises a jour qui gerent aussi, les deplacements etc...
                    case SDL_SCANCODE_A:
                    srcrect = { ((int)sprite * 33) + 33, 0, 33, 66 };
                    direction = false;	
			        break;

		            case SDL_SCANCODE_D:
                    srcrect = { ((int)sprite * 33) + 33, 66, 33, 66 };
                    direction = true;
		            break;

                    case SDL_SCANCODE_S:
                    if (direction)
                        srcrect = { 165, 66, 33, 66 }; //!bool direction pour savoir si le perso est a gauche ou droite
                    else
                        srcrect = { 165, 0, 33, 66 };
                    break;

                    case SDL_SCANCODE_W: //!faut un bool inAir
                    if (direction)
                        srcrect = { 132, 66, 33, 66 }; //!bool direction
                    else
                        srcrect = { 132, 00, 33, 66 };
                    break;


                    case SDL_SCANCODE_ESCAPE:
                    case SDL_SCANCODE_Q:
                        quit = true;
                        break;

                    default:
                    if (direction)
                        srcrect = { 0, 66, 33, 66 }; 
                    else 
                        srcrect = { 0, 0, 33, 66 };
                    break;
				}
			}
            else if (event.type == SDL_KEYUP)
                {
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_a:
                        srcrect = { 0, 0, 33, 66 };
                        break;

                        case SDLK_d:
                        srcrect = { 0, 66, 33, 66 };
                        break;

                        case SDLK_w: //!faut un bool inAir
                        if (direction)
                            srcrect = { 132, 66, 33, 66 };
                        else
                            srcrect = { 132, 0, 33, 66 };
                        break;
                    
                        default:
                        if (direction)
                            srcrect = { 0, 66, 33, 66 }; 
                        else 
                            srcrect = { 0, 0, 33, 66 };
                        break;
                    }
                }

        }

        
 
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
        SDL_RenderPresent(renderer);
    }
 
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
 
    return 0;
}
