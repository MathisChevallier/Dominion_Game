#include "royaumeVictoire.hpp"

RoyaumeVictoire::RoyaumeVictoire(const std::string &nom, int cout, const std::vector<std::string> &effet, const std::string &desc, int priorite, const std::string &couleur)
    :Royaume(nom, cout, priorite, couleur, effet, desc){}

RoyaumeVictoire::~RoyaumeVictoire(){}

std::string RoyaumeVictoire::getType() const {
    return "RoyaumeVictoire";
}

// Une carte RoyaumeVictoire est jouer que lors du comptage des scores
void RoyaumeVictoire::jouerCarte() const{
    for(std::string s : (this)->getEffets()){
        effetCarte(s);
    }
}
