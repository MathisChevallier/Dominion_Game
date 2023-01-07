#include "partie.hpp"

Partie* Partie::p_partieStatic = new Partie("");

Partie::Partie(std::string s):p_nomPartie(s),p_numTour(1),p_rebut(new Rebut()),p_joueurs({}){
    p_partieStatic = this;
}

Partie::~Partie(){
    // Libère l'espace mémoire alloué pour p_rebut et p_achat
    //delete p_achat;
    delete p_rebut;

    // Parcours le vecteur de joueurs
    for (Joueur* j : p_joueurs) {
        // Libère l'espace mémoire alloué pour chaque joueur
        delete j;
    }
    p_joueurs.clear();
}

std::string Partie::getNomPartie() const{
    return p_nomPartie;
}

std::vector<Joueur*> Partie::getJoueurPartie() const{
    return p_joueurs;
}

void Partie::ajouterCarteRebutDeLaPartie(const Carte* const &c){
    p_rebut->ajouterCarteRebut(c);
}

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

void Partie::tourComplet(){
    unsigned int nbTourDeJeu = p_numTour;
    //while(!((this)->finPartie())){
    while(p_numTour < 10){
        Joueur::j_joueurStatic = p_joueurs[0];
        //faire jouer le joueur en début de p_joueur puis l'enlever et le mettre à la fin du vecteur
        if(nbTourDeJeu % p_joueurs.size() == 1){
            std::cout << "\033[1;4mTour " << nbTourDeJeu/p_joueurs.size() + 1 << " :\033[0m" << std::endl << std::endl;
        }
        while(nbTourDeJeu % p_joueurs.size() != 0){
            nbTourDeJeu++;
        }

        p_joueurs[0]->TourDeJeu(nbTourDeJeu/p_joueurs.size());
        //Mettre le joueur qui à jouer à la fin de la liste des joueurs
        std::rotate(p_joueurs.begin(), p_joueurs.begin() + 1, p_joueurs.end());
        if(p_numTour % p_joueurs.size() == 0){
            std::cout << "Fin du tour " << nbTourDeJeu/p_joueurs.size() << "." << std::endl;
            std::cout << "Voulez vous continuer la partie (o ou n) : ";
            char suitePartie = 'o';
            std::cin >> suitePartie;
            while(suitePartie != 'o' && suitePartie != 'n'){
                std::cerr << "\033[1;31m" << suitePartie << " n'est pas une réponse convenable. \033[0m" << std::endl;
                std::cout << "Voulez vous continuer la partie (o ou n) : ";
                std::cin >> suitePartie;
            }
            if(suitePartie == 'n'){
                std::cout << "Partie " << p_nomPartie  << " sauvegardée." << std::endl;
                p_numTour++;
                break;
            }
            std::cout << std::endl;
        }
        p_numTour++;
        nbTourDeJeu = p_numTour;
    }
    if((this)->testFinPartie()){
        (this)->finPartie();
    }
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
    (this)->tourComplet();
}

void Partie::reprendrePartie(){
    (this)->tourComplet();
}

bool Partie::testFinPartie(){
    //Regarder si pile Province vide ou si 3 piles vides
    return true;
}

void Partie::finPartie(){
    //Regarder si pile Province vide ou si 3 piles vides
    std::cout << "\033[1;4mRésultat :\033[0m" << std::endl << std::endl;
    int maxPoints = INT_MIN;
    Joueur* jPremier;
    for(Joueur* j : p_joueurs){
        Joueur::j_joueurStatic = j;
        j->defausserMain();
        for(const Carte* c : j->getDefausse()->getListeCartesDefausse()){
            j->getDeck()->ajouterCarteSurDeck(c);
        }
        j->getDefausse()->setListeCartesDefausse({});
        std::cout << j << ": " << j->getDefausse()->getListeCartesDefausse().size() << " / " << j->getMainJeu()->getListeCartesMain().size() << " / " << j->getMainJeu()->getListeCartesJouees().size() << " / " << j->getDeck()->getListeCartesDeck().size() << std::endl;
        int ptsJoueur = j->compterPointsVictoire();
        if(ptsJoueur > maxPoints){
            maxPoints = ptsJoueur;
            jPremier = j;
        }
    }
    std::cout << "Le gagnant de la partie est " << jPremier << "avec " << maxPoints << " points de victoire." << std::endl;
}


//static Joueur* d_joueurStatic = p;    
