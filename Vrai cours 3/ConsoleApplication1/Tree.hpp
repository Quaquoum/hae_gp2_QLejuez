#pragma once

template<typename Value>
class Tree {
public:
	Value v = {};
	Tree* l = nullptr;
	Tree* r = nullptr;

	Tree(Value v)
	{
		this->v = v;
	}

	Tree* insert(Value nu)
	{
		if (v > nu)
		{
			//mettre a gauche
			if (l) l ->insert(nu);
			if (!l) l = new Tree<Value>(nu);
		}

		if (v <= nu)
		{
			//mettre a droite
			if (r) r ->insert(nu);
			if (!r) r = new Tree<Value>(nu);
		}

		return this;
	}

	Tree* remove(Value o)
	{
		if (o == v)
		{
			//remove
			auto _l = l;
			auto _r = r;
			if (!l)
			{
				delete this;
				return _r;
			}
			else if (!r)
			{
				delete this;
				return _l;
			}
			else {
				l->merge(r);
				delete this;
				return _l;
			}
		}
		else
		{
			if (o < v)
			{
				if (l)
					l = l->remove(o);
			}
			else
			{
				if (r)
					r = r->remove(o);
			}
			return this;
		}
	}

	Tree* merge(Tree* other)
	{
		Value vo = other->v;

		insert(vo);

		if (other->l) merge(other->l);
		if (other->r) merge(other->r);

		delete other;

		return this;
	}

	Tree* search(Value o)
	{
		if (v == o)
		{
			return this;
		}
		else
			if (o < v)
			{
				if (l)
					return l->search(o);
				else return nullptr;
			}
			else
			{
				if (r)
					return r->search(o)
				else
					return nullptr;
			}

		return nullptr;
	}
};