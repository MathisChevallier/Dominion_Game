#include "defausse.hpp"

Defausse::Defausse():def_cartes({}){}

Defausse::~Defausse(){
    def_cartes.clear();
}

std::vector<const Carte*> Defausse::getListeCartesDefausse() const{
    return def_cartes;
}

void Defausse::afficher(){
    for(const Carte* c : def_cartes){
        std::cout << c->getNom() << " / ";
    }
    std::cout << std::endl;
}

void Defausse::setListeCartesDefausse(const std::vector<const Carte*> &c){
    def_cartes = c;
}

void Defausse::ajouterCarteDefausse(const Carte* const &c){
    def_cartes.push_back(c);
}