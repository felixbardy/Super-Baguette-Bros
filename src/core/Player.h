#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

/// TODO Fixer clairement à quoi ressemblent les contrôles du joueur avant de l'implémenter

class Player : public Entity
{
private:

    /// Indique si le joueur est dans l'air
    bool in_air;

    /// Indique si le joueur est en train de sauter
    bool jumping;

    /// Stocke les masques passés comme input
    uint16_t current_input;

public:

    /// Constructeur par défaut de Player
    Player();
    /// Destructeur de Player
    ~Player();

    /** \brief Modifie la position du joueur lors d'un deplacement à gauche
     * \param pos La position initiale du joueur
     **/
    void moveLeft();

    /** \brief Modifie la position du joueur lors d'un deplacement à droite
     * \param pos La position initiale du joueur
     **/
    void moveRight();

    /** \brief Modifie la position du joueur lors d'un saut
     * \param pos La position initiale du joueur
     **/
    void jump();

    /// Retourne la valeur de jumping
    bool isJumping();

    /// Retourne la valeur de in_air
    bool isInAir();

    /** \brief Permet d'activer les inputs voulus du joueur
     * \param mask Le masque représentant les inputs à activer
     **/
    void addInput(uint16_t mask);

    /** \brief Permet de désactiver les inputs voulus du joueur
     * \param mask Le masque représentant les inputs à désactiver
     **/
    void clearInput(uint16_t mask);

    /** \brief Renvoie vrai si les inputs passés sont activés
     * \param mask Le masque représentant les inputs à vérifier
     **/
    bool checkInput(uint16_t mask);

    /// Désactive tous les inputs du joueur
    void clearAllInputs();

    /// Une suite de tests pour s'assurer du bon fonctionnement de Player
    void testRegression();

    // Masques d'input
    // Masques
    static const uint16_t JUMP     = 1 << 0; // = 0x0...01
    static const uint16_t DOWN     = 1 << 1; // = 0x0...10
    static const uint16_t UP       = 1 << 2; // etc...
    static const uint16_t LEFT     = 1 << 3;
    static const uint16_t RIGHT    = 1 << 4;
    // Il reste de la place pour encore 11 inputs (ex: attaque)

};



#endif //PLAYER_H
