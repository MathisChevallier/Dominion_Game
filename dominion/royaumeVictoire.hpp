#ifndef ROYAUMEVICTOIRE_H
#define ROYAUMEVICTOIRE_H

#include <iostream>
#include <string>
#include <vector>
#include "royaume.hpp"

class RoyaumeVictoire : public Royaume{
    public:
    RoyaumeVictoire(const std::string &nom, int cout, const std::vector<std::string> &effet, const std::string &desc, int priorite, const std::string &couleur = "\033[32m");
    ~RoyaumeVictoire();
    std::string getType() const override;
    void jouerCarte() const;
};

#endif