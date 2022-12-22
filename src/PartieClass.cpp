#include <iostream>
#include "PartieClass.hpp"

Partie::Partie(){
    nbJoueur = 3;
}

Partie::~Partie(){
}

int Partie::getNbJoueur() {return this->nbJoueur;} //this->nbJoueur
