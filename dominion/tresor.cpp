#include "tresor.hpp"

Tresor::Tresor(const std::string &nom, int cout, int valeur, const std::string &couleur):Carte(nom, cout, couleur), t_valeur(valeur){}
    
Tresor::~Tresor(){}

int Tresor::getValeur() const{
    return t_valeur;
}

void Tresor::jouerCarte() const{
    // ajouter tresor a la main
}