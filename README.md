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

![Diagramme UML](UML_Dominion.pdf)

## Commande pour lancer le jeu :
 
Téléchargez les archives 'src' et 'dominion' puis effectuez la commande "make run". Le code se compilera si besoin et le jeu se lancera. Il ne vous reste plus qu'à suivre les instructions à l'écran.
 
Commande pour tester fuite mémoire : valgrind -s --leak-check=full ./dominion
Il faut au préalable avoir valgrind d'installé.

## Quelques aperçus du jeu :


Interface graphique:
<img width="1024" alt="Dominion1" src="https://github.com/MathisChevallier/Dominion_Game/assets/118447835/9d4639fa-b356-4fb5-89e5-ee37c940def1">

![Dominion2](https://github.com/MathisChevallier/Dominion_Game/assets/118447835/8504b7f4-a8a4-4f46-8446-43bf287fa22c)

<img width="1024" alt="Dominion4" src="https://github.com/MathisChevallier/Dominion_Game/assets/118447835/ead49d31-af86-438d-87da-cab598126050">


Interface console:

Création d'une partie
<img width="1024" alt="Dominion6" src="https://github.com/MathisChevallier/Dominion_Game/assets/118447835/98500259-02f0-4950-9732-3044c448c94e">


Main d'un joueur au début de son tour
<img width="1024" alt="Dominion7" src="https://github.com/MathisChevallier/Dominion_Game/assets/118447835/ca461098-36c7-448e-88c9-3ddc089572e0">

Ligne d'achat avec caractéristiques et résumé explictaif de chaque carte 
<img width="960" alt="Dominion8" src="https://github.com/MathisChevallier/Dominion_Game/assets/118447835/89a3a75c-3cd2-4419-ae67-f08ad50a4d76">


Affichage des cartes disponible achetable par le joueur pour faciliter la lecture
<img width="953" alt="Dominion9" src="https://github.com/MathisChevallier/Dominion_Game/assets/118447835/ac45e134-f881-4e26-a55d-3f134986b899">

## Diagramme UML :

![image](https://github.com/MathisChevallier/Dominion_Game/assets/118447835/77505113-c1eb-4f83-a83e-1be8aa441ce3)

