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
    Animation** animations;
    /// Nombre d'animations associées au segment
    int nAnimations;
public:
    ///Constructeur par défaut, le segment est inutilisable tel quel.
    Segment();
    /// Constructeur par données. Une fois les pointeurs passées, l'objet se charge de la destruction
    Segment(Platform* platforms, int nPlatforms,  Animation** animations, int nAnimations);
    /// Destructeur 
    ~Segment();
    /// Suite de tests pour s'assurer du bon fonctionnement de Segment
    void testRegression();

    /** \brief Passe le tableau de plateformes déjà alloué au Segment
     * \param platforms pointeur vers les plateformes
     * \param size taille du tableau à charger
     **/
    void setPlatforms(Platform* platforms, int size);

    /** \brief Passe le tableau d'Animations déjà alloué  au Segment
     * \param animations pointeur vers le tableau d'Animations
     * \param size taille du tableau à charger
     **/
    void setAnimations(Animation** animations, int size);
    

    void loadPlatforms(Platform*& platforms, int& size);

    void loadAnimations(Animation**& animations, int& size);
};

#endif //SEGMENT_H