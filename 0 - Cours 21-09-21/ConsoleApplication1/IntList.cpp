#include "IntList.hpp"

IntList* append(IntList* l, int value)
{
	//Construire une liste 
	IntList* list = (IntList*)malloc(sizeof(IntList));

	list->next = nullptr;
	list->value = value;

	if (!l)
		return list;
	if (l->next)
	{
		l->next = list;
		return l;
	}


	return list;
}

IntList* appendFirst(IntList* l, int value)
{
	IntList* v = (IntList*)malloc(sizeof(IntList));
	v->value = value;
	v->next = l;
	return v;
}

IntList* appendLast(IntList* l, int value)
{
	if (!l)
	{
		return appendFirst(l, value);
	}
	if (l->next)
	{
		appendLast(l->next, value);
	}
	else
	{
		l->next = appendFirst(nullptr, value);
	}
	return l;
}

IntList* remove(IntList* l, int value)
{
	//fin de la liste
	if (!l)
		return nullptr;

	//verifier si la liste a la valeur voulu
	if (l->value == value)
	{
		IntList* rest = l->next;
		free(l);
		return rest;
	}
	else  //refaire une boucle pour vérifier le prochain
	{
		l->next = remove(l->next, value);
		return l;
	}
}

int length(IntList* l)
{
	if (!l) return 0;
	else return 1 + length(l->next);

	return 0;
}