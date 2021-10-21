#pragma once
#include <iostream>

class Int64Array {
public:
	int64_t * data;
	int maxSize;
	int curSize;

	Int64Array(int size = 0);

	void Zero(int idx, int nbElem);

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

	void ensure(int size);
	void ensureNew(int size);

	void set_unsafe(int pos, int64_t elem);
	void set(int pos, int64_t elem);

	void push_back(int64_t elem);

	void insert(int pos, int64_t elem);
	void _shift_from_to(int end, int cur);
	void shift_right(int pos);

	//inserer l'element en respectant la relation d'ordre data[a-1] < data[a]
	void insert_ordered(int64_t elem)
	{
		int pos = search_position(0, elem);
		if (pos == -1) insert(0, elem);
		else insert(pos, elem);

		//check_shift(elem, maxSize);

	}

	void check_shift(int64_t elem, int cur)
	{
		//si data est plus grand ou égal > avancer
		if (data[cur] >= elem)
		{
			check_shift(elem, cur - 1);
		}

		if (data[cur] < elem)
		{
			//si data est plus petit que elem inserer
			insert(cur +1, elem);
			return;
		}
	}

	int search_position(int idx, int elem)
	{
		//si data est plus grand ou égal > avancer
		if (idx >= curSize)
			return curSize;

		if (data[idx] >= elem)
			return idx;
	
		if (data[idx] < elem)
			search_position(idx + 1, elem);
	}


	void append_sorted(const int64_t* arr, int sz)
	{
		if (sz <= 0) return;

		insert_ordered(arr[0]);
		append_sorted(arr + 1, sz - 1);

	}

	void clear()
	{
		curSize = 0;
	}

	void load(const int64_t* arr, int sz)
	{
		if (sz == 0) return;

		set(curSize, arr[0]);
		load(arr + 1, sz - 1);
	}

	void insertionSort(const int64_t* arr, int sz)
	{
		clear();
		load(arr, sz);

		//en iteratif
		int j;
		for (int i = 1; i < sz; i++)
		{
			j = i;
			while (j > 0 && data[j] < data[j - 1])
			{
				int64_t temp = data[j];
				data[j] = data[j - 1];
				data[j - 1] = temp;
				j--;
			}
		}

		//for i 1 n
		//j = i
		//while j > 0 && arr[j] < arr[j-1]
		//swap (j,j-1)
	}

	void bsearch(int nb)
	{
		int pos = searchMid(nb, 0, maxSize);
		insert(pos, nb);
	}

	int searchMid(int nb, int start, int end)
	{
		if (start == end - 1)
		{
			return end;
		}

		int midValue = (start + end) / 2;

		if (data[midValue] < nb)
		{
			searchMid(nb, start, midValue - 1);
		}
		if (data[midValue] > nb)
		{
			searchMid(nb, midValue + 1, end);
		}

	}
};