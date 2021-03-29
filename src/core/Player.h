#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

namespace PlayerInput
{
    // Masques
    const uint16_t JUMP     = 1 << 0; // = 0x0...01
    const uint16_t DOWN     = 1 << 1; // = 0x0...10
    const uint16_t UP       = 1 << 2; // etc...
    const uint16_t LEFT     = 1 << 3;
    const uint16_t RIGHT    = 1 << 4;
    // Il reste de la place pour encore 11 inputs (ex: attaque)

};


/// TODO Fixer clairement à quoi ressemblent les contrôles du joueur avant de l'implémenter

class Player : public Entity
{
private:
    /// Stocke les masques passés comme input
    uint16_t current_input;
public:
    Player(/* args */);
    ~Player();
    void addInput(uint16_t mask);
    void clearInput(uint16_t mask);
    bool checkInput(uint16_t mask);
    void clearAllInputs();
    
    void testRegression();
};



#endif //PLAYER_H