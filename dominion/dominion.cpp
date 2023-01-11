#include "dominion.hpp"

Dominion::Dominion():d_parties({}){
    std::cout << "Bienvenue dans Dominion en ligne : " << std::endl;
}

Dominion::~Dominion(){}

void Dominion::choixFonctionnalites(){
    while(true){
        std::cout << "Choix de la Fonctionnalités : "      << std::endl;
        std::cout << "  1 - Créer un nouvelle partie"      << std::endl;
        std::cout << "  2 - Reprendre une partie en cours" << std::endl;
        std::cout << "  3 - Quitter Dominion"              << std::endl;
        std::cout << "Indiquez votre choix (1, 2 ou 3) : ";
        int choix;
        std::cin >> choix;
        std::cout << std::endl;
        while(choix != 1 && choix != 2 && choix != 3){
            std::cerr << "\033[1;31mChoix " << choix << " n'est pas un choix de fonctionnalité. \033[0m" << std::endl;
            std::cout << "Choix de la Fonctionnalités : "      << std::endl;
            std::cout << "  1 - Créer une nouvelle partie"     << std::endl;
            std::cout << "  2 - Reprendre une partie en cours" << std::endl;
            std::cout << "  3 - Quitter Dominion"              << std::endl;
            std::cout << "Indiquez votre choix (1, 2 ou 3) : ";
            std::cin >> choix;
            std::cout << std::endl;
        }
        if(choix == 1){
            (this)->creerNouvellePartie();
        }
        else if(choix == 2){
            (this)->reprendrePartieEnCours();
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
    static Partie* d_partieStatic = p;    

    std::cout << "A combien de joueurs voulez vous jouer (entre 1 et 4) : ";
    int nombreJoueur;
    std::cin >> nombreJoueur; 
    while(nombreJoueur < 1 || nombreJoueur > 4){
        std::cerr << "\033[1;31mVous ne pouvez pas jouer à Dominion à " << nombreJoueur << " joueurs. \033[0m" << std::endl;
        std::cout << "A combien de joueurs voulez vous jouer (entre 1 et 4) : ";
        std::cin >> nombreJoueur; 
    }

    //Bon nombre Carte Victoire et Tresor
        //p->creerCarteTresorVictoirePartie(int i);
        //appeler le bon constructeur de achat

    for(int i=1;i<=nombreJoueur;i++){
        p->creerJoueurHumain(i);
    } 

    if(nombreJoueur == 1){
        (this)->creerIAPartieSolo(p);
    }
    else{
        (this)->creerIAPartieMulti(p, nombreJoueur);
    }

    //creation du jeu de base
    std::vector<const Royaume*> cartesPartie = {};
    //changer les cartes
    cartesPartie.push_back(ATELIER);
    cartesPartie.push_back(BUCHERON);
    cartesPartie.push_back(CAVE);
    cartesPartie.push_back(CHAPELLE);
    cartesPartie.push_back(FORGERON);
    cartesPartie.push_back(MARCHE);
    cartesPartie.push_back(MINE);
    cartesPartie.push_back(RENOVATION);
    cartesPartie.push_back(SORCIERE);
    cartesPartie.push_back(VILLAGE);

        //ajoute les cartes utilisees par extensions dans cartesPartie
        //quelles extensions ?

    //Crée un objet rd de type std::random_device qui génère des nombres aléatoires de haute qualité
    std::random_device rd;
    //crée un générateur de nombres aléatoires de type std::mt19937 initialisé avec une graine générée par rd
    std::mt19937 g(rd());
    //shuffle permet de mélanger un vecteur à partir de son itérateur de début et de fin et d'un générateur de nombre aléatoire
    std::shuffle(cartesPartie.begin(), cartesPartie.end(), g);

    std::cout << std::endl <<  "Choix des 10 cartes Royaume qui seront en jeu : " << std::endl;
    std::cout << "  1 - Choisir manuellement"     << std::endl;
    std::cout << "  2 - Choisir aléatoirement" << std::endl;
    std::cout << "Indiquez votre choix (1 ou 2) : ";
    int choixCarte;
    std::cin >> choixCarte; 
    while(choixCarte != 1 && choixCarte != 2){
        std::cerr << "\033[1;31mChoix " << choixCarte << " n'est pas un choix de fonctionnalité. \033[0m" << std::endl;
        std::cout << "Choix des 10 cartes Royaume qui seront en jeu : " << std::endl;
        std::cout << "  1 - Choisir manuellement"     << std::endl;
        std::cout << "  2 - Choisir aléatoirement" << std::endl;
        std::cout << "Indiquez votre choix (1 ou 2) : ";
        std::cin >> choixCarte; 
    }

    Achat* a = new Achat();
    a->completerLigneAchatGauche(nombreJoueur);
    if(choixCarte == 1){
        //(this)->choixManuelCarte(cartesPartie);
    }
    else{
        p->choixCarteAleatoirePourAchat(cartesPartie);
        listeCarte();
    }
    a->completerLigneAchatCentreAuto(nombreJoueur);
    a->afficherLigneAchat();


    std::cout << "Partie " << d_partieStatic->getNomPartie() << " a bien été créé." << std::endl << std::endl;   

    p->lancerPartie();
}

void Dominion::creerIAPartieSolo(Partie* p){
    int nombreAI;
    std::cout << "Avec combien d'AI voulez vous jouer (entre 1 et 3): ";
    std::cin >> nombreAI; 
    while(nombreAI < 1 || nombreAI > 3){
        std::cerr << "\033[1;31m" << nombreAI << " n'est pas une réponse convenable. \033[0m" << std::endl;
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
            std::cout << "Voulez vous jouer avec des IA (o ou n) : ";
            char questionAI;
            std::cin >> questionAI;
        }
        int nombreAI;
        if(questionAI == 'n'){}
        else{
            std::cout << "Avec combien d'AI voulez vous jouer : ";
            std::cin >> nombreAI; 
            while(nombreAI < 1 || nombreAI+i > 4){
                std::cerr << "\033[1;31m" << nombreAI << " n'est pas une réponse convenable. \033[0m" << std::endl;
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

void Dominion::reprendrePartieEnCours(){
    if(d_parties.size() == 0){
        std::cout << "Aucune partie n'est en cours." << std::endl << std::endl;
        std::cout << "La partie reprend" << std::endl;
    }
    else{
        std::cout << "Voici la liste des parties en cours : " << std::endl;
        for(unsigned int i=0;i<d_parties.size();i++){
            std::cout << "  " << i+1 << " - "<< d_parties[i]->getNomPartie() << std::endl;
        }
    }
    std::cout << std::endl;
}
