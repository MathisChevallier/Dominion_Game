#ifndef JOUEUR_H
#define JOUEUR_H

#include <iostream>
#include <string>
#include <map>
#include "deck.hpp"
#include "mainJeu.hpp"
#include "defausse.hpp"
#include "partie.hpp"

class Partie;

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
    static void nettoyer();
    Deck* getDeck();
    MainJeu* getMainJeu();
    Defausse* getDefausse();
    std::string getNomJoueur() const;
    std::string getCouleurJoueur() const;
    int getPointsVictoire() const;
    const Carte* devoilerCarte();
    void piocherCarte();
    void piocherMain();
    void defausserCarteDeLaMain(const Carte* const &c);
    void defausserPremiereCarteDuDeck();
    void defausserMain();
    void acheterCarte(int i);
    void ajouterCarteTresorAMain(int i);
    void ajouterCarteALaMain(const Carte* const &c);
    void enleverCarteDeLaMain(const Carte* const &c);
    void ajouterCarteSurLeDeck(const Carte* const &c);
    void ajouterACartesJouees(const Carte* const &c);
    void phaseAction();
    void phaseAchat();
    void TourDeJeu(int i);
    void ajouterPointsVictoire(int i);
    int compterPointsVictoire() const;
    friend std::ostream& operator<<(std::ostream& os, const Joueur* const &j);
};

#endif