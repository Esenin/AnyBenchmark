#pragma once

#include <memory.h> // for memset

#include "iTree.h"

//! template @class VEBoasTree is van Emde Boas Tree, container for [0, 2^K] integers
//! implementation
template <unsigned K>
class VEBoasTree : public ITree
{
private:
	unsigned long long tMin;
	unsigned long long tMax;
	VEBoasTree<(K >> 1)> *children[1ULL << (K >> 1)];
	VEBoasTree<(K >> 1)> *aux;

	inline static unsigned long long none(unsigned long long const k)
	{
		return (1ULL << k);
	}

public:
	VEBoasTree()
		: tMin(none(K))
		, aux(nullptr)
	{
		memset(children, 0, sizeof(children)); // looks faster
		/*for (unsigned long long i = 0; i < (1ULL << (K >> 1)); i++)
			children[i] = nullptr;*/
	}

	~VEBoasTree()
	{
		unsigned long long const rightBound = (1ULL << (K >> 1));
		delete aux;
		for (unsigned long long i = 0; i < rightBound; ++i)
		{
			delete children[i];
		}
	}

	inline bool empty() const
	{
		return tMin == none(K);
	}

	inline unsigned long long high(unsigned long long const &key) const
	{
		return key >> (K >> 1);
	}

	inline unsigned long long low(unsigned long long const &key) const
	{
		return key & ((1ULL << (K >> 1)) - 1ULL);
	}

	inline unsigned long long merge(unsigned long long const &high, unsigned long long const &low) const
	{
		return ((high << (K >> 1)) | low);
	}

	void insert(unsigned long long key)
	{
		if (empty())
		{
			tMin = key;
			tMax = key;
			return;
		}

		if (key < tMin)
		{
			unsigned long long tempKey = key;
			key = tMin;
			tMin = tempKey;
		}

		if (key > tMax)
		{
			tMax = key;
		}

		if (K != 1)
		{
			unsigned long long keyHigh = high(key);
			unsigned long long keyLow = low(key);

			if (children[keyHigh] == nullptr)
			{
				children[keyHigh] = new VEBoasTree<(K >> 1)>();
			}

			if (children[keyHigh]->empty())
			{
				if (aux == nullptr)
				{
					aux = new VEBoasTree<(K >> 1)>();
				}
				aux->insert(keyHigh);
			}

			children[keyHigh]->insert(keyLow);
		}
	}

	bool lookup(unsigned long long const &key)
	{
		if (empty())
		{
			return false;
		}
		if (key == tMin || key == tMax)
		{
			return true;
		}
		unsigned long long keyHigh = high(key);
		unsigned long long keyLow = low(key);
		return (children[keyHigh] != nullptr) && (children[keyHigh]->lookup(keyLow));
	}
};
