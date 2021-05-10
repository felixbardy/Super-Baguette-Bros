#include "Objects.h"

Platform::Platform() {}

Platform::Platform(Vec2f pos, float width, float height, float angle)
{
    setPosition(pos);
    setWidth(width);
    setHeight(height);
    setAngle(angle);
}

Platform::~Platform() {}

/*
Platform::testRegression()
{
}
*/

Piece::Piece() {}

Piece::Piece(Vec2f pos, void* origin_segment)
{
    setHeight(0.7);
    setWidth(0.7);
    setPosition(pos);
    origin = origin_segment;
    taken = false;
}

Piece::~Piece() {}

void* Piece::getOrigin() const { return origin; }

void Piece::setTaken(bool state) { taken = state; }

bool Piece::isTaken() const { return taken; }