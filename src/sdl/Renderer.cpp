#include "Renderer.h"

GraphicRenderer::GraphicRenderer(World* world, SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* sprite_sheet)
: world(world), window(window), renderer(renderer), sprite_sheet(sprite_sheet), unit_size(33)
{}

GraphicRenderer::~GraphicRenderer()
{}

void GraphicRenderer::renderWorld()
{
    //1• Récupérer des données

    // Les dimensions de la fenêtre
    int win_w, win_h;
    SDL_GetWindowSize(window, &win_w, &win_h);

    // Le centre de la fenêtre
    int win_center_x, win_center_y;
    win_center_x = win_w / 2;
    win_center_y = win_h / 2;

    const Player& player = world->getPlayer();

    //FIXME Récupérer la vraie fin du niveau
    // La fin du niveau
    int world_end = 10000;

    // Le décalage de la caméra dans le monde
    this->camera_offset = 
    max(
        0, // Minimum 0
        min(
            int(player.getPosition().x*unit_size - (win_w - unit_size) / 2), // Normalement: centré sur le joueur
            world_end - win_w // Maximum: la fin du niveau moins un écran
            )
    );

    //2• Dessiner le monde
    //2.1• Effacer la fenêtre

    SDL_RenderClear(renderer);

    //2.2• Dessiner l'arrière plan

    //2.3• Dessiner les plateformes

    Platform** all_platforms = world->getPlatforms();
    const int* platform_sizes = world->getPlatformsSizes();
    SDL_Rect srcrect_platform = {0, 132, 33, 33};

    for (int i = 0; i < 3; i++)
    {   // Dessiner chaque liste de plateformes
        const Platform* platforms = all_platforms[i];
        const int size = platform_sizes[i];
        for (int j = 0; j < size; j++)
        {
            const Platform& platform = platforms[j];
            Vec2f position = platform.getPosition();
            int length = platform.getWidth();
            //? Peut-être vérifier si la plateforme est dessinable
            SDL_Rect dstrect;
            for (Vec2f pos = position; pos.x < position.x + length; pos += {1,0})
            {
                Vec2f screen_pos = worldToScreen(pos);
                dstrect = {(int)screen_pos.x, (int)screen_pos.y, unit_size, unit_size};
                SDL_RenderCopy(renderer, sprite_sheet, &srcrect_platform, &dstrect);
            }
        }
    }

    //2.4• Dessiner les pièces
    //2.5• Dessiner les autres entités 
    //2.6• Dessiner le joueur
    Vec2f screen_pos = worldToScreen(player.getPosition());
    //FIXME Choisir le bon sprite de joueur en fonction de ses actions
    SDL_Rect srcrect_player = {0,66,33,66};
    SDL_Rect dstrect = {(int)screen_pos.x,(int)screen_pos.y, unit_size, 2*unit_size};
    SDL_RenderCopy(renderer, sprite_sheet, &srcrect_player, &dstrect);
    //2.7• Dessiner le 1er plan
    
    //3• Afficher le monde
    SDL_RenderPresent(renderer);
}

Vec2f GraphicRenderer::worldToScreen(Vec2f pos)
{
    int win_h;
    SDL_GetWindowSize(window, NULL, &win_h);
    return Vec2f(
        pos.x * unit_size - camera_offset,
        win_h - pos.y * unit_size
    );
}