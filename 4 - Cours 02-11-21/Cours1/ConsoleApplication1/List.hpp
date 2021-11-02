#pragma once

class List
{
public:

	double val = 0.0;
	List* next = nullptr;
	List* head = nullptr;


	List(double elem)
	{
		val = elem;
		head = this;
	}

	List(double elem, List* _next)
	{
		val = elem;
		next = _next;
		head = this;
	}

	//remove
	List* remove()
	{

	}

	//push_first
	List* push_first(double nu_elem)
	{
		//decaller vers la droite
		List* newList = new List(nu_elem);
		newList->next = head;
		head = newList;

		return head;
	}

	//push_back
	List* push_back()
	{

	}

};