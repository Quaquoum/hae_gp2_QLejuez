#pragma once

template<typename Type>
class List
{
public:

	Type val = {};
	List* next = nullptr;


	List(Type elem)
	{
		val = elem;
	}

	List(Type elem, List* _next)
	{
		val = elem;
		next = _next;
	}

	//push_first
	List* push_first(Type nu_elem)
	{
		auto l = new List(nu_elem);
		l->next = this;
		return l;
	}

	List* remove(Type elem)
	{
		if (val == elem)
		{
			List* n = next;
			delete this;
			return n;
		}
		else
		{
			if (next) 
				next->remove(elem);
			return this;
		}
	}

	//push_back
	List* push_back(Type nu_elem)
	{
		if (next) next->push_back(nu_elem);
		else
		{
			next = new List(nu_elem);
		}
		return this;
	}
};