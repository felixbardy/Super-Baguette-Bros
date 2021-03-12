#ifndef ENTITY_H
#define ENTITY_H

/// TODO Écrire la déclaration de Entity

/// FIXME Trouver ou coder une vraie classe de vecteurs
struct vec2D
{
        
};

class Entity
{
private:
    ///? On pourrait ajouter un membre statique (commun à tous les instances de Entity)
    ///? et un constant pour avoir des IDs d'objet comme ceci:
    ///? static int last_ID;
    ///? const int ID;
    vec2D pos;
    vec2D vel;
    float width, height;
    float angle;
public:
    Entity(vec2D pos, float width, float height, float angle);
    ~Entity();

    vec2D   getPosition() const;
    void    setPosition(vec2D newpos);

    vec2D   getVelocity() const;
    void    setVelocity(vec2D newvel);

    float   getAngle() const;
    void    setAngle(float newangle);

    float   getWidth() const;
    void    setWidth(float newwidth);

    float   getHeight() const;
    void    setHeight(float newheight);


    void    applyForce(vec2D force);
    void    move(vec2D offset);
    void    rotate(float angle);
};




#endif //ENTITY_H