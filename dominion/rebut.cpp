#include "rebut.hpp"

Rebut::Rebut():r_cartes({}){}

Rebut::~Rebut(){
    r_cartes.clear();
}

std::vector<const Carte*> Rebut::getCarteRebut(){
    return r_cartes;
}

void Rebut::ajouterCarteRebut(const Carte* const &c){
    r_cartes.push_back(c);
}