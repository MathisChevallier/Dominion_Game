# Dominion_Game

Ce projet a été réalisé en binôme. Il s'agit du projet majorant de la promotion.

Création du jeu de société Dominion. L'interface graphique est inspirée et similaire à la version officielle.
Il s'agit d'un jeu de deck-buiding, c'est à dire que tous les joueurs commencent avec les mêmes cartes en main, puis font des choix pour acheter des cartes parmis celles de la ligne d'achat, commune à tous les joueurs.
Le joueur avec le plus de points de victoire à la fin de la partie gagne.
Toutes les règles ainsi que des extentions ont été implémentées.

Il est possible de jouer contre l'ordinateur, qui s'adapte à chaque tour aux conditions de jeu. Il est capable de gagner et réalise des choix stratégiques (pas de hasard). Chaque partie est donc différente.

## Ressources :
![Enonce](Enonce-Projet.pdf)  

![Règles du jeu](Domion_base_regles_vf.pdf)

## Commande pour lancer le jeu :
 
Téléchargez les archives 'src' et 'dominion' puis effectuez la commande "make run". Le code se compilera si besoin et le jeu se lancera. Il ne vous reste plus qu'à suivre les instructions à l'écran.
 
Commande pour tester fuite mémoire : valgrind -s --leak-check=full ./dominion
Il faut au préalable avoir valgrind d'installé.

## Quelques aperçus du jeu :


Interface graphique:
<img width="1024" alt="Dominion1" src="https://github.com/MathisChevallier/Dominion_Game/assets/118447835/9d4639fa-b356-4fb5-89e5-ee37c940def1">

![Dominion2](https://github.com/MathisChevallier/Dominion_Game/assets/118447835/2868a707-94b5-4887-8198-e61b8aba3c94)

<img width="1024" alt="Dominion4" src="https://github.com/MathisChevallier/Dominion_Game/assets/118447835/f7733e23-4a46-45d5-b1ef-1dcd031aa9d5">

Interface console:

Création d'une partie
<img width="1024" alt="Dominion6" src="https://github.com/MathisChevallier/Dominion_Game/assets/118447835/ce24c467-62f1-4ba2-9cff-6da7a359176f">

Main d'un joueur au début de son tour
<img width="1024" alt="Dominion7" src="https://github.com/MathisChevallier/Dominion_Game/assets/118447835/48a21fa0-5491-42ce-b095-d0e3cc99b48a">

Ligne d'achat avec caractéristiques et résumé explictaif de chaque carte 
<img width="1024" alt="Dominion8" src="https://github.com/MathisChevallier/Dominion_Game/assets/118447835/4fa5b5eb-6052-4b4e-bb81-11af3283d30e">

Affichage des cartes disponible achetable par le joueur pour faciliter la lecture
<img width="1024" alt="Dominion9" src="https://github.com/MathisChevallier/Dominion_Game/assets/118447835/133f2ca3-344a-40fb-819e-0d2af0aa6412">
