#include "effet.hpp"

void effetCarte(const std::string &s){
    //Faire un if and else nom carte
    
    // Effets de base
    if(s == "+1 Carte"){
        //Pioche une carte
        Joueur::j_joueurStatic->piocherCarte();
    }
    else if(s == "+1 Action"){
        //Recupere une action
        Joueur::j_joueurStatic->getMainJeu()->ajouterAction(1);
    }
    else if(s == "+1 Achat"){
        //Recupere un achat
        Joueur::j_joueurStatic->getMainJeu()->ajouterAchat(1);
    }
    else if(s == "+1 Tresor"){
        //Recupere un tresor pour la phase d'achat
        Joueur::j_joueurStatic->getMainJeu()->ajouterTresorTour(1);
    }
    else if(s == "Ecarter 1 Carte de la main"){ 
        //Ecarte une carte de la main
        Joueur::j_joueurStatic->ecarterCarteDeLaMain(MainJeu::m_carteStatic);
    }
    else if(s == "Défausser 1 Carte de la main"){
        //Defausse une carte de la main
        Joueur::j_joueurStatic->defausserCarteDeLaMain(MainJeu::m_carteStatic);
    }       
    else if(s == "Défausser premiere Carte du deck"){ 
        //Defausse une carte du deck
        Joueur::j_joueurStatic->defausserPremiereCarteDuDeck();
    }
    else if(s == "Devoilez 1 Carte"){

    }
    
    else if(s == "effet Attaque"){
        effetAttaque();
    }
    // Effet spécifique à une carte => Certaines cartes ne sont pas présentes car n'utilisent que des effets de base
    else if(s == "effet Atelier"){
        Joueur::j_joueurStatic->acheterCarte(4);
    }
    else if(s == "effet Aventurier"){

    }
    else if(s == "effet Bibliotheque"){

    }
    else if(s == "effet Bureaucrate"){
        bool presence = false;
        for(const Carte* c : Joueur::j_joueurStatic->getMainJeu()->getMain()){
            if(dynamic_cast<const Victoire*>(c) != nullptr){
                presence = true;
                Joueur::j_joueurStatic->ajouterCarteSurLeDeck(c);
                break;
            }
        }
        if(presence == false){
            std::cout << Joueur::j_joueurStatic << "n'a pas de carte victoire en main." << std::endl;
            Joueur::j_joueurStatic->getMainJeu();
        }
    }
    else if(s == "effet Cave"){

    }
    else if(s == "effet Chambre du Conseil"){

    }
    else if(s == "effet Chancelier"){
        for(const Carte* carte : Joueur::j_joueurStatic->getDeck()->getListeCartesDeck()){
            MainJeu::m_carteStatic = const_cast<Carte*>(carte);
            effetCarte("Défausser premiere Carte du deck");
        }
    }
    else if(s == "effet Chapelle"){
        char choixJoueur;
        for(int i=1;i<=4;i++){
            std::cout << "Voulez vous écarter une carte de votre main (o ou n) : ";
            std::cin >> choixJoueur;
            while(choixJoueur != 'o' || choixJoueur != 'n'){
                std::cerr << "\033[1;31m" << choixJoueur << " n'est pas une réponse convenable. \033[0m" << std::endl;
                std::cout << "Voulez vous écarter une carte de votre main (o ou n) : ";
                std::cin >> choixJoueur;
            }
            if(choixJoueur == 'n'){
                break;
            }
            else{
                //Demander ecarter
            }
        }
    }
    else if(s == "effet Douves"){

    }
    else if(s == "effet Espion"){

    }
    else if(s == "effet Festin"){
        effetCarte("Ecarter 1 Carte de la main");
        Joueur::j_joueurStatic->acheterCarte(4);
    }
    else if(s == "effet Jardins"){

    }
    else if(s == "effet Milice"){

    }
    else if(s == "effet Mine"){

    }
    else if(s == "effet Preteur sur Gages"){
        bool presenceCuivre = false;
        for(const Carte* c : Joueur::j_joueurStatic->getMainJeu()->getMain()){
            if(c->getNom() == "Cuivre"){
                MainJeu::m_carteStatic = const_cast<Carte*>(c);
                effetCarte("Ecarter 1 Carte de la main");
                presenceCuivre = true;
                break;
            }
        }
        if(presenceCuivre){
            Joueur::j_joueurStatic->getMainJeu()->ajouterTresorTour(3);
        }
    }
    else if(s == "effet Renovation"){

    }
    else if(s == "effet Salle du Trone"){

    }
    else if(s == "effet Sorciere"){

    }
    else if(s == "effet Voleur"){

    }
    //Exception pas d'effet meme si normalement ca n'arrive pas car c'est nous qui créons les effets pour chaque carte
    else{

    }
}

void effetAttaque(){
    for(Joueur* j : Partie::p_partieStatic->getJoueurPartie()){
        if(MainJeu::m_carteStatic->getNom() == "Bureaucrate"){
            Joueur::j_joueurStatic->ajouterCarteSurLeDeck(ARGENT); //normalement enleve de phase achat du style Partie::p_partiStatic->getAchatPartie()->achatCarte(ARGENT) =>doit enlever de achat la carte
            std::cout << Joueur::j_joueurStatic << "reçoit une carte Argent et la place sur son deck" << std::endl;
        }


        if(j == Joueur::j_joueurStatic){}
        else{
            Joueur* jTour = Joueur::j_joueurStatic;
            bool Reaction = false;
            for(const Carte* c : j->getMainJeu()->getMain()){
                char choixJ;
                if (dynamic_cast<const ActionReaction*>(c) != nullptr) {
                    std::cout << Joueur::j_joueurStatic << "peut jouer la carte " << c << "pour éviter l'Attaque (o ou n) : ";
                    std::cin >> choixJ;
                    while(choixJ != 'o' && choixJ != 'n'){
                        std::cerr << "\033[1;31m" << choixJ << " n'est pas une réponse convenable. \033[0m" << std::endl;
                        std::cout << Joueur::j_joueurStatic << " peut jouer la carte " << c << "pour éviter l'Attaque (o ou n) : ";
                        std::cin >> choixJ;
                    }
                    if(choixJ == 'o'){
                        Reaction = true;
                    }
                    break;
                }
            }
            if(Reaction == false){
                Joueur::j_joueurStatic = j;
                effetCarte("effet " + MainJeu::m_carteStatic->getNom());
            }
            Joueur::j_joueurStatic = jTour;
        }
    }
}

