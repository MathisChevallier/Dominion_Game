#include <iostream>
#include "jeuBase.hpp"
#include "dominion.hpp"

int main(){

    Dominion* d = new Dominion();
    d->choixFonctionnalites();
    delete d; 
    detruireCartes();

    return 0;
}