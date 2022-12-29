#ifndef PARTIE_H
#define PARTIE_H

#include <iostream>
#include <string>
#include <vector>
//#include "achat.hpp"
#include "rebut.hpp"
#include "joueur.hpp"

class Partie{
    std::string p_nomPartie;
    //Achat* p_achat;
    Rebut* p_rebut;
    std::vector<Joueur*> p_joueurs;
    public:
    static Partie* p_partieStatic; //Partie qui est en cours
    Partie(std::string s);
    ~Partie();
    std::string getNomPartie() const;
    std::vector<Joueur*> getJoueurPartie() const;
    void creerJoueurHumain(int i);
    void creerJoueurAI();
    Joueur* getPremierJoueur();
    void lancerPartie();
    bool finPartie();
};

#endif