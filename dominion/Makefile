CXX=g++
CXXFLAGS=-std=c++17 -Wall -Wextra -Werror

%.o: fichierCPP/%.cpp
	$(CXX) $(CXXFLAGS) $< -c -o fichierCPP/$@

dominion: fichierCPP/carte.o fichierCPP/tresor.o fichierCPP/victoire.o fichierCPP/royaume.o fichierCPP/action.o fichierCPP/actionAttaque.o fichierCPP/actionReaction.o fichierCPP/royaumeVictoire.o fichierCPP/actionVictoire.o fichierCPP/jeuBase.o fichierCPP/extIntrigue.o fichierCPP/deck.o fichierCPP/mainJeu.o fichierCPP/defausse.o fichierCPP/joueur.o fichierCPP/joueurHumain.o fichierCPP/joueurAI.o fichierCPP/rebut.o fichierCPP/achat.o fichierCPP/partie.o fichierCPP/dominion.o fichierCPP/effet.o fichierCPP/main.o
	$(CXX) $^ -o $@ -lsfml-graphics -lsfml-window -lsfml-system

.PHONY: run clean

play: ./dominion
	./$<

clean:
	rm -f fichierCPP/*.o *~ *.core 