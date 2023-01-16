#ifndef MAINJEU_H
#define MAINJEU_H

#include <iostream>
#include <string>
#include <vector>
#include "action.hpp"
#include "actionAttaque.hpp"
#include "actionReaction.hpp"
#include "victoire.hpp"
#include "tresor.hpp"


class MainJeu{
    int m_nbActionsAJouer = 1;
    int m_nbTresorTour = 0;
    int m_nbAchats = 1;
    std::vector<const Carte*> m_cartes;
    std::vector<const Carte*> m_cartesJouees;
    public:
    static Carte* m_carteStatic; //Carte qui est jouée
    MainJeu();
    ~MainJeu();
    int getActionsAJouer() const;
    int getTresorTour() const;
    int getAchat() const;
    std::vector<const Carte*>& getMain();
    std::vector<const Carte*>& getCartesJouees();
    int getNbFoisCarteDansMain(const Carte* c) const;
    void ajouterAction(int n);
    void ajouterTresorTour(int n);
    void ajouterAchatTour(int n);
    void retirerActionTour();
    void reinitialiserCompteur();
    std::vector<const Carte*> getListeCartesMain() const;
    std::vector<const Carte*> getListeCartesJouees() const;
    void ajouterCarteMain(const Carte* const &c);
    void enleverCarteMain(const Carte* const &c);
    void ajouterCarteJouee(const Carte* const &c);
    void enleverCarteJouee(const Carte* const &c);
    bool contientCarteAction();
    friend std::ostream& operator<<(std::ostream& os, const MainJeu* const &m);
};

#endif