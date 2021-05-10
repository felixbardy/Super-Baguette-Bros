#include "Segment.h"
#include <cassert>
#include <iostream>

using namespace std;

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

    for (auto piece : pieces)
        delete piece;
}


void Segment::testRegression()
{

    cout << "Segment: constructeur par défaut... ";

    Segment S;
    assert(S.platforms == nullptr);
    assert(S.nPlatforms == 0);
    assert(S.animations == nullptr);
    assert(S.getNAnimation() == 0);

    cout << "OK" << endl;


    cout << "Segment: Constructuer... ";

    Platform * Plats = nullptr;
    Plats = new Platform[5];
    Animation** A = nullptr;
    A = new Animation*[5];
    Segment S2(Plats, 5, A, 5);
    assert(S2.nPlatforms == 5);
    assert(S2.getNAnimation() == 5);
    assert(S2.platforms != nullptr);
    assert(S2.animations != nullptr);

    cout << "OK" << endl;


    cout << "Segment: Set... ";

    Platform * Plats2 = nullptr;
    Plats2 = new Platform[10];
    Animation** A2 = nullptr;
    A2 = new Animation*[10];
    S.setPlatforms(Plats2, 10);
    assert(S.platforms != nullptr);
    assert(S.nPlatforms == 10);
    S.setAnimations(A2, 10);
    assert(S.animations != nullptr);
    assert(S.nAnimations == 10);

    cout << "OK" << endl;

    cout << "Segment: load... ";

    Platform * Plat3 = nullptr;
    int p3;
    Animation** A3;
    int a3;
    S2.loadPlatforms(Plat3, p3);
    assert(Plat3 != nullptr);
    assert(p3 == S2.nPlatforms);
    S2.loadAnimations(A3, a3);
    assert(A3 != nullptr);
    assert(a3 == S2.nAnimations);

    cout << "OK" << endl;
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

int Segment::getNAnimation()
{
    return nAnimations;
}

void Segment::addPiece(int x, int y)
{
    this->pieces.push_back( new Piece({(float)x,(float)y}, this) );
}

vector<Piece*>* Segment::getPieces()
{
    return &pieces;
}
