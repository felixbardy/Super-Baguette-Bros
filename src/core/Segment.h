#ifndef SEGMENT_H
#define SEGMENT_H

#include <vector>

#include "Animation.h"
#include "Objects.h"

/** \class Segment Segment.h "src/core/segment.h"
 * \brief représente une portion d'un niveau
 * 
 * Un Segment est une portion de niveau.<br>
 * Il s'agit d'une classe de stockage qui contient 
 * les plateformes, pièces, animations et autres entités
 * de sa section du niveau.<br>
 * Il sera chargé et déchargé au besoin par World 
 * pour alléger les calculs en évitant par exemple 
 * d'avoir à détécter les collisions entre le joueur au début
 * et une plateforme en bout de niveau.
 * 
 **/
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
    /// Les pièces du segment
    std::vector<Piece*> pieces;
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
    
    /** \brief Ajoute une pièce de coordonée x,y au segment
     * \param x position en x de la pièce
     * \param y position en y de la pièce
     **/
    void addPiece(int x, int y);

    /// Renvoie un pointeur vers le vecteur de pieces du segment
    vector<Piece*>* getPieces();
};

#endif //SEGMENT_H