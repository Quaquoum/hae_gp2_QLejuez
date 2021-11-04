#include "pch.h"
#include <iostream>
#include "IntArray.hpp"
#include "Tool.hpp"

#pragma region Str

int StrLen(const char* list)
{
	if (list == nullptr)
	{
		return 0;
	}
	if (*list != '\0')
	{
		//check le caractere suivant
		return StrLen(++list) + 1;
	}
	if (*list == 0)
	{
		return 0;
	}
}

int StrCmp(const char* src, const char* dst)
{
	if ((src == nullptr) && (dst == nullptr)) return 0;
	if ((*src == 0) && (*dst == 0)) return 0;

	if (*dst == 0) return 1;
	if (*src == 0) return -1;
	if (*dst == *src) return StrCmp(src + 1, dst + 1);
	if (*dst < *src) return -1;
	else return 1;

}

const char* StrStr(const char* src, const char* dst)
{
	if (src == nullptr) return nullptr;
	if (*src == 0) return nullptr;

	if (0 == StrCmp(src,dst))
		return src;
	else
		return StrStr(src + 1, dst);

}

const char* StrChr(const char* s, char c)
{
	if (s == nullptr) return 0;
	if (*s == 0) return nullptr;
	if (*s == c) return s;

	return StrChr(s + 1, c);

}

void StrCpy(char* dst, const char* src)
{
	if (src == nullptr) return;
	if (dst == nullptr) return;
	if (*src == 0)
	{
		*dst = 0;
		return;
	}
	else
	{
		*dst = *src;
		StrCpy(dst + 1, src + 1);
	}
}

void StrCat(char* dst, const char* src)
{
	if (src == nullptr) return;
	if (dst == nullptr) return;

	if (*dst == 0)
	{
		StrCpy(dst, src);
	}
	else
	{
		return StrCat(dst + 1, src);
	}


}


/*int main()
{
	//strlen - Renvoi le nombre de caractères
	const char* listvide = "";
	const char* listnull = nullptr;
	char c = 'l';
	const char* copy;

	const char* list = "Salut";
	char* list2 = (char*)malloc(150);
	list2[0] = 0;

	StrCat(list2, "Oui");
	printf("%s \n", list2);

	//printf("%s \n", StrStr(list, list2));
	
	//printf("%s \n", copy);

	//printf("%s \n", StrChr(list, c));
	//printf("%s \n", StrChr(listvide, c));
	//printf("%s \n", StrChr(listnull, c));

	/*printf ("%d", StrLen(list));
	printf("%d", StrLen(listvide));
	printf("%d", StrLen(listnull));
}*/

#pragma endregion

#pragma region Int Array

int main()
{

#pragma region SpeedTest
	/*
	srand(0);
	Int64Array ti6;
	{
		for (int i = 0; i < 100000; i++)
		{
			ti6.push_back(rand() % 11353453);
		}
	}

	{
		double t0 = getTimeStamp();
		Int64Array ti7;

		ti7.append_sorted(ti6.data, ti6.curSize);

		double t1 = getTimeStamp();
		printf("time elapsed append : %llf s", (t1 - t0));

		//ti4.bsearch(11);
	}

	{
		double t0 = getTimeStamp();
		Int64Array ti8;

		ti8.insertionSort(ti6.data, ti6.curSize);

		double t1 = getTimeStamp();
		printf("time elapsed tsort : %llf s", (t1 - t0));
	}*/
#pragma endregion

	//enlever les int64_Array dans le hpp
	int64_t tt[] = { 500,0,12,3,10,5 };
	int sz = sizeof(tt) / sizeof(int);

	//Int64Array ti3;
	//ti3.append_sorted(tt,sz);

	//Int64Array ti4;
	//ti4.insertionSort(tt, sz);

	//ti4.bsearch(11);

	Int64Array ListOrdered(1000);
	for (int i = 0; i < 10000; i++)
		ListOrdered.set(i, i*2);

	int res = ListOrdered.bsearch(8);

	return 0;

}

#pragma endregion
