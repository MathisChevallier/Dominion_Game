#ifndef JOUEUR_H
#define JOUEUR_H

#include <iostream>
#include <string>
#include "deck.hpp"
#include "mainJeu.hpp"
#include "defausse.hpp"

class Joueur{
    const std::string j_nom;
    const std::string j_couleur;
    int j_pointsVictoire;
    Deck* j_deck;
    MainJeu* j_main;
    Defausse* j_defausse;
    public:
    static Joueur* j_joueurStatic; //Joueur qui est en train de jouer
    Joueur(const std::string &s, const std::string &c);
    ~Joueur();
    Deck* getDeck();
    MainJeu* getMainJeu();
    Defausse* getDefausse();
    std::string getNomJoueur() const;
    std::string getCouleurJoueur() const;
    int getPointsVictoire() const;
    void piocherCarte();
    void piocherMain();
    void defausserCarteDeLaMain(const Carte* const &c);
    void defausserPremiereCarteDuDeck();
    void defausserMain();
    void acheterCarte(int i);
    void ajouterCarteALaMain(const Carte* const &c);
    void ecarterCarteDeLaMain(const Carte* const &c);
    void ajouterCarteSurLeDeck(const Carte* const &c);
    void phaseAction();
    void phaseAchat();
    void TourDeJeu(int i);
    friend std::ostream& operator<<(std::ostream& os, const Joueur* const &j);
};

#endif