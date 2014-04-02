#pragma once

#include "iTree.h"

class SplayTree : public ITree
{
public:
	SplayTree();

	void insert(unsigned long long key);
	void insertConst(unsigned long long const &key);
	bool lookup(unsigned long long const &key);


	const unsigned long long& minimum();
	const unsigned long long& maximum();

	bool empty() const;
	unsigned long size() const;

private:
	struct Node
	{
		Node *parent;
		Node *left;
		Node *right;
		unsigned long long key;

		Node(unsigned long long const &init = 0, Node *nParent = nullptr)
			:  parent(nParent)
			, left(nullptr)
			, right(nullptr)
			, key(init)
		{}
	};

	Node *mRoot;
	unsigned long mSize;

	void replace(Node *u, Node *v);
	void rotateLeft(Node *x);
	void rotateRight(Node *x);
	void splay(Node *x);

	Node* find(const unsigned long long &key);
	Node* subtreeMinimum(Node *u);
	Node* subtreeMaximum(Node *u);

	inline void zig(Node *x);
};
