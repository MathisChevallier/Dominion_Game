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

   Achat::~Achat(){}

    std::vector<const Carte*>& Achat::getTresors_or()           {return tresors_or;}
    std::vector<const Carte*>& Achat::getTresors_argent()       {return tresors_argent;}
    std::vector<const Carte*>& Achat::getTtresors_cuivre()      {return tresors_cuivre;}
    std::vector<const Carte*>& Achat::getVictoires_province()   {return victoires_province;}
    std::vector<const Carte*>& Achat::getVictoires_duche()      {return victoires_duche;}
    std::vector<const Carte*>& Achat::getVictoires_domaine()    {return victoires_domaine;}
    std::vector<const Carte*>& Achat::getVictoires_malediction(){return victoires_malediction;}

    void Achat::afficherLigneAchat(){
        std::cout<<"taille tresors_or: "<< tresors_or.size()<<"\n";
        std::cout<<"taille tresors_argent: "<< tresors_argent.size()<<"\n";
        std::cout<<"taille tresors_cuivre: "<< tresors_cuivre.size()<<"\n";
        std::cout<<"taille victoires_province: "<< victoires_province.size()<<"\n";
        std::cout<<"taille victoires_duche: "<< victoires_duche.size()<<"\n";
        std::cout<<"taille victoires_domaine: "<< victoires_domaine.size()<<"\n";
        std::cout<<"taille victoires_malediction: "<< victoires_malediction.size()<<"\n";
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
        std::cout<< nombreJoueur << "taille getCartesUtilisees: " << Partie::p_cartes_utilisees.size() << std::endl;
        std::cout<< "taille(0): " << Partie::p_cartes_utilisees.at(0) << std::endl;
        std::cout<< "taille(9): " << Partie::p_cartes_utilisees.at(9) << std::endl;
        for(size_t i = 0; i<Partie::p_cartes_utilisees.size(); i++){
            /*
            if(Partie::p_cartes_utilisees.at(i)->getNom() == "Jardin"){
                if(nombreJoueur==2){
                    for(size_t j = 0; j<8; j++){
                        tab_royaumes.at(i).push_back(JARDIN);
                    }
                }else {
                    for(size_t j = 0; j<12; j++){
                        tab_royaumes.at(i).push_back(JARDIN);
                    }
                }
            }else{
            */
                for(size_t j = 0; j<10; j++){
                    tab_royaumes.at(i).push_back(Partie::p_cartes_utilisees.at(i));
                }
            //}
        }

     }


        
