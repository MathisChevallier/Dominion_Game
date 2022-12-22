#include <iostream>
#include "PartieClass.hpp"

int main()
{
	Partie* p1 = new Partie();
	
	std::cout << "nb de joueur " << p1->getNbJoueur();

	delete p1;

	return 0;
}