#include "dominion.hpp"

Dominion::Dominion():d_parties({}),d_historique({}){
    std::cout << "Bienvenue dans Dominion en ligne : " << std::endl;
}

Dominion::~Dominion(){
    Partie::nettoyer();

    for (Partie* p : d_parties) {
        // Libère l'espace mémoire alloué pour chaque partie
        delete p;
    }
    d_parties.clear();
    for (Partie* p : d_historique) {
        // Libère l'espace mémoire alloué pour chaque partie
        delete p;
    }
    d_historique.clear();
}

void Dominion::choixFonctionnalites(){
    while(true){
        std::cout << "Choix de la Fonctionnalités : "      << std::endl;
        std::cout << "  1 - Créer une nouvelle partie"      << std::endl;
        std::cout << "  2 - Reprendre une partie en cours" << std::endl;
        std::cout << "  3 - Historique des parties" << std::endl;
        std::cout << "  4 - Quitter Dominion"              << std::endl;
        std::cout << "Indiquez votre choix (1, 2, 3 ou 4) : ";
        int choix;
        std::cin >> choix;
        while(choix < 1 || choix > 4){ 
            std::cerr << "\033[1;31mChoix " << choix << " n'est pas un choix de fonctionnalité. \033[0m" << std::endl << std::endl;
            std::cout << "Choix de la Fonctionnalités : "      << std::endl;
            std::cout << "  1 - Créer une nouvelle partie"     << std::endl;
            std::cout << "  2 - Reprendre une partie en cours" << std::endl;
            std::cout << "  3 - Historique des parties"        << std::endl;
            std::cout << "  4 - Quitter Dominion"              << std::endl;
            //Permet d'enlever ce qu'il y a dans le cin (pas de boucle infini si l'utilisateur met un caractère)
            std::cin.clear(); 
            std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
            std::cout << "Indiquez votre choix (1, 2, 3 ou 4) : ";
            std::cin >> choix;
        }
        if(choix == 1){
            (this)->creerNouvellePartie();
        }
        else if(choix == 2){
            (this)->reprendrePartieEnCours();
        }
        else if(choix == 3){
            (this)->historiquePartie();
        }
        else{
            break;
        }
    }
    std::cout << "C'était dominion en ligne codé par CHEVALLIER Mathis et MARTIN Hugues en C++" << std::endl;
}

void Dominion::creerNouvellePartie(){// Créer nom partie puis demander combien de joueur(Humain, IA), quelles extensions, quels cartes (aleatoire ou pas) 
    std::cout << "Donner un nom à cette partie : ";
    std::string nomPartie;
    std::cin >> nomPartie;
    Partie* p = new Partie(nomPartie);
    d_parties.push_back(p);
    Partie::p_partieStatic = p;    

    std::cout << "A combien de joueurs voulez vous jouer (entre 1 et 4) : ";
    int nombreJoueur;
    std::cin >> nombreJoueur; 
    while(nombreJoueur < 1 || nombreJoueur > 4){
        std::cerr << "\033[1;31mVous ne pouvez pas jouer à Dominion à " << nombreJoueur << " joueurs. \033[0m" << std::endl;
        std::cin.clear(); 
        std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
        std::cout << "A combien de joueurs voulez vous jouer (entre 1 et 4) : ";
        std::cin >> nombreJoueur; 
    }

    //Bon nombre Carte Victoire et Tresor
    //p->creerCarteTresorVictoirePartie(int i);
    for(int i=1;i<=nombreJoueur;i++){
        p->creerJoueurHumain(i);
    } 

    if(nombreJoueur == 1){
        (this)->creerIAPartieSolo(p);
    }
    else{
        (this)->creerIAPartieMulti(p, nombreJoueur);
    }

    std::vector<fonctionSetCarte> fonctionCarte = {setCarte1(), setCarte1()};
    std::vector<std::string> extension =          {"Jeu de Base", "Extension 1"};

    //creation du jeu de base
    std::vector<const Royaume*> cartesPartie = {};


    //Choix des extensions
    while(extension.size() != 0){
        if(cartesPartie.size() == 0){
            std::cout << std::endl <<  "Choisissez une extension avec laquelle vous voulez jouer, tapez son numéro associé : " << std::endl;
            for(unsigned int i=0;i<extension.size();i++){
                std::cout << "  " << i+1 << " - " << extension[i] << std::endl;
            }
            std::cout << "Indiquez votre choix (entre 1 et " << extension.size() << ") : ";
            unsigned int choixExtension;
            std::cin >> choixExtension; 
            while(choixExtension < 1 || choixExtension > extension.size()){
                std::cerr << "\033[1;31m" << choixExtension << " n'est pas une réponse convenable. \033[0m" << std::endl;
                std::cout << std::endl <<  "Choisissez une extension avec laquelle vous voulez jouer, tapez son numéro associé : " << std::endl;
                for(unsigned int i=0;i<extension.size();i++){
                    std::cout << "  " << i+1 << " - " << extension[i] << std::endl;
                }
                std::cin.clear(); 
                std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
                std::cout << "Indiquez votre choix (entre 1 et " << extension.size() << ") : ";
                std::cin >> choixExtension; 
            }
            std::vector<const Royaume*> cartesAjoutees = fonctionCarte[choixExtension - 1];
            cartesPartie.insert(cartesPartie.end(), cartesAjoutees.begin(), cartesAjoutees.end());
            fonctionCarte.erase(fonctionCarte.begin() + choixExtension - 1);
            extension.erase(extension.begin() + choixExtension - 1);
            std::cout << cartesPartie.size() << " / " << fonctionCarte.size() << " / " << extension.size() << " / " << std::endl;
        }
        else{
            std::cout << std::endl <<  "Si vous voulez jouer avec une autre extension, tapez son numéro associé sinon tapez 0 : " << std::endl;
            for(unsigned int i=0;i<extension.size();i++){
                std::cout << "  " << i+1 << " - " << extension[i] << std::endl;
            }
            std::cout << "Indiquez votre choix (entre 0 et " << extension.size() << ") : ";
            unsigned int choixExtension;
            std::cin >> choixExtension; 
            while(std::cin.fail() || choixExtension > extension.size()){
                std::cerr << "\033[1;31mCe n'est pas une réponse convenable. \033[0m" << std::endl;
                std::cout << std::endl <<  "Si vous voulez jouer avec une autre extension, tapez son numéro associé sinon tapez 0 : " << std::endl;
                for(unsigned int i=0;i<extension.size();i++){
                    std::cout << "  " << i+1 << " - " << extension[i] << std::endl;
                }
                std::cin.clear(); 
                std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
                std::cout << "Indiquez votre choix (entre 0 et " << extension.size() << ") : ";
                std::cin >> choixExtension; 
            }
            if(choixExtension == 0){break;}
            std::vector<const Royaume*> cartesAjoutees = fonctionCarte[choixExtension];
            cartesPartie.insert(cartesPartie.end(), cartesAjoutees.begin(), cartesAjoutees.end());
            fonctionCarte.erase(fonctionCarte.begin() + choixExtension - 1);
            extension.erase(extension.begin() + choixExtension - 1);
        }
    }

    std::cout << std::endl <<  "Choix des 10 cartes Royaume qui seront en jeu : " << std::endl;
    std::cout << "  1 - Choisir manuellement 1 ou plusieurs cartes"     << std::endl;
    std::cout << "  2 - Choisir un set de 10 cartes conseillés"     << std::endl;
    std::cout << "  3 - Choisir aléatoirement" << std::endl;
    std::cout << "Indiquez votre choix (1, 2 ou 3) : ";
    int choixCarte;
    std::cin >> choixCarte; 
    std::cout << std::endl;
    while(choixCarte != 1 && choixCarte != 2 && choixCarte != 3){
        std::cerr << "\033[1;31mChoix " << choixCarte << " n'est pas un choix de fonctionnalité. \033[0m" << std::endl;
        std::cout << "Choix des 10 cartes Royaume qui seront en jeu : " << std::endl;
        std::cout << "  1 - Choisir manuellement 1 ou plusieurs cartes"     << std::endl;
        std::cout << "  2 - Choisir un set de 10 cartes conseillés"     << std::endl;
        std::cout << "  3 - Choisir aléatoirement" << std::endl;
        std::cin.clear(); 
        std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
        std::cout << "Indiquez votre choix (1, 2 ou 3) : ";
        std::cin >> choixCarte; 
        std::cout << std::endl;
    }

    p->getAchat()->completerLigneAchatGauche(nombreJoueur);
    //Remettre cartes utilisees à zéro si une partie a déjà été créé
    Partie::p_cartes_utilisees = {};
    if(choixCarte == 1){
        (this)->choixManuelCarte(cartesPartie);
    }
    else if(choixCarte == 2){
        (this)->choixSetCarte(cartesPartie);
    }
    else{
        p->choixCarteAleatoirePourAchat(cartesPartie, 10);
        listeCarte();
    }
    cartesPartie.clear();
    
    p->getAchat()->completerLigneAchatCentreAuto(nombreJoueur);
    p->getAchat()->afficherLigneAchat();

    std::cout << "Partie " << Partie::p_partieStatic->getNomPartie() << " a bien été créé." << std::endl << std::endl;   

    std::cout << "Appuie sur une lettre puis ENTREE pour commencer la partie : " << std::endl << std::endl;
    std::string input;
    std::cin >> input;
    while(input == "\n"){
        std::cin.clear(); 
        std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
        std::cin >> input;
    }

    p->lancerPartie();
    (this)->testFinPartie();
}

void Dominion::creerIAPartieSolo(Partie* p){
    int nombreAI;
    std::cout << "Avec combien d'AI voulez vous jouer (entre 1 et 3): ";
    std::cin >> nombreAI; 
    while(nombreAI < 1 || nombreAI > 3){
        std::cerr << "\033[1;31m" << nombreAI << " n'est pas une réponse convenable. \033[0m" << std::endl;
        std::cin.clear(); 
        std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
        std::cout << "Avec combien d'AI voulez vous jouer (entre 1 et 3) : ";
        std::cin >> nombreAI; 
    }     
    for(int j=1;j<=nombreAI;j++){
        p->getNomPartie();
        //p->creerJoueurBot(j);
    }
}

void Dominion::creerIAPartieMulti(Partie* p, int i){
    if(i != 4){
        std::cout << "Voulez vous ajouter une ou des IA à la partie (o ou n) : ";
        char questionAI;
        std::cin >> questionAI; 
        while(questionAI != 'o' && questionAI != 'n'){
            std::cerr << "\033[1;31m" << questionAI << " n'est pas une réponse convenable. \033[0m" << std::endl;
            std::cin.clear(); 
            std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
            std::cout << "Voulez vous jouer avec des IA (o ou n) : ";
            std::cin >> questionAI;
        }
        int nombreAI;
        if(questionAI == 'n'){}
        else{
            std::cout << "Avec combien d'AI voulez vous jouer : ";
            std::cin >> nombreAI; 
            while(nombreAI < 1 || nombreAI+i > 4){
                std::cerr << "\033[1;31m" << nombreAI << " n'est pas une réponse convenable. \033[0m" << std::endl;
                std::cin.clear(); 
            std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
                std::cout << "Avec combien d'AI voulez vous jouer : ";
                std::cin >> nombreAI;
            }     
            for(int j=1;j<=nombreAI;j++){
                p->getNomPartie();
                //p->creerJoueurBot(j);
            }        
        }
    }
    else{}
}

void Dominion::choixManuelCarte(std::vector<const Royaume*> &vec){
    //std::vector<const Royaume*> vec = v;
    std::cout << "Voici les cartes avec lesquelles vous pouvez jouer : " << std::endl;
    for(size_t i=0;i<10;i++){
        std::cout << "  ";
        for(size_t i=0; i<vec.size(); i++){
            if(i%5 == 0 && i != 0){
                std::cout << std::endl << "  ";
            }
            std::string nomCarte = vec[i]->getNom();
            nomCarte.append(18 - nomCarte.length(), ' ');
            if(i < 9){
                std::cout << " " << i+1 << "  - " << nomCarte << "(" << vec[i]->getCout() << ") ;";
            }
            else{
                std::cout << " " << i+1 << " - " << nomCarte << "(" << vec[i]->getCout() << ") ;";
            }
        }
        unsigned int choixCarte;
        std::cout << std::endl << "Vous pouvez encore choisir " << 10 - i << " cartes, tapez un numéro associé à une carte sinon tapez 0 pour tirer le reste aléatoirement : ";
        std::cin >> choixCarte;
        while(choixCarte > vec.size()){
            std::cerr << "\033[1;31mCe n'est pas une réponse convenable. \033[0m" << std::endl;
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n' );
            std::cout << "Vous pouvez encore choisir " << 10 - i << " cartes, tapez un numéro associé à une carte sinon tapez 0 pour tirer le reste aléatoirement : ";
            std::cin >> choixCarte;
        }
        if(choixCarte == 0){
            std::cout << vec.size();
            Partie::p_partieStatic->choixCarteAleatoirePourAchat(vec, 10-i);
            break;
        }
        else{
            Partie::p_cartes_utilisees.push_back(vec[choixCarte-1]);
            std::cout << "La carte " << vec[choixCarte-1] << " a été ajouté à la ligne d'achat de la partie." << std::endl << std::endl;
            vec.erase(vec.begin() + choixCarte - 1);
        }
    }
}

void Dominion::choixSetCarte(const std::vector<const Royaume*>& v){
    //Ajouter combinaison avec extension avant
    //Le jeu de base seul
    if(std::find(v.begin(), v.end(), ATELIER) != v.end()){
        std::cout << "Voici 5 sets de 10 cartes que nous pouvons vous conseiller : " << std::endl;
        std::vector<const Royaume*> c1 = setPremierePartie();
        std::vector<const Royaume*> c2 = setRichessesTresors();
        std::vector<const Royaume*> c3 = setInteraction();
        std::vector<const Royaume*> c4 = setChangementTaille();
        std::vector<const Royaume*> c5 = setPlaceDuVillage();
        std::vector<std::vector<const Royaume*>> set = {c1, c2, c3, c4, c5};
        unsigned int choixSet;
        std::cout << "Pour choisir un set de cartes, tapez son numéro associé : ";
        std::cin >> choixSet;
        std::cout << std::endl;
        while(choixSet < 1 || choixSet > 5){
            std::cerr << "\033[1;31m" << choixSet << " n'est pas une réponse convenable. \033[0m" << std::endl;
            std::cin.clear(); 
            std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
            std::cout << "Pour choisir un set de cartes, tapez son numéro associé : ";
            std::cin >> choixSet;
            std::cout << std::endl;
        }
        Partie::p_cartes_utilisees = set[choixSet-1];
        c1.clear();
        c2.clear();
        c3.clear();
        c4.clear();
        c5.clear();
        set.clear();
    }
}

void Dominion::reprendrePartieEnCours(){
    if(d_parties.size() == 0){
        std::cout << "Aucune partie n'est en cours." << std::endl << std::endl;
    }
    else{
        std::cout << "Voici la liste des parties en cours : " << std::endl;
        for(unsigned int i=0;i<d_parties.size();i++){
            std::cout << "  " << i+1 << " - "<< d_parties[i]->getNomPartie() << std::endl;
        }
        unsigned int choixPartie;
        std::cout << "Pour reprendre une partie, tapez son numéro sinon tapez 0 : ";
        std::cin >> choixPartie;
        while(choixPartie > d_parties.size()){
            std::cerr << "\033[1;31mCe n'est pas une réponse convenable. \033[0m" << std::endl;
            std::cin.clear(); 
            std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
            std::cout << "Pour reprendre une partie, tapez son numéro sinon tapez 0 : ";
            std::cin >> choixPartie;
        }
        std::cout << std::endl;
        if(choixPartie == 0){}
        else{
            d_parties[choixPartie-1]->reprendrePartie();
            (this)->testFinPartie();
        }
    }
}

void Dominion::testFinPartie(){
    if(Partie::p_partieStatic->getFinPartie() == true){
        d_historique.push_back(Partie::p_partieStatic);
        for (auto it = d_parties.begin(); it != d_parties.end(); ++it) {
            if (*it == Partie::p_partieStatic) { // Si l'itérateur pointe vers l'élément à supprimer
                d_parties.erase(it); // Supprime l'élément du vecteur
                break; 
            }
        }
    }
}

void Dominion::historiquePartie(){
    if(d_historique.size() == 0){
        std::cout << "L'historique des parties est vide." << std::endl << std::endl;
    }
    else{
        std::cout << "Voici l'historique des parties : " << std::endl;
        for(unsigned int i=0;i<d_historique.size();i++){
            std::cout << "  " << i+1 << " - "<< d_historique[i]->getNomPartie() << std::endl;
        }
        unsigned int choixPartie;
        std::cout << "Pour accéder aux détails d'une partie, tapez son numéro sinon tapez 0 : ";
        std::cin >> choixPartie;
        while(choixPartie > d_historique.size()){
            std::cerr << "\033[1;31mCe n'est pas une réponse convenable. \033[0m" << std::endl;
            std::cin.clear(); 
            std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
            std::cout << "Pour accéder aux détails d'une partie, tapez son numéro sinon tapez 0 : ";
            std::cin >> choixPartie;
        }
        std::cout << std::endl;
        if(choixPartie == 0){}
        else{
            d_historique[choixPartie-1]->detailPartie();
        }
    }
}
