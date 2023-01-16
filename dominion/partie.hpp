#ifndef PARTIE_H
#define PARTIE_H

#include <iostream>
#include <string>
#include <vector>
#include <climits>
#include "achat.hpp"
#include "rebut.hpp"
//#include "joueur.hpp"
#include "joueurHumain.hpp"
#include "joueurAI.hpp"

class Achat;
class JoueurHumain;

class Partie{
    std::string p_nomPartie;
    int p_numTour;
    bool p_finPartie;
    Achat* p_achat;
    Rebut* p_rebut;
    std::vector<Joueur*> p_joueurs;
    
    public:
    static std::vector<const Royaume*> p_cartes_utilisees;
    static Partie* p_partieStatic; //Partie qui est en cours

    Partie(std::string s);
    ~Partie();
    static void nettoyer();
    std::string getNomPartie() const;
    bool getFinPartie() const;
    Achat* getAchat() const;
    Rebut* getRebut() const;
    std::vector<Joueur*> getJoueurPartie() const;
    //static std::vector<const Carte*> getCartesUtilisees();
    void ajouterCarteRebutDeLaPartie(const Carte* const &c);
    void creerJoueurHumain(int i);
    void creerJoueurAI(int i);
    void tourComplet();
    void lancerPartie();
    void reprendrePartie();
    void detailPartie();
    bool testFinPartie();
    void finPartie();
    void choixCarteAleatoirePourAchat(std::vector<const Royaume*> cartesPartie);
};

#endif