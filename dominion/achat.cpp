#include "achat.hpp"


Achat::Achat():tresors_or({}),tresors_argent({}),tresors_cuivre({}),victoires_province({}),victoires_duche({}),victoires_domaine({}),victoires_malediction({}),tab_royaumes({{},{},{},{},{},{},{},{},{},{}})
{
    //initialisation pour deux joueurs
    for (size_t i = 0; i<30; i++){

        if(i<8){
            victoires_province.push_back(PROVINCE);
            victoires_duche.push_back(DUCHE);
            victoires_domaine.push_back(DOMAINE);
        }

        if(i<10){
            tresors_argent.push_back(ARGENT);
            victoires_malediction.push_back(MALEDICTION);
        }

        if(i<16){
            tresors_cuivre.push_back(CUIVRE);
        }  
        tresors_or.push_back(OR);
        tresors_argent.push_back(ARGENT);
        tresors_cuivre.push_back(CUIVRE);
    }
   }

Achat::~Achat(){
    tresors_or.clear();
    tresors_argent.clear();
    tresors_cuivre.clear();
    victoires_province.clear();
    victoires_duche.clear();
    victoires_domaine.clear();
    victoires_malediction.clear();
    tab_royaumes.clear();
}

std::vector<const Carte*>& Achat::getTresors_or()           {return tresors_or;}
std::vector<const Carte*>& Achat::getTresors_argent()       {return tresors_argent;}
std::vector<const Carte*>& Achat::getTtresors_cuivre()      {return tresors_cuivre;}
std::vector<const Carte*>& Achat::getVictoires_province()   {return victoires_province;}
std::vector<const Carte*>& Achat::getVictoires_duche()      {return victoires_duche;}
std::vector<const Carte*>& Achat::getVictoires_domaine()    {return victoires_domaine;}
std::vector<const Carte*>& Achat::getVictoires_malediction(){return victoires_malediction;}

void Achat::afficherLigneAchat(){
    std::cout<<"Voici la ligne d'achat : \n";
    std::cout<< "   " << OR <<"       -> Cartes restantes: " <<tresors_or.size()        <<" | Cout: " << OR->getCout()      <<" | Valeur: " << OR->getValeur() << std::endl;
    std::cout<< "   " << ARGENT <<"   -> Cartes restantes: " <<tresors_argent.size()    <<" | Cout: " << ARGENT->getCout()  <<" | Valeur: " << ARGENT->getValeur() << std::endl;
    std::cout<< "   " << CUIVRE <<"   -> Cartes restantes: " <<tresors_cuivre.size()    <<" | Cout: " << CUIVRE->getCout()  <<" | Valeur: " << CUIVRE->getValeur() << std::endl;
    std::cout<< "   " << PROVINCE <<" -> Cartes restantes: " <<victoires_province.size()<<" | Cout: " << PROVINCE->getCout()<<" | Points: " << PROVINCE->getPoints()<< std::endl;
    std::cout<< "   " << DUCHE <<"    -> Cartes restantes: " <<victoires_duche.size()   <<" | Cout: " << DUCHE->getCout()   <<" | Points: " << DUCHE->getPoints()   << std::endl;
    std::cout<< "   " << DOMAINE <<"  -> Cartes restantes: " <<victoires_domaine.size() <<" | Cout: " << DOMAINE->getCout() <<" | Points: " << DOMAINE->getPoints() << std::endl;
    std::cout<< "   " << MALEDICTION <<" -> Cartes restantes: " <<victoires_malediction.size()<<" | Cout: " <<MALEDICTION->getCout()<<" | Points: " <<MALEDICTION->getPoints()<< "\n";
     
    for (size_t i = 0; i<tab_royaumes.size(); i++){
        if(tab_royaumes.at(i).size()>0){
            std::cout << "   " << tab_royaumes.at(i).at(0) << " -> Cartes restantes: " << tab_royaumes.at(i).size()<< " | Cout: "<<tab_royaumes.at(i).at(0)->getCout() << " | effet: "<< tab_royaumes.at(i).at(0)->getDescriptionEffet()<< std::endl;
        }else {
            std::cout << "   " << "Pile vide.\n";
        }
    }
}

void Achat::completerLigneAchatGauche(int nombreJoueur){
    //deja initialisee pour 2 joueurs
    if(nombreJoueur == 3){
        for (size_t i = 0; i<10; i++){
            getVictoires_malediction().push_back(MALEDICTION);
        }
    }else if(nombreJoueur == 4){
        for (size_t i = 0; i<20; i++){
            getVictoires_malediction().push_back(MALEDICTION);
        }
        for (size_t i = 0; i<4; i++){
            getVictoires_province().push_back(PROVINCE);
            getVictoires_duche().push_back(DUCHE);
            getVictoires_domaine().push_back(DOMAINE);
        }
    }
}

void Achat::completerLigneAchatCentreAuto(int nombreJoueur){
    for(size_t i = 0; i<10; i++){
        //Jardin !!!
        if(Partie::p_cartes_utilisees.at(i)->getNom() == "Jardins"){
            if(nombreJoueur==2){
                for(size_t j = 0; j<8; j++){
                    tab_royaumes.at(i).push_back(JARDINS);
                }
            }else {
                for(size_t j = 0; j<12; j++){
                    tab_royaumes.at(i).push_back(JARDINS);
                }
            }
        }else{
            for(size_t j = 0; j<10; j++){
                tab_royaumes.at(i).push_back(Partie::p_cartes_utilisees.at(i));
            }
        }
    }
}

void Achat::afficherLigneAchatPhaseAchat(int i){
    //Ajouter reste carte tresor et victoire + carte royaume
    unsigned numCarte = 1;
    if(i >= 0){
        std::cout <<  "   " << numCarte << " - " << CUIVRE <<"   -> Cartes restantes: " <<tresors_cuivre.size()    <<" | Cout: " << CUIVRE->getCout()  <<" | Valeur: " << CUIVRE->getValeur() << std::endl;
        numCarte++;
    }
    if(i >= 2){
        std::cout << "   " << numCarte << " - " << DOMAINE <<"  -> Cartes restantes: " <<victoires_domaine.size() <<" | Cout: " << DOMAINE->getCout() <<" | Points: " << DOMAINE->getPoints() << std::endl;
        numCarte++;
    }
    if(i >= 3){
        std::cout << "   " << numCarte << " - " << ARGENT <<"   -> Cartes restantes: " <<tresors_argent.size()    <<" | Cout: " << ARGENT->getCout()  <<" | Valeur: " << ARGENT->getValeur() << std::endl;
        numCarte++;
    }
    if(i >= 8){
        std::cout << "   " << numCarte << " - " << PROVINCE <<" -> Cartes restantes: " <<victoires_province.size()<<" | Cout: " << PROVINCE->getCout()<<" | Points: " << PROVINCE->getPoints()<< std::endl;
        numCarte++;
    }
}
