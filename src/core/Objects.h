#ifndef OBJECTS_H
#define OBJECTS_H

#include "Entity.h"

/** \class Platform Objects.h "src/core/Objects.h"
 * \brief représente une plateforme
 * 
 * Cette classe est un simple alias de Entity avec un constructeur plus restreint 
 * destinée à représenter une plateforme
 **/
class Platform : public Entity
{
private:
    /* data */
public:
    /// Constructeur par défaut de Platform
    Platform();

    /** \brief Constructeur de Platform
     * \param pos La position de la plateforme
     * \param width La longueur de la plateforme
     * \param height La heuteur de la plateforme
     * \param angle L'angle de la plateforme (rotation centrée)
     **/
    Platform(Vec2f pos, float width, float height, float angle);

    /// Destructeur de Platform
    ~Platform();
    // void testRegression();
};

/** \class Piece Objects.h "src/core/Objects.h"
 * \brief représente une pièce
 * 
 * Cette classe représente une pièce, elle ajoute aux attributs de Entity deux données:<br>
 * <ul>
 * <li>Piece::origin : L'adresse du segment d'origine (définie à la création)</li>
 * <li>Piece::taken : Un booléen indiquant si la pièce a déjà été collectée</li>
 * </ul>
 * 
 * La classe a un constructeur très simple, à l'image de la structure nécéssaire.
 **/
class Piece : public Entity
{
    private:
        /// L'adresse du segment d'origine de la pièce
        void* origin;
        /// Indique si la pièce a été collectée
        bool taken;
    public:
        /// Constructeur par défaut
        Piece();

        /** \brief Constructeur de Piece
         * \param pos la position de la Piece
         * \param origin_segment l'adresse du segment parent
         **/
        Piece(Vec2f pos, void* origin_segment);

        /// Destructeur de Piece
        ~Piece();

        /// Renvoie l'adresse du segment d'origine de la pièce
        void* getOrigin() const;

        /// Définit l'état "pris" de la pièce
        void setTaken(bool state);

        /// Renvoie l'état "pris" de la pièce
        bool isTaken() const;
};



#endif //OBJECTS_H