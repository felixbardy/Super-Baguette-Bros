#include "World.h"

#include <assert.h>

#include "extern/tinyxml2.h"

World::World()
: platforms(nullptr), segments(nullptr),
 nPlatforms(nullptr), centerLoadedSegment(1)
{
    
}

World::World(std::string filename)
: platforms(nullptr), segments(nullptr),
 nPlatforms(nullptr)
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

            // 1.5.2• Affecter la nouvelle plateforme
            segment_platforms[platform_index] = Platform(Vec2f(x,y),width,height,angle);

            // 1.5.3• Récupérer la prochaine plateforme (= nullptr à la fin)
            platform = platform->NextSiblingElement("Platform");
        }
        }

        //* 2• Récupérer les animations
        //TODO Récupérer les animations

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
                    Vec2f(start_x, start_y),
                    Vec2f(mov_x, mov_y),
                    speed,
                    true
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
        }

        }

        //* 3• Affecter les données au segment
        this->segments[segment_index].setPlatforms(segment_platforms,nPlatforms);
        //FIXME Remplacer 0 par le nombre d'animations
        this->segments[segment_index].setAnimations(segment_animations,nAnimations);

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
: segments(segments), nSegments(nSegments), centerLoadedSegment(1)
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


void World::loadPreviousSegment()
{
    /// test si le premier segment charger est deja le premier du niveau 
    if(centerLoadedSegment > 1)
    {

        ///unload des animations

        /// methode inneficace (peut etre utile pour debug la version + rapide)
        /*

        int n=0;
        for (Animation* anim : animations){
            if((anim->object>platforms[2])&
            (anim->object<(platforms[2]+(nPlatforms[2]*sizeof(Platform)))))
            {
                animations.erase(animations.begin() + n);
            }
            n++;
        }

        */

        /// Méthode alternative (+ rapide)

        //! Cette méthode repose sur le fait que toutes les animations
        //! chargées depuis un segment ont des indexs adjacents dans le vecteur
        int n=0;
        for (Animation* anim : animations)
        {
            if( anim->object == platforms[2] )
            {// Si l'objet pointé est le premier du tableau d'animations on s'arrête
                break;
            }
            n++;
        }
        animations.erase(animations.begin() + n, animations.begin() + n + segments[centerLoadedSegment+1].getNAnimation());

        /// Décalage des données

        platforms[2]=platforms[1];
        platforms[1]=platforms[0];
        
        nPlatforms[2]=nPlatforms[1];
        nPlatforms[1]=nPlatforms[0];
        segments[centerLoadedSegment-2].loadPlatforms(platforms[0],nPlatforms[0]);

        //TODO Charger les nouvelles animations


    }

}

/// quasiment identique a loadPreviousSegments
void World::loadNextSegment()
{
    /// test si le dernier segment charger est deja le dernier du niveau
    if(centerLoadedSegment < nSegments-2)
    {

        ///unload des animations

        /// methode inneficace (peut etre utile pour debug la version + rapide)
        /*

        int n=0;
        for (Animation* anim : animations){
            if((anim->object>platforms[0])&
            (anim->object<(platforms[0]+(nPlatforms[0]*sizeof(Platform)))))
            {
                animations.erase(animations.begin() + n);
            }
            n++;
        }

        */

        ///methode alternative (+ rapide)

        //! Cette méthode repose sur le fait que toutes les animations
        //! chargées depuis un segment ont des indexs adjacents dans le vecteur
        int n=0;
        for (Animation* anim : animations){
            if(anim->object == platforms[0])
            {// Si l'objet pointé est le premier du tableau d'animations on s'arrête
                break;
            }
            n++;
        }
        animations.erase(animations.begin() + n, animations.begin() + n + segments[centerLoadedSegment-1].getNAnimation());

        ///changement de place des references

        platforms[0]=platforms[1];
        platforms[1]=platforms[2];
        
        nPlatforms[0]=nPlatforms[1];
        nPlatforms[1]=nPlatforms[2];
        segments[centerLoadedSegment+2].loadPlatforms(platforms[2],nPlatforms[2]);




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

        for (int i=0; (i<3) & (on_platform==0) ;i++)
        {
            for (int j = 0; j < *nPlatforms; j++)
            {
                // 3.3.1• Sinon, décrémenter la position en y
                if (player.superposition(platforms[i][j])) on_platform=1;

            }
        }
        if (!on_platform) player.fall();
	}

    player.clearAllInputs();
}