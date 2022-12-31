#ifndef ACTIONATTAQUE_H
#define ACTIONATTAQUE_H

#include <iostream>
#include <string>
#include <vector>
#include "royaume.hpp"

class ActionAttaque : public Royaume{
    std::vector<std::string> const r_effetAttaque;
    public:
    ActionAttaque(const std::string &nom, int cout, const std::vector<std::string> &effet, const std::string &desc, const std::vector<std::string> &effetAttaque, const std::string &couleur = "\033[0m");
    ~ActionAttaque();
    std::vector<std::string> getEffetAttaque() const;
    void jouerCarte() const;
};

#endif