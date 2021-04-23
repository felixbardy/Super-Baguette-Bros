#include "Hitbox.h"

#include <iostream>

Hitbox::Hitbox(Vec2f pos, float width, float height)
: pos(pos), width(width), height(height)
{
}

Hitbox::~Hitbox()
{
}


Vec2f Hitbox::getPos() const { return pos; }

void Hitbox::setPos(Vec2f newpos) { pos = newpos; }

void Hitbox::getDimensions(float* width, float* height) const
{
    if (!(width == NULL)) *width = this->width;

    if (!(height == NULL)) *height = this->height;
}

void Hitbox::setWidth(float newwidth)
{
    width = newwidth;
}

void Hitbox::setHeight(float newheight)
{
    height = newheight;
}

bool Hitbox::overlaping(const Hitbox& h1, const Hitbox& h2)
{
    return !( // Vrai sauf si:
           ((h2.pos.x + h2.width) < h1.pos.x)  // h2 est complètement à gauche de h1
        || ((h1.pos.x + h1.width) < h2.pos.x)  // h1 est complètement à gauche de h2
        || ((h2.pos.y + h2.height) < h1.pos.y) // h2 est complètement en dessous de h1
        || ((h1.pos.y + h1.height) < h2.pos.y) // h1 est complètement en dessous de h2
    );
}

Hitbox Hitbox::upper(float scale) const
{
    //TODO À valider ou modifier
    assert(scale >= -1 && scale <= 1 && scale != 0);

    if (scale > 0) // si scale est positif
    return Hitbox(
        Vec2f(
            pos.x,
            pos.y
        ),
        width,
        (height / 2.0f) * (1 - scale)
    );
    else // si scale est négatif
    return Hitbox(
        Vec2f(
            pos.x,
            pos.y - (height / 2.0f) * (1 + scale)
        ),
        width,
        (height / 2.0f) * (-scale)
    );
}

Hitbox Hitbox::lower(float scale) const
{
    //TODO À valider ou modifier
    assert(scale >= -1 && scale <= 1 && scale != 0);

    if (scale > 0) // si scale est positif
    return Hitbox(
        Vec2f(
            pos.x,
            pos.y - (1 + 1 - scale) * (height / 2.0f)
        ),
        width,
        (height / 2.0f) * (1 - scale)
    );
    else // si scale est négatif
    return Hitbox(
        Vec2f(
            pos.x,
            pos.y - (height / 2.0f)
        ),
        width,
        (height / 2.0f) * (-scale)
    );
}

Hitbox Hitbox::right_inner(float scale) const
{
    //TODO À implémenter
    std::cout<<"Attention! Appel à une méthode non implémentée de Hitbox!"<<std::endl;
}

Hitbox Hitbox::left_inner(float scale) const
{
    //TODO À implémenter
    std::cout<<"Attention! Appel à une méthode non implémentée de Hitbox!"<<std::endl;
}


Hitbox Hitbox::top(float scale) const
{
    //TODO À implémenter
    std::cout<<"Attention! Appel à une méthode non implémentée de Hitbox!"<<std::endl;
}

Hitbox Hitbox::bottom(float scale) const
{
    return Hitbox(
        Vec2f(
            pos.x,
            pos.y - height * scale
        ),
        width,
        height * scale
    );
}

Hitbox Hitbox::right_outer(float scale) const
{
    //TODO À implémenter
    std::cout<<"Attention! Appel à une méthode non implémentée de Hitbox!"<<std::endl;
}

Hitbox Hitbox::left_outer(float scale) const
{
    //TODO À implémenter
    std::cout<<"Attention! Appel à une méthode non implémentée de Hitbox!"<<std::endl;
}

Hitbox Hitbox::resized(float scale) const
{
    //TODO À implémenter
    std::cout<<"Attention! Appel à une méthode non implémentée de Hitbox!"<<std::endl;
}