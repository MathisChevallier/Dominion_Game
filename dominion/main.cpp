#include <iostream>
#include "jeuBase.hpp"
#include "dominion.hpp"

/*
//Déclaration des cartes en tant que variable globale
Action *Atelier, *Aventurier, *Bibliotheque, *Bucheron, *Cave, *ChambreDuConseil, *Chancelier, *Chapelle, *Festin, *Festival, *Forgeron,
       *Laboratoire, *Marche, *Mine, *PreteurSurGages, *Renovation, *SalleDuTrone, *Village; 
ActionAttaque *Bureaucrate, *Espion, *Milice, *Sorciere, *Voleur;
ActionReaction *Douves;
Victoire *Province, *Duche, *Domaine, *Malediction; //Jardins; //Jardins action ou victoire ??
Tresor *Cuivre, *Argent, *Or;

// Creation Cartes jeu de base 
void creerCarte(){
    // Creation Cartes Tresor
    Cuivre = new Tresor("Cuivre", 0, 1);
    Argent = new Tresor("Argent", 3, 2);
    Or     = new Tresor("Or",     6, 3);

    // Creation Cartes Victoire
    Province    = new Victoire("Province"   , 8, 5);
    Duche       = new Victoire("Duche"      , 5, 3);
    Domaine     = new Victoire("Domaine"    , 2, 1);
    Malediction = new Victoire("Malédiction", 0, -1);
    //Jardins     = Victoire("Jardins"   , 4, 3);

    // Creation Cartes Actions, Action-Attaque, Action-Réaction
    Atelier          = new Action("Atelier"           , 3, {"effet Atelier"}, "Recevez une carte coûtant jusqu'à 4 Trésors.");
    Aventurier       = new Action("Aventurier"        , 6, {"effet Aventurier"}, "Dévoilez des cartes de votre deck jusqu'à ce que 2 cartes Trésor soient devoilées. Ajoutez ces cartes Trésor à votre main et de défaussez les autres cartes dévoilées.");
    Bibliotheque     = new Action("Bibliothèque"      , 5, {"effet Bibliothèque"}, "Piochez jusqu'à ce que vous ayez 7 cartes en main. Chaque carte Action piochée peut être mise de côté. Défaussez les cartes mises de côté lorsque vous avez terminé de piocher.");
    Bucheron         = new Action("Bucheron"          , 3, {"+1 Achat", "+1 Trésor", "+1 Trésor"}, "+1 Achat \n +2 Tresors");
    Cave             = new Action("Cave"              , 2, {"+1 Action", "effet Cave"}, "+1 Action \n Défaussez autant de cartes que vous voulez. +1 Carte par carte défaussée.");
    ChambreDuConseil = new Action("Chambre Du Conseil", 5, {"+1 Carte", "+1 Carte", "+1 Carte", "+1 Carte", "+1 Achat", "effet Chambre du conseil"}, "+4 Cartes \n +1 Achat \n Tous vos adversaires piochent 1 carte.");
    Chancelier       = new Action("Chancelier"       , 3, {"+1 Tresor", "+1 Tresor", "effet Chancelier"}, "+2 Trésors \n Vous pouvez immédiatement défausser votre deck.");
    Chapelle         = new Action("Chapelle"         , 2, {"effet Chapelle"}, "Ecartez jusqu'à 4 cartes de votre main.");
    Festin           = new Action("Festin"           , 4, {"effet Festin"}, "Ecartez cette carte. Recevez une carte coûtant jusqu'à 5 Trésors.");
    Festival         = new Action("Festival"         , 5, {"+1 Action", "+1 Action", "+1 Achat", "+1 Tresor", "+1 Tresor"}, "+2 Actions \n +1 Achat \n +2 Tresors");
    Forgeron         = new Action("Forgeron"         , 4, {"+1 Carte", "+1 Carte", "+1 Carte"}, "+3 Cartes");
    Laboratoire      = new Action("Laboratoire"      , 5, {"+1 Carte", "+1 Carte", "+1 Action"}, "+2 Cartes \n +1 Action");
    Marche           = new Action("Marche"           , 5, {"+1 Carte", "+1 Action", "+1 Achat", "+1 Tresor"}, "+1 Carte \n +1 Action \n +1 Achat \n +1 Tresor");
    Mine             = new Action("Mine"             , 5, {"effet Mine"}, "Ecartez une carte Tresor de votre main. Recevez une carte Tresor coûtant jusqu'à 3 Trésors de plus ; Ajoutez cette carte à votre main.");
    PreteurSurGages  = new Action("Preteur Sur Gages", 4, {"effet Preteur Sur Gages"}, "Ecartez une cartes Cuivre de votre main et recevez +3 Trésors.");
    Renovation       = new Action("Renovation"       , 4, {"effet Renovation"}, "Ecartez une carte de votre main. Recevez une carte coûtant jusqu'à 2 Trésors de plus que la carte écartée.");
    SalleDuTrone     = new Action("Salle Du Trone"   , 4, {"effet Salle Du Trone"}, "Choisissez 1 carte Action de votre main. Jouez-la deux fois.");
    Village          = new Action("Village"          , 3, {"+1 Carte", "+1 Action", "+1 Action"}, "+1 Carte \n +2 Actions");

    Bureaucrate = new ActionAttaque("Bureaucrate", 4, {}, "Recevez 1 carte Argent : placez-la sur votre deck. Tous vos adversaires dévoilent 1 carte Victoire et la placent sur leur deck (sinon ils dévoilent leur main afin que vous puissiez voir qu'ils n'ont pas de cartes Victoire. ", {"effet Bureaucrate"});
    Espion      = new ActionAttaque("Espion"     , 4, {"+1 Carte", "+1 Action"}, "+1 Carte \n +1 Action \n Tous les joueurs (vous aussi) dévoilent leur première carte de leur deck. Vous décidez ensuite si chaque carte dévoilée est défaussée ou replacée sur son deck.", {"effet Espion"});
    Milice      = new ActionAttaque("Milice"     , 4, {"+1 Tresor", "+1 Tresor"}, "+2 Tresors \n Tous vos adversaires défaussent leurs cartes de façon à n'avoir que 3 cartes en main.", {"effet Milice"});
    Sorciere    = new ActionAttaque("Sorciere"   , 5, {"+1 Carte", "+1 Carte"}, "+2 Cartes \n Tous vos adversaires reçoivent une carte Malédiction", {"effet Sorciere"});
    Voleur      = new ActionAttaque("Voleur"     , 4, {}, "Tous vos adversaires dévoilent les 2 premières cartes de leur deck. S'ils dévoilent des cartes Trésor, ils en écartent 1 de votre choix. Parmi ces cartes Tresor écartées, recevez celle de votre choix. Les autres cartes dévoilées sont défaussées.", {"effet Voleur"});
        
    Douves = new ActionReaction("Douves", 2, {"+1 Carte", "+1 Carte"}, "+2 Cartes \n Lorsqu'un adversaire joue une carte Attaque, vous pouvez dévoiler cette carte de votre main. Dans ce cas, l'Attaque n'a pas d'effet sur vous.", {"effet Douves"});
}
*/

int main(){

    Dominion* d = new Dominion();
    d->choixFonctionnalites();   

    /*
    Partie* p1 = new Partie("hello1");
    static Partie* d_partieStatic = p1;
    std::cout << d_partieStatic->getNomPartie();
    p1->creerJoueurHumain(1);
    Joueur* j1 = p1->getPremierJoueur();
    j1->piocherMain();
    std::cout << "Main : ";
    j1->getMainJeu()->afficherCartesMain();
    j1->TourDeJeu();
    std::cout << j1;
    //j1->defausserMain();
    //j1->piocherMain();
    std::cout << j1->getMainJeu();
    std::cout << "Défausse : ";
    j1->getDefausse()->afficherOrdreCartes();
    std::cout << std::endl;
    j1->TourDeJeu();
    //j1->defausserMain();
    //j1->piocherMain();
    //std::cout << j1;
    std::cout << j1->getMainJeu();
    std::cout << "Défausse : ";
    j1->getDefausse()->afficherOrdreCartes() ;
    std::cout << std::endl;
    j1->TourDeJeu();
    //j1->defausserMain();
    //j1->piocherMain();
    //std::cout << j1;
    std::cout << j1->getMainJeu();
    for(const Carte* c : j1->getMainJeu()->getListeCartesMain()){
        MainJeu::m_carteStatic = const_cast<Carte*>(c);
        if(c->getNom() == "Village"){
            const Action* a1 = static_cast<const Action*>(c);
            a1->jouerCarte();
        }
    }
    std::cout << j1->getMainJeu();
    std::cout << "Défausse : ";
    j1->getDefausse()->afficherOrdreCartes() ;
    std::cout << std::endl;
    d->choixFonctionnalites();*/
    /*Deck *d1 = new Deck();
    d1->afficherOrdreCartes();
    std::cout << std::endl;
    d1->melanger();
    d1->afficherOrdreCartes();
    std::cout << std::endl;
    d1->melanger();
    d1->afficherOrdreCartes();
    std::cout << std::endl;
    const Carte *c1 = d1->getPremiereCarteSurPioche();
    const Carte *c2 = d1->piocherPremiereCarte();
    d1->afficherOrdreCartes();
    std::cout << std::endl;
    const Carte *c3 = d1->piocherPremiereCarte();
    d1->afficherOrdreCartes();
    std::cout << std::endl;
    const Carte *c4 = d1->piocherPremiereCarte();
    d1->afficherOrdreCartes();
    // La carte pointée par "carte" est bien un trésor
    if (dynamic_cast<const Tresor*>(c1) != nullptr) {
    // "tresor" est maintenant un pointeur de type "Tresor*" constant
    const Tresor* t1 = static_cast<const Tresor*>(c1);
    std::cout << t1->getValeur();
    std::cout << t1->getNom();
    } else {
    // La carte pointée par "carte" n'est pas un trésor
    }
    std::cout << c2->getCout();
    std::cout << c3->getCout();
    std::cout << c4->getCout();
    std::cout << FORGERON->getDescriptionEffet();
    std::cout << VILLAGE->getDescriptionEffet();
    std::cout << ATELIER->getDescriptionEffet();
    detruireCartes();
    delete d1;
    */

    return 0;
}