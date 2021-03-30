#include "World.h"

#include <assert.h>

#include "extern/tinyxml2.h"

World::World()
: platforms(nullptr), segments(nullptr),
 nPlatforms(nullptr), last_loaded_segment(-1)
{
}

World::World(std::string filename)
: platforms(nullptr), segments(nullptr),
 nPlatforms(nullptr), last_loaded_segment(-1)
{
    //FIXME Les erreurs qui stoppent l'exécution dans XMLCheckResult ou dans exit(...)
    //      devraient être remplacées par une non-confirmation de l'initialistion de World
    //      ou au moins donner un contexte plus clair..;
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

    // Récupérer la liste des segments
    XMLElement* segment_list = root->FirstChildElement("Segments");
    // S'il est inexistant, go back to Orang-outan...
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

    for (int segment_index = 0; segment_index < nSegments; segment_index++)
    {   
        //* RÉCUPÉRATION DE SEGMENT *//
        //* 1• Récupérer les platformes
        // 1.1• Récupérer l'élément Platforms
        XMLElement * platform_list = segment->FirstChildElement("Platforms");
        // Si elles n'existent pas, on est dans le caca...
        if (segment_list == nullptr) exit(XML_ERROR_PARSING_ELEMENT);

        // 1.2• Récupérer la taille du tableau
        result = segment_list->QueryIntAttribute("count", &count);
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

            segment_platforms[platform_index] = Platform(Vec2f(x,y),width,height,angle);

            // 1.5.2• Récupérer la prochaine plateforme (= nullptr à la fin)
            platform = platform->NextSiblingElement("Platform");
        }
        }

        //* 2• Récupérer les animations
        //TODO Récupérer les animations
        //? Cache misère en attendant l'implémentation
        Animation** segment_animations = new Animation*[0];

        //* 3• Affecter les données au segment
        this->segments[segment_index].setPlatforms(segment_platforms,nPlatforms);
        //FIXME Remplacer 0 par le nombre d'animations
        this->segments[segment_index].setAnimations(segment_animations,0);

        //* 3• Récupérer le segment suivant
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
: segments(segments), nSegments(nSegments)
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
        if (!anim->from_segment) delete anim;
    
    if (segments != nullptr)
        delete [] segments;

    if (platforms != nullptr)
        delete platforms;

    if (nPlatforms != nullptr)
        delete [] nPlatforms;
}

void World::loadFirstSegments()
{
    Segment* segment;
    Platform* new_platforms;
    Animation** new_animations;
    int platforms_size;
    int animations_size;

    for (int i = 0; i < 3; i++)
    {
        // On récupère les données du segment
        segment = &segments[i];
        segment->loadPlatforms(new_platforms, platforms_size);
        segment->loadAnimations(new_animations, animations_size);

        // On charge les plateformes dans World
        platforms[i] = new_platforms;
        nPlatforms[i] = platforms_size;

        // Et on charge les animations dans World
        for (int j = 0; j < animations_size; j++)
            animations.push_back(new_animations[j]);
    }
    
}

void World::testRegression()
{
    // TODO Implémenter le test de régression de World
}

Platform** World::getPlatforms() const
{
    return platforms;
}

const int* World::getPlatformsSizes() const
{
    return nPlatforms;
}


const Player& World::getPlayer() const{
    return player;
}

void World::setPlayerInputs(uint16_t input_mask)
{
    player.addInput(input_mask);
}

void World::step()
{
    // 3• On applique l'update physique:

    // 3.1• Si le joueur va à droite/gauche: incrémenter/décrémenter la position en x
    if (player.checkInput(Player::RIGHT)) player.moveRight();

    if (player.checkInput(Player::LEFT)) player.moveLeft();

    // 3.2• Si le joueur saute, on met in_air à true et on incrémente la position en y
    if (player.checkInput(Player::JUMP)) player.jump();
    // 3.3• Si le joueur ne saute pas, vérifier la présence d'une plateforme en dessous:
    else
    {
        // 3.3.1• Si il y a une plateforme, fixer la position du joueur à sa hauteur*

        bool on_platform = 0;

        for (int i=0;i<3;i++)
        {
            for (int j = 0; j < *nPlatforms; j++)
            {
                // 3.3.1• Sinon, décrémenter la position en y
                //TODO optimiser la fonction avec arret auto quand on_platform=1;
                if (player.superposition(platforms[i][j])) on_platform=1;

            }
        }
        if (!on_platform) player.fall();
	}

    player.clearAllInputs();
}