#ifndef ROYAUMEVICTOIRE_H
#define ROYAUMEVICTOIRE_H

#include <iostream>
#include <string>
#include <vector>
#include "royaume.hpp"

class RoyaumeVictoire : public Royaume{
    public:
    RoyaumeVictoire(const std::string &nom, int cout, const std::vector<std::string> &effet, const std::string &desc, const std::string &couleur = "\033[32m");
    ~RoyaumeVictoire();
    void jouerCarte() const;
};

#endif