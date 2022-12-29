#ifndef VICTOIRE_H
#define VICTOIRE_H

#include <iostream>
#include "carte.hpp"

class Victoire : public Carte{
    int const v_valeur;
    public:
    Victoire(const std::string &nom, int cout ,int valeur, const std::string &couleur = "\033[32m"); //La couleur d'une carte victoire est par défaut verte
    ~Victoire();
    int getValeur() const;
    void jouerCarte() const;
};

#endif