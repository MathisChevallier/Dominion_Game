#include "rebut.hpp"

Rebut::Rebut():r_cartes({}){}

Rebut::~Rebut(){}

void Rebut::ajouterCarteRebut(const Carte* const &c){
    r_cartes.push_back(c);
}