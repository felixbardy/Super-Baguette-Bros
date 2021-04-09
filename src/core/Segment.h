#ifndef SEGMENT_H
#define SEGMENT_H

#include "Animation.h"
#include "Platform.h"

class Segment
{
private:
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
    
    /** \brief Renvoie le tableau de plateformes et sa taille en données-résultat
     * \param platforms pointeur auquel affecter le tableau
     * \param size entier auquel affecter la taille du tableau
     **/
    void loadPlatforms(Platform*& platforms, int& size);

    /** \brief Renvoie le tableau de pointeurs d'Animations et sa taille en données-résultat
     * \param platforms pointeur auquel affecter le tableau
     * \param size entier auquel affecter la taille du tableau
     **/
    void loadAnimations(Animation**& animations, int& size);

    /// Retourne la taille du tableau d'Animations du Segment
    int getNAnimation();
};

#endif //SEGMENT_H