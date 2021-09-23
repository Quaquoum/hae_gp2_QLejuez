// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//


#include "pch.h"
#include <iostream>
#include "Toto.h"
#include "IntArray.hpp"

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

/*int main2()
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
} */


/*int main()
{
	int tab[] = { 0,1,2,3 };
	int *c = &tab[0];
	*c = 0;

	//*c => pile
	//afficher c
	//incrementer la valeur
	//incremente c et prend le contenu

	//printf("%d", *c++); //incremente c et prend le contenu - 0 303
	//printf("%d", (*c)++); // prend le contenu de c et incremente le - 0
	//printf("%d", *++c); //incremente c et prend le contenu - 1
	printf("%d", ++*c); // prend le contenu de c et incremente le - 1


	return 0;
}*/

/*struct Vec {
	float x = 0;
	float y = 0;
	float z = 0;
};

int main()
{
	//Vec toto;
	Vec* toto = new Vec();

	toto->y = 67; // (*toto).y = 67;
	(*toto).z = 66;
	(*toto).x = 10;

	printf("%f %f %f", toto->x, toto->y, toto->z);

	return 0;
}*/


/*struct Vec4 {
	float x = 1;
	float y = 1;
	float z = 1;
	float w = 1;

	Vec4 add(Vec4 v)
	{
		Vec4 res;
		res.x = x + v.x;
		res.y = y + v.y;
		res.z = z + v.z;
		res.w = w + v.w;
		return res;
	};

	void incr(float f)
	{
		x = x + f;
		y = y + f;
		z = z + f;
		w = w + f;
	};

	Vec4 div(Vec4 v)
	{
		Vec4 res;
		res.x = x / v.x;
		res.y = y / v.y;
		res.z = z / v.z;
		res.w = w / v.w;
		return res;
	};
};



int main()
{
	//Vec toto;
	Vec4 a;
	Vec4 b;

	a.x = 16;
	b.x = 20;

	a.y = 30;
	b.y = 10;

	a.z = b.z = 8;

	a.w = 10;
	b.w = 5;

	//Vec4 res = a.div(b);
	//Vec4 res = a.add(b);
	Vec4 res = res.incr(10);
	

	printf("%f %f %f %f", res.x,res.y,res.z,res.w);
	return 0;
}*/

int main()
{
	IntArray bob;

	for (int i = 0; i < 16; i++)
	{
		bob.set(i, i * i);
	}
	for (int i = 0; i < 16; i++)
	{
		printf("%d", bob.get(i));
	}

	printf("\n");

	return 0;
}