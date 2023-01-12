#ifndef JEUBASE_H
#define JEUBASE_H

#include "action.hpp"
#include "actionAttaque.hpp"
#include "actionReaction.hpp"
#include "royaumeVictoire.hpp"
#include "victoire.hpp"
#include "tresor.hpp"

//Liste des cartes du jeu de base (variable globale)
extern const Action *ATELIER, *AVENTURIER, *BIBLIOTHEQUE, *BUCHERON, *CAVE, *CHAMBREDUCONSEIL, *CHANCELIER, *CHAPELLE, *FESTIN,
        *FESTIVAL, *FORGERON, *LABORATOIRE, *MARCHE, *MINE, *PRETEURSURGAGES, *RENOVATION, *SALLEDUTRONE, *VILLAGE; 

extern const ActionAttaque *BUREAUCRATE, *ESPION, *MILICE, *SORCIERE, *VOLEUR;

extern const ActionReaction *DOUVES;

extern const RoyaumeVictoire *JARDINS;

extern const Victoire *PROVINCE, *DUCHE, *DOMAINE, *MALEDICTION; //Jardins; //Jardins action ou victoire ??

extern const Tresor *CUIVRE, *ARGENT, *OR;

//Desctruction des pointeurs de carte
extern void detruireCartes();

//Affichage liste des cartes du jeu de base
extern void listeCarte();

extern std::vector<const Royaume*> setCarte1();


#endif
