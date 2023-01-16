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
        Joueur::j_joueurStatic->getMainJeu()->ajouterAchatTour(1);
    }
    else if(s == "+1 Tresor"){
        //Recupere un tresor pour la phase d'achat
        Joueur::j_joueurStatic->getMainJeu()->ajouterTresorTour(1);
    }
    else if(s == "Ecarter 1 Carte de la main"){ 
        //Ecarte une carte de la main
        Joueur::j_joueurStatic->enleverCarteDeLaMain(MainJeu::m_carteStatic);
        Partie::p_partieStatic->ajouterCarteRebutDeLaPartie(MainJeu::m_carteStatic);
    }
    else if(s == "Défausser 1 Carte de la main"){
        //Defausse une carte de la main
        Joueur::j_joueurStatic->defausserCarteDeLaMain(MainJeu::m_carteStatic);
    }       
    else if(s == "Défausser premiere Carte du deck"){ 
        //Defausse une carte du deck
        Joueur::j_joueurStatic->defausserPremiereCarteDuDeck();
    }

    // Effet spécifique à une carte => Certaines cartes ne sont pas présentes car n'utilisent que des effets de base
    else if(s == "effet Atelier"){
        Joueur::j_joueurStatic->acheterCarte(4);
    }
    else if(s == "effet Aventurier"){
        int carteTresor = 0;
        std::vector<const Carte*> cartesDevoilees = {};
        while(carteTresor != 2){
            const Carte* c = Joueur::j_joueurStatic->devoilerCarte();
            if(dynamic_cast<const Tresor*>(c) != nullptr){
                Joueur::j_joueurStatic->ajouterCarteALaMain(c);
                carteTresor++;
            }
            else{
                cartesDevoilees.push_back(c);
            }
        }
        for(const Carte* c : cartesDevoilees){
            Joueur::j_joueurStatic->getDefausse()->ajouterCarteDefausse(c);
        }
        cartesDevoilees.clear();
    }
    else if(s == "effet Bibliotheque"){
        std::vector<const Carte*> cartesActionsDeCote = {};
        while(Joueur::j_joueurStatic->getMainJeu()->getMain().size() < 7){
            const Carte* c = Joueur::j_joueurStatic->devoilerCarte();
            if(dynamic_cast<const Royaume*>(c) != nullptr){
                char choix;
                std::cout << "Voulez vous mettre la carte " << c << "de côté (o ou n) : ";
                std::cin >> choix;
                while(choix != 'o' && choix != 'n'){
                    std::cerr << "\033[1;31m" << choix << " n'est pas une réponse convenable. \033[0m" << std::endl;
                    std::cout << "Voulez vous mettre la carte " << c << "de côté (o ou n) : ";
                    std::cin >> choix;
                }
                if(choix == 'o'){
                    cartesActionsDeCote.push_back(c);
                }
                else{
                    Joueur::j_joueurStatic->ajouterCarteALaMain(c);
                }
            }
            else{
                Joueur::j_joueurStatic->ajouterCarteALaMain(c);
            }
        }
        for(const Carte* c : cartesActionsDeCote){
            Joueur::j_joueurStatic->getDefausse()->ajouterCarteDefausse(c);
        }
        cartesActionsDeCote.clear();
    }
    else if(s == "effet Bureaucrate"){
        Joueur::j_joueurStatic->getDeck()->ajouterCarteSurDeck(ARGENT); //normalement enleve de phase achat du style Partie::p_partieStatic->getAchatPartie()->achatCarte(ARGENT) =>doit enlever de achat la carte
        std::cout << Joueur::j_joueurStatic << "reçoit une carte Argent et la place sur son deck" << std::endl;

        Joueur* jTour = Joueur::j_joueurStatic;
        for(Joueur* j : Partie::p_partieStatic->getJoueurPartie()){
            bool reaction = effetAttaque(j);
            if(reaction==false){
                Joueur::j_joueurStatic = j;
                bool presence = false;
                for(const Carte* c : Joueur::j_joueurStatic->getMainJeu()->getMain()){
                    if(dynamic_cast<const Victoire*>(c) != nullptr){
                        presence = true;
                        Joueur::j_joueurStatic->ajouterCarteSurLeDeck(c);
                        std::cout << Joueur::j_joueurStatic << "place la carte " << c << "sur son deck." << std::endl;
                        break;
                    }
                }
                if(presence == false){
                    std::cout << Joueur::j_joueurStatic << "n'a pas de carte victoire en main." << std::endl;
                    Joueur::j_joueurStatic->getMainJeu();
                }
                Joueur::j_joueurStatic = jTour;
            }
        }
    }
    else if(s == "effet Cave"){
        std::cout << "Défaussez autant de cartes que vous voulez. \033[1m+1 Carte\033[0m par carte défaussée." << std::endl;
        int CarteAPiocher = 0;
        while(Joueur::j_joueurStatic->getMainJeu()->getMain().size() != 0){
            std::cout << "Voici les cartes de votre main : " << std::endl;
            std::vector<const Carte*> carteMain = {};
            unsigned int numCarte = 1;
            for(const Carte *c : Joueur::j_joueurStatic->getMainJeu()->getListeCartesMain()){
                carteMain.push_back(c);
                std::cout << "  " << numCarte << " - " << c << std::endl;
                numCarte++;
            }
            unsigned int choixCarte;
            std::cout << "Pour défausser une carte, tapez son numéro sinon tapez 0 : ";
            std::cin >> choixCarte;
            while(choixCarte >= numCarte){
                std::cerr << "\033[1;31m" << choixCarte << " n'est pas une réponse convenable. \033[0m" << std::endl;
                std::cout << "Pour défausser une carte, tapez son numéro sinon tapez 0 : ";
                std::cin >> choixCarte;
            }
            if(choixCarte == 0){
                carteMain.clear();
                break;
            }
            else{
                Joueur::j_joueurStatic->defausserCarteDeLaMain(carteMain[choixCarte-1]);
                CarteAPiocher++;
            }
            carteMain.clear();
        }
        for(int i=0;i<CarteAPiocher;i++){
            Joueur::j_joueurStatic->piocherCarte();
        }
    }
    else if(s == "effet Chambre du Conseil"){
        Joueur* jTour = Joueur::j_joueurStatic;
        for(Joueur* j : Partie::p_partieStatic->getJoueurPartie()){
            if(j == jTour){}
            else{
                Joueur::j_joueurStatic = j;
                j->piocherCarte();
                std::cout << j << "pioche une carte." << std::endl;
                Joueur::j_joueurStatic = jTour;
            }
        }
    }
    else if(s == "effet Chancelier"){
        for(const Carte* carte : Joueur::j_joueurStatic->getDeck()->getListeCartesDeck()){
            MainJeu::m_carteStatic = const_cast<Carte*>(carte);
            effetCarte("Défausser premiere Carte du deck");
        }
        std::cout << Joueur::j_joueurStatic << "défausse son deck." << std::endl;
    }
    else if(s == "effet Chapelle"){
        Carte* carteJouee = MainJeu::m_carteStatic;
        for(int i=1;i<=4;i++){
            std::vector<const Carte*> carteMain = {};
            if(Joueur::j_joueurStatic->getMainJeu()->getMain().size() == 0){
                carteMain.clear();
                break;
            }
            std::cout << "Voici les cartes de votre main : " << std::endl;
            unsigned int numCarte = 1;
            for(const Carte *c : Joueur::j_joueurStatic->getMainJeu()->getListeCartesMain()){
                carteMain.push_back(c);
                std::cout << "  " << numCarte << " - " << c << std::endl;
                numCarte++;
            }
            unsigned int choixCarte;
            std::cout << "Pour écarter une carte, tapez son numéro sinon tapez 0 : ";
            std::cin >> choixCarte;
            while(choixCarte >= numCarte){
                std::cerr << "\033[1;31m" << choixCarte << " n'est pas une réponse convenable. \033[0m" << std::endl;
                std::cout << "Pour écarter une carte, tapez son numéro sinon tapez 0 : ";
                std::cin >> choixCarte;
            }
            if(choixCarte == 0){
                break;
            }
            else{
                MainJeu::m_carteStatic = const_cast<Carte*>(carteMain[choixCarte-1]);
                effetCarte("Ecarter 1 Carte de la main");  
                MainJeu::m_carteStatic = carteJouee;         
            }
            carteMain.clear();
        }
    }
    else if(s == "effet Douves"){
        //Peut être mettre std::cout ici mais problème pour avoir le boolean en choix
    }
    else if(s == "effet Espion"){
        Joueur* jTour = Joueur::j_joueurStatic;
        for(Joueur* j : Partie::p_partieStatic->getJoueurPartie()){
            bool reaction = effetAttaque(j);
            //Attaque est même appliqué au joueur qui joue
            if(j == jTour){
                reaction = false;
            }
            if(reaction==false){
                Joueur::j_joueurStatic = j;
                const Carte* c = Joueur::j_joueurStatic->devoilerCarte();
                char choix;
                std::cout << jTour << "choisit si la carte est défaussée ou replacée sur le deck (d ou r) : ";
                std::cin >> choix;
                while(choix != 'd' && choix != 'r'){
                    std::cerr << "\033[1;31m" << choix << " n'est pas une réponse convenable. \033[0m" << std::endl;
                    std::cout << jTour << "choisit si la carte est défaussée ou replacée sur le deck (d ou r) : ";
                    std::cin >> choix;
                }
                if(choix == 'd'){
                    Joueur::j_joueurStatic->defausserCarteDeLaMain(c);
                }
                else{
                    Joueur::j_joueurStatic->ajouterCarteSurLeDeck(c);
                }
                Joueur::j_joueurStatic = jTour;
            }
        }
    }
    else if(s == "effet Festin"){
        effetCarte("Ecarter 1 Carte de la main");
        Joueur::j_joueurStatic->acheterCarte(4);
    }
    else if(s == "effet Jardins"){
        int pointsVictoire = Joueur::j_joueurStatic->getDeck()->getListeCartesDeck().size()/10;
        Joueur::j_joueurStatic->ajouterPointsVictoire(pointsVictoire);
    }
    else if(s == "effet Milice"){
        Joueur* jTour = Joueur::j_joueurStatic;
        for(Joueur* j : Partie::p_partieStatic->getJoueurPartie()){
            bool reaction = effetAttaque(j);
            if(reaction==false){
                Joueur::j_joueurStatic = j;
                Carte* carteJouee = MainJeu::m_carteStatic;
                while(Joueur::j_joueurStatic->getMainJeu()->getMain().size() > 3){
                    std::vector<const Carte*> carteMain = {};
                    std::cout << "Voici les cartes de votre main : " << std::endl;
                    unsigned int numCarte = 1;
                    for(const Carte *c : Joueur::j_joueurStatic->getMainJeu()->getListeCartesMain()){
                        carteMain.push_back(c);
                        std::cout << "  " << numCarte << " - " << c << std::endl;
                        numCarte++;
                    }
                    unsigned int choixCarte;
                    std::cout << "Défaussez une carte, tapez son numéro : ";
                    std::cin >> choixCarte;
                    while(choixCarte >= numCarte || choixCarte == 0){
                        std::cerr << "\033[1;31m" << choixCarte << " n'est pas une réponse convenable. \033[0m" << std::endl;
                        std::cout << "Défaussez une carte, tapez son numéro : ";
                        std::cin >> choixCarte;
                    }
                    MainJeu::m_carteStatic = const_cast<Carte*>(carteMain[choixCarte-1]);
                    effetCarte("Défausser 1 Carte de la main");  
                    MainJeu::m_carteStatic = carteJouee;  
                    carteMain.clear();       
                }
                std::cout << std::endl;
                Joueur::j_joueurStatic = jTour;
            }
        }
    }
    else if(s == "effet Mine"){
        std::cout << "Vous pouvez écarter une carte Trésor de votre main et recevoir une carte Trésor coûtant 3 de plus. ";
        std::vector<const Carte*> cartesTresorMain = {};
        for(const Carte* c : Joueur::j_joueurStatic->getMainJeu()->getMain()){
            if(dynamic_cast<const Tresor*>(c) != nullptr){
                cartesTresorMain.push_back(c);
            }
        }
        if(cartesTresorMain.size() == 0){}
        else{
            unsigned int numCarte = 1;
            for(const Carte *c : cartesTresorMain){
                std::cout << "  " << numCarte << " - " << c << std::endl;
                numCarte++;
            }
            unsigned int choixCarte;
            std::cout << "Ecartez une carte Trésor, tapez son numéro sinon tapez 0 : ";
            std::cin >> choixCarte;
            while(choixCarte >= numCarte){
                std::cerr << "\033[1;31m" << choixCarte << " n'est pas une réponse convenable. \033[0m" << std::endl;
                std::cout << "Ecartez une carte Trésor, tapez son numéro sinon tapez 0 : ";
                std::cin >> choixCarte;
            }
            if(choixCarte == 0){}
            else{
                Carte *cJeu = MainJeu::m_carteStatic;
                MainJeu::m_carteStatic = const_cast<Carte*> (cartesTresorMain[choixCarte-1]);
                effetCarte("Ecarter 1 Carte de la main");
                MainJeu::m_carteStatic = cJeu;
                // ajouter à la main une nouvelle carte trésor
            }
        }
        cartesTresorMain.clear();
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
        std::vector<const Carte*> carteMain = {};
        std::cout << "Voici les cartes de votre main : " << std::endl;
        unsigned int numCarte = 1;
        for(const Carte *c : Joueur::j_joueurStatic->getMainJeu()->getListeCartesMain()){
            carteMain.push_back(c);
            std::cout << "  " << numCarte << " - " << c << std::endl;
            numCarte++;
        }
        unsigned int choixCarte;
        std::cout << "Ecartez une carte et recevez une carte coûtant jusqu'à 2 Trésors de plus, tapez son numéro : ";
        std::cin >> choixCarte;
        while(choixCarte >= numCarte || choixCarte == 0){
            std::cerr << "\033[1;31m" << choixCarte << " n'est pas une réponse convenable. \033[0m" << std::endl;
            std::cout << "Ecartez une carte et recevez une carte coûtant jusqu'à 2 Trésors de plus, tapez son numéro : ";
            std::cin >> choixCarte;
        }
        int cout = carteMain[choixCarte-1]->getCout();
        Carte *cJeu = MainJeu::m_carteStatic;
        MainJeu::m_carteStatic = const_cast<Carte*> (carteMain[choixCarte-1]);
        effetCarte("Ecarter 1 Carte de la main");
        MainJeu::m_carteStatic = cJeu;
        std::cout << cout ; //pour variable unused
        //Phase d'achat avec 2 de plus
        carteMain.clear();
    }
    else if(s == "effet Salle du Trone"){
        //std::vector<const Carte*> carteMain = {};
        std::vector <const Royaume*> carteRoyaume = {};
        for(const Carte *c : Joueur::j_joueurStatic->getMainJeu()->getListeCartesMain()){
            if (dynamic_cast<const Action*>(c) != nullptr || dynamic_cast<const ActionAttaque*>(c) != nullptr || dynamic_cast<const ActionReaction*>(c) != nullptr) {
                const Royaume* r1 = static_cast<const Royaume*>(c);
                carteRoyaume.push_back(r1);
            }    
        }
        if(carteRoyaume.size() != 0){
            std::cout << "Voici les cartes actions de votre main : " << std::endl;
            int numCarte = 1;
            for(const Royaume *r : carteRoyaume){
                std::cout << "  " << numCarte << " - " << r << std::endl;
                numCarte++;
            }
            unsigned int choixCarte;
            std::cout << "Pour jouer une carte deux fois, tapez son numéro sinon tapez 0 : ";
            std::cin >> choixCarte;
            while(choixCarte > carteRoyaume.size()){
                std::cerr << "\033[1;31m" << choixCarte << " n'est pas une réponse convenable. \033[0m" << std::endl;
                std::cout << "Pour jouer une carte deux fois, tapez son numéro sinon tapez 0 : ";
                std::cin >> choixCarte;
            }
            if(choixCarte == 0){}
            else{
                MainJeu::m_carteStatic = const_cast<Royaume*> (carteRoyaume[choixCarte-1]);
                Joueur::j_joueurStatic->ajouterACartesJouees(carteRoyaume[choixCarte-1]);
                for(int i=0;i<2;i++){
                    std::cout << Joueur::j_joueurStatic << "joue ";
                    carteRoyaume[choixCarte-1]->jouerCarte();
                }
            }
        }
        carteRoyaume.clear();
        std::cout << std::endl;
    }
    else if(s == "effet Sorciere"){
        Joueur* jTour = Joueur::j_joueurStatic;
        for(Joueur* j : Partie::p_partieStatic->getJoueurPartie()){
            bool reaction = effetAttaque(j);
            if(reaction == false){
                Joueur::j_joueurStatic = j;
                Joueur::j_joueurStatic->getDefausse()->ajouterCarteDefausse(MALEDICTION);
                std::cout << Joueur::j_joueurStatic << "reçoit une " << MALEDICTION << "." << std::endl;
                Joueur::j_joueurStatic = jTour;

            }
        }
        //Enlever de la liste achat
    }
    else if(s == "effet Voleur"){
        Joueur* jTour = Joueur::j_joueurStatic;
        std::vector<const Carte*> carteTresorVolees = {};
        for(Joueur* j : Partie::p_partieStatic->getJoueurPartie()){
            bool reaction = effetAttaque(j);
            if(reaction == false){
                Joueur::j_joueurStatic = j;
                std::vector<const Carte*> carteTresorVoleesJoueur = {};
                for(int i=0;i<2;i++){
                    const Carte* c = Joueur::j_joueurStatic->devoilerCarte();
                    if(dynamic_cast<const Tresor*>(c) == nullptr){
                        Joueur::j_joueurStatic->getDefausse()->ajouterCarteDefausse(c);
                    }
                    else{
                        carteTresorVoleesJoueur.push_back(c);
                    }
                }
                if(carteTresorVoleesJoueur.size() == 0){}
                else if(carteTresorVoleesJoueur.size() == 1){
                    carteTresorVolees.push_back(carteTresorVoleesJoueur[0]);
                }
                else{
                    //joueur jTour choisit parmi les deux
                    std::cout << "Voici les cartes Trésors dévoilées : " << std::endl;
                    int numCarte = 1;
                    for(const Carte *r : carteTresorVoleesJoueur){
                        std::cout << "  " << numCarte << " - " << r << std::endl;
                        numCarte++;
                    }
                    unsigned int choixCarte;
                    std::cout << "Ecarter la carte Trésor de votre choix, tapez son numéro : ";
                    std::cin >> choixCarte;
                    while(choixCarte > carteTresorVoleesJoueur.size()  && choixCarte < 1){
                        std::cerr << "\033[1;31m" << choixCarte << " n'est pas une réponse convenable. \033[0m" << std::endl;
                        std::cout << "Ecarter la carte Trésor de votre choix, tapez son numéro : ";
                        std::cin >> choixCarte;
                    }
                    carteTresorVolees.push_back(carteTresorVoleesJoueur[choixCarte - 1]);
                    if(choixCarte == 1){
                        Joueur::j_joueurStatic->getDefausse()->ajouterCarteDefausse(carteTresorVoleesJoueur[1]);
                    }
                    else{
                        Joueur::j_joueurStatic->getDefausse()->ajouterCarteDefausse(carteTresorVoleesJoueur[0]);
                    }
                }
                carteTresorVoleesJoueur.clear();
                Joueur::j_joueurStatic->getDefausse()->afficher();
                Joueur::j_joueurStatic = jTour;
            }
            std::cout << std::endl;
        }
        while(carteTresorVolees.size() != 0){
            std::cout << "Parmi ces cartes Trésors écartées, vous pouvez recevoir celles de votre choix : " << std::endl;
            int numCarte = 1;
            for(const Carte *r : carteTresorVolees){
                std::cout << "  " << numCarte << " - " << r << std::endl;
                numCarte++;
            }
            unsigned int choix;
            std::cout << "Choisissez la carte Trésor de votre choix, tapez son numéro sinon tapez 0 : ";
            std::cin >> choix;
            while(choix > carteTresorVolees.size()){
                std::cerr << "\033[1;31m" << choix << " n'est pas une réponse convenable. \033[0m" << std::endl;
            std::cout << "Choisissez la carte Trésor de votre choix, tapez son numéro sinon tapez 0 : ";
                std::cin >> choix;
            }
            if(choix == 0){
                break;
            }
            else{
                Joueur::j_joueurStatic->getDefausse()->ajouterCarteDefausse(carteTresorVolees[choix - 1]);
                carteTresorVolees.erase(carteTresorVolees.begin() + choix - 1);
            }
        }
        //Demander quelles cartes il garde et la/les mettre dans la défausse et détruire du vecteur
        for(const Carte* c : carteTresorVolees){
            Partie::p_partieStatic->ajouterCarteRebutDeLaPartie(c);
        }
        std::cout << Partie::p_partieStatic->getRebut()->getCarteRebut().size();
        Joueur::j_joueurStatic->getDefausse()->afficher();
        carteTresorVolees.clear();
    }
    //Exception pas d'effet meme si normalement ca n'arrive pas car c'est nous qui créons les effets pour chaque carte
    else{

    }
}


bool effetAttaque(Joueur* j){
    if(j == Joueur::j_joueurStatic){ return true;}
    else{
        for(const Carte* c : j->getMainJeu()->getMain()){
            char choixJ;
            if (dynamic_cast<const ActionReaction*>(c) != nullptr) {
                std::cout << j << "peut jouer la carte " << c << "pour éviter l'Attaque (o ou n) : ";
                std::cin >> choixJ;
                while(choixJ != 'o' && choixJ != 'n'){
                    std::cerr << "\033[1;31m" << choixJ << " n'est pas une réponse convenable. \033[0m" << std::endl;
                    std::cout << j << " peut jouer la carte " << c << "pour éviter l'Attaque (o ou n) : ";
                    std::cin >> choixJ;
                }
                if(choixJ == 'o'){
                    return true;
                }
                break;
            }
        }
        std::cout << j << "est attaqué." << std::endl;
        return false;
    }
}

/*
void effetAttaque(){
    if(MainJeu::m_carteStatic->getNom() == "Bureaucrate"){
        Joueur::j_joueurStatic->ajouterCarteSurLeDeck(ARGENT); //normalement enleve de phase achat du style Partie::p_partieStatic->getAchatPartie()->achatCarte(ARGENT) =>doit enlever de achat la carte
        std::cout << Joueur::j_joueurStatic << "reçoit une carte Argent et la place sur son deck" << std::endl;
    }

    for(Joueur* j : Partie::p_partieStatic->getJoueurPartie()){
        if(j == Joueur::j_joueurStatic){}
        else{
            Joueur* jTour = Joueur::j_joueurStatic;
            Joueur::j_joueurStatic = j;
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
                effetCarte("effet " + MainJeu::m_carteStatic->getNom());
            }
            Joueur::j_joueurStatic = jTour;
        }
    }
}
*/
