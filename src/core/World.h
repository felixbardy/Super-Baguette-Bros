#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "Player.h"
#include "Animation.h"
#include "Platform.h"

/// TODO Implémenter World en dernier lieu
//? Placer Segment dans un fichier séparé serait une bonne idée

class Segment
{
private:
    //? Ajouter un ID de Segment répercuté sur les Entités / Animations permettrait de savoir quoi supprimer pour décharger le Segment
    //? static int ID;
    /// Tableau des plateformes associées au segment
    Platform* platforms;
    /// Nombre de plateformes associées au segment
    int nPlatforms;
    /// Tableau des animations associées au segment
    Animation* animations;
    /// Nombre d'animations associées au segment
    int nAnimations;
public:
    // TODO Définir un constructeur par flux de fichier pour charger le segment depuis un fichier de niveau
    /// Constructeur par données
    Segment(Platform* platforms, Animation* animations);
    /// Destructeur 
    ~Segment();
    void testRegression();
};

class World
{
private:
    /// Le joueur
    Player player;

    Segment* segments;
    int nSegments;

    // TODO Décider de la meilleure façon de stocker les plateformes
    //! Les plateformes doivent avoir des adresses fixes
    //? IDEE: -platforms est un tableau 2D stockant les n segments chargés (à priori 3)
    //?       -pour savoir si une animation/entité doit être supprimée, il suffit de regarder
    //?        si l'objet pointé est dans la plage d'adresse du tableau de plateformes remplacé
    Platform* platforms;
    int nPlatforms;

    //? Ajouter une liste pour d'autres entités

    //! A chaque suppression d'animation de ce vector: FAIRE UN delete SUR LE POINTEUR
    /// Tableau dynamique stockant les pointeurs vers les Animations
    std::vector<Animation*> animations;

public:
    World(/* args */);
    ~World();
    void testRegression();
};



#endif //WORLD_H