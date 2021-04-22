#include "extern/vector2d.h"

/** \class Hitbox Hitbox.h "src/Hitbox.h"
 * \brief représente une boite de collision
 * 
 * Exemple de Hitbox::upper:<br>
 * scale est situé sur une échelle continue de -1 à 1:<br>
 * 1    -> Toute la partie haute<br>
 * 0.5  -> La moitié de la partie haute en partant du haut<br>
 * 0    -> Renvoie une erreur<br>
 * -0.5 -> La moitié de la partie haute en partant du milieu<br>
 * -1   -> Toute la partie haute<br>
 * Autres exemples en image:<br>
 * \image html hitbox1.jpg width=25%
 * \image html hitbox2.jpg width=25%
 * \image html hitbox3.jpg width=25%
 * 
 **/
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
     * \param width le float auquel affecter la largeur
     * \param heigth le float auquel affecter la hauteur
     **/
    void getDimensions(float* width, float* height) const;

    /** \brief Remplace la largeur de la Hitbox
     * \param width la largeur à affecter
     **/
    void setWidth(float width);

    /** \brief Remplace la hauteur de la Hitbox
     * \param width la hauteur à affecter
     **/
    void setHeight(float height);


    /** \brief Renvoie true si les 2 hitboxs sont superposées, faux sinon
     * \param h1 la 1ère Hitbox
     * \param h2 la 2ème Hitbox
     **/
    static bool overlaping(const Hitbox& h1, const Hitbox& h2);


    /** \brief Renvoie la partie intérieure haute de la Hitbox (voir doc. de la classe)
     * \param scale paramètre de modulation
     **/
    Hitbox upper(float scale = 1) const;

    /** \brief Renvoie la partie intérieure basse de la Hitbox (voir doc. de la classe)
     * \param scale paramètre de modulation
     **/
    Hitbox lower(float scale = 1) const;

    /** \brief Renvoie la partie intérieure droite de la Hitbox (voir doc. de la classe)
     * \param scale paramètre de modulation
     **/
    Hitbox right_inner(float scale = 1) const;

    /** \brief Renvoie la partie intérieure gauche de la Hitbox (voir doc. de la classe)
     * \param scale paramètre de modulation
     **/
    Hitbox left_inner(float scale = 1) const;


    /** \brief Renvoie la partie extérieure haute de la Hitbox (voir doc. de la classe)
     * \param scale paramètre de modulation
     **/
    Hitbox top(float scale = 0.25) const;

    /** \brief Renvoie la partie extérieure basse de la Hitbox (voir doc. de la classe)
     * \param scale paramètre de modulation
     **/
    Hitbox bottom(float scale = 0.25) const;

    /** \brief Renvoie la partie extérieure droite de la Hitbox (voir doc. de la classe)
     * \param scale paramètre de modulation
     **/
    Hitbox right_outer(float scale = 0.25) const;

    /** \brief Renvoie la partie extérieure gauche de la Hitbox (voir doc. de la classe)
     * \param scale paramètre de modulation
     **/
    Hitbox left_outer(float scale = 0.25) const;


    /** \brief Renvoie la Hitbox redimensionnée (voir doc. de la classe)
     * \param scale facteur de redimensionnement
     **/
    Hitbox resized(float scale) const;

};

