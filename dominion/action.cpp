#include "action.hpp"

Action::Action(const std::string &nom, int cout, const std::vector<std::string> &effet, const std::string &desc, int priorite, const std::string &couleur)
    :Royaume(nom, cout, priorite, couleur, effet, desc){}

Action::~Action(){}

//Lorsqu'une carte Action est jouée, on appelle la fonction effetCarte pour chaque effet de cette carte
void Action::jouerCarte() const{
    std::cout << c_couleur << (this)->getNom() << "\033[0m." << std::endl;
    for(std::string s : (this)->getEffets()){
        effetCarte(s);
    }
}

    