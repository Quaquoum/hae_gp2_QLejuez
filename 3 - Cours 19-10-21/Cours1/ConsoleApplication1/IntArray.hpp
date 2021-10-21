#pragma once
#include <iostream>;

class Int64Array {
public:
	int64_t * data;
	int maxSize;
	int curSize;

	Int64Array(int size = 0)
	{
		//Allouer le tableau
		if (size < 0) size = 0;
		curSize = size;
		if (size <= 0) maxSize = 16;
		else
			maxSize = size;

		data = (int64_t*) malloc(maxSize * sizeof(int64_t));

		Zero(0,size);
	}

	void Zero(int idx, int nbElem)
	{
		if (idx < nbElem)
		{
			data[idx] = 0;
			Zero(idx + 1, nbElem);
		}
	}

	int64_t& get(int pos)
	{
		ensure(pos + 1);
		curSize = pos + 1;
		return data[pos];
	}

	int64_t& operator[](int idx) {
		return get(idx);
	}

	~Int64Array()
	{
		free(data);
		data = nullptr;
		maxSize = 0;
		curSize = 0;
	}

	void ensure(int size)
	{
		if (maxSize > size)
		{
			return;
		}

		int oldSize = maxSize;
		maxSize = size;
		data = (int64_t*)realloc(data, maxSize* sizeof(int64_t));
		Zero(oldSize, maxSize);
	}

#pragma region EnsureNew
	void ensureNew(int size)
	{
		if (maxSize > size)
		{
			return;
		}

		int oldSize = maxSize;
		maxSize = size;
		int64_t* oldData = data;
		data = new int64_t(size);
		memcpy(data, oldData, oldSize * sizeof(int64_t));
		delete[]oldData;
		Zero(oldSize, maxSize);
	}
#pragma endregion

	void set_unsafe(int pos, int64_t elem)
	{
		data[pos] = elem;
	}

	void set(int pos, int64_t elem)
	{
		ensure(pos + 1);
		data[pos] = elem;
		if (pos >= curSize) curSize = pos + 1;
	}

	void push_back(int64_t elem)
	{
		set(curSize, elem);
	}

	void insert(int pos, int64_t elem)
	{
		//a b c d
		//0 a b c d
		//e a b c d
		shift_right(curSize - pos);
		set(pos, elem);

	}

	void shift_right(int pos)
	{
		ensure(pos);
		set(pos, data[pos - 1]);
		if (pos > 0)
			shift_right(--pos);

	}

	void insert_ordered(int pos, int64_t elem)
	{

	}


};