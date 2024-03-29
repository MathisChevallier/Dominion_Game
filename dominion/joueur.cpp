#include "joueur.hpp"

Joueur* Joueur::j_joueurStatic = new Joueur("","");

Joueur::Joueur(const std::string &s, const std::string &c):j_nom(s),j_couleur("\033[0;3" + c + "m"), j_pointsVictoire(0), j_deck(new Deck()), j_main(new MainJeu()), j_defausse(new Defausse()){
    std::cout << "Joueur " << j_couleur << s << "\033[0m a été créé." << std::endl;
    j_joueurStatic = this;
}
    
Joueur::~Joueur(){
    delete j_deck;
    delete j_main;
    delete j_defausse;
}

Deck* Joueur::getDeck(){
    return j_deck;
}

MainJeu* Joueur::getMainJeu(){
    return j_main;
}

Defausse* Joueur::getDefausse(){
    return j_defausse;
}

std::string Joueur::getNomJoueur() const{
    return j_nom;
}

std::string Joueur::getCouleurJoueur() const{
    return j_couleur;
}


int Joueur::getPointsVictoire() const{
    return j_pointsVictoire;
}


void Joueur::piocherCarte(){
    if(j_deck->getNbCartes() == 0){
        // mettre defausse dans deck et melanger
        j_deck->setListeCartesDeck(j_defausse->getListeCartesDefausse());
        j_defausse->setListeCartesDefausse({});
        j_deck->melanger();
        std::cout << (this) << "mélange son deck." << std::endl;
        std::cout << "Le deck du " << (this) << "est composé de " << j_deck->getListeCartesDeck().size() << " cartes." << std::endl;
    }
    const Carte* c = j_deck->piocherPremiereCarte();
    j_main->ajouterCarteMain(c);
}
    
void Joueur::piocherMain(){
    std::cout << (this) << "pioche une nouvelle main de 5 cartes." << std::endl;
    // Une main se compose de 5 cartes
    for(int i=0;i<5;i++){
        (this)->piocherCarte();
    }
    // Réinitialiser compteur d'action, d'achat et d'or de la nouvelle main
    j_main->reinitialiserCompteur();
}

void Joueur::defausserCarteDeLaMain(const Carte* const &c){
    j_main->enleverCarteMain(c);
    j_defausse->ajouterCarteDefausse(c);
}

void Joueur::defausserPremiereCarteDuDeck(){
    const Carte* c = j_deck->piocherPremiereCarte();
    j_defausse->ajouterCarteDefausse(c);
}

void Joueur::defausserMain(){
    // Pour chaque carte de la main, j'enlève la carte de la main et la met dans la défausse 
    for(const Carte* c : j_main->getListeCartesMain()){
        j_main->enleverCarteMain(c);
        j_defausse->ajouterCarteDefausse(c);
    }
    for(const Carte* c : j_main->getListeCartesJouees()){
        j_main->enleverCarteJouee(c);
        j_defausse->ajouterCarteDefausse(c);
    }
}

void Joueur::acheterCarte(int i){
    std::cout << i;
    //regarder p_partieStatic et donner choix au joueur de choisir
}

void Joueur::ajouterCarteALaMain(const Carte* const &c){
    j_main->ajouterCarteMain(c);
}

void Joueur::ecarterCarteDeLaMain(const Carte* const &c){
    j_main->enleverCarteMain(c); // Ajouter dans rebut
}

void Joueur::ajouterCarteSurLeDeck(const Carte* const &c){
    j_main->enleverCarteMain(c);
    j_deck->ajouterCarteSurDeck(c);
}

void Joueur::ajouterACartesJouees(const Carte* const &c){
    j_main->enleverCarteMain(c);
    j_main->ajouterCarteJouee(c);
}


void Joueur::phaseAction(){
    std::cout << "\033[4mDébut phase Action :\033[0m" << std::endl;
    std::cout << (this)->getMainJeu();
    while(j_main->contientCarteAction() && j_main->getActionsAJouer() != 0){
        std::cout << "Voici les cartes actions de votre main : " << std::endl;
        std::vector <const Royaume*> carteRoyaume = {};
        int numCarte = 1;
        for(const Carte *c : (this)->getMainJeu()->getListeCartesMain()){
            if (dynamic_cast<const Royaume*>(c) != nullptr) {
                const Royaume* r1 = static_cast<const Royaume*>(c);
                carteRoyaume.push_back(r1);
                std::cout << "  " << numCarte << " - " << r1 << std::endl;
                numCarte++;
            }
            
        }
        unsigned int choixCarte;
        std::cout << "Pour jouer une carte, tapez son numéro sinon tapez 0 : ";
        std::cin >> choixCarte;
        while(choixCarte > carteRoyaume.size()){
            std::cerr << "\033[1;31m" << choixCarte << " n'est pas une réponse convenable. \033[0m" << std::endl;
            std::cout << "Pour jouer une carte, tapez son numéro sinon tapez 0 : ";
            std::cin >> choixCarte;
        }
        if(choixCarte == 0){
            break;
        }
        else{
            MainJeu::m_carteStatic = const_cast<Royaume*> (carteRoyaume[choixCarte-1]);
            j_main->ajouterAction(-1);
            std::cout << (this) << "joue ";
            carteRoyaume[choixCarte-1]->jouerCarte();
            (this)->ajouterACartesJouees(carteRoyaume[choixCarte-1]);
        }
        std::cout << (this)->getMainJeu();
    }
}

void Joueur::phaseAchat(){
    std::cout << "\033[4mDébut phase Achat :\033[0m" << std::endl;
    for(const Carte* c : j_main->getListeCartesMain()){
        if (dynamic_cast<const Tresor*>(c) != nullptr) {
            // "tresor" est maintenant un pointeur de type "Tresor*" constant
            const Tresor* t1 = static_cast<const Tresor*>(c);
            j_main->ajouterTresorTour(t1->getValeur());
        }
    }
    std::cout << "Vous avez \033[33m" << j_main->getTresorTour() << " trésors\033[0m disponibles pour cet phase d'achat." << std::endl;
    j_main->getMain().push_back(MILICE);
    j_main->getMain().push_back(DOUVES);
    j_main->getMain().push_back(VILLAGE);
    //while(j_main->getAchat() != 0){}
}

void Joueur::TourDeJeu(int i){
    std::cout << j_couleur << "Tour " << i << " - Joueur "<< j_nom << ":\033[0m" << std::endl;
    (this)->phaseAction();
    (this)->phaseAchat();
    (this)->defausserMain();
    (this)->getDefausse()->afficher();
    (this)->piocherMain();
    std::cout << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Joueur* const &j){
    os << "Joueur " << j->getCouleurJoueur() << j->getNomJoueur() << "\033[0m ";
    return os;
}
