#include "World.h"

#include <iostream>
#include <cassert>
#include <assert.h>


#include "extern/tinyxml2.h"

World::World()
: score(0), frameCount(0),
  segments(nullptr), centerLoadedSegment(1),
  platforms(nullptr), nPlatforms(nullptr)
{
    
}

World::World(std::string filename)
: score(0), frameCount(0),
  segments(nullptr), centerLoadedSegment(1),
  platforms(nullptr), segmentWidth(30),
  nPlatforms(nullptr)
{
    using namespace tinyxml2;

    // Initialisation du document
    XMLDocument xml_doc;
    // Sert à récupérer les résultats des fonctions
    XMLError result;

    // On charge le document
    result = xml_doc.LoadFile("data/levels/example_level.xml");
    // On renvoie la potentielle erreur
    XMLCheckResult(result);

    // Récupérer la racine du DOM
    XMLNode* root = xml_doc.FirstChild();
    // Si c'est nullptr, y'a de quoi avoir peur...
    if (root == nullptr) exit(XML_ERROR_FILE_READ_ERROR);

    // Récupérer la largeur de segment
    XMLElement* segment_width_elt = root->FirstChildElement("SegmentWidth");
    // Si c'est nullptr, j'ai peur...
    if (segment_width_elt == nullptr) exit(XML_ERROR_PARSING_ELEMENT);
    result = segment_width_elt->QueryFloatText(&(this->segmentWidth)); XMLCheckResult(result);

    // Récupérer l'objectif

    XMLElement* goal = root->FirstChildElement("Goal");
    // Si c'est nullptr, j'ai peur...
    if (goal == nullptr) exit(XML_ERROR_PARSING_ELEMENT);
    int goal_x, goal_y, goal_seg_index;
    result = goal->QueryIntAttribute("segment_index", &goal_seg_index); XMLCheckResult(result);
    result = goal->QueryIntAttribute("x", &goal_x); XMLCheckResult(result);
    result = goal->QueryIntAttribute("y", &goal_y); XMLCheckResult(result);

    this->goal = Entity({(float)goal_x + goal_seg_index * segmentWidth, (float)goal_y},2,2,0);

    cout << "goal.x: " << this->goal.getPosition().x <<endl;
    cout << "goal.y: " << this->goal.getPosition().y <<endl;
    cout << "goal.width: " << this->goal.getWidth() <<endl;
    cout << "goal.height: " << this->goal.getHeight() <<endl;
    


    // Récupérer la liste des segments
    XMLElement* segment_list = root->FirstChildElement("Segments");
    // Si c'est nullptr, je meurs...
    if (segment_list == nullptr) exit(XML_ERROR_PARSING_ELEMENT);

    // Récupérer le nombre total de segments
    int count;
    result = segment_list->QueryIntAttribute("count", &count); XMLCheckResult(result);
    this->nSegments = count;

    // Allouer le tableau de Segments
    this->segments = new Segment[count];

    // Récupération du 1er segment
    XMLElement * segment = segment_list->FirstChildElement("Segment");
    Platform * segment_platforms = nullptr;
    Animation** segment_animations = nullptr;

    for (int segment_index = 0; segment_index < nSegments; segment_index++)
    {   
        //* RÉCUPÉRATION DE SEGMENT *//
        //* 0• Récupérer l'offset du segment

        float offset = segment_index * segmentWidth;

        //* 1• Récupérer les platformes
        // 1.1• Récupérer l'élément Platforms
        XMLElement * platform_list = segment->FirstChildElement("Platforms");
        // Si elles n'existent pas, on est dans le caca...
        if (platform_list == nullptr) exit(XML_ERROR_PARSING_ELEMENT);

        // 1.2• Récupérer la taille du tableau
        result = platform_list->QueryIntAttribute("count", &count);
        XMLCheckResult(result);
        int nPlatforms = count;

        // Si la liste est vide
        if (nPlatforms == 0) // Allouer une liste vide
            segment_platforms = new Platform[0];
        else // sinon...
        {
        // 1.3• Allouer le tableau de plateformes
        segment_platforms = new Platform[nPlatforms];
        // 1.4• Récupérer la première plateforme
        XMLElement * platform = platform_list->FirstChildElement("Platform");

        // 1.5• Traiter toute la liste de plateformes
        for (int platform_index = 0; platform_index < nPlatforms; platform_index++)
        {
            // 1.5.1• Récupérer les caractéristiques de la plateforme
            int x,y,width,height,angle;
            // x
            result = platform->QueryIntAttribute("x", &x);
            XMLCheckResult(result);
            // y
            result = platform->QueryIntAttribute("y", &y);
            XMLCheckResult(result);
            // width
            result = platform->QueryIntAttribute("width", &width);
            XMLCheckResult(result);
            // height
            result = platform->QueryIntAttribute("height", &height);
            XMLCheckResult(result);
            // angle
            result = platform->QueryIntAttribute("angle", &angle);
            XMLCheckResult(result);

            // 1.5.2• Affecter la nouvelle plateforme
            segment_platforms[platform_index] = Platform(Vec2f(x + offset, y),width,height,angle);

            // 1.5.3• Récupérer la prochaine plateforme (= nullptr à la fin)
            platform = platform->NextSiblingElement("Platform");
        }
        }

        //* 2• Récupérer les animations
        // 2.1• Récupérer l'élément Animations
        XMLElement * animations_list = segment->FirstChildElement("Animations");
        // Mon imagination pour ces blaques est limitée...
        if (animations_list == nullptr) exit(XML_ERROR_PARSING_ELEMENT);
        
        // 2.2• Récupérer la taille du tableau
        result = animations_list->QueryIntAttribute("count", &count); XMLCheckResult(result);
        int nAnimations = count;

        // Si le tableau est vide 
        if (nAnimations == 0) // Allouer un tableau vide
            segment_animations = new Animation*[0];
        else // Sinon...
        {
        // 2.3• Allouer le tableau
        segment_animations = new Animation*[nAnimations];

        // 2.4• Récupérer la 1ère Animation
        XMLElement * animation = animations_list->FirstChildElement("Animation");

        // 2.5• Traiter toute la liste d'Animations
        for (int animation_index = 0; animation_index < nAnimations; animation_index++)
        {

            // 2.5.1• Récupérer le type de l'Animation
            int temp_int;
            AnimationType type;
            
            result = animation->QueryIntAttribute("type", &temp_int);
            XMLCheckResult(result);
            type = (AnimationType) temp_int;

            // 2.5.2• Allouer et affecter l'animation en fonction de son type
            if (type == LINEAR)
            {
                float start_x, start_y, mov_x, mov_y, speed;
                int target;

                // target
                result = animation->QueryIntAttribute("target", &target);
                XMLCheckResult(result);

                // start.x
                result = animation->QueryFloatAttribute("start_x", &start_x);
                XMLCheckResult(result);

                // start.y
                result = animation->QueryFloatAttribute("start_y", &start_y);
                XMLCheckResult(result);

                // mov.x
                result = animation->QueryFloatAttribute("mov_x", &mov_x);
                XMLCheckResult(result);

                // mov.y
                result = animation->QueryFloatAttribute("mov_y", &mov_y);
                XMLCheckResult(result);

                // speed
                result = animation->QueryFloatAttribute("speed", &speed);
                XMLCheckResult(result);

                LinearAnimation temp_anim = createLinearAnimation(
                    segment_platforms + target,
                    Vec2f(start_x + offset, start_y),
                    Vec2f(mov_x, mov_y),
                    speed,
                    &segments[segment_index]
                );

                segment_animations[animation_index] = new LinearAnimation(temp_anim);
            }
            else
            {
                cout << "Le chargement du type d'animation " << type << " n'a pas été implémenté!";
                exit(1);
            }

            // 2.5.3• Récupérer la prochaine animation (= nullptr à la fin)
            animation = animation->NextSiblingElement("Animation");
        } // Fin for animations

        } // Fin else
        
        //* 3• Récupérer les pièces
        XMLElement * pieces = segment->FirstChildElement("Pieces");

        XMLElement * bloc = pieces->FirstChildElement("Bloc");
        
        while (bloc != nullptr)
        {
            int minx, miny, maxx, maxy;

            // Bottom left
            result = bloc->QueryIntAttribute("minx", &minx);
            XMLCheckResult(result);
            result = bloc->QueryIntAttribute("miny", &miny);
            XMLCheckResult(result);

            // Top right
            result = bloc->QueryIntAttribute("maxx", &maxx);
            XMLCheckResult(result);
            result = bloc->QueryIntAttribute("maxy", &maxy);
            XMLCheckResult(result);

            Segment& current_segment = this->segments[segment_index];

            for (int x = minx; x <= maxx; x++)
            for (int y = miny; y <= maxy; y++)
            {
                current_segment.addPiece(x + offset, y);
            }

            // On récupère le bloc suivant
            bloc = bloc->NextSiblingElement("Bloc");
        }

        //* 4• Affecter les données au segment
        this->segments[segment_index].setPlatforms(segment_platforms,nPlatforms);
        this->segments[segment_index].setAnimations(segment_animations,nAnimations);

        //* 5• Récupérer le segment suivant
        segment = segment->NextSiblingElement("Segment");
    }

    XMLElement * player_data = root->FirstChildElement("Player");
    // Si player est nullptr, y'a un problème dans le fichier 
    if (player_data == nullptr) exit(XML_ERROR_PARSING_ELEMENT);

    //Récupération des attributs de Player
    int x,y;
    // x
    result = player_data->QueryIntAttribute("x", &x);
    XMLCheckResult(result);
    // y
    result = player_data->QueryIntAttribute("y", &y);
    XMLCheckResult(result);

    this->player.setPosition(Vec2f(x,y));

    this->platforms =   new Platform*[3];
    this->nPlatforms =  new int[3];

    loadFirstSegments();

}

World::World(Segment* segments, int nSegments)
: segments(segments), nSegments(nSegments), 
  score(0), centerLoadedSegment(1)
{
    platforms = new Platform*[3];
    nPlatforms = new int[3];
    //TODO Initialiser le joueur avec une position passée en paramètre
    player = Player();

    loadFirstSegments();
}

World::~World()
{
    for (Animation* anim : animations)
        if (anim->origin_segment == nullptr) delete anim;
    
    if (segments != nullptr)
        delete [] segments;

    if (platforms != nullptr)
        delete [] platforms;

    if (nPlatforms != nullptr)
        delete [] nPlatforms;
}

void World::loadFirstSegments()
{
    Segment* segment;
    Platform* new_platforms;
    Animation** new_animations;
    std::vector<Piece*>* new_pieces;
    int platforms_size;
    int animations_size;

    for (int i = 0; i < 3; i++)
    {
        // On récupère les données du segment
        segment = &segments[i];
        segment->loadPlatforms(new_platforms, platforms_size);
        segment->loadAnimations(new_animations, animations_size);
        new_pieces = segment->getPieces();

        // On charge les plateformes dans World
        platforms[i] = new_platforms;
        nPlatforms[i] = platforms_size;

        // On charge les animations dans World
        for (int j = 0; j < animations_size; j++)
            animations.push_back(new_animations[j]);
        
        // On charge les pieces dans World
        for (int j = 0; j < new_pieces->size(); j++)
            pieces.push_back( (*new_pieces)[j] );
    }
    
    
}

/// Charge le segment précédent et décale les autres dans la structure de donnée
void World::loadPreviousSegment()
{
    /// Déchargement des animations

    // On parcours le vecteur à l'envers pour être sûr
    // d'itérer sur l'intégralité malgré les suppressions
    for (int n = animations.size() - 1; n >= 0; n--)
    {
        Animation* anim = animations[n];
        if( anim->origin_segment == &segments[centerLoadedSegment + 1] )
            animations.erase(animations.begin() + n);
    }

    // Même chose pour les pièces
    for (int n = pieces.size() - 1; n >= 0; n--)
    {
        Piece* piece = pieces[n];
        // On en profite pour retirer les pièces prises
        if ( piece->isTaken() || piece->getOrigin() == &segments[centerLoadedSegment + 1] )
            pieces.erase(pieces.begin() + n);
    } 

    /// Décalage des données
    platforms[2]=platforms[1];
    nPlatforms[2]=nPlatforms[1];
    
    platforms[1]=platforms[0];
    nPlatforms[1]=nPlatforms[0];

    // On charge le segment d'index center-2 dans l'emplacement d'index 0
    segments[centerLoadedSegment-2].loadPlatforms(platforms[0],nPlatforms[0]);

    // On charge les animations
    Animation** new_animations;
    int new_anim_size;
    segments[centerLoadedSegment-2].loadAnimations(new_animations, new_anim_size);

    for (int i = 0; i < new_anim_size; i++)
        animations.push_back(new_animations[i]);

    // On charge les pieces
    std::vector<Piece*>* new_pieces = segments[centerLoadedSegment-2].getPieces();
    for (auto piece : *new_pieces)
        if (!piece->isTaken()) pieces.push_back(piece);

    // On met à jour l'index de segment central
    centerLoadedSegment--; 
}

/// Charge le segment suivant et décale les autres dans la structure de donnée
void World::loadNextSegment()
{
    /// Déchargement des animations

    // On parcours le vecteur à l'envers pour être sûr
    // d'itérer sur l'intégralité malgré les suppressions
    for (int n = animations.size() - 1; n >= 0; n--){
        Animation* anim = animations[n];
        if(anim->origin_segment == &(segments[centerLoadedSegment - 1]))
        {// Si l'objet pointé est le premier du tableau d'animations on s'arrête
            animations.erase(animations.begin() + n);
        }
    }

    // Même chose pour les pièces
    for (int n = pieces.size() - 1; n >= 0; n--)
    {
        Piece* piece = pieces[n];
        // On en profite pour retirer les pièces prises
        if ( piece->isTaken() || piece->getOrigin() == &segments[centerLoadedSegment - 1] )
            pieces.erase(pieces.begin() + n);
    } 

    ///changement de place des references

    platforms[0]=platforms[1];
    nPlatforms[0]=nPlatforms[1];
    
    platforms[1]=platforms[2];
    nPlatforms[1]=nPlatforms[2];

    // On charge le segment d'index center+2 dans l'emplacement d'index 2
    segments[centerLoadedSegment+2].loadPlatforms(platforms[2],nPlatforms[2]);


    // On charge les segments
    Animation** new_animations;
    int new_anim_size;
    segments[centerLoadedSegment+2].loadAnimations(new_animations, new_anim_size);

    for (int i = 0; i < new_anim_size; i++)
        animations.push_back(new_animations[i]);

    // On charge les pieces
    std::vector<Piece*>* new_pieces = segments[centerLoadedSegment+2].getPieces();
    for (auto piece : *new_pieces)
        if (!piece->isTaken()) pieces.push_back(piece);

    // On met à jour l'index de segment central
    centerLoadedSegment++; 
}




void World::testRegression()
{
    //TODO Tester les frames

    cout << "World: constructeur par defaut... " ;
    World w1;
    assert(w1.getPlatforms() == nullptr);
    assert(w1.segments == nullptr);
    assert(w1.nPlatforms == nullptr);
    assert(w1.centerLoadedSegment == 1);
    assert(w1.frameCount == 0);
    assert(w1.score == 0);
    cout << "OK" << endl;

    //TODO Implémenter le test du constructeur par fichier
    cout << "World: constructeur par fichier... " ;

    /*World w3("data/levels/example_level.xml");
    assert(w3.score == 0);
    assert(w3.frameCount == 0);
    assert(w3.getPlatforms() != nullptr);
    assert(w3.getPlatformsSizes() != nullptr);
    assert(w3.segments != nullptr);
    assert(w3.nSegments == 6);*/
    

    cout << "WIP" << endl;

    cout << "World: constructeur par segment... ";

    Segment * s = nullptr;
    s = new Segment[5];
    World w2(s, 5);
    assert(w2.getPlatforms() != nullptr);
    assert(w2.getPlatformsSizes() != nullptr);
    assert(w2.segments != nullptr);
    assert(w2.nSegments == 5);
    assert(w2.score == 0);

    cout << "OK" << endl;

    cout << "World: Player du constructeur par segment:" << endl;
    w2.getPlayer().testRegression();
    w2.setPlayerInputs(Player::RIGHT);
    assert(w2.player.checkInput(Player::RIGHT));
    cout << "OK" << endl;

    cout << "World: segments... ";
    //TODO test regression de load segment
    cout << "WIP" << endl;

    cout << "World: step...";
    //TODO test regression de step
    cout << "WIP" << endl;

    cout << "World: des autres getters...";
    assert(getScore() == 0);
    score++;
    assert(getScore() == 1);
    w2.segmentWidth = 1;
    assert(w2.getWorldEnd() == w2.nSegments * w2.segmentWidth);
    cout << "OK" << endl;

}

Platform** World::getPlatforms() const { return platforms; }

const int* World::getPlatformsSizes() const { return nPlatforms; }


const Player& World::getPlayer() const { return player; }

int World::getScore() const { return score; }

const std::vector<Piece*>& World::getPieces() const { return pieces; }

int World::getWorldEnd() const { return (nSegments) * segmentWidth; }

const Entity& World::getGoal() const { return goal; }

void World::setPlayerInputs(uint16_t input_mask) { player.addInput(input_mask); }

void World::step()
{
    // 3• On applique l'update physique:

    // 3.1• Si le joueur va à droite/gauche: incrémenter/décrémenter la position en x
    if (player.checkInput(Player::RIGHT)) player.moveRight();

    if (player.checkInput(Player::LEFT)) player.moveLeft();

    if (player.checkInput(Player::DOWN) && !player.isInAir())
        player.setHeight(1);
    else
        player.setHeight(2);

    // 3.2• Si le joueur saute, on met in_air à true et on incrémente la position en y
    if (player.checkInput(Player::JUMP)) 
    {
        if(!player.isInAir())
            player.jump();
        else if (player.jumpsAvailable() < 20)
            player.jump();
    }
    // 3.3• Si le joueur ne saute pas, vérifier la présence d'une plateforme en dessous:
    //else
    //{

        bool on_platform = false;

        for (int i=0; i < 3; i++)
        {
            for (int j = 0; j < nPlatforms[i]; j++)
            {
                if (Hitbox::overlaping( // Si il y a collision entre...
                    player.getHitbox().bottom(0.05f),         // Juste sous le joueur
                    platforms[i][j].getHitbox().upper(0.2f)   // La partie haute de la plateforme
                    ))
                {
                    // 3.3.1• Si il y a une plateforme, fixer la position du joueur à sa hauteur
                    Platform& platform = platforms[i][j];
                    on_platform = true;
                    player.setPosition({
                        player.getPosition().x,
                        platform.getPosition().y + platform.getHeight()
                    });
                    break;
                }
            }
            if (on_platform) break;
        }
        // 3.3.1• Sinon, tomber
        if (!on_platform) player.fall();
        else 
        {
            player.setInAir(false);
            player.jumpReset();
        }
	//}

    player.clearAllInputs();

    //4• Collectage des pièces
    Piece* piece = nullptr;
    for (int i = pieces.size() - 1; i >= 0; i--)
    {
        piece = pieces[i];
        if (!piece->isTaken())
        {
            // Si le joueur touche la pièce
            if (Hitbox::overlaping(piece->getHitbox(), player.getHitbox()))
            {
                // Marquer la pièce comme prise
                pieces[i]->setTaken(true);

                // Et augmenter le score du joueur
                score++;
            }
        }
    }

    //5• On a gagné?
    if (Hitbox::overlaping(player.getHitbox(), goal.getHitbox()))
    {
        //TODO On a gagné
        cout << "victoire";
    }

    // Si le joueur tombe du niveau, perdre une vie.
    //FIXME Actuellement, les segments sont chargés et déchargés jusqu'à atteindre le début
    if (player.getPosition().y < 0 
        || player.getPosition().x < 0 
        || player.getPosition().y > 25
        || player.getPosition().x > getWorldEnd())
    {
        Vec2f posInitiale;
        posInitiale.x=1;
        posInitiale.y=1;
        player.removeLife();
        player.setPosition(posInitiale);
        cout << "Nombre de vies:" << player.getLives() << endl;
        loadFirstSegments();
    }
    

    //TODO Si le joueur n'a plus de vie: perdre
    if (player.getLives() == 0)
    {
        //TODO Completer
    }

    //5• Chargement/Déchargement de segments
    
    if (centerLoadedSegment < nSegments - 2 
        && 
        player.getPosition().x > (centerLoadedSegment + 1) * segmentWidth)
    {
        loadNextSegment();
    }

    if (centerLoadedSegment > 1
        && player.getPosition().x < (centerLoadedSegment) * segmentWidth)
    {
        loadPreviousSegment();
    }

    //6• Incrémenter le compteur de frames
    frameCount++;
}
