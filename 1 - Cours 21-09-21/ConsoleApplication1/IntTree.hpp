#pragma once

#include <cstdlib>
#include <cstring>

struct IntTree {

	int value = 0.0;

	//le fils gauche de l'arbre
	IntTree* fg = nullptr;
	//le fils droit de l'arbre
	IntTree* fd = nullptr;

	//relation d'ordre
	//valeur de fg < valeur < valeur fd
};

IntTree* create(int value)
{
	IntTree* node = (IntTree*)malloc(sizeof(IntTree));
	node->value = value;
	node->fg = node->fd = nullptr;
	return node;

}

int count(IntTree* head)
{
	if (!head) return 0;
	return 1 + count(head->fg) + count(head->fd);
}

IntTree* insert(IntTree* head, int value)
{
	return nullptr;
}

IntTree* remove(IntTree* head, int value)
{
	return nullptr;
}