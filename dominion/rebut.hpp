#ifndef REBUT_H
#define REBUT_H

#include <iostream>
#include <string>
#include <vector>
#include "carte.hpp"

class Rebut{
    std::vector<const Carte*> r_cartes;
    public:
    Rebut();
    ~Rebut();
    std::vector<const Carte*> getCarteRebut();
    void ajouterCarteRebut(const Carte* const &c);
};

#endif