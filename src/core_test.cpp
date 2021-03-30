#include <iostream>

#include "core/World.h"

//TODO Exécuter tous les tests régressions du module 'core'

int main()
{
    std::cout<<"Début des tests régression..."<<std::endl;
    World w;
    w.testRegression();
    Entity e;
    e.testRegression();
    Player p;
    p.testRegression();
    //Platform p2;
    //p2.testRegression();
    Segment s;
    s.testRegression();
    testRegressionAnimations();
    return 0;
}