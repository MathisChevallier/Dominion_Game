#ifndef TRESOR_H
#define TRESOR_H

#include <iostream>
#include "carte.hpp"

class Tresor : public Carte{
    int const t_valeur;
    public:
    Tresor(const std::string &nom, int cout, int valeur, int priorite, const std::string &couleur = "\033[33m"); //La couleur d'une carte tresor est par défaut jaune
    ~Tresor();
    int getValeur() const;
    void jouerCarte() const;
};

#endif