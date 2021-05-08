#include "extern/vector2d.h"

/** \class Hitbox Hitbox.h "src/core/Hitbox.h"
 * \brief représente une boite de collision
 * 
 * Une Hitbox a une position (Hitbox::getPos), une longueur et une largeur (Hitbox::getDimensions)
 * \image html hitbox.jpg width=25%
 * La classe implémente Hitbox::overlaping pour tester les collisions entre 2 Hitbox.
 * Elle implémente également des getters et setters pour toutes ses données
 * et de nombreuses méthodes pour séléctionner des sous parties ou les alentours de la Hitbox.<br>
 * Ces dernières prennent un paramètre scale dont le fonctionnement est décris pour chaque méthode.<br><br>
 * 
 * Cette structure permet d'effectuer des détections de collisions plus fines tout en restant lisibles.<br>
 * Exemples de détections:<br>
 * <i>"La collision entre le dessous du joueur et le dessus de la plateforme"</i>
 * ```cpp
 * Hitbox player_hb, platform_hb;
 * 
 * if ( Hitbox::overlaping( player_hb.bottom(), platform_hb.top() ) )
 *     //do something
 * ```
 * <i>"La collision entre la tête du joueur et le bas de la plateforme"</i>
 * ```cpp
 * Hitbox player_hb, platform_hb;
 * 
 * if ( Hitbox::overlaping( player_hb.upper(), platform_hb.lower() ) )
 *     //do something
 * ```
 *
 * Tour d'horizon des méthodes de modulation des hitboxes:
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

    /**
     * Constructeur par defaut
     **/
    Hitbox();

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
     * 
     * width et height peuvent être NULL
     * \param width le float auquel affecter la largeur
     * \param heigth le float auquel affecter la hauteur
     **/
    void getDimensions(float* width, float* height) const;

    /** \brief Remplace la largeur de la Hitbox
     * \param width la largeur à affecter
     **/
    void setWidth(float newwidth);

    /** \brief Remplace la hauteur de la Hitbox
     * \param width la hauteur à affecter
     **/
    void setHeight(float newheight);


    /** \brief Renvoie true si les 2 hitboxs sont superposées, faux sinon
     * \param h1 la 1ère Hitbox
     * \param h2 la 2ème Hitbox
     **/
    static bool overlaping(const Hitbox& h1, const Hitbox& h2);


    /** \brief Renvoie la partie intérieure haute de la Hitbox (modulée par scale)
     * 
     * \f[
     * \text{scale} \in [-1,1] \: \setminus \: 0 : \\\
     * \begin{cases}
     *     [-1,0[ \: :&      \left\vert scale \right\vert \text{ fois la partie haute en partant du milieu de la Hitbox} \\\
     *     ]0,1] \: :&       scale \text{ fois la partie haute en partant du bord haut de la Hitbox} 
     * \end{cases}
     * \f]
     * 
     * 
     * \image html hitbox_upper.jpg width=25%
     * 
     * \param scale paramètre de modulation
     **/
    Hitbox upper(float scale = 1) const;

    /** \brief Renvoie la partie intérieure basse de la Hitbox (modulée par scale)
     * 
     * \f[
     * \text{scale} \in [-1,1] \: \setminus \: 0 : \\\
     * \begin{cases}
     *     [-1,0[ \: :&      \left\vert scale \right\vert \text{ fois la partie basse en partant du milieu de la Hitbox} \\\
     *     ]0,1] \: :&       scale \text{ fois la partie basse en partant du bord bas de la Hitbox} 
     * \end{cases}
     * \f]
     * 
     * \image html hitbox_lower.jpg width=25%
     * 
     * \param scale paramètre de modulation
     **/
    Hitbox lower(float scale = 1) const;

    /** \brief Renvoie la partie intérieure droite de la Hitbox (modulée par scale)
     * 
     * \f[
     * \text{scale} \in [-1,1] \: \setminus \: 0 : \\\
     * \begin{cases}
     *     [-1,0[ \: :&      \left\vert scale \right\vert \text{ fois la partie droite en partant du milieu de la Hitbox} \\\
     *     ]0,1] \: :&       scale \text{ fois la partie droite en partant du bord droit de la Hitbox} 
     * \end{cases}
     * \f]
     * 
     * \image html hitbox_right_inner.jpg width=25%
     * 
     * \param scale paramètre de modulation
     **/
    Hitbox right_inner(float scale = 1) const;

    /** \brief Renvoie la partie intérieure gauche de la Hitbox (modulée par scale)
     * 
     * \f[
     * \text{scale} \in [-1,1] \: \setminus \: 0 : \\\
     * \begin{cases}
     *     [-1,0[ \: :&      \left\vert scale \right\vert \text{ fois la partie gauche en partant du milieu de la Hitbox} \\\
     *     ]0,1] \: :&       scale \text{ fois la partie gauche en partant du bord gauche de la Hitbox} 
     * \end{cases}
     * \f]
     * 
     * \image html hitbox_left_inner.jpg width=25%
     * 
     * \param scale paramètre de modulation
     **/
    Hitbox left_inner(float scale = 1) const;


    /** \brief Renvoie la partie extérieure haute de la Hitbox (modulée par scale)
     * 
     * \f[
     * \text{scale} \in [0,+\infty[ \: : \\\
     * \text{Renvoie une Hitbox de la même largeur et de hauteur }
     *  scale \text{ fois la hauteur initiale située juste au dessus de la Hitbox initiale.}
     * \f]
     * 
     * \image html hitbox_top.jpg width=25%
     * 
     * \param scale paramètre de modulation
     **/
    Hitbox top(float scale = 0.25) const;

    /** \brief Renvoie la partie extérieure basse de la Hitbox (modulée par scale)
     * 
     * \f[
     * \text{scale} \in [0,+\infty[ \: : \\\
     * \text{Renvoie une Hitbox de la même largeur et de hauteur }
     *  scale \text{ fois la hauteur initiale située juste au dessous de la Hitbox initiale.}
     * \f]
     * 
     * \image html hitbox_bottom.jpg width=25%
     * 
     * \param scale paramètre de modulation
     **/
    Hitbox bottom(float scale = 0.25) const;

    /** \brief Renvoie la partie extérieure droite de la Hitbox (modulée par scale)
     * 
     * \f[
     * \text{scale} \in [0,+\infty[ \: : \\\
     * \text{Renvoie une Hitbox de la même hauteur et de largeur }
     *  scale \text{ fois la largeur initiale située juste à droite de la Hitbox initiale.}
     * \f]
     * 
     * \image html hitbox_right_outer.jpg width=25%
     * 
     * \param scale paramètre de modulation
     **/
    Hitbox right_outer(float scale = 0.25) const;

    /** \brief Renvoie la partie extérieure gauche de la Hitbox (modulée par scale)
     * 
     * \f[
     * \text{scale} \in [0,+\infty[ \: : \\\
     * \text{Renvoie une Hitbox de la même hauteur et de largeur }
     *  scale \text{ fois la largeur initiale située juste à gauche de la Hitbox initiale.}
     * \f]
     * 
     * \image html hitbox_left_outer.jpg width=25%
     * 
     * \param scale paramètre de modulation
     **/
    Hitbox left_outer(float scale = 0.25) const;


    /** \brief Renvoie la Hitbox redimensionnée (modulée par scale)
     * 
     * \f[
     * \text{scale} \in [0,+\infty[ \: : \\\
     * \text{Renvoie une Hitbox de même centre avec des dimension de }
     *  scale \text{ fois les dimensions initiales.}
     * \f]
     * 
     * \image html hitbox_resized.jpg width=25%
     * 
     * \param scale facteur de redimensionnement
     **/
    Hitbox resized(float scale) const;

    /**
     * Test de regression de Hitbox.
    */
    void testRegression();

};

