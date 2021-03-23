#include "Segment.h"

Segment::Segment() 
: platforms(nullptr), nPlatforms(0),
 animations(nullptr), nAnimations(0)
{
}

Segment::Segment(Platform* platforms, int nPlatforms,  Animation* animations, int nAnimations)
: platforms(platforms), nPlatforms(nPlatforms),
 animations(animations), nAnimations(nAnimations)
{
}

Segment::~Segment()
{
    if (platforms != nullptr){
        delete[] platforms;
        platforms = nullptr;
    }
    if (animations != nullptr){
        delete[] animations;
        animations = nullptr;
    }
}


void Segment::testRegression()
{
    //TODO Implémenter le test de régression de Segment
}