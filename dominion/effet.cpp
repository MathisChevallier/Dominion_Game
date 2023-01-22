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
        Joueur::j_joueurStatic->getMainJeu()->ajouterAchatTour(1);
        Joueur::j_joueurStatic->getMainJeu()->ajouterTresorTour(4);
        Joueur::j_joueurStatic->acheterCarte(4);
        while(Joueur::j_joueurStatic->getMainJeu()->getTresorTour() != 0){
            Joueur::j_joueurStatic->getMainJeu()->ajouterTresorTour(-1);
        }
        std::cout << Joueur::j_joueurStatic << "obtient la carte grâce à l'Atelier." << std::endl;
    }
    else if(s == "effet Aventurier"){
        int carteTresor = 0;
        std::vector<const Carte*> cartesDevoilees = {};
        while(carteTresor != 2){
            const Carte* c = Joueur::j_joueurStatic->devoilerCarte();
            if(c->getType() == "Tresor"){
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
        if(Joueur::j_joueurStatic->getType() == "JoueurAI"){
            int nbActionRestanteTour = Joueur::j_joueurStatic->getMainJeu()->getActionsAJouer();
            while(Joueur::j_joueurStatic->getMainJeu()->getMain().size() < 7){
                int nbCarteActionMain = 0;
                int prioActionMaxMain = 0;
                for(const Carte* cContexte : Joueur::j_joueurStatic->getMainJeu()->getMain()){
                    if(cContexte->getType() == "Action" || cContexte->getType() == "ActionAttaque" || cContexte->getType() == "ActionReaction"){
                        nbCarteActionMain++;
                        if(cContexte->getPrioCarte() > prioActionMaxMain){
                            prioActionMaxMain = cContexte->getPrioCarte();
                        }
                    }
                }
                const Carte* c = Joueur::j_joueurStatic->devoilerCarte();
                if(dynamic_cast<const Royaume*>(c) != nullptr){
                    const Royaume* r1 = static_cast<const Royaume*>(c);
                    bool ajoutAction = false;
                    for(std::string s : r1->getEffets()){
                        if(s == "+1 Action"){
                            ajoutAction = true;
                        }
                    }
                    if((nbActionRestanteTour - nbCarteActionMain) > 0  && (ajoutAction || r1->getPrioCarte() > prioActionMaxMain)){
                        Joueur::j_joueurStatic->ajouterCarteALaMain(c);
                        std::cout<<Joueur::j_joueurStatic<<" bot ajoute "<< c << " a sa main.\n";
                    }
                    else{
                        cartesActionsDeCote.push_back(c);
                        std::cout<<Joueur::j_joueurStatic<<" bot met "<< c << " de cote.\n";
                    }
                }else{
                    Joueur::j_joueurStatic->ajouterCarteALaMain(c);
                    std::cout<<Joueur::j_joueurStatic<<" bot ajoute "<< c << " a sa main.\n";
                }
            }
        }else{
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
                    if(c->getType() == "Victoire"){
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
        int CarteAPiocher = 0;
        if(Joueur::j_joueurStatic->getType() == "JoueurAI"){
            for(const Carte *c : Joueur::j_joueurStatic->getMainJeu()->getListeCartesMain()){
                if(c->getType() == "Victoire" || c->getType() == "Royaumevictoire" || c->getNom() == "Cave" || (c->getType() == "Cuivre" && (Partie::p_partieStatic->getNumTour() > 10))){
                    Joueur::j_joueurStatic->defausserCarteDeLaMain(c);
                    std::cout << Joueur::j_joueurStatic<<"defausse "<<c<< ".\n";
                    CarteAPiocher++;
                }
            }
            for(int i=0;i<CarteAPiocher;i++){
                Joueur::j_joueurStatic->piocherCarte();
            }
        }else{
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
        if(Joueur::j_joueurStatic->getType() == "JoueurAI"){
            unsigned int i = 0;
            bool finProche = (Partie::p_partieStatic->getAchat()->nbPileVide() == 2 || Partie::p_partieStatic->getAchat()->getVictoires_province().size() <= 2);
            for(const Carte *c : Joueur::j_joueurStatic->getMainJeu()->getListeCartesMain()){
                if(i<4 && ( c->getNom() == "Malédiction" || (c->getNom() == "Domaine" && !finProche) 
                || (c->getNom() == "Cuivre" && (Partie::p_partieStatic->getNumTour()/Partie::p_partieStatic->getJoueurPartie().size()) > 6) )){
                    MainJeu::m_carteStatic = const_cast<Carte*>(c);
                    effetCarte("Ecarter 1 Carte de la main");  
                    MainJeu::m_carteStatic = carteJouee;
                    i++;
                }
            }
        }else{
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

                if(jTour->getType()=="JoueurAI"){
                    if(jTour->getNomJoueur() != j->getNomJoueur()){
                        if(c->getType()=="Victoire" || c->getType()=="RoyaumeVictoire" || (c->getNom() == "Cuivre" && (Partie::p_partieStatic->getNumTour()/Partie::p_partieStatic->getJoueurPartie().size()) > 6)
                         || c->getPrioCarte()<=10){
                            std::cout << jTour << " choisit de replacer sur le deck la carte "<<c<<".\n";
                            Joueur::j_joueurStatic->ajouterCarteSurLeDeck(c);
                        }else{
                            std::cout << jTour << " choisit de défausser la carte "<<c<<".\n";
                             Joueur::j_joueurStatic->getDefausse()->ajouterCarteDefausse(c);
                        }
                    }else{
                        if(c->getType()=="Victoire" || c->getType()=="RoyaumeVictoire" || (((Partie::p_partieStatic->getNumTour()/Partie::p_partieStatic->getJoueurPartie().size()) > 6) && (c->getNom() == "Cuivre"))
                         || c->getPrioCarte()<=10){
                            std::cout << jTour << " choisit de défausser la carte "<<c<<".\n";
                            Joueur::j_joueurStatic->getDefausse()->ajouterCarteDefausse(c);
                        }else{
                            std::cout << jTour << " choisit de replacer sur le deck la carte "<<c<<".\n";
                            Joueur::j_joueurStatic->ajouterCarteSurLeDeck(c);
                        }
                    }

                }else{
                    char choix;
                    std::cout << jTour << " choisit si la carte est défaussée ou replacée sur le deck (d ou r) : ";
                    std::cin >> choix;
                    while(choix != 'd' && choix != 'r'){
                        std::cerr << "\033[1;31m" << choix << " n'est pas une réponse convenable. \033[0m" << std::endl;
                        std::cout << jTour << " choisit si la carte est défaussée ou replacée sur le deck (d ou r) : ";
                        std::cin >> choix;
                    }
                    if(choix == 'd'){
                        Joueur::j_joueurStatic->getDefausse()->ajouterCarteDefausse(c);
                    }
                    else{
                        Joueur::j_joueurStatic->ajouterCarteSurLeDeck(c);
                    }
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
                if(Joueur::j_joueurStatic->getType() == "JoueurAI"){
                    while(Joueur::j_joueurStatic->getMainJeu()->getMain().size() > 3){
                        const Carte* choixC = nullptr;
                        for(const Carte *c : Joueur::j_joueurStatic->getMainJeu()->getListeCartesMain()){
                            if(choixC == nullptr || c->getType()=="Victoire" || c->getType()=="RoyaumeVictoire" || (c->getPrioCarte() < choixC->getPrioCarte())){
                                choixC = c;
                            }
                        }
                        MainJeu::m_carteStatic = const_cast<Carte*>(choixC);
                        effetCarte("Défausser 1 Carte de la main"); 
                        MainJeu::m_carteStatic = carteJouee;  
                    }
                }else{
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
                }       
            }
            std::cout << std::endl;
            Joueur::j_joueurStatic = jTour;
        }
    }
    else if(s == "effet Mine"){
        if(Joueur::j_joueurStatic->getType() == "JoueurAI"){
            const Carte* cTresorEcarte = nullptr;
            for(const Carte *c : Joueur::j_joueurStatic->getMainJeu()->getListeCartesMain()){
                if(dynamic_cast<const Tresor*>(c) != nullptr && c->getType()!="Or" && (cTresorEcarte == nullptr || dynamic_cast<const Tresor*>(c)->getValeur() > dynamic_cast<const Tresor*>(cTresorEcarte)->getValeur() )){
                    cTresorEcarte = c;
                }
            }
            if(cTresorEcarte == nullptr){
                std::cout << Joueur::j_joueurStatic << " n'a pas de carte Tresor en main." << std::endl;
            }else{
                Carte *cJeu = MainJeu::m_carteStatic;
                MainJeu::m_carteStatic = const_cast<Carte*> (cTresorEcarte);
                effetCarte("Ecarter 1 Carte de la main");
                MainJeu::m_carteStatic = cJeu;

                int cout = cTresorEcarte->getCout();
                const Carte* choix = Partie::p_partieStatic->getAchat()->acheterCarteTresor(cout + 3);
                Joueur::j_joueurStatic->getMainJeu()->ajouterCarteMain(choix);
                std::cout << Joueur::j_joueurStatic << "obtient en main la carte " << choix << " grâce à la Mine." << std::endl;
            }
        }else{
            std::cout << "Vous pouvez écarter une carte Trésor de votre main et recevoir une carte\033[33m Trésor \033[0mcoûtant 3 de plus. " << std::endl;
            std::vector<const Carte*> cartesTresorMain = {};
            for(const Carte* c : Joueur::j_joueurStatic->getMainJeu()->getMain()){
                if(dynamic_cast<const Tresor*>(c) != nullptr){
                    cartesTresorMain.push_back(c);
                }
            }
            if(cartesTresorMain.size() == 0){std::cout << "Vous n'avez pas de carte\033[33m Trésor \033[0men main. ";}
            else{
                unsigned int numCarte = 1;
                for(const Carte *c : cartesTresorMain){
                    std::cout << "  " << numCarte << " - " << c << std::endl;
                    numCarte++;
                }
                unsigned int choixCarte;
                std::cout << "Ecartez une carte Trésor, tapez son numéro sinon tapez 0 : ";
                std::cin >> choixCarte;
                while(std::cin.fail() || choixCarte >= numCarte){
                    std::cerr << "\033[1;31mCe n'est pas une réponse convenable. \033[0m" << std::endl;
                    std::cin.clear(); 
                    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
                    std::cout << "Ecartez une carte Trésor, tapez son numéro sinon tapez 0 : ";
                    std::cin >> choixCarte;
                }
                if(choixCarte == 0){}
                else{
                    Carte *cJeu = MainJeu::m_carteStatic;
                    int cout = cartesTresorMain[choixCarte-1]->getCout();
                    MainJeu::m_carteStatic = const_cast<Carte*> (cartesTresorMain[choixCarte-1]);
                    effetCarte("Ecarter 1 Carte de la main");
                    MainJeu::m_carteStatic = cJeu;
                    const Carte* choix = Partie::p_partieStatic->getAchat()->acheterCarteTresor(cout + 3);
                    Joueur::j_joueurStatic->getMainJeu()->ajouterCarteMain(choix);
                    std::cout << Joueur::j_joueurStatic << "obtient la carte " << choix << " grâce à la carte Mine." << std::endl; 
                }
            }
            cartesTresorMain.clear();
        }
    }
    else if(s == "effet Preteur Sur Gages"){
        Carte *cJeu = MainJeu::m_carteStatic;
        bool presenceCuivre = false;
        for(const Carte* c : Joueur::j_joueurStatic->getMainJeu()->getListeCartesMain()){
            if(c->getNom() == "Cuivre"){
                MainJeu::m_carteStatic = const_cast<Carte*>(c);
                effetCarte("Ecarter 1 Carte de la main");
                presenceCuivre = true;
                break;
            }
        }
        if(presenceCuivre){
            Joueur::j_joueurStatic->getMainJeu()->ajouterTresorTour(3);
            std::cout<<"+3 tresors car une carte cuivre a ete ecartee grace au Preteur sur Gages.\n";
        }
        MainJeu::m_carteStatic = cJeu;
    }
    else if(s == "effet Renovation"){
        if(Joueur::j_joueurStatic->getType() == "JoueurAI"){
            const Carte* cEcarte = nullptr;
            for(const Carte *c : Joueur::j_joueurStatic->getMainJeu()->getListeCartesMain()){
                if(c->getCout()<=2 || c->getCout()>=6 || c->getNom() == "Renovation"){
                    cEcarte = c;
                }
            }
            if(cEcarte == nullptr){
                int prioMin = 0;
                for(const Carte *c : Joueur::j_joueurStatic->getMainJeu()->getListeCartesMain()){
                    if(prioMin == 0 || c->getPrioCarte() < cEcarte->getPrioCarte()){
                        cEcarte = c;
                        prioMin = c->getPrioCarte();
                    }
                }
            }
            int cout = cEcarte->getCout();
            Joueur::j_joueurStatic->getMainJeu()->ajouterAchatTour(1);
            Joueur::j_joueurStatic->getMainJeu()->ajouterTresorTour(cout+2);
            Carte *cJeu = MainJeu::m_carteStatic;
            MainJeu::m_carteStatic = const_cast<Carte*> (cEcarte);
            effetCarte("Ecarter 1 Carte de la main");
            MainJeu::m_carteStatic = cJeu;
            Joueur::j_joueurStatic->acheterCarte(cout +2);
            std::cout << Joueur::j_joueurStatic << "obtient la carte grâce à la carte Renovation." << std::endl;        
            while(Joueur::j_joueurStatic->getMainJeu()->getTresorTour() != 0){
                Joueur::j_joueurStatic->getMainJeu()->ajouterTresorTour(-1);
            }
        }else{
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
                std::cin.clear(); 
                std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
                std::cout << "Ecartez une carte et recevez une carte coûtant jusqu'à 2 Trésors de plus, tapez son numéro : ";
                std::cin >> choixCarte;
            }
        
            int cout = carteMain[choixCarte-1]->getCout();
            Carte *cJeu = MainJeu::m_carteStatic;
            MainJeu::m_carteStatic = const_cast<Carte*> (carteMain[choixCarte-1]);
            effetCarte("Ecarter 1 Carte de la main");
            MainJeu::m_carteStatic = cJeu;
            Joueur::j_joueurStatic->acheterCarte(cout +2);
            std::cout << Joueur::j_joueurStatic << "obtient la carte grâce à la carte Renovation." << std::endl;
            carteMain.clear();
        }
    }
    else if(s == "effet Salle du Trone"){
        if(Joueur::j_joueurStatic->getType() == "JoueurAI"){
            int prioMax = 0;
            const Carte* cPrioMax = nullptr;
            for(const Carte *c : Joueur::j_joueurStatic->getMainJeu()->getListeCartesMain()){
                if ((c->getPrioCarte() >= prioMax) && (c->getType() == "Action" || c->getType() == "ActionAttaque" || c->getType() == "ActionReaction")) {
                    /*if(c->getPrioCarte() == prioMax){
                        const Royaume* r1 = static_cast<const Royaume*>(c);
                        bool ajoutAction = false;
                        bool ajoutAchat = false;
                        bool ajoutCarte = false;
                        for(std::string s : r1->getEffets()){
                            if(s == "+1 Action"){
                                ajoutAction = true;
                            }else if(s == "+1 Achat") {
                                ajoutAchat = true;
                            }else if(s == "+1 Carte"){
                                ajoutCarte = true;
                            }
                        }
                        int nbAction = 0;
                        int nbTresor = 0;
                        int nbCarte = 0;
                        for(const Carte *c : Joueur::j_joueurStatic->getMainJeu()->getListeCartesMain()){
                            if(c->getType() == "Action"){
                                nbAction++;
                            }else if(c->getType() == "Tresor") {
                                nbTresor = (dynamic_cast<const Tresor*>(c))->getValeur();
                            }
                        }
                        if()*/
                    //}else{
                        prioMax = c->getPrioCarte();
                        cPrioMax = c;
                    //}
                }    
            }
            if(cPrioMax == nullptr){}
            else{
                MainJeu::m_carteStatic = const_cast<Carte*>(cPrioMax);
                Joueur::j_joueurStatic->ajouterACartesJouees(cPrioMax);
                for(int i=0;i<2;i++){
                    std::cout << Joueur::j_joueurStatic << "joue ";
                    cPrioMax->jouerCarte();
                }
            }
        }
        else{
            std::vector <const Royaume*> carteRoyaume = {};
            for(const Carte *c : Joueur::j_joueurStatic->getMainJeu()->getListeCartesMain()){
                if (c->getType() == "Action" || c->getType() == "ActionAttaque" || c->getType() == "ActionReaction") {
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
        }
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
        std::vector<const Tresor*> carteTresorVolees = {};
        for(Joueur* j : Partie::p_partieStatic->getJoueurPartie()){
            bool reaction = effetAttaque(j);
            if(reaction == false){
                Joueur::j_joueurStatic = j;
                std::vector<const Tresor*> carteTresorVoleesJoueur = {};
                for(int i=0;i<2;i++){
                    const Carte* c = Joueur::j_joueurStatic->devoilerCarte();
                    if(c->getType() != "Tresor"){
                        Joueur::j_joueurStatic->getDefausse()->ajouterCarteDefausse(c);
                    }
                    else{
                        const Tresor* t = static_cast<const Tresor*>(c);
                        carteTresorVoleesJoueur.push_back(t);
                    }
                }
                if(carteTresorVoleesJoueur.size() == 0){}
                else if(carteTresorVoleesJoueur.size() == 1){
                    carteTresorVolees.push_back(carteTresorVoleesJoueur[0]);
                }
                else{
                    unsigned int choixCarte2 = 0;
                    if(jTour->getType() == "JoueurAI"){                
                        const Tresor* tInit = nullptr;
                        int i=0;
                        for(const Tresor* t : carteTresorVoleesJoueur){
                            if( tInit==nullptr || (t->getValeur()) > (tInit->getValeur())){
                                choixCarte2 = i;
                            }
                            i++;
                        }
                        std::cout << "Le "<<jTour<<" a choisi d'ecarter la carte "<< carteTresorVoleesJoueur.at(choixCarte2)<<" de "<< j << std::endl;
                        choixCarte2++;
                    }else{
                        std::cout << "Voici les cartes Trésors dévoilées :" << std::endl;
                        int numCarte = 1;
                        for(const Carte *r : carteTresorVoleesJoueur){
                            std::cout << "  " << numCarte << " - " << r << std::endl;
                            numCarte++;
                        }
                        std::cout << "Ecarter la carte Trésor de votre choix, tapez son numéro : ";
                        std::cin >> choixCarte2;
                        while(choixCarte2 > carteTresorVoleesJoueur.size()  && choixCarte2 < 1){
                            std::cerr << "\033[1;31m" << choixCarte2 << " n'est pas une réponse convenable. \033[0m" << std::endl;
                            std::cout << "Ecarter la carte Trésor de votre choix, tapez son numéro : ";
                            std::cin >> choixCarte2;
                        }
                    }
                    carteTresorVolees.push_back(carteTresorVoleesJoueur[choixCarte2 - 1]);
                    if(choixCarte2 == 1){
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
            unsigned int choix = 0;
            if(Joueur::j_joueurStatic->getType() == "JoueurAI"){ 
                for(unsigned int i=0; i<carteTresorVolees.size(); i++){
                    if(carteTresorVolees.at(i)->getValeur() > carteTresorVolees.at(choix)->getValeur()){
                        choix = i;
                    }
                }
                std::cout << "Le "<<Joueur::j_joueurStatic<<" a choisi de voler la carte "<< carteTresorVolees.at(choix)<< std::endl;
            }else{
                unsigned int numCarte = 1;
                std::cout << "Parmi ces cartes Trésors écartées, vous pouvez recevoir celles de votre choix : " << std::endl;
                for(const Carte *r : carteTresorVolees){
                    std::cout << "  " << numCarte << " - " << r << std::endl;
                    numCarte++;
                }
                std::cout << "Choisissez la carte Trésor de votre choix, tapez son numéro sinon tapez 0 : ";
                std::cin >> choix;
                while(choix > carteTresorVolees.size()){
                    std::cerr << "\033[1;31m" << choix << " n'est pas une réponse convenable. \033[0m" << std::endl;
                    std::cout << "Choisissez la carte Trésor de votre choix, tapez son numéro sinon tapez 0 : ";
                    std::cin >> choix;
                }
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
        if(j->getType() == "JoueurAI"){
            for(const Carte* c : j->getMainJeu()->getMain()){
                if (c->getType() == "ActionReaction") {
                    std::cout<<"Le " << j->getNomJoueur() << " joue la carte "<< c <<" en défense !\n";
                    return true;
                }
            }
            return false;
        }else{
            for(const Carte* c : j->getMainJeu()->getMain()){
                char choixJ;
                if (c->getType() == "ActionReaction") {
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
}
