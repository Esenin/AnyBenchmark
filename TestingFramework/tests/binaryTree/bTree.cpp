#include "bTree.h"

using namespace Tree;

BTree::BTree()
	: mRoot(new Page())
{
}

BTree::~BTree()
{
	deleteSubDetour(mRoot);
	delete mRoot;
}

bool BTree::lookup(const unsigned long long &key)
{
	return lookupRec(mRoot, key);
}

bool BTree::lookupRec(BTree::Page *localRoot, unsigned long long const &key)
{
	for(int i = 0; i < localRoot->count; i++)
	{
		if (localRoot->keys[i] == key)
			return true;

		if (localRoot->keys[i] > key)
		{
			if (localRoot->isLeaf)
				return false;

			return lookupRec(localRoot->children[i], key);
		}
	}
	return (localRoot->isLeaf)? false : lookupRec(localRoot->children[localRoot->count], key);
}

void BTree::insert(unsigned long long key)
{
	if (lookup(key))
		return;
	insertFirst(key);
}

bool BTree::empty() const
{
	return mRoot->count == 0;
}

void BTree::insertFirst(unsigned long long const &key)
{
	Page *root = mRoot;
	if (root->count == pageSize - 1)
	{
		Page *newNode = new Page();
		mRoot = newNode;
		newNode->isLeaf = false;
		newNode->count = 0;
		newNode->children[0] = root;
		splitChild(newNode, 0);
		insertNonFull(newNode, key);
	}
	else
	{
		insertNonFull(root, key);
	}
}

void BTree::insertNonFull(BTree::Page *host, const unsigned long long &key)
{
	int i = host->count - 1;
	if (host->isLeaf)
	{
		while ((i >= 0) && (key < host->keys[i]))
		{
			host->keys[i + 1] = host->keys[i];
			i--;
		}
		host->keys[i + 1] = key;
		host->count++;
		return;
	}

	while ((i >= 0) && (key < host->keys[i]))
	{
		i--;
	}
	i++;
	if (host->children[i]->count == pageSize - 1)
	{
		splitChild(host, i);
		if (key > host->keys[i])
		{
			i++;
		}
	}
	insertNonFull(host->children[i], key);

}

void BTree::splitChild(BTree::Page *host, short const index)
{
	Page *z = new Page();
	Page *y = host->children[index];
	z->isLeaf = y->isLeaf;

	z->count = pivot - 1;
	for (short i = 0; i < pivot - 1; i++)
	{
		z->keys[i] = y->keys[i + pivot];
	}
	if (!y->isLeaf)
	{
		for (short i = 0; i < pivot; i++)
		{
			z->children[i] = y->children[i + pivot];
		}
	}
	y->count = pivot - 1;
	for (short i = host->count; i >= index + 1; i--)
	{
		host->children[i + 1] = host->children[i];
	}
	host->children[index + 1] = z;
	for (short i = host->count - 1; i >= index; i--)
	{
		host->keys[i + 1] = host->keys[i];
	}
	host->keys[index] = y->keys[pivot - 1];
	host->count++;
}

void BTree::deleteSubDetour(BTree::Page *current)
{
	if (current->isLeaf)
		return;

	for (short i = 0; i <= current->count; i++)
	{
		if (current->children[i] == nullptr)
			return;
		if (current->children[i]->isLeaf)
		{
			delete current->children[i];
		}
		else
		{
			deleteSubDetour(current->children[i]);
			delete current->children[i];
		}
		current->children[i] = nullptr;
	}
}
