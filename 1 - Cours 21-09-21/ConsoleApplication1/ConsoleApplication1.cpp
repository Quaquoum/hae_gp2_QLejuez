// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include "Toto.h"

namespace Oui
{

}

/*void main1()
{
	printf("%i \n", 0);
	printf("%f \n", 0.5);
	printf("%s \n", "Toto");

	long long int t = 123456789123456789;
	printf("%lld\n", t);


}*/

int main()
{
	printf("0\n");
	//Allocation statique
	// l'instance est sur la pile / stack
	Toto tStatic;

	//afficher(tStatic.x)
	printf("%f \n", tStatic.x);

	//garde pour plus tard
	//Allocation statique
	// l'instance est sur le tas / heap
	Toto* tDynamic = new Toto();

	return 0;
}