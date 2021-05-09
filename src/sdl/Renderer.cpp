#include "Renderer.h"

GraphicRenderer::GraphicRenderer(World* world, SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* sprite_sheet, TTF_Font* font)
: world(world), window(window), renderer(renderer), sprite_sheet(sprite_sheet), font(font)
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

    // La fin du niveau
    int world_end = world->getWorldEnd();

    // Le décalage de la caméra dans le monde
    this->camera_offset = 
    max(
        0, // Minimum 0
        min(
            int(player.getPosition().x*unit_size - (win_w - unit_size) / 2), // Normalement: centré sur le joueur
            world_end*unit_size - win_w // Maximum: la fin du niveau moins un écran
            )
    );

    //2• Dessiner le monde
    //2.1• Effacer la fenêtre

    SDL_RenderClear(renderer);

    //2.2• Dessiner l'arrière plan

    //2.3• Dessiner les plateformes

    Platform** all_platforms = world->getPlatforms();
    const int* platform_sizes = world->getPlatformsSizes();
    SDL_Rect srcrect_platform = {0, 66, 33, 30};

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

    const std::vector<Piece*> pieces = world->getPieces();
    SDL_Rect srcrect_piece = {33, 66, 24, 24};
    SDL_Rect dstrect;
    Vec2f screen_pos;

    for (auto piece : pieces)
    {
        if (!piece->isTaken())
        {
            screen_pos = worldToScreen(piece->getPosition());
            dstrect = {(int)screen_pos.x, (int)screen_pos.y + unit_size, unit_size, unit_size};
            SDL_RenderCopy(renderer, sprite_sheet, &srcrect_piece, &dstrect);
        }
    }

    //2.5• Dessiner les autres entités 
    //2.6• Dessiner le joueur
    drawPlayer(game_ticks, player_inputs);
    //2.7• Dessiner le 1er plan
    
    //2.7.1• Afficher les vies
    // Dessin du coeur
    SDL_Rect srcrect_coeur = {57,66,34,30};
    dstrect = {0, 0, 2*unit_size, 2*unit_size};
    SDL_RenderCopy(renderer, sprite_sheet, &srcrect_coeur, &dstrect);


    // Nombre de vies
    std::string text = to_string(player.getLives());
    SDL_Surface* text_surface = TTF_RenderText_Blended(font, text.c_str(), {255, 255, 255});
	SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

    dstrect = {2*unit_size, 0, unit_size * (int)text.length(), 2*unit_size};
    SDL_RenderCopy(renderer, text_texture, NULL, &dstrect);

    // Libérer la surface et la texture
    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);

    //2.7.2• Afficher le score

    // Dessin de la pièce
    dstrect = {win_w - 2*unit_size, 0, 2*unit_size, 2*unit_size};
    SDL_RenderCopy(renderer, sprite_sheet, &srcrect_piece, &dstrect);

    text = to_string(world->getScore());
    text_surface = TTF_RenderText_Blended(font, text.c_str(), {255, 255, 255});
	text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

    dstrect = {win_w - (2 + (int)text.length()) * unit_size, 0, (int)text.length() * unit_size, 2*unit_size};
    SDL_RenderCopy(renderer, text_texture, NULL, &dstrect);

    // Libérer la surface et la texture
    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);

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
        win_h - (pos.y+2) * unit_size
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
    SDL_Rect srcrect_player = {0, 0, 33, 66}; //Valeur de base
    //cout<<"("<<screen_pos.x<<", "<<screen_pos.y<<")"<<endl;

    SDL_RendererFlip flip = SDL_FLIP_NONE;

    if (player_inputs & (Player::LEFT | Player::RIGHT))
        srcrect_player = {33 + (33*int(game_ticks/3)) % 99, 0, 33, 66};
    
    if ((player_inputs & Player::JUMP) || player.isInAir())
        srcrect_player = {132, 0, 33, 66};
    else if (player_inputs & Player::DOWN)
        srcrect_player = {165, 0, 33, 66};
    
    if (player.getDirection() == Player::LEFT) flip = SDL_FLIP_HORIZONTAL;

    SDL_Rect dstrect = {(int)screen_pos.x,(int)screen_pos.y, unit_size, 2*unit_size};
    SDL_RenderCopyEx(renderer, sprite_sheet, &srcrect_player, &dstrect, 0, NULL, flip);
}