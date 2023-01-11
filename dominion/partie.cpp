#include "partie.hpp"

std::vector<const Royaume*> Partie::p_cartes_utilisees = {};

Partie* Partie::p_partieStatic = new Partie("");

Partie::Partie(std::string s):p_nomPartie(s),p_rebut(new Rebut()),p_joueurs({}){
    p_partieStatic = this;
}

Partie::~Partie(){
    delete p_achat;
    delete p_rebut;
}

std::string Partie::getNomPartie() const{
    return p_nomPartie;
}

std::vector<Joueur*> Partie::getJoueurPartie() const{
    return p_joueurs;
}
/*
std::vector<const Carte*> Partie::getCartesUtilisees(){
    return p_cartes_utilisees;
}
*/

void Partie::creerJoueurHumain(int i){
    std::string nom;
    std::cout << "Donnez un nom au joueur numéro " << i << ": ";
    std::cin >> nom;
    p_joueurs.push_back(new Joueur(nom, std::to_string(i)));
}

void Partie::creerJoueurAI(){}


Joueur* Partie::getPremierJoueur(){
    return p_joueurs[0];
}

void Partie::lancerPartie(){
    for(Joueur* j : p_joueurs){
        std::cout << "Le " << j << "commence avec\033[0;33m 7 cuivres\033[0m."  << std::endl;
        std::cout << "Le " << j << "commence avec\033[0;32m 3 domaines\033[0m." << std::endl;
    }
    std::cout << std::endl;

    for(Joueur* j : p_joueurs){
        std::cout << "Le " << j << "mélange son deck."  << std::endl;
    }
    std::cout << std::endl;

    for(Joueur* j : p_joueurs){
        j->piocherMain();
    }
    std::cout << std::endl;
    unsigned int nbTour=1;
    unsigned int nbTourDeJeu=1;
    //while(!((this)->finPartie())){
    while(nbTour < 10){
        Joueur::j_joueurStatic = p_joueurs[0];
        //faire jouer le joueur en début de p_joueur puis l'enlever et le mettre à la fin du vecteur
        while(nbTourDeJeu % p_joueurs.size() != 0){
            nbTourDeJeu++;
        }
        p_joueurs[0]->TourDeJeu(nbTourDeJeu/p_joueurs.size());
        //Mettre le joueur qui à jouer à la fin de la liste des joueurs
        std::rotate(p_joueurs.begin(), p_joueurs.begin() + 1, p_joueurs.end());
        nbTour++;
        nbTourDeJeu = nbTour;
    }
}

bool Partie::finPartie(){
    //Regarder si pile Province vide ou si 3 piles vides
    return false;
}

void Partie::choixCarteAleatoirePourAchat(std::vector<const Royaume*> cartesPartie){
    //le tableau en argument est deja melange
    for(size_t i = 0; i<10; i++){
        p_cartes_utilisees.push_back(cartesPartie.at(i));
    }
}


//static Joueur* d_joueurStatic = p;    
