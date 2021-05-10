#include "Hitbox.h"

#include <iostream>
#include <cassert>

Hitbox::Hitbox()
: width(0), height(0)
{
    pos.x = 0;
    pos.y = 0;
}

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
    assert(scale >= -1 && scale <= 1 && scale != 0);

    if (scale > 0) // si scale est positif
    return Hitbox(
        Vec2f(
            pos.x,
            pos.y + (height / 2.0f) * (1+1-scale)
        ),
        width,
        (height / 2.0f) * (scale)
    );
    else // si scale est négatif
    return Hitbox(
        Vec2f(
            pos.x,
            pos.y + (height / 2.0f)
        ),
        width,
        (height / 2.0f) * (-scale)
    );
}

Hitbox Hitbox::lower(float scale) const
{
    assert(scale >= -1 && scale <= 1 && scale != 0);

    if (scale > 0) // si scale est positif
    return Hitbox(
        Vec2f(
            pos.x,
            pos.y
        ),
        width,
        (height / 2.0f) * (scale)
    );
    else // si scale est négatif
    return Hitbox(
        Vec2f(
            pos.x,
            pos.y + (height / 2.0f) * (1 + scale) //? rappel: scale < 0
        ),
        width,
        (height / 2.0f) * (-scale)
    );
}

Hitbox Hitbox::right_inner(float scale) const
{
    assert(scale >= -1 && scale <= 1 && scale != 0);

    if (scale > 0) // si scale est positif
    return Hitbox(
        Vec2f(
            pos.x + (width / 2.0f) * (1 + 1 - scale),
            pos.y
        ),
        (width / 2.0f) * (scale),
        height
    );
    else // si scale est négatif
    return Hitbox(
        Vec2f(
            pos.x + (width / 2.0f),
            pos.y
        ),
        (width / 2.0f) * (-scale),
        height
    );
}

Hitbox Hitbox::left_inner(float scale) const
{
    assert(scale >= -1 && scale <= 1 && scale != 0);

    if (scale > 0) // si scale est positif
    return Hitbox(
        Vec2f(
            pos.x,
            pos.y
        ),
        (width / 2.0f) * (scale),
        height
    );
    else // si scale est négatif
    return Hitbox(
        Vec2f(
            pos.x + (width / 2.0f) * (1 + scale), //? rappel: scale < 0
            pos.y
        ),
        (width / 2.0f) * (-scale),
        height
    );
}


Hitbox Hitbox::top(float scale) const
{
    assert(scale > 0);
    return Hitbox(
        Vec2f(
            pos.x,
            pos.y + height
        ),
        width,
        height * scale
    );
}

Hitbox Hitbox::bottom(float scale) const
{
    assert(scale > 0);
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
    assert(scale > 0);
    return Hitbox(
        Vec2f(
            pos.x + width,
            pos.y
        ),
        width * scale,
        height
    );
}

Hitbox Hitbox::left_outer(float scale) const
{
    assert(scale > 0);
    return Hitbox(
        Vec2f(
            pos.x - width * scale,
            pos.y
        ),
        width * scale,
        height
    );
}

Hitbox Hitbox::resized(float scale) const
{
    assert(scale >= 0);
    return Hitbox(
        Vec2f(
            pos.x + (1-scale) * width / 2.0f,
            pos.y + (1-scale) * height / 2.0f
        ),
        width * scale,
        height * scale
    );
}

void Hitbox::testRegression()
{
    cout << "Hitbox: constructeur par défaut... ";
    Hitbox h;
    assert(h.pos.x == 0 && h.pos.y == 0);
    assert(h.width == 0 && h.height == 0);
    cout << "OK" << endl;


    cout << "Hitbox: constructeur par données... ";
    Vec2f vecTest;
    vecTest.x = 5.0;
    vecTest.y = 10.0;
    Hitbox h2(vecTest, 2.0, 4.0);
    Vec2f vecTest2 = h2.getPos();
    assert(vecTest == vecTest2);
    float* h1 = nullptr;
    h1 = new float[1];
    float* w1 = nullptr;
    w1 = new float[1];
    h2.getDimensions(w1, h1);
    assert(*h1 == h2.height && *w1 == h2.width);
    cout << "OK" << endl;

    cout << "Hitbox: setters... ";
    h.setPos(vecTest);
    h.setHeight(3);
    h.setWidth(5);
    assert(h.pos == vecTest);
    assert(h.height == 3 && h.width == 5);
    cout << "OK" << endl;

    cout << "Hitbox: overlapping... ";
    bool test = overlaping(h, h2); //doit retourner vrai
    assert(test); 
    Hitbox h3;
    test = overlaping(h, h3); //doit retourner faux
    assert(!test);
    cout << "OK" << endl;

    cout << "Hitbox: upper... ";
    h3 = h2.upper(0.5);
    assert(h3.pos.x == 5 && h3.pos.y == 13);
    assert(h3.height == 1 && h3.width == 2);
    h3 = h2.upper(-0.5);
    assert(h3.pos.x == 5 && h3.pos.y == 12);
    assert(h3.height == 1 && h2.width == 2);
    cout << "OK" << endl;

    cout << "Hitbox: lower... ";
    h3 = h2.lower(0.5);
    assert(h3.pos.x == 5 && h3.pos.y == 10);
    assert(h3.height == 1 && h3.width == 2);
    h3 = h2.lower(-0.5);
    assert(h3.pos.x == 5 && h3.pos.y == 11);
    assert(h3.height == 1 && h3.width == 2);
    cout << "OK" << endl;

    cout << "Hitbox: right_inner... ";
    h3 = h2.right_inner(0.5);
    assert(h3.pos.x == 6.5 && h3.pos.y == 10);
    assert(h3.height == 4 && h3.width == 0.5);
    h3 = h2.right_inner(-0.5);
    assert(h3.pos.x == 6 && h3.pos.y == 10);
    assert(h3.height == 4 && h3.width == 0.5);
    cout << "OK" << endl;

    cout << "Hitbox: left_inner... ";
    h3 = h2.left_inner(0.5);
    assert(h3.pos.x == 5 && h3.pos.y == 10);
    assert(h3.height == 4 && h3.width == 0.5);
    h3 = h2.left_inner(-0.5);
    assert(h3.pos.x == 5.5 && h3.pos.y == 10);
    assert(h3.height == 4 && h3.width == 0.5);
    cout << "OK" << endl;

    cout << "Hitbox: top... ";
    h3 = h2.top(2.5);
    assert(h3.pos.x == 5 && h3.pos.y == 14);
    assert(h3.height == 10 && h3.width == 2);
    cout << "OK" << endl;

    cout << "Hitbox: bottom... ";
    h3 = h2.bottom(2.5);
    assert(h3.pos.x == 5 && h3.pos.y == 0);
    assert(h3.height == 10 && h3.width == 2);
    cout << "OK" << endl;

    cout << "Hitbox: right_outer... ";
    h3 = h2.right_outer(2.5);
    assert(h3.pos.x == 7 && h3.pos.y == 10);
    assert(h3.height == 4 && h3.width == 5);
    cout << "OK" << endl;

    cout << "Hitbox: left_outer... ";
    h3 = h2.left_outer(2.5);
    assert(h3.pos.x == 0 && h3.pos.y == 10);
    assert(h3.height == 4 && h3.width == 5);
    cout << "OK" << endl;

    cout << "Hitbox: resized... ";
    h3 = h2.resized(10);
    assert(h3.pos.x == -4 && h3.pos.y == -8);
    assert(h3.height == 40 && h3.width == 20);
    h3 = h2.resized(0);
    assert(h3.pos.x == 6 && h3.pos.y == 12);
    assert(h3.height == 0 && h3.width == 0);
    cout << "OK" << endl;
}
