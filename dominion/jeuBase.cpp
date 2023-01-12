#include "jeuBase.hpp"


// Creation Cartes Tresor
const Tresor *CUIVRE = new Tresor("Cuivre", 0, 1);
const Tresor *ARGENT = new Tresor("Argent", 3, 2);
const Tresor *OR     = new Tresor("Or",     6, 3);

// Creation Cartes Victoire
const Victoire *PROVINCE    = new Victoire("Province"   , 8, 6);
const Victoire *DUCHE       = new Victoire("Duche"      , 5, 3);
const Victoire *DOMAINE     = new Victoire("Domaine"    , 2, 1);
const Victoire *MALEDICTION = new Victoire("Malédiction", 0, -1, "\033[35m");

// Creation Cartes Actions, Action-Attaque, Action-Réaction
const Action *ATELIER          = new Action("Atelier"           , 3, {"effet Atelier"}, "Recevez une carte coûtant jusqu'à 4 Trésors.");
const Action *AVENTURIER       = new Action("Aventurier"        , 6, {"effet Aventurier"}, "Dévoilez des cartes de votre deck jusqu'à ce que 2 cartes Trésor soient devoilées. Ajoutez ces cartes Trésor à votre main et défaussez les autres cartes dévoilées.");
const Action *BIBLIOTHEQUE     = new Action("Bibliothèque"      , 5, {"effet Bibliotheque"}, "Piochez jusqu'à ce que vous ayez 7 cartes en main. Chaque carte Action piochée peut être mise de côté. Défaussez les cartes mises de côté lorsque vous avez terminé de piocher.");
const Action *BUCHERON         = new Action("Bucheron"          , 3, {"+1 Achat", "+1 Tresor", "+1 Tresor"}, "+1 Achat ; +2 Tresors");
const Action *CAVE             = new Action("Cave"              , 2, {"+1 Action", "effet Cave"}, "+1 Action ; Défaussez autant de cartes que vous voulez. +1 Carte par carte défaussée.");
const Action *CHAMBREDUCONSEIL = new Action("Chambre Du Conseil", 5, {"+1 Carte", "+1 Carte", "+1 Carte", "+1 Carte", "+1 Achat", "effet Chambre du Conseil"}, "+4 Cartes ; +1 Achat ; Tous vos adversaires piochent 1 carte.");
const Action *CHANCELIER       = new Action("Chancelier"       , 3, {"+1 Tresor", "+1 Tresor", "effet Chancelier"}, "+2 Trésors ; Vous pouvez immédiatement défausser votre deck.");
const Action *CHAPELLE         = new Action("Chapelle"         , 2, {"effet Chapelle"}, "Ecartez jusqu'à 4 cartes de votre main.");
const Action *FESTIN           = new Action("Festin"           , 4, {"effet Festin"}, "Ecartez cette carte. Recevez une carte coûtant jusqu'à 5 Trésors.");
const Action *FESTIVAL         = new Action("Festival"         , 5, {"+1 Action", "+1 Action", "+1 Achat", "+1 Tresor", "+1 Tresor"}, "+2 Actions ; +1 Achat ; +2 Tresors");
const Action *FORGERON         = new Action("Forgeron"         , 4, {"+1 Carte", "+1 Carte", "+1 Carte"}, "+3 Cartes");
const Action *LABORATOIRE      = new Action("Laboratoire"      , 5, {"+1 Carte", "+1 Carte", "+1 Action"}, "+2 Cartes ; +1 Action");
const Action *MARCHE           = new Action("Marche"           , 5, {"+1 Carte", "+1 Action", "+1 Achat", "+1 Tresor"}, "+1 Carte ; +1 Action ; +1 Achat ; +1 Tresor");
const Action *MINE             = new Action("Mine"             , 5, {"effet Mine"}, "Ecartez une carte Tresor de votre main. Recevez une carte Tresor coûtant jusqu'à 3 Trésors de plus ; Ajoutez cette carte à votre main.");
const Action *PRETEURSURGAGES  = new Action("Preteur Sur Gages", 4, {"effet Preteur Sur Gages"}, "Ecartez une cartes Cuivre de votre main et recevez +3 Trésors.");
const Action *RENOVATION       = new Action("Renovation"       , 4, {"effet Renovation"}, "Ecartez une carte de votre main. Recevez une carte coûtant jusqu'à 2 Trésors de plus que la carte écartée.");
const Action *SALLEDUTRONE     = new Action("Salle du Trone"   , 4, {"effet Salle du Trone"}, "Choisissez 1 carte Action de votre main. Jouez-la deux fois.");
const Action *VILLAGE          = new Action("Village"          , 3, {"+1 Carte", "+1 Action", "+1 Action"}, "+1 Carte ; +2 Actions");

const ActionAttaque *BUREAUCRATE = new ActionAttaque("Bureaucrate", 4, {}, "Recevez 1 carte Argent : placez-la sur votre deck. Tous vos adversaires dévoilent 1 carte Victoire et la placent sur leur deck (sinon ils dévoilent leur main afin que vous puissiez voir qu'ils n'ont pas de cartes Victoire. ", {"effet Bureaucrate"});
const ActionAttaque *ESPION      = new ActionAttaque("Espion"     , 4, {"+1 Carte", "+1 Action"}, "+1 Carte ; +1 Action ; Tous les joueurs (vous aussi) dévoilent leur première carte de leur deck. Vous décidez ensuite si chaque carte dévoilée est défaussée ou replacée sur son deck.", {"effet Espion"});
const ActionAttaque *MILICE      = new ActionAttaque("Milice"     , 4, {"+1 Tresor", "+1 Tresor"}, "+2 Tresors ; Tous vos adversaires défaussent leurs cartes de façon à n'avoir que 3 cartes en main.", {"effet Milice"});
const ActionAttaque *SORCIERE    = new ActionAttaque("Sorciere"   , 5, {"+1 Carte", "+1 Carte"}, "+2 Cartes ; Tous vos adversaires reçoivent une carte Malédiction", {"effet Sorciere"});
const ActionAttaque *VOLEUR      = new ActionAttaque("Voleur"     , 4, {}, "Tous vos adversaires dévoilent les 2 premières cartes de leur deck. S'ils dévoilent des cartes Trésor, ils en écartent 1 de votre choix. Parmi ces cartes Tresor écartées, recevez celle de votre choix. Les autres cartes dévoilées sont défaussées.", {"effet Voleur"});
        
const ActionReaction *DOUVES = new ActionReaction("Douves", 2, {"+1 Carte", "+1 Carte"}, "\033[0m+2 Cartes ; \033[34mLorsqu'un adversaire joue une carte Attaque, vous pouvez dévoiler cette carte de votre main. Dans ce cas, l'Attaque n'a pas d'effet sur vous. \033[0m", {"effet Douves"});

const RoyaumeVictoire *JARDINS = new RoyaumeVictoire("Jardins", 4, {"effet Jardins"}, "\033[32mVaut 1 Point de Victoire pour chaque 10 cartes dans votre deck (arrondi à l'unité inférieure). \033[0m");

void detruireCartes(){
    delete ATELIER;
    delete AVENTURIER;
    delete BIBLIOTHEQUE;
    delete BUCHERON;
    delete CAVE;
    delete CHAMBREDUCONSEIL;
    delete CHANCELIER;
    delete CHAPELLE;
    delete FESTIN;
    delete FESTIVAL;
    delete FORGERON;
    delete JARDINS;
    delete LABORATOIRE;
    delete MARCHE;
    delete MINE;
    delete PRETEURSURGAGES;
    delete RENOVATION;
    delete SALLEDUTRONE;
    delete VILLAGE;
    delete BUREAUCRATE;
    delete ESPION;
    delete MILICE;
    delete SORCIERE;
    delete VOLEUR;
    delete DOUVES;
    delete PROVINCE;
    delete DUCHE;
    delete DOMAINE;
    delete MALEDICTION;
    delete CUIVRE;
    delete ARGENT;
    delete OR;
}

void listeCarte(){
        std::cout << "Les 25 cartes du jeu de bases sont : " << std::endl;
        std::cout << "       Atelier, Aventurier, Bibliothèque, Bûcheron, Bureaucrate, Cave, Chambre du Conseil, Chancelier, Chapelle,"  << std::endl;
        std::cout << "       Douves, Espion, Festin, Festival, Forgeron, Jardin, Laboratoire, Marché,  Milice, Mine, Prêteur sur Gages," << std::endl;
        std::cout << "       Rénovation, Salle du Trône, Sorcière, Village, Voleur" <<std::endl << std::endl;
}

std::vector<const Royaume*> setCarte1(){
    return {ATELIER, AVENTURIER, BIBLIOTHEQUE, BUCHERON, CAVE, CHAMBREDUCONSEIL, CHANCELIER, CHAPELLE, FESTIN, FESTIVAL, FORGERON, JARDINS, LABORATOIRE, MARCHE, MINE, PRETEURSURGAGES, RENOVATION, SALLEDUTRONE, VILLAGE, BUREAUCRATE, ESPION, MILICE, SORCIERE, VOLEUR, DOUVES};
}
