#pragma once

#include <QtCore/QList>
#include <QtCore/QSet>

#include "iTree.h"

namespace Tree
{
typedef unsigned long long Type;
//! @class VEBLayoutBinTree is a modification of AVL-like binary tree
//! implementation idea: each node has also children of host-key
//! that must decrease number of cachemisses
class VEBLayoutBinTree : public ITree
{
public:
	VEBLayoutBinTree();
	~VEBLayoutBinTree();

	void insert(unsigned long long key);
	bool lookup(unsigned long long const &key);
	bool isEmpty() const;
	//! Builds the tree from inputted  values due hastily implementation of "insert" method
	void buildTree();

protected:
	enum ChildIndex
	{
		leftLeftChild
		, leftRightChild
		, rightLeftChild
		, rightRightChild
	};

	struct Page
	{
		Type key;
		bool hasLeftChild;
		Type leftKey;
		bool hasRightChild;
		Type rightKey;
		Page* children[4];

		Page()
			: hasLeftChild(false)
			, hasRightChild(false)
		{
			for (int i = 0; i < 4; i++)
			{
				children[i] = nullptr;
			}
		}

		~Page()
		{
			for (int i = 0; i < 4; i++)
			{
				if (this->children[i] != nullptr)
				{
					delete this->children[i];
				}
			}
		}
	};

	Page *mRoot;
	QList<Type> mData;

	void makeSubTree(Page* &locRoot, int const leftBound, int const rightBound);
	bool findIn(Page *subTree, Type const &key);
};
}

