#include "partie.hpp"

std::vector<const Royaume*> Partie::p_cartes_utilisees = {};

Partie* Partie::p_partieStatic = nullptr;

Partie::Partie(std::string s):p_nomPartie(s),p_numTour(1),p_finPartie(false),p_achat(new Achat()),p_rebut(new Rebut()),p_joueurs({}){
    p_partieStatic = this;
}

Partie::~Partie(){
    // Libère l'espace mémoire alloué pour p_rebut et p_achat
    delete p_achat;
    delete p_rebut;
    // Nettoyer le pointeur static de la classe Joueur
    Joueur::nettoyer();

    // Parcours le vecteur de joueurs
    for (Joueur* j : p_joueurs) {
        // Libère l'espace mémoire alloué pour chaque joueur
        delete j;
    }
    p_joueurs.clear();
}

void Partie::nettoyer() {
    p_partieStatic = nullptr;
}

int Partie::getNumTour(){
    return p_numTour;
}

std::string Partie::getNomPartie() const{ return p_nomPartie;}
bool Partie::getFinPartie() const{ return p_finPartie;}
Achat* Partie::getAchat() const{ return p_achat;}
Rebut* Partie::getRebut() const{ return p_rebut;}
std::vector<Joueur*> Partie::getJoueurPartie() const{ return p_joueurs;}

void Partie::ajouterCarteRebutDeLaPartie(const Carte* const &c){
    p_rebut->ajouterCarteRebut(c);
}

void Partie::creerJoueurHumain(int i){
    std::string nom;
    std::cout << "Donnez un nom au joueur numéro " << i << ": ";
    std::cin >> nom;
    p_joueurs.push_back(new JoueurHumain(nom, std::to_string(i)));
    std::cout << p_joueurs[p_joueurs.size()-1] << "\033[0ma été créé." << std::endl;
}

void Partie::creerJoueurAI(int i){
    p_joueurs.push_back(new JoueurAI("Bot "+std::to_string(i), std::to_string(i+p_joueurs.size())));
    std::cout << p_joueurs[p_joueurs.size()-1] << "\033[0ma été créé." << std::endl;
}

void Partie::tourComplet(){
    unsigned int nbTourDeJeu = p_numTour;
    while(!((this)->testFinPartie())){
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
            std::cout << "Voulez vous continuer la partie (O ou N) : ";
            char suitePartie = 'O';
            std::cin >> suitePartie;
            while(suitePartie != 'O' && suitePartie != 'N'){
                std::cerr << "\033[1;31m" << suitePartie << " n'est pas une réponse convenable. \033[0m" << std::endl;
                std::cin.clear(); 
                std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
                std::cout << "Voulez vous continuer la partie (O ou N) : ";
                std::cin >> suitePartie;
            }
            if(suitePartie == 'N'){
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
    Partie::p_partieStatic = this;
    (this)->tourComplet();
}

void Partie::detailPartie(){
    std::cout << "\033[1;4mDétails de la partie :\033[0m " << p_nomPartie << std::endl;
    std::cout << "\033[1;4mNombre de tours :\033[0m " << p_numTour / p_joueurs.size() << std::endl;
    (this)->finPartie();
}

bool Partie::testFinPartie(){
     if(p_achat->nbPileVide() == 3 || p_achat->getVictoires_province().size() == 0){
        return true;
    }
    else{
        return false;
    }
}

void Partie::finPartie(){
    std::cout << "\033[1;4mRésultat :\033[0m " << std::endl << std::endl;
    int maxPoints = INT_MIN;
    Joueur* jPremier;
    for(Joueur* j : p_joueurs){
        Joueur::j_joueurStatic = j;
        j->defausserMain();
        for(const Carte* c : j->getDefausse()->getListeCartesDefausse()){
            j->getDeck()->ajouterCarteSurDeck(c);
        }
        j->getDefausse()->setListeCartesDefausse({});
        std::cout << j << "possède " << j->getDeck()->getListeCartesDeck().size() << " cartes dans son deck à la fin de la partie." << std::endl;
        int ptsJoueur = j->compterPointsVictoire();
        if(ptsJoueur > maxPoints){
            maxPoints = ptsJoueur;
            jPremier = j;
        }
    }
    p_finPartie = true;
    std::cout << "Le gagnant de la partie est " << jPremier << "avec " << maxPoints << " points de victoire." << std::endl << std::endl;
}

void Partie::choixCarteAleatoirePourAchat(std::vector<const Royaume*> cartesPartie, int nbr){
    //Mélanger les cartes du vecteur
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cartesPartie.begin(), cartesPartie.end(), g);

    //le tableau en argument est deja melange
    for(int i = 0; i<nbr; i++){
        p_cartes_utilisees.push_back(cartesPartie.at(i));
    }
    sort(p_cartes_utilisees.begin(), p_cartes_utilisees.end(), triCarte);
}

bool triCarte(const Royaume* a, const Royaume* b) {
    if (a->getCout() == b->getCout()) {
        return a->getNom() < b->getNom();
    }
    return a->getCout() < b->getCout();
}