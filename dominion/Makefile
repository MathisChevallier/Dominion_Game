CXX=g++
CXXFLAGS=-std=c++17 -Wall -Wextra -Werror

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -c -o $@

dominion: carte.o tresor.o victoire.o royaume.o action.o actionAttaque.o actionReaction.o royaumeVictoire.o jeuBase.o deck.o mainJeu.o defausse.o partie.o rebut.o achat.o joueur.o joueurHumain.o joueurAI.o dominion.o effet.o main.o
	$(CXX) $^ -o $@

.PHONY: run clean

run: dominion
	./$<

clean:
	rm -f *.o *~ *.core 