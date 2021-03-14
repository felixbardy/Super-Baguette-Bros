#ifndef ENTITY_H
#define ENTITY_H

#include "vector2D.h"

class Entity
{
private:
    ///? On pourrait ajouter un membre statique (commun à tous les instances de Entity)
    ///? et un constant pour avoir des IDs d'objet comme ceci:
    ///? static int last_ID;
    ///? const int ID;
    Vec2f pos;
    Vec2f vel;
    float width, height;
    float angle;
public:
    Entity(Vec2f pos, float width, float height, float angle);
    ~Entity();

    Vec2f   getPosition() const;
    void    setPosition(Vec2f newpos);

    Vec2f   getVelocity() const;
    void    setVelocity(Vec2f newvel);

    float   getAngle() const;
    void    setAngle(float newangle);

    float   getWidth() const;
    void    setWidth(float newwidth);

    float   getHeight() const;
    void    setHeight(float newheight);


    void    applyForce(Vec2f force);
    void    move(Vec2f offset);
    void    rotate(float angle);
};




#endif //ENTITY_H