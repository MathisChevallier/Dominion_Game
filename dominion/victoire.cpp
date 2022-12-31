#include "victoire.hpp"

Victoire::Victoire(const std::string &nom, int cout, int valeur, const std::string &couleur):Carte(nom, cout, couleur), v_valeur(valeur){}
    
Victoire::~Victoire(){}

int Victoire::getValeur() const{
    return v_valeur;
}

void Victoire::jouerCarte() const{
    // ajouter point aux points de victoire joueur
}