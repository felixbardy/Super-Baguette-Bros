#ifndef ANIMATION_H
#define ANIMATION_H

#include "Entity.h"

/// TODO Implémenter l'animation après Entity

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
    ///? Peut être remplacé par un ID
    Entity* object;
    AnimationType type;
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
LinearAnimation create_linear_animation(Entity* object, Vec2f start_point, Vec2f movement, float speed);

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
RotationAnimation create_rotation_animation(Entity* object, float start_angle, float rotation_speed);

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
BouncyAnimation create_bouncy_animation(Entity* object, float rebound_height, float rebound_width, int max_bounces);

struct PhysicAnimation : Animation
{
    /// Accélération
    Vec2f acc;
    /// Tendance à rebondir (0 (arrêt immédiat) -> 1 (pas de perte d'énergie))
    float bounciness;
    ///TODO Ajouter des caractéristiques
};

/** \brief Renvoie une structure d'animation physique avec les paramètres donnés
 * \param object L'objet auquel associer l'animation
 * \param acceleration L'acceleration constante à appliquer à l'objet (habituellement la gravité)
 * \param bounciness La propention de l'objet à rebondir (de 0 à 1)
 **/
PhysicAnimation create_physic_animation(Entity* object, Vec2f acceleration, float bounciness);

///TODO Ajouter des types d'animation si besoin

#endif //ANIMATION_H