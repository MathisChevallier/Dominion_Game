#ifndef DEFAUSSE_H
#define DEFAUSSE_H

#include <iostream>
#include <string>
#include <vector>
#include "carte.hpp"

class Defausse{
    std::vector<const Carte*> def_cartes;
    public:
    Defausse();
    ~Defausse();
    std::vector<const Carte*> getListeCartesDefausse() const;
    void setListeCartesDefausse(const std::vector<const Carte*> &c);
    void ajouterCarteDefausse(const Carte* const &c);
};

#endif