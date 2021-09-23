#pragma once

#include <cstdlib>

class IntArray {
	int* data = nullptr;
	int size = 0;

public :
	IntArray() {
		//data = new int[size = 19492];
		data = (int*) malloc(65535 * sizeof(int) );
		this->size = size;
	};

	IntArray(int size)
	{
		//data = new int[size];
		data = (int*)malloc(size * sizeof(int));
		this->size = size;
	}

	~IntArray() {
		//liberer la mémoire
		//delete [] data;
		free(data);
	}

	void set(int idx, int value) {
		//si idx est hors des bornes du tableau
		//faire throw "exception:out of bounds";
		if ((idx < 0) || (idx >= size))
			throw "exception:out of bounds";

		//recup la donnée a la case idx et l'affecter
		data[idx] = value; // *(data + idx) = value;
	};

	int get(int idx) {
		if ((idx < 0) || (idx >= size))
			throw "exception:out of bounds";
		//si idx est hors des bornes du tableau
		//faire throw "exception:out of bounds";

		//recup la donnée a la case idx et la retourner
		
		return data[idx];
	};
};