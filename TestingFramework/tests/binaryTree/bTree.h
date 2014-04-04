#pragma once

#include "iTree.h"

namespace Tree
{
class BTree : public ITree
{
public:
	BTree();
	virtual ~BTree();

	bool lookup(unsigned long long const &key);
	void insert(unsigned long long key);
	bool empty() const;

protected:
	static short const pageSize = 16;
	static short const pivot = pageSize / 2;
	struct Page
	{
		short count;
		bool isLeaf;
		Page* children[pageSize];
		unsigned long long keys[pageSize];


		Page()
			: count(0)
			, isLeaf(true)

		{
			for (short i = 0; i < pageSize; i++)
			{
				children[i] = nullptr;
			}
		}

	};

	Page *mRoot;

	bool lookupRec(Page *localRoot, unsigned long long const &key);
	void insertFirst(unsigned long long const &key);
	void insertNonFull(Page *host, unsigned long long const &key);
	void splitChild(Page *host, short const index);
	void deleteSubDetour(Page *current);
};



}