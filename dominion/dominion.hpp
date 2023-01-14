#ifndef DOMINION_H
#define DOMINION_H

#include <iostream>
#include <string>
#include <vector>
#include "partie.hpp"

using fonctionSetCarte = std::vector<const Royaume*>;

class Dominion{
    std::vector<Partie*> d_parties;  
    std::vector<Partie*> d_historique;      
    public:
    Dominion();
    ~Dominion();
    void choixFonctionnalites();
    void creerNouvellePartie();
    void choixManuelCarte(std::vector<const Royaume*> &v);
    void choixSetCarte(const std::vector<const Royaume*>& v);
    void reprendrePartieEnCours();
    void historiquePartie();
    void creerIAPartieSolo(Partie* p);
    void creerIAPartieMulti(Partie* p, int i);
    void testFinPartie();
};

#endif

