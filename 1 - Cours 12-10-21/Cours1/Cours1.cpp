// Cours1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include "IntArray.hpp"

double IntArray::tempRes = 0;

/*int main()
{
	IntArray tablo(15);

	for (int i = 0; i < 15; i++)
	{
		tablo.set(i, (i * i));
	}

	std::function<void(int)> foo = [](int value) {
		printf("%d \n", value);
	};

	//tablo.iter(foo);
	double res = tablo.sum();

	int tab[4] = { 0,1,2,3 };
	IntArray* maCopie = IntArray::fromArray(tab, 4);

	maCopie->printArray();

	std::cout << "Hello World!\n" << res << "\n";
}*/

void Memcpy(char* dst, const char* src, int len)
{
	for (int i = 0; i < len; i++)
	{
		dst[i] = src[i];
	}
}

const char* StrChr(const char* grange, char chat)
{
	while (*grange)
	{
		if (*grange == chat)
			return grange;
		grange++;
	}

	return nullptr;
}

const char* StrStr(const char * a, const char * b)
{
	//récup longueur de b
	int size = strlen(b);

	//tant que a
	while (*a)
	{
		bool found = true;
		//pour chaque b
		for (int i = 0; i < size; i++)
		{
			if (a[i] != b[i])
			{
				//si on trouve pas un char A, avancer A
				a++;
				found = false;
				break;
			}
		}
		if (found)
			return a;
	}
	return nullptr;
}


/*
int main()
{
	int s[4] = { 0,0,0,0 };
	int t[4] = { 0,1,2,3 };

	Memcpy((char*)s, (char*)t, 4 * sizeof(int));

	for (int i = 0; i < 4; i++)
	{
		printf("%d\n", s[i]);
	}

	const char* toto = StrStr("salut", "lu");

	return 0;
}
*/

int add(int a, int b) // avec que des +1
{
	if (b == 0)
		return a;
	else if (b > 0)
		return 1 + add(a, b - 1);
	else
		return -1 + add(a, b + 1);
	
}

int sub(int a, int b) // avec des additions
{
	return add(a, -b);
}

int mul(int a, int b)// avec des additions
{
	//si b est particulier
	if (b == 0 || a == 0)
	{
		return 0;
	}
	if (b < 0)
		return sub(0, mul(a, sub(0,b)));

	return add(a, mul(a, b - 1));
}

int divInt(int a, int b) // avec des soustractions utiliser une fonction intermédiaire 
{
	if (a == 0)
		return 0;
	if (b == 0)
		throw "division by zero";
	if (a < b)
		return 0;

	if (a < 0)
		return sub(0, divInt(sub(0, 0),b));



	return 1 + divInt( sub(a,b),b);

}
//int mod(int a, int b); // reste de la division
//int len(int vecX, int vecY); // avec les fonctions precédentes


int main()
{
	int res = divInt(13, 4);

	return 0;
}