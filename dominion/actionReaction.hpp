#ifndef ACTIONREACTION_H
#define ACTIONREACTION_H

#include <iostream>
#include <string>
#include <vector>
#include "royaume.hpp"

class ActionReaction : public Royaume{
    std::vector<std::string> const r_effetReaction;
    public:
    ActionReaction(const std::string &nom, int cout, const std::vector<std::string> &effet, const std::string &desc, const std::vector<std::string> &effetReaction, int priorite, const std::string &couleur = "\033[34m");
    ~ActionReaction();
    std::string getType() const override;
    std::vector<std::string> getEffetReaction() const;
    void jouerCarte() const;
};

#endif