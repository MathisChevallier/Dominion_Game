#ifndef EFFET_H
#define EFFET_H

#include <iostream>
#include <string>
#include "dominion.hpp"

//Fonction permettant de faire les effets de chaque carte (fonction globale)
extern void effetCarte(const std::string &s);

//Fonction permettant de faire les effets Attaque des cartes
bool effetAttaque(Joueur* j);

#endif