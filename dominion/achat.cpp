#include "achat.hpp"

std::map<int, const Carte*> Achat::mapAchat = {};

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

    std::cout<< "   " << OR <<"       -> Cartes restantes: ";
    if(tresors_or.size()>0) {std::cout<<tresors_or.size();} else {std::cout<<"Vide";}
    std::cout<<" | Cout: " << OR->getCout()      <<" | Valeur: " << OR->getValeur() << std::endl;

    std::cout<< "   " << ARGENT <<"   -> Cartes restantes: ";
    if(tresors_argent.size()>0) {std::cout<<tresors_argent.size();} else {std::cout<<"Vide";}
    std::cout<<" | Cout: " << ARGENT->getCout()  <<" | Valeur: " << ARGENT->getValeur() << std::endl;

    std::cout<< "   " << CUIVRE <<"   -> Cartes restantes: ";
    if(tresors_cuivre.size()>0) {std::cout<<tresors_cuivre.size();} else {std::cout<<"Vide";}
    std::cout<<" | Cout: " << CUIVRE->getCout()  <<" | Valeur: " << CUIVRE->getValeur() << std::endl;

    std::cout<< "   " << PROVINCE <<" -> Cartes restantes: ";
    if(victoires_province.size()>0) {std::cout<<victoires_province.size();} else {std::cout<<"Vide";}
    std::cout<<"  | Cout: " << PROVINCE->getCout()<<" | Points: " << PROVINCE->getPoints()<< std::endl;

    std::cout<< "   " << DUCHE <<"    -> Cartes restantes: ";
    if(victoires_duche.size()>0) {std::cout<<victoires_duche.size();} else {std::cout<<"Vide";}
    std::cout<<"  | Cout: " << DUCHE->getCout()   <<" | Points: " << DUCHE->getPoints()   << std::endl;
    
    std::cout<< "   " << DOMAINE <<"  -> Cartes restantes: ";
    if(victoires_domaine.size()>0) {std::cout<<victoires_domaine.size();} else {std::cout<<"Vide";}
    std::cout<<"  | Cout: " << DOMAINE->getCout() <<" | Points: " << DOMAINE->getPoints() << std::endl;

    std::cout<< "   " << MALEDICTION <<"    -> Cartes restantes: ";
    if(victoires_malediction.size()>0) {std::cout<<victoires_malediction.size();} else {std::cout<<"Vide";}
    std::cout<<" | Cout: " <<MALEDICTION->getCout()<<" | Points: " <<MALEDICTION->getPoints()<< std::endl;

    size_t affichage=14;
    for (size_t i = 0; i<tab_royaumes.size(); i++){
        if(tab_royaumes.at(i).size()>0){
            std::cout << "   " << tab_royaumes.at(i).at(0);
            if(tab_royaumes.at(i).at(0)->getNom().size() < affichage){
                for(size_t j=0; j<affichage-tab_royaumes.at(i).at(0)->getNom().size(); j++){
                    std::cout<<" ";
                }
            }
            std::cout << " -> Cartes restantes: " << tab_royaumes.at(i).size()<< " | Cout: "<<tab_royaumes.at(i).at(0)->getCout() << " | effet: "<< tab_royaumes.at(i).at(0)->getDescriptionEffet()<< std::endl;
        }else {
            std::cout << "   " << "Pile vide.\n";
        }

    }
    std::cout<<"\n";
}

void Achat::completerLigneAchatGauche(int nombreJoueur){
    //deja initialisee pour 2 joueurs
    if(nombreJoueur==3 || nombreJoueur==4){
        if(nombreJoueur == 3){
            for (size_t i = 0; i<10; i++){
                getVictoires_malediction().push_back(MALEDICTION);
            }
        }else if(nombreJoueur == 4){
            for (size_t i = 0; i<20; i++){
                getVictoires_malediction().push_back(MALEDICTION);
            }
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

void Achat::afficherLigneAchatPhaseAchat(int nbTresors){
    unsigned numCarte = 1;
    Achat::mapAchat = {};

    if(nbTresors >= 0){
        if(tresors_cuivre.size()>0){
            std::cout << "\n   " << numCarte << " - " << CUIVRE <<"     -> Cartes restantes: " <<tresors_cuivre.size() <<      " | Cout: " << CUIVRE->getCout()  <<" | Valeur: " << CUIVRE->getValeur() << std::endl;
            mapAchat.insert(std::pair<int,const Carte*>(numCarte,CUIVRE));
            numCarte++;
        }
        if(victoires_malediction.size()>0){
            std::cout << "   " << numCarte << " - " << MALEDICTION <<"-> Cartes restantes: " <<victoires_malediction.size()<<" | Cout: " << MALEDICTION->getCout()<<" | Points: " << MALEDICTION->getPoints()<< std::endl;
            mapAchat.insert(std::pair<int,const Carte*>(numCarte,MALEDICTION));
            numCarte++;
        }
    }
    if(nbTresors >= 2){
        if(victoires_domaine.size()>0){
            std::cout << "   " << numCarte << " - " << DOMAINE <<"    -> Cartes restantes: " <<victoires_domaine.size() <<   "  | Cout: " << DOMAINE->getCout() <<" | Points: " << DOMAINE->getPoints() << std::endl;
            mapAchat.insert(std::pair<int,const Carte*>(numCarte,DOMAINE));
            numCarte++;
        }
    }
    if(nbTresors >= 3){
        if(tresors_argent.size()>0){
            std::cout << "   " << numCarte << " - " << ARGENT <<"     -> Cartes restantes: " <<tresors_argent.size()    <<   " | Cout: " << ARGENT->getCout()  <<" | Valeur: " << ARGENT->getValeur() << std::endl;
            mapAchat.insert(std::pair<int,const Carte*>(numCarte,ARGENT));
            numCarte++;
        }
    }
    if(nbTresors >= 5){
        if(victoires_duche.size()>0){
            std::cout << "   " << numCarte << " - " << DUCHE <<"      -> Cartes restantes: " <<victoires_duche.size()<<      " | Cout: " << DUCHE->getCout()<<" | Points: " << DUCHE->getPoints()<< std::endl;
            mapAchat.insert(std::pair<int,const Carte*>(numCarte,DUCHE));
            numCarte++;
        }
    }
    if(nbTresors >= 6){
        if(tresors_or.size()>0){
            std::cout << "   " << numCarte << " - " << OR <<"         -> Cartes restantes: " <<tresors_or.size()<<           " | Cout: " << OR->getCout()<<" | Points: " << OR->getValeur()<< std::endl;
            mapAchat.insert(std::pair<int,const Carte*>(numCarte,OR));
            numCarte++;
        }
    }
    if(nbTresors >= 8){
        if(victoires_province.size()>0){
            std::cout << "   " << numCarte << " - " << PROVINCE <<"   -> Cartes restantes: " <<victoires_province.size()<<   " | Cout: " << PROVINCE->getCout()<<" | Points: " << PROVINCE->getPoints()<< std::endl;
            mapAchat.insert(std::pair<int,const Carte*>(numCarte,PROVINCE));
            numCarte++;
        }
    }
    size_t affichage2=10;
    for(size_t i=0; i<tab_royaumes.size(); i++){
        if(tab_royaumes.at(i).size()>0 && tab_royaumes.at(i).at(0)->getCout()<=nbTresors){
            std::cout << "   " << numCarte << " - " << tab_royaumes.at(i).at(0);
            if(numCarte==10){affichage2--;}
            if(tab_royaumes.at(i).at(0)->getNom().size() <= affichage2){
                for(size_t j=0; j<=affichage2-tab_royaumes.at(i).at(0)->getNom().size(); j++){
                    std::cout<<" ";
                }
            }
            std::cout << "-> Cartes restantes: " << tab_royaumes.at(i).size();
            if(tab_royaumes.at(i).size() < 10) {std::cout<<" ";}
            std::cout <<" | Cout: " << tab_royaumes.at(i).at(0)->getCout() << std::endl;
            mapAchat.insert(std::pair<int,const Carte*>(numCarte,tab_royaumes.at(i).at(0)));
            numCarte++;
        }
    }
    std::cout<<"\n";
}

const Carte* Achat::acheterCarte(int achatCarte){
    if(achatCarte==0){
        return nullptr;
    }else {
        if(mapAchat.at(achatCarte)->getNom() == "Or"){
            tresors_or.erase(tresors_or.end() - 1);
        }else if(mapAchat.at(achatCarte)->getNom() == "Argent"){
            tresors_argent.erase(tresors_argent.end() - 1);
        }else if(mapAchat.at(achatCarte)->getNom() == "Cuivre"){
            tresors_cuivre.erase(tresors_cuivre.end() - 1);
        }else if(mapAchat.at(achatCarte)->getNom() == "Province"){
            victoires_province.erase(victoires_province.end() - 1);
        }else if(mapAchat.at(achatCarte)->getNom() == "Duche"){
            victoires_duche.erase(victoires_duche.end() - 1);
        }else if(mapAchat.at(achatCarte)->getNom() == "Domaine"){
            victoires_domaine.erase(victoires_domaine.end() - 1);
        }else if(mapAchat.at(achatCarte)->getNom() == "Malédiction"){
            victoires_malediction.erase(victoires_malediction.end() - 1);
        }else {
            for(size_t i=0; i<tab_royaumes.size(); i++){
                if(tab_royaumes.at(i).size()>0 && (tab_royaumes.at(i).at(0)->getNom() == mapAchat.at(achatCarte)->getNom())){
                    tab_royaumes.at(i).erase(tab_royaumes.at(i).end() - 1);
                }
            }
        }
        return mapAchat.at(achatCarte);
    }
}

std::map<int, const Carte*> Achat::afficherLigneAchatTresor(int nbTresors){
    unsigned numCarte = 1;
    std::map<int, const Carte*> mapAchat;
    if(nbTresors >= 0){
        std::cout << "   " << numCarte << " - " << CUIVRE <<"     -> Cartes restantes: " <<tresors_cuivre.size()    <<   " | Cout: " << CUIVRE->getCout()  <<" | Valeur: " << CUIVRE->getValeur() << std::endl;
        mapAchat.insert(std::pair<int,const Carte*>(numCarte,CUIVRE));
        numCarte++;
    }
    if(nbTresors >= 3){
        std::cout << "   " << numCarte << " - " << ARGENT <<"     -> Cartes restantes: " <<tresors_argent.size()    <<   " | Cout: " << ARGENT->getCout()  <<" | Valeur: " << ARGENT->getValeur() << std::endl;
        mapAchat.insert(std::pair<int,const Carte*>(numCarte,ARGENT));
        numCarte++;
    }
    if(nbTresors >= 6){
        std::cout << "   " << numCarte << " - " << OR <<"     -> Cartes restantes: " <<tresors_or.size()    <<   " | Cout: " << OR->getCout()  <<" | Valeur: " << OR->getValeur() << std::endl;
        mapAchat.insert(std::pair<int,const Carte*>(numCarte,OR));
        numCarte++;
    }
    return mapAchat;
}

const Carte* Achat::acheterCarteTresor(std::map<int, const Carte*> mapAchat){
    std::cout << "Entrez un chiffre pour acheter le trésor associé, 0 pour passer cette phase." << std::endl;
    unsigned int achatCarte = 0;
    std::cin >> achatCarte;
    while ( achatCarte==0 || achatCarte > mapAchat.size()){
        std::cerr << "\033[1;31mVous ne pouvez pas acheter la carte n°" << achatCarte << "\033[0m" << std::endl;
        std::cout << "Entrez un chiffre entre 1 et "<<mapAchat.size()<<" pour acheter la carte, sinon 0 pour ne rien acheter.";
        std::cin >> achatCarte;
    }
    if(achatCarte==0){
        return nullptr;
    }else {
        if(mapAchat.at(achatCarte)->getNom() == "Or"){
            tresors_or.erase(tresors_or.end() - 1);
        }else if(mapAchat.at(achatCarte)->getNom() == "Argent"){
            tresors_argent.erase(tresors_argent.end() - 1);
        }else if(mapAchat.at(achatCarte)->getNom() == "Cuivre"){
            tresors_cuivre.erase(tresors_cuivre.end() - 1);
        }
        return mapAchat.at(achatCarte);
    }
}