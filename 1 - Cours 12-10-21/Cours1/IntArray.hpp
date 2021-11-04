#pragma once

#include <cstdlib>
#include <functional>

class IntArray {
	int* data = nullptr;
	int size = 0;

public:
	IntArray() {
		//data = new int[size = 19492];
		data = (int*)malloc(65535 * sizeof(int));
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

	void printArray()
	{
		for (int i = 0; i < size; i++)
		{
			printf("%d : %d \n", i, data[i]);
		}
	}

	void resize(int newSize)
	{
		//si la taille d'allocation est suffisante
		if (size >= newSize)
			// 	   sortir
			return;

		//#ifdef MALLOC_VERSION
		data = (int*)realloc(data, newSize * sizeof(int));
		memset(data + size, 0, (newSize - size) * sizeof(int));
		//for (int i = size; i < newSize; i++) 
		//	data[i] = 0;
		size = newSize;

		/*#else
				int* ndata = new int[newSize];
				//memcpy(ndata, data, size * sizeof(int));
				for (int i = 0; i < size; i++)
					ndata[i] = data[i];
				for (int i = size; i < newSize; i++)
					ndata[i] = 0;
				int* oldData = data;
				this->data = ndata;
				delete oldData;
				size = newSize;
		#endif*/

	}

	void insertAt(int idx, int value)
	{
		int oldSize = size;

		/*
		//si l'index est a un index plus haut que la limite du tableau
		while (idx > size)
			resize(size + 1);
			*/

			//si il manque une place pour insérer un nouvel élément
		if (data[size] != 0)
			resize(size + 1);

		for (int i = oldSize; i >= idx; i--)
		{
			data[i] = data[i - 1];
		}
		data[idx] = value;

	}

	void insert(int value)
	{
		int idx = 0;
		while ((idx < size) && (data[idx] < value))
		{
			idx++;
		}
		insertAt(idx, value);
	}

	void qsort();

	static double tempRes;

	void reverse()
	{
		for (int i = 0; i < size / 2; i++)
		{
			int old = data[i];
			data[i] = data[size - i - 1];
			data[size - i - 1] = old;
		}
	}

	void iter(std::function<void(int)> f)
	{
		for (int i = 0; i < size; i++)
		{
			f(data[i]);
		}
	}

	double sum()
	{
		//avoir une variable temporaire
		tempRes = 0.0;

		//créer une fonction qui accumule les valeurs
		std::function<void(int)> add = [](int value) {
			tempRes += value;
		};

		//iterer avec
		iter(add);

		//renvoyer res
		return tempRes;
	}

	int get(int idx) {
		if ((idx < 0) || (idx >= size))
			throw "exception:out of bounds";
		//si idx est hors des bornes du tableau
		//faire throw "exception:out of bounds";

		//recup la donnée a la case idx et la retourner

		return data[idx];
	};

	static IntArray* fromArray(int* data, int len)
	{
		//Allouer un nouveau intArray
		IntArray* copy = new IntArray(len);

		//copier les données dans la nouvelle instance
		for (int i = 0; i < len; i++)
			copy->set(i, data[i]);
		//mcpy(copy->data, data, len * sizeof(int));

		//renvoyer cette copie
		return copy;
	}

};