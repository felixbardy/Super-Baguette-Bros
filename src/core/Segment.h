#ifndef SEGMENT_H
#define SEGMENT_H

#include "Animation.h"
#include "Platform.h"

class Segment
{
private:
    //? Ajouter un ID de Segment répercuté sur les Entités / Animations
    //? permettrait de savoir quoi supprimer pour décharger le Segment
    //! Pas besoin d'ID pour l'instant 
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
    ///Constructeur par défaut, le segment est inutilisable tel quel.
    Segment();
    /// Constructeur par données. Une fois les pointeurs passées, l'objet se charge de la destruction
    Segment(Platform* platforms, int nPlatforms,  Animation* animations, int nAnimations);
    /// Destructeur 
    ~Segment();
    void testRegression();

    //TODO Définir des getters pour pouvoir charger le segment avec World
};

#endif //SEGMENT_H