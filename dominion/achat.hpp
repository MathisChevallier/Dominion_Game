#ifndef ACHAT_H
#define ACHAT_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "carte.hpp"
#include "partie.hpp"
#include "jeuBase.hpp"

class Partie;

class Achat{
    //liste des royaumes + tresor + victoire
    std::vector<const Carte*> tresors_or;
    std::vector<const Carte*> tresors_argent;
    std::vector<const Carte*> tresors_cuivre;
    std::vector<const Carte*> victoires_province;
    std::vector<const Carte*> victoires_duche;
    std::vector<const Carte*> victoires_domaine;
    std::vector<const Carte*> victoires_malediction;
    std::vector< std::vector<const Royaume*> > tab_royaumes;
    

    public:
    Achat();
    ~Achat();
    std::vector<const Carte*>& getTresors_or();
    std::vector<const Carte*>& getTresors_argent();
    std::vector<const Carte*>& getTtresors_cuivre();
    std::vector<const Carte*>& getVictoires_province();
    std::vector<const Carte*>& getVictoires_duche();
    std::vector<const Carte*>& getVictoires_domaine();
    std::vector<const Carte*>& getVictoires_malediction();

    void afficherLigneAchat();
    void completerLigneAchatGauche(int nombreJoueur);
    void completerLigneAchatCentreAuto(int nombreJoueur);
<<<<<<< Updated upstream



    //choix aleatoire des dix cartes
    //choix des dix cartes
=======
    std::map<int, const Carte*> afficherLigneAchatPhaseAchat(int nbTresors);
    const Carte* acheterCarte(std::map<int, const Carte*> mapAchat);
    const Carte* acheterCarteTresor(std::map<int, const Carte*> mapAchat);
>>>>>>> Stashed changes
};

#endif


/*
Lors de l'appel du constructeur dans partie: (ex)
 MaClasse obj1;
  MaClasse::MonConstructeur1 obj2;  // équivalent à MaClasse obj2;
  MaClasse obj3(10);
  MaClasse::MonConstructeur2 obj4(10);
*/