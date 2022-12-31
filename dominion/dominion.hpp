#ifndef DOMINION_H
#define DOMINION_H

#include <iostream>
#include <string>
#include <vector>
#include "partie.hpp"

class Dominion{
    std::vector<Partie*> d_parties;    
    public:
    Dominion();
    ~Dominion();
    void choixFonctionnalites();
    void creerNouvellePartie();
    void reprendrePartieEnCours();
    void creerIAPartieSolo(Partie* p);
    void creerIAPartieMulti(Partie* p, int i);
};

#endif

