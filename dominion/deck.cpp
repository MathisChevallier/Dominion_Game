#include "deck.hpp"


Deck::Deck(){
    //Utiliser la méthode reserve() pour réserver suffisamment de place dans le vector
    deck_cartes.reserve(10);

    //Créer la main de départ composé des 10 cartes
    deck_cartes.push_back(CUIVRE);
    deck_cartes.push_back(CUIVRE);
    deck_cartes.push_back(CUIVRE);
    deck_cartes.push_back(CUIVRE);
    deck_cartes.push_back(CUIVRE);
    deck_cartes.push_back(CUIVRE);
    deck_cartes.push_back(CUIVRE);
    deck_cartes.push_back(DOMAINE);
    deck_cartes.push_back(DOMAINE);
    deck_cartes.push_back(DOMAINE);

    (this)->melanger();
}
    
Deck::~Deck(){
    //On vide le vecteur sans supprimer les cartes
    deck_cartes.clear();
}

std::vector<const Carte*> Deck::getListeCartesDeck() const{
    return deck_cartes;
}

void Deck::setListeCartesDeck(const std::vector<const Carte*> &liste){
    deck_cartes = liste;
}

int Deck::getNbCartes() const{
    return deck_cartes.size();
}

int Deck::getNbFoisCarteDansDeck(const Carte* c) const{
    unsigned int compteurC = 0;
    for(size_t i=0; i<getListeCartesDeck().size(); i++){
        if(getListeCartesDeck().at(i)->getNom() == c->getNom()){
            compteurC++;
        }
    }
    return compteurC;
}

const Carte* Deck::getPremiereCarteSurPioche() const{
    return deck_cartes[0];
}

const Carte* Deck::piocherPremiereCarte(){
    //itérateur pointant vers la première carte du deck
    auto c = deck_cartes.begin();
    const Carte* copie = deck_cartes[0];
    //Permet d'effacer la carte du deck pointé par l'itérateur c
    deck_cartes.erase(c);
    return copie;
}

void Deck::ajouterCarteSurDeck(const Carte* const &c){
    //Ajoute la Carte en première position du vecteur deck_cartes
    deck_cartes.insert(deck_cartes.begin(), c);
}
    

void Deck::melanger(){
    //Crée un objet rd de type std::random_device qui génère des nombres aléatoires de haute qualité
    std::random_device rd;
    //crée un générateur de nombres aléatoires de type std::mt19937 initialisé avec une graine générée par rd
    std::mt19937 g(rd());

    //shuffle permet de mélanger un vecteur à partir de son itérateur de début et de fin et d'un générateur de nombre aléatoire
    std::shuffle(deck_cartes.begin(), deck_cartes.end(), g);
}

