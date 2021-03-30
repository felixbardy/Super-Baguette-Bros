#include "Platform.h"

Platform::Platform()
{
}

Platform::Platform(Vec2f pos, float width, float height, float angle)
{
    setPosition(pos);
    setWidth(width);
    setHeight(height);
    setAngle(angle);
}

Platform::~Platform()
{
}

/*
Platform::testRegression()
{
}
*/