# Dominion_Game
 
Création du jeu de société Dominion.
 
## Ressources :
![Enonce](Enonce-Projet.pdf)  

![Règles du jeu](Dominio_base_regles_vf.pdf)

## TO DO :
classe Achat -> créer selon nombre de personne, créer selon aléatoire ou pas + extension

achat -> phase achat + effet avec achat

joueur IA -> ajouter priorité aux cartes pour pouvoir les jouer et les acheter + faire tour IA

faire fonctionnalité stocker résultat partie (3-Historique parties)

## Ajouts :

07/01/2023 :

 Système de sauvegarde de partie avec demande à la fin de chaque Tour de jeu

 Effets de chaque carte + test carte => AVENTURIER, BIBLIOTHEQUE, BUREAUCRATE, VILLAGE, LABORATOIRE, FESTIVAL, FORGERON, MARCHE, BUCHERON : OK

 Création classe RoyaumeVictoire pour la carte JARDINS

 Comptage et affichage des points avec détails des points de chaque joueur 
 
 ## Lancer jeu :
 
 compiler projet : make run
 
 tester fuite mémoire : valgrind -s --leak-check=full ./dominion
