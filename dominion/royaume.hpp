#ifndef ROYAUME_H
#define ROYAUME_H

#include <iostream>
#include <string>
#include <vector>
#include "carte.hpp"

//Forward déclaration pour pouvoir utiliser cette fonction dans jouerCarte()
extern void effetCarte(const std::string &s); 

class Royaume : public Carte{
    protected:
    std::vector<std::string> const r_effets;
    std::string const r_descriptionEffet;
    public:
    Royaume(const std::string &nom, int cout, int priorite, const std::string &couleur, const std::vector<std::string> &effet, const std::string &desc);
    virtual ~Royaume();
    std::string getDescriptionEffet() const;
    std::vector<std::string> getEffets() const;
    
    virtual void jouerCarte() const = 0;
};

#endif