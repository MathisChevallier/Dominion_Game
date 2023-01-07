#ifndef PARTIE_H
#define PARTIE_H

#include <iostream>
#include <string>
#include <vector>
#include <climits>
//#include "achat.hpp"
#include "rebut.hpp"
#include "joueur.hpp"

class Partie{
    std::string p_nomPartie;
    int p_numTour;
    //Achat* p_achat;
    Rebut* p_rebut;
    std::vector<Joueur*> p_joueurs;
    public:
    static Partie* p_partieStatic; //Partie qui est en cours
    Partie(std::string s);
    ~Partie();
    std::string getNomPartie() const;
    std::vector<Joueur*> getJoueurPartie() const;
    void ajouterCarteRebutDeLaPartie(const Carte* const &c);
    void creerJoueurHumain(int i);
    void creerJoueurAI();
    Joueur* getPremierJoueur();
    void tourComplet();
    void lancerPartie();
    void reprendrePartie();
    bool testFinPartie();
    void finPartie();
};

#endif