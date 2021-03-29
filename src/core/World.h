#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "Player.h"
#include "Segment.h"


class World
{
private:
    /// Le joueur
    Player player;

    Segment* segments;
    int nSegments;
    int last_loaded_segment;

    //? IDEE: -platforms est un tableau 2D stockant les n segments chargés (à priori 3)
    //?       -pour savoir si une animation doit être supprimée, il suffit de regarder
    //?        si l'objet pointé est dans la plage d'adresse du tableau de plateformes remplacé
    Platform** platforms;
    int* nPlatforms;

    //? Ajouter une liste pour d'autres entités

    //! A chaque suppression d'animation de ce vector: FAIRE UN delete SUR LE POINTEUR
    /// Tableau dynamique stockant les pointeurs vers les Animations
    std::vector<Animation*> animations;

    /// Charge les 3 premiers segments
    void loadFirstSegments();
    //TODO Implémenter des méthodes pour le chargement des segments
    //? Soit des méthodes du genre 'chargerSuivant()' et 'chargerPrecedant()'
    //? Soit 'chargerSegment(int from, int to)' (from: index dans 'segments', to: index dans 'platforms')

public:
    //TODO Définir un constructeur par flux de fichier pour pouvoir charger un niveau 
    /// Constructeur par défaut (objet inutilisable)
    World();
    /// Constructeur par données 
    World(Segment* segments, int nSegments);
    ~World();
    void testRegression();

    //FIXME Les 2 getters sont une solution moche, on peut sûrement trouver mieux

    /// Retourne le tableau 2D contenant les plateformes chargées
    Platform** getPlatforms() const;

    /// Retourne les tailles des tableaux de plateformes
    const int* getPlatformsSizes() const;

    /// Retourne une référence vers le Player
    const Player& getPlayer() const;

    /** \brief Passe l'input au Player pour l'nterpréter lors de la prochaine boucle
     * \param input_mask Le masque représentant les inputs à activer
     **/
    void setPlayerInputs(uint16_t input_mask);


};



#endif //WORLD_H