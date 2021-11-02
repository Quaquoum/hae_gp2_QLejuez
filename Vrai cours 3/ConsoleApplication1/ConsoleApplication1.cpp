#include "pch.h"
#include <iostream>
#include "List.hpp"
#include <vector>
#include <algorithm>

typedef List<double> ListD;
typedef List<float> ListF;
typedef List<int> ListI;
typedef List<std::string> ListS;

int main()
{
	
	ListD* v0 = new ListD(66);
	auto v1 = new ListD(70, v0);
	auto v2 = v1->push_first(34);
	auto v3 = v2->remove(34);
	auto v4 = v3->push_back(34);
	

	ListF* f0 = new ListF(76);
	ListI* i0 = new ListI(86);
	ListS* s0 = new ListS("96");
	s0 = s0->push_back("97");
	s0 = s0->remove("96");

	std::vector<double> vd = {0.0,1.0,2.0};
	vd.push_back(13);
	vd[0] = 14;

	for (int i = 0; i < vd.size(); ++i)
	{
		printf("%f", vd[i]);
	}
	printf("\n-------------\n");
	
	for (auto f : vd)
	{
		printf("%f", f);
	}
	printf("\n-------------\n");

	for (auto iter = vd.begin(); iter != vd.end();)
	{
		printf("%f", *iter);
		if (*iter == 1.0)
			iter = vd.erase(iter);
		else
			iter++;
	}
	printf("\n-------------\n");


	/*
	List* v1 = new List(45, v0);
	List* v2 = v1->push_first(34);
	List* v3 = v2->remove(34);
	List* v4 = v3->push_back(34);
	*/

	return 0;
}