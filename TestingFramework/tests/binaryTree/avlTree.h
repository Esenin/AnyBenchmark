#pragma once

#include "iTree.h"

namespace Tree
{
//! @class AVLTree is a classic simple implementation of avl binary tree
class AVLTree : public ITree
{
public:
	AVLTree();
	~AVLTree();

	void insert(Type const &key);

	bool lookup(Type const &key) const;

	bool isEmpty() const;

protected:
	struct Node;

	Node *mRoot;

	void setRoot(Node *node);
	int height();
	Node* findNode(Type key) const;
	void rotateLeft(Node *n);
	void rotateRight(Node * n);
	void balanceAtNode(Node *n);
};

}
