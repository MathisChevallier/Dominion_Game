#include "mainJeu.hpp"

Carte* MainJeu::m_carteStatic = nullptr;

MainJeu::MainJeu(){}

MainJeu::~MainJeu(){
    m_cartes.clear();
    m_cartesJouees.clear();
}

int MainJeu::getActionsAJouer() const{
    return m_nbActionsAJouer;
}

int MainJeu::getTresorTour() const{
    return m_nbTresorTour;
}

int MainJeu::getAchat() const{
    return m_nbAchats;
}

std::vector<const Carte*>& MainJeu::getMain(){
    return m_cartes;
}

std::vector<const Carte*>& MainJeu::getCartesJouees(){
    return m_cartesJouees;
}

int MainJeu::getNbFoisCarteDansMain(const Carte* c) const{
    unsigned int compteurC = 0;
    for(size_t i=0; i<getListeCartesMain().size(); i++){
        if(getListeCartesMain().at(i)->getNom() == c->getNom()){
            compteurC++;
        }
    }
    return compteurC;
}

void MainJeu::ajouterAction(int n){
    m_nbActionsAJouer += n;
}
    
void MainJeu::ajouterTresorTour(int n){
    m_nbTresorTour += n;
}
    
void MainJeu::ajouterAchatTour(int n){
    m_nbAchats += n;
}
    
void MainJeu::retirerActionTour(){
    m_nbActionsAJouer -= 1;
}

void MainJeu::reinitialiserCompteur(){
    m_nbActionsAJouer = 1;
    m_nbTresorTour = 0;
    m_nbAchats = 1;
}

std::vector<const Carte*> MainJeu::getListeCartesMain() const{
    return m_cartes;
}

std::vector<const Carte*> MainJeu::getListeCartesJouees() const{
    return m_cartesJouees;
}

void MainJeu::ajouterCarteMain(const Carte* const &c){
    m_cartes.push_back(c);
}

void MainJeu::enleverCarteMain(const Carte* const &c){
    for (auto it = m_cartes.begin(); it != m_cartes.end(); ++it) {
        if (*it == c) { // Si l'itérateur pointe vers l'élément à supprimer
            m_cartes.erase(it); // Supprime l'élément du vecteur
            break; 
        }
    }
}

void MainJeu::ajouterCarteJouee(const Carte* const &c){
    m_cartesJouees.push_back(c);
}

void MainJeu::enleverCarteJouee(const Carte* const &c){
    for (auto it = m_cartesJouees.begin(); it != m_cartesJouees.end(); ++it) {
        if (*it == c) { // Si l'itérateur pointe vers l'élément à supprimer
            m_cartesJouees.erase(it); // Supprime l'élément du vecteur
            break; 
        }
    }
}

bool MainJeu::contientCarteAction(){
    for(const Carte* c : m_cartes){
        if (dynamic_cast<const Action*>(c) != nullptr || dynamic_cast<const ActionAttaque*>(c) != nullptr || dynamic_cast<const ActionReaction*>(c) != nullptr) {
            return true;
        }
    }
    return false;
}


std::ostream& operator<<(std::ostream& os, const MainJeu* const &m){
    os << "Vous avez " << m->getActionsAJouer() << " Action(s), " << m->getAchat() << " Achat(s) et " << m->getTresorTour() << " Trésor(s).\nMain : " << std::endl;
    for(const Carte* c : m->getListeCartesMain()){
        if(dynamic_cast<const Royaume*>(c) != nullptr) {
            const Royaume* r = static_cast<const Royaume*>(c);
            std::cout << "  " << r << r->getCouleurCarte() << ": " << r->getDescriptionEffet() << "\033[0m" << std::endl; 
        }
        else if(dynamic_cast<const Victoire*>(c) != nullptr) {
            const Victoire* v = static_cast<const Victoire*>(c);
            std::cout << "  " << v->getCouleurCarte() << v->getNom() << " : " << v->getPoints() << " Victoire(s)\033[0m" << std::endl; 
        }
        else{
            const Tresor* t = static_cast<const Tresor*>(c);
            std::cout << "  " << t->getCouleurCarte() << t->getNom() << " : " << t->getValeur() << " Trésor(s)\033[0m" << std::endl; 
        }
    }
    return os;
}