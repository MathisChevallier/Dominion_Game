#ifndef CARTE_H
#define CARTE_H

#include <iostream>
#include <string>


class Carte{
    protected:
    std::string const c_nom;
    int const c_cout;
    int const c_prio;
    std::string const c_couleur; //permet d'avoir la couleur d'affichage de la carte
    public:
    Carte(const std::string &nom, int cout, int priorite, const std::string &couleur);
    virtual ~Carte();
    std::string getNom() const;
    int getPrioCarte() const;
    //void setPrioCarte(int i);
    std::string getCouleurCarte() const;
    //virtual std::string getDescriptionEffet();
    int getCout() const;
    void mettreDefausse();
    void mettreRebus();
    virtual void jouerCarte() const = 0;     
    friend std::ostream& operator<<(std::ostream& os, const Carte* const &c);
};

#endif