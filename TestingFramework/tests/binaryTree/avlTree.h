#pragma once

#include "iTree.h"

namespace Tree
{
typedef unsigned long long Type;
//! @class AVLTree is a classic simple implementation of avl binary tree
class AVLTree : public ITree
{
public:
	AVLTree();
	AVLTree(Type key);
	~AVLTree();

	void insert(Type key);

	bool lookup(Type const &key);

	bool isEmpty() const;

protected:
	struct Node
	{
		Type data;
		Node *parent;
		Node *leftChild;
		Node *rightChild;
		int height;

		Node(Type key)
			: parent(nullptr)
			, leftChild(nullptr)
			, rightChild(nullptr)
			, height(0)
		{
			this->data = key;
		}
		~Node()
		{
			if (leftChild != nullptr)
			{
				delete leftChild;
			}
			if (rightChild != nullptr)
			{
				delete rightChild;
			}
		}

		int updateHeight();
		int getBalance();
		Node* setLeftChild(Node* newLeft);
		Node* setRightChild(Node* newRight);
	};

	Node *mRoot;

	void setRoot(Node *node);
	int height();
	Node* findNode(Type key);
	void rotateLeft(Node *n);
	void rotateRight(Node * n);
	void balanceAtNode(Node *n);
};

}
