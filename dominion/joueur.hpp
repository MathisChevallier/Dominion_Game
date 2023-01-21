#ifndef JOUEUR_H
#define JOUEUR_H

#include <iostream>
#include <string>
#include <map>
#include "deck.hpp"
#include "mainJeu.hpp"
#include "defausse.hpp"

class Joueur{
    protected:
    const std::string j_nom;
    const std::string j_couleur;
    int j_pointsVictoire;
    Deck* j_deck;
    MainJeu* j_main;
    Defausse* j_defausse;
    
    public:
    static Joueur* j_joueurStatic; //Joueur qui est en train de jouer
    Joueur(const std::string &s, const std::string &c);
    virtual ~Joueur();
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
    void ajouterCarteALaMain(const Carte* const &c);
    void enleverCarteDeLaMain(const Carte* const &c);
    void ajouterCarteSurLeDeck(const Carte* const &c);
    void ajouterACartesJouees(const Carte* const &c);
    void TourDeJeu(int i);
    void ajouterPointsVictoire(int i);
    int compterPointsVictoire() const;
    
    virtual std::string getType() const = 0;
    virtual int getPrio(const Carte* carte) = 0;
    virtual void acheterCarte(int i) = 0;
    virtual void phaseAction() = 0;
    virtual void phaseAchat() = 0;
    friend std::ostream& operator<<(std::ostream& os, const Joueur* const &j);

};

#endif