#include "actionReaction.hpp"

ActionReaction::ActionReaction(const std::string &nom, int cout, const std::vector<std::string> &effet, const std::string &desc, const std::vector<std::string> &effetReaction, const std::string &couleur)
    :Royaume(nom,cout,couleur,effet,desc), r_effetReaction(effetReaction){}

ActionReaction::~ActionReaction(){}

std::vector<std::string> ActionReaction::getEffetReaction() const{
    return r_effetReaction;
}

//Lorsqu'une carte Action est jouée, on appelle la fonction effetCarte pour chaque effet de cette carte
void ActionReaction::jouerCarte() const{
    std::cout << c_couleur << (this)->getNom() << "\033[0m." << std::endl << std::endl;
    for(std::string s : (this)->getEffets()){
        effetCarte(s);
    }
}
