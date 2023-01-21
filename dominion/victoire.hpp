#ifndef VICTOIRE_H
#define VICTOIRE_H

#include <iostream>
#include "carte.hpp"

class Victoire : public Carte{
    int const v_points;
    public:
    Victoire(const std::string &nom, int cout, int pointsVictoire, int priorite, const std::string &couleur = "\033[32m"); //La couleur d'une carte victoire est par défaut verte
    ~Victoire();
    std::string getType() const override;
    int getPoints() const;
    void jouerCarte() const;
};

#endif