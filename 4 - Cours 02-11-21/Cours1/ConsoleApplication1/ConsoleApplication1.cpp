#include "pch.h"
#include <iostream>
#include "IntArray.hpp"
#include "Tool.hpp"
#include "List.hpp"


int mainList()
{
	List* v0 = new List(66);
	List* v1 = new List(67, v0);

	v0->push_first(2);

	return 0;
}