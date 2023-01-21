#ifndef DECK_H
#define DECK_H

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include "carte.hpp"
#include "jeuBase.hpp"
#include "deck.hpp"

class Deck{
    std::vector<const Carte*> deck_cartes;
    public:
    Deck();
    virtual ~Deck();
    std::vector<const Carte*> getListeCartesDeck() const;
    void setListeCartesDeck(const std::vector<const Carte*> &liste);
    const Carte* getPremiereCarteSurPioche() const;
    int getNbCartes() const;
    int getNbFoisCarteDansDeck(const Carte* c) const;
    const Carte* piocherPremiereCarte();
    void ajouterCarteSurDeck(const Carte* const &c);
    void melanger();
};

#endif