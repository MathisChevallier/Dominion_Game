#ifndef ACTION_H
#define ACTION_H

#include <iostream>
#include <string>
#include <vector>
#include "royaume.hpp"

class Action : public Royaume{
    public:
    Action(const std::string &nom, int cout, const std::vector<std::string> &effet, const std::string &desc, int priorite, const std::string &couleur = "\033[0m");
    ~Action();
    void jouerCarte() const;
};

#endif