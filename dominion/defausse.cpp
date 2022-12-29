#include "defausse.hpp"

Defausse::Defausse():def_cartes({}){}

Defausse::~Defausse(){}

std::vector<const Carte*> Defausse::getListeCartesDefausse() const{
    return def_cartes;
}

void Defausse::setListeCartesDefausse(const std::vector<const Carte*> &c){
    def_cartes = c;
}

void Defausse::ajouterCarteDefausse(const Carte* const &c){
    def_cartes.push_back(c);
}