#ifndef OBJECTS_H
#define OBJECTS_H

#include "Entity.h"

class Platform : public Entity
{
private:
    /* data */
public:
    Platform();
    Platform(Vec2f pos, float width, float height, float angle);
    ~Platform();
    // void testRegression();
};

class Piece : public Entity
{
    private:
        /// L'adresse du segment d'origine de la pièce
        void* origin;
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