#include "extern/vector2d.h"

class Hitbox
{
private:
    // La position de la Hitbox
    Vec2f pos;
    // La largeur de la Hitbox
    float width;
    // La hauteur de la Hitbox
    float height;
public:
    /** \brief Constructeur par données de Hitbox
     * \param pos la position de la Hitbox
     * \param width la largeur de la Hitbox
     * \param height le hauteur de la Hitbox
     **/
    Hitbox(Vec2f pos, float width, float height);

    /// Destructeur de Hitbox
    ~Hitbox();

    /// Renvoie la position de la Hitbox
    Vec2f getPos() const;
    /// Affecte la nouvelle position à la Hitbox
    void setPos(Vec2f newpos);

    /** \brief Renvoie les dimensions de la Hitbox
     * \param width pointeur vers le float à affecter
     * 
     **/
    void getDimensions(float* width, float* height) const;
    void setWidth(float width);
    void setHeight(float height);

    static bool overlaping(const Hitbox& h1, const Hitbox& h2);

    Hitbox upper(float scale) const;
    Hitbox lower(float scale) const;
    Hitbox right_inner(float scale) const;
    Hitbox left_inner(float scale) const;

    Hitbox top(float scale) const;
    Hitbox bottom(float scale) const;
    Hitbox right_outer(float scale) const;
    Hitbox left_outer(float scale) const;

    Hitbox resized(float scale) const;

};

