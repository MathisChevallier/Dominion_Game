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
    void ajouterCarteRebut(const Carte* const &c);
};

#endif