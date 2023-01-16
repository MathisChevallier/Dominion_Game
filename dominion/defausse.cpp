#include "defausse.hpp"

Defausse::Defausse():def_cartes({}){}

Defausse::~Defausse(){
    def_cartes.clear();
}

std::vector<const Carte*> Defausse::getListeCartesDefausse() const{
    return def_cartes;
}

int Defausse::getNbFoisCarteDansDefausse(const Carte* c) const{
    unsigned int compteurC = 0;
    for(size_t i=0; i<getListeCartesDefausse().size(); i++){
        if(getListeCartesDefausse().at(i)->getNom() == c->getNom()){
            compteurC++;
        }
    }
    return compteurC;
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