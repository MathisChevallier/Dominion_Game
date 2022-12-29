#include "carte.hpp"

Carte::Carte(const std::string &nom, int cout, const std::string &couleur):c_nom(nom), c_cout(cout), c_couleur(couleur){}

Carte::~Carte(){}

std::string Carte::getNom() const{
    return c_nom;
}
    
std::string Carte::getCouleurCarte() const{
    return c_couleur;
}

int Carte::getCout() const{
    return c_cout;
}

void Carte::mettreDefausse(){
    //Enlever de main (peut etre plus à mettre dans joueur)
}

void Carte::mettreRebus(){
    //Enlever de main et deck (peut etre plus à mettre dans joueur)
}

std::ostream& operator<<(std::ostream& os, const Carte* const &c){
    os << c->getCouleurCarte() << c->getNom() << "\033[0m"; 
    return os;
}
