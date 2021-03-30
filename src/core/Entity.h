#ifndef ENTITY_H
#define ENTITY_H

#include "extern/vector2d.h"

/// \brief Classe universelle d'entité
/** 
 * La Classe dont héritent toutes les entités compatibles avec le module Animation
 **/
class Entity
{
private:
    ///? On pourrait ajouter un membre statique (commun à tous les instances de Entity)
    ///? et un constant pour avoir des IDs d'objet comme ceci:
    ///? static int last_ID;
    ///? const int ID;

    ///Position de l'objet
    Vec2f pos;
    ///Vitesse de l'objet (si appliquable)
    Vec2f vel;
    ///Dimensions de l'objet
    float width, height;
    ///Inclinaison de l'objet
    float angle;
public:
    /** \brief constructeur de Entity
     * Ce constructeur ne devrait pas être utilisé en dehors d'une classe héritant de Entity
     * \param pos Position de l'objet
     * \param width Largeur de l'objet
     * \param height Hauteur de l'objet
     * \param angle Inclinaison de l'objet
     **/
    Entity();
    Entity(Vec2f pos, float width, float height, float angle);
    ~Entity();
    void testRegression();

    /// \brief Renvoie la position de l'objet
    Vec2f   getPosition() const;
    /// \brief Remplace la position de l'objet par celle donnée
    void    setPosition(Vec2f newpos);

    /// \brief Renvoie la vitesse de l'objet (si appliquable)
    Vec2f   getVelocity() const;
    /// \brief Remplace la vitesse de l'objet par celle donnée (si appliquable)
    void    setVelocity(Vec2f newvel);

    /// \brief Renvoie l'inclinaison (en radians) de l'objet
    float   getAngle() const;
    /// \brief Remplace l'inclinaison (en radians) de l'objet par celle donnée
    void    setAngle(float newangle);

    /// \brief Renvoie la largeur de l'objet
    float   getWidth() const;
    /// \brief Remplace la largeur de l'objet par celle donnée
    void    setWidth(float newwidth);

    /// \brief Renvoie la hauteur de l'objet
    float   getHeight() const;
    /// \brief Remplace la hauteur de l'objet par celle donnée
    void    setHeight(float newheight);

    /// \brief Ajoute la force donnée à la vitesse de l'objet (si appliquable)
    void    applyForce(Vec2f force);
    /// \brief Ajoute le mouvement donné à la position de l'objet
    void    move(Vec2f offset);
    /// \brief Ajoute l'angle donné (en radians) à l'inclinaison de l'objet 
    void    rotate(float angle);

    /// \brief Vérifie s'il y a une superposition entre deux entités
    bool    superposition(Entity ent2);
};




#endif //ENTITY_H
