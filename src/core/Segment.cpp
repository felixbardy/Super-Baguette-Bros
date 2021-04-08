#include "Segment.h"

Segment::Segment() 
: platforms(nullptr), nPlatforms(0),
 animations(nullptr), nAnimations(0)
{
}

Segment::Segment(Platform* platforms, int nPlatforms,  Animation** animations, int nAnimations)
: platforms (platforms),  nPlatforms (nPlatforms),
  animations(animations), nAnimations(nAnimations)
{
}

Segment::~Segment()
{
    
    if (platforms != nullptr){
        delete [] platforms;
        platforms = nullptr;
    }
    if (animations != nullptr){
        for (int i = 0; i < nAnimations; i++)
        {   
            // On libère chaque animation
            //? Normalement, aucune animation n'a été libérée
            delete animations[i];
        }
        // Puis on libère le tableau
        delete[] animations;
        animations = nullptr;
    }
}


void Segment::testRegression()
{
    //TODO Implémenter le test de régression de Segment
}

void Segment::setPlatforms(Platform* platforms, int size)
{
    this->platforms = platforms;
    this->nPlatforms = size;
}

void Segment::setAnimations(Animation** animations, int size)
{
    this->animations = animations;
    this->nAnimations = size;
}

void Segment::loadPlatforms(Platform*& platforms, int& size)
{
    platforms = this->platforms;
    size = nPlatforms;
}

void Segment::loadAnimations(Animation**& animations, int& size)
{
    animations = this->animations;
    size = nAnimations;
}