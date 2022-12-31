#include "actionAttaque.hpp"

ActionAttaque::ActionAttaque(const std::string &nom, int cout, const std::vector<std::string> &effet, const std::string &desc, const std::vector<std::string> &effetAttaque, const std::string &couleur)
    :Royaume(nom,cout,couleur,effet,desc), r_effetAttaque(effetAttaque){}

ActionAttaque::~ActionAttaque(){}

std::vector<std::string> ActionAttaque::getEffetAttaque() const{
    return r_effetAttaque;
}

//Lorsqu'une carte ActionAttaque est jouée, on appelle la fonction effetCarte pour chaque effet et appelle la fonction effetCarte pour chaque effetAttaque
void ActionAttaque::jouerCarte() const{
    std::cout << c_couleur << (this)->getNom() << "\033[0m." << std::endl << std::endl;
    for(std::string s : (this)->getEffets()){
        effetCarte(s);
    }
    for(std::string s : (this)->getEffetAttaque()){
        //Cet appel permet de pouvoir vérifier lespotentielles cartes ActionReaction dans les mains des adversaires
        effetCarte("effet Attaque");
    }
}