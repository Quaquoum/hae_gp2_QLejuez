
#include "pch.h"
#include <iostream>
#include "IntArray.hpp"

/*void IntArray::resize(int newSize) {

	//si la taille est suffisante sortir
	if (size >= newSize)
		return;

	data = (int*)realloc(data, (newSize + 1) * sizeof(int));

	//met des zero dans la zone nouvellement allouée
	for (int i = size; i < newSize; i++)
	{
		data[i] = 0;
	}


	size = (newSize + 1);

	/*
	int* ndata = new int[newSize]
	for (int i = 0; i < size; i++)
	ndata[i] = data[i];
	for (int i = size; i < newSize; i++)
	ndata[i] = 0;
	int* oldData = data;
	this->data = ndata;
	delete oldData;
	size = (newSize)
	
	
	*//*
}*/