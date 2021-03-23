#ifndef PLATFORM_H
#define PLATFORM_H

#include "Entity.h"

/// TODO Implémenter Platform après Entity

class Platform : Entity
{
private:
    /* data */
public:
    Platform();
    Platform(Vec2f pos, float width, float height, float angle);
    ~Platform();
    // void testRegression();
};



#endif //PLATFORM_H