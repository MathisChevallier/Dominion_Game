#include "royaume.hpp"

Royaume::Royaume(const std::string &nom, int cout, const std::string &couleur, const std::vector<std::string> &effet, const std::string &desc)
    :Carte(nom, cout, couleur), r_effets(effet), r_descriptionEffet(desc){}

Royaume::~Royaume(){}

std::string Royaume::getDescriptionEffet() const{
    return r_descriptionEffet;
}
    
std::vector<std::string> Royaume::getEffets() const{
    return r_effets;
}
