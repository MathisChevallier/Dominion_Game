#ifndef PARTIE_H
#define PARTIE_H

#include <iostream>
#include <string>
#include <vector>
#include "achat.hpp"
#include "rebut.hpp"
#include "joueur.hpp"

class Achat;

class Partie{
    std::string p_nomPartie;
    Achat* p_achat;
    Rebut* p_rebut;
    std::vector<Joueur*> p_joueurs;
    
    public:
    static std::vector<const Carte*> p_cartes_utilisees;
    static Partie* p_partieStatic; //Partie qui est en cours
    Partie(std::string s);
    ~Partie();
    std::string getNomPartie() const;
    std::vector<Joueur*> getJoueurPartie() const;
    static std::vector<const Carte*> getCartesUtilisees();

    void creerJoueurHumain(int i);
    void creerJoueurAI();
    Joueur* getPremierJoueur();
    void lancerPartie();
    bool finPartie();
    void choixCarteAleatoirePourAchat(std::vector<const Carte*> cartesPartie);
};

#endif