#include "victoire.hpp"

Victoire::Victoire(const std::string &nom, int cout, int pointsVictoire, const std::string &couleur):Carte(nom, cout, couleur), v_points(pointsVictoire){}
    
Victoire::~Victoire(){}

int Victoire::getPoints() const{
    return v_points;
}

void Victoire::jouerCarte() const{
    // ajouter point aux points de victoire joueur
}