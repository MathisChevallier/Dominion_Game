#include "tresor.hpp"

Tresor::Tresor(const std::string &nom, int cout, int valeur, int priorite, const std::string &couleur):Carte(nom, cout, priorite, couleur), t_valeur(valeur){}
    
Tresor::~Tresor(){}

std::string Tresor::getType() const {
    return "Tresor";
}

int Tresor::getValeur() const{
    return t_valeur;
}

void Tresor::jouerCarte() const{
    // ajouter tresor a la main
}
