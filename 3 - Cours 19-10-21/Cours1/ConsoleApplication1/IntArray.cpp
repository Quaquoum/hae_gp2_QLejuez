#include <iostream>
#include "pch.h"
#include "IntArray.hpp"
#include <cstdlib>

Int64Array::Int64Array(int size)
{
	//Allouer le tableau
	if (size < 0) size = 0;
	curSize = size;
	if (size <= 0) maxSize = 16;
	else
		maxSize = size;

	data = (int64_t*)malloc(maxSize * sizeof(int64_t));

	Zero(0, size);
}

void Int64Array::Zero(int idx, int nbElem)
{
	memset(data + idx, 0, nbElem * sizeof(int64_t));
}

void Int64Array::ensure(int size)
{
	if (maxSize > size)
	{
		return;
	}

	int oldSize = maxSize;
	maxSize = size;
	data = (int64_t*)realloc(data, maxSize * sizeof(int64_t));
	Zero(oldSize, maxSize);
}

void Int64Array::ensureNew(int size)
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

void Int64Array::set_unsafe(int pos, int64_t elem)
{
	data[pos] = elem;
}

void Int64Array::set(int pos, int64_t elem)
{
	ensure(pos + 1);
	data[pos] = elem;
	if (pos >= curSize) curSize = pos + 1;
}

void Int64Array::push_back(int64_t elem)
{
	set(curSize, elem);
}

void Int64Array::insert(int pos, int64_t elem)
{
	//ensure(maxSize + 1);
	shift_right(pos);
	set(pos, elem);

}

void Int64Array::_shift_from_to(int end, int cur)
{
	//swap cur and its prev

	if (cur != end)
	{
		set(cur, data[cur - 1]);
		_shift_from_to(end, cur - 1);
	}
	else
	{
		return;
	}


	/*if (cur <= end)
	return;
	data[cur] = data[cur - 1];*/

}

void Int64Array::shift_right(int pos)
{
	/*int sz = curSize;
	ensure(curSize+1);
	_shift_from_to(pos, sz-1);*/

	_shift_from_to(pos, maxSize);
}
