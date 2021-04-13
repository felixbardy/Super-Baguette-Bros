#include "Renderer.h"

GraphicRenderer::GraphicRenderer(World* world, SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* sprite_sheet)
: world(world), window(window), renderer(renderer), sprite_sheet(sprite_sheet)
{
    int win_h;
    SDL_GetWindowSize(window, NULL, &win_h);
    this->unit_size = win_h / 20;
}

GraphicRenderer::~GraphicRenderer()
{}

void GraphicRenderer::renderWorld(Uint32 game_ticks, uint16_t player_inputs)
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
                dstrect = {(int)screen_pos.x, (int)screen_pos.y + unit_size, unit_size, unit_size};
                SDL_RenderCopy(renderer, sprite_sheet, &srcrect_platform, &dstrect);
            }
        }
    }

    //2.4• Dessiner les pièces
    //2.5• Dessiner les autres entités 
    //2.6• Dessiner le joueur
    drawPlayer(game_ticks, player_inputs);
    //2.7• Dessiner le 1er plan
    
    //3• Afficher le monde
    SDL_RenderPresent(renderer);
}

/**
 * \brief Renvoie les coordonnées sur la fenêtre correspondant aux coordonnées du monde données
 * \param pos les coordonées à convertir
 **/
Vec2f GraphicRenderer::worldToScreen(Vec2f pos) const
{
    int win_h;
    SDL_GetWindowSize(window, NULL, &win_h);
    return Vec2f(
        pos.x * unit_size - camera_offset,
        win_h - pos.y * unit_size
    );
}

/**
 * \brief Dessine le joueur
 * \param game_ticks le numéro de frame actuel (utilisé pour alterner les sprites de marche)
 * \param player_inputs les inputs fournis au joueur cette frame là
 **/
void GraphicRenderer::drawPlayer(Uint32 game_ticks, uint16_t player_inputs)
{
    //2.6• Dessiner le joueur
    const Player& player = world->getPlayer();

    Vec2f screen_pos = worldToScreen(player.getPosition());
    SDL_Rect srcrect_player = {0, 66, 33, 66}; //Valeur de base
    //cout<<"("<<screen_pos.x<<", "<<screen_pos.y<<")"<<endl;

    //TODO Définir un booléen 'flip' pour retourner le sprite si le joueur est orienté à gauche
    //TODO Définir un champ pour la direction du joueur dans Player pour pouvoir faire ça
    if (player_inputs & (Player::LEFT | Player::RIGHT))
        srcrect_player = {33 + (33*int(game_ticks/3)) % 99, 66, 33, 66};
    
    if ((player_inputs & Player::JUMP) || player.isInAir())
        srcrect_player = {132, 66, 33, 66};
    else if (player_inputs & Player::DOWN)
        srcrect_player = {165, 66, 33, 66};

    SDL_Rect dstrect = {(int)screen_pos.x,(int)screen_pos.y, unit_size, 2*unit_size};
    SDL_RenderCopy(renderer, sprite_sheet, &srcrect_player, &dstrect);
}