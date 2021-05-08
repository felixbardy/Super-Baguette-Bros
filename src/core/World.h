#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <vector>

#include "Player.h"
#include "Segment.h"


class World
{
private:
    /// Le joueur
    Player player;

    // Le score du joueur
    int score;

    /// Tableau de segments prechargés
    Segment* segments;
    
    /// Taille du tableau de segments
    int nSegments;

    /// Index du segment central parmis ceux actuellement chargés
    int centerLoadedSegment;

    /// Largeur d'un segment
    float segmentWidth;

    /// Tableau 2D mettant en relation les plateformes des segments avec World
    Platform** platforms;

    /// Tableau stockant les tailles des tableaux de segments
    int* nPlatforms;

    /// Contient les pièces actuellement chargées
    std::vector<Piece*> pieces;

    //? Ajouter une liste pour d'autres entités

    /// Tableau dynamique stockant les pointeurs vers les Animations
    std::vector<Animation*> animations;

    /// Charge les 3 premiers segments
    void loadFirstSegments();

    /// Décale les segments chargés vers le début du niveau (si un segment plus proche du debut existe) 
    void loadPreviousSegment();

    /// Décale les segments chargés vers la fin du niveau (si un segment plus loin du debut existe) 
    void loadNextSegment();

public:
    /// Constructeur par défaut (objet inutilisable)
    World();
    /// Constructeur par fichier
    World(std::string filename);
    /// Constructeur par données 
    World(Segment* segments, int nSegments);
    ~World();
    void testRegression();

    //FIXME Les 2 getters sont une solution moche, on peut sûrement trouver mieux

    /// Retourne le tableau 2D contenant les plateformes chargées
    Platform** getPlatforms() const;

    /// Retourne les tailles des tableaux de plateformes
    const int* getPlatformsSizes() const;

    /// Retourne une référence du Player
    const Player& getPlayer() const;

    /// Renvoie une référence du vecteur de pieces
    const std::vector<Piece*>& getPieces() const;

    // Renvoie la longueur totale du niveau
    int getWorldEnd() const;

    /** \brief Passe l'input au Player pour l'nterpréter lors de la prochaine boucle
     * \param input_mask Le masque représentant les inputs à activer
     **/
    void setPlayerInputs(uint16_t input_mask);

    /// Exécute une frame dans le monde
    void step();
};



#endif //WORLD_H