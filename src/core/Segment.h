#ifndef SEGMENT_H
#define SEGMENT_H

#include "Animation.h"
#include "Platform.h"

class Segment
{
private:
    //? Ajouter un ID de Segment répercuté sur les Entités / Animations permettrait de savoir quoi supprimer pour décharger le Segment
    //? static int ID;
    /// Position de debut du segment
    int debut;
    /// Position de fin du segment
    int fin;
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
    ///Constructeur par défaut
    Segment();
    /// Constructeur par données
    Segment(Platform* platforms, int nPlatforms,  Animation* animations, int nAnimations);
    /// Destructeur 
    ~Segment();
    void testRegression();
};

#endif //SEGMENT_H