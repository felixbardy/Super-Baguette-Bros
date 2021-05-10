#ifndef ANIMATION_H
#define ANIMATION_H

#include "Entity.h"

enum AnimationType
{
    ///* Ordonner les types d'animation par priorité pour pouvoir les comparer simplement
    ///* si l'ordre devient important un jour
    ///* Ex: GRAVITY < BOUNCY donc on exécute GRAVITY puis BOUNCY
    LINEAR,
    ROTATION,
    BOUNCY,
    PHYSIC
};

struct Animation
{
    // Pointeur vers 'objet affecté par l'animation
    Entity* object;
    // Type de l'animation
    AnimationType type;
    // L'adresse du segment ayant créé l'animation (ou nullptr si elle a été créée autrement)
    void* origin_segment;
};

//* * * * * * * * * * * * *//
//* ANIMATION STRUCTURES  *//
//* * * * * * * * * * * * *//
//? L'idée ici est de créer des structures dérivées de Animation
//? qui soient spécifiques à chaque type d'animation pour ne pas
//? s'encombrer de paramètres inutiles à telle ou telle animation

struct LinearAnimation : Animation
{
    /// Le point de départ de l'animation
    Vec2f start_point;
    /// Le point d'arrivée relatif à la position de départ
    Vec2f movement;
    /// La vitesse de déplacement de l'objet
    float speed;
};

/** \brief Renvoie une structure d'animation linéaire avec les paramètres donnés
 * \param object L'objet auquel associer l'animation
 * \param start_point Le point de départ de l'objet
 * \param movement Le mouvement de l'objet
 * \param speed La vitesse de déplacement de l'objet
 **/
LinearAnimation createLinearAnimation( Entity* object, Vec2f start_point, Vec2f movement, float speed, void* origin_segment = nullptr );

struct RotationAnimation : Animation
{
    /// Angle initial de l'objet
    float start_angle;
    /// La vitesse de rotation (peut être négative)
    float rotation_speed;
};

/** \brief Renvoie une structure d'animation rotative avec les paramètres donnés
 * \param object L'objet auquel associer l'animation
 * \param start_angle L'inclinaison initiale de l'objet
 * \param rotation_speed La vitesse de rotation de l'objet (négative pour le sens horaire)
 **/
RotationAnimation createRotationAnimation(Entity* object, float start_angle, float rotation_speed, void* origin_segment = nullptr );

struct BouncyAnimation : Animation
{
    /// La hauteur d'un rebond
    float height;
    /// La longueur d'un rebond
    float width;
    /// Nombre max de rebonds
    int max_bounces;
    /// Nombre de rebonds déjà effectués
    int bounces;
};

/** \brief Renvoie une structure d'animation de rebond avec les paramètres donnés
 * \param object L'objet auquel associer l'animation
 * \param rebound_height La hauteur d'un rebond
 * \param rebound_width La longueur d'un rebond
 * \param max_bounces Le nombre de rebonds avant disparition de l'objet
 **/
BouncyAnimation createBouncyAnimation(Entity* object, float rebound_height, float rebound_width, int max_bounces, void* origin_segment = nullptr );

struct PhysicAnimation : Animation
{
    /// Accélération
    Vec2f acc;
    /// Tendance à rebondir (0 (arrêt immédiat) -> 1 (pas de perte d'énergie))
    float bounciness;
};

/** \brief Renvoie une structure d'animation physique avec les paramètres donnés
 * \param object L'objet auquel associer l'animation
 * \param acceleration L'acceleration constante à appliquer à l'objet (habituellement la gravité)
 * \param bounciness La propention de l'objet à rebondir (de 0 à 1)
 **/
PhysicAnimation createPhysicAnimation(Entity* object, Vec2f acceleration, float bounciness, void* origin_segment = nullptr );

void testRegressionAnimations();

#endif //ANIMATION_H