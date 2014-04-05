#include "splayTree.h"

using namespace Tree;

SplayTree::SplayTree()
	: mRoot(nullptr)
	, mSize(0)
{}

SplayTree::~SplayTree()
{
	deleteSubDetour(mRoot);
}

void SplayTree::insert(unsigned long long key)
{
	insertConst(key);
}

void SplayTree::insertConst(unsigned long long const &key)
{
	Node *curr = mRoot;
	Node *p = nullptr;

	while(curr != nullptr)
	{
		p = curr;
		if (key > curr->key)
		{
			curr = curr->right;
		}
		else if (key < curr->key)
		{
			curr = curr->left;
		}
		else
		{
			splay(curr);
			return;
		}
	}

	curr = new Node(key, p);

	if (p == nullptr)
	{
		mRoot = curr;
	}
	else if (p->key < curr->key)
	{
		p->right = curr;
	}
	else
	{
		p->left = curr;
	}

	splay(curr);
	mSize++;
}

SplayTree::Node* SplayTree::find(unsigned long long const &key)
{
	Node *curr = mRoot;
//	Node *prev = nullptr;

	while(curr != nullptr)
	{
//		prev = curr;
		if (curr->key < key)
		{
			curr = curr->right;
		}
		else if (key < curr->key)
		{
			curr = curr->left;
		}
		else
		{
//			splay(curr);
			return curr;
		}
	}
//	if (prev != nullptr)
//	{
//		splay(prev);
//	}
	return nullptr;
}

bool SplayTree::lookup(const unsigned long long &key)
{
	Node *found = find(key);
	return (found != nullptr && found->key == key);
}

const unsigned long long& SplayTree::minimum()
{
	return subtreeMinimum(mRoot)->key;
}

const unsigned long long& SplayTree::maximum()
{
	return subtreeMaximum(mRoot)->key;
}

bool SplayTree::empty() const
{
	return mRoot == nullptr;
}

unsigned long SplayTree::size() const
{
	return mSize;
}

void SplayTree::rotateLeft(SplayTree::Node *x)
{
	Node *y = x->right;
	x->right = y->left;
	if (y->left)
	{
		y->left->parent = x;
	}

	y->parent = x->parent;

	if (x->parent == nullptr)
	{
		mRoot = y;
	}
	else if (x == x->parent->left)
	{
		x->parent->left = y;
	}
	else
	{
		x->parent->right = y;
	}

	y->left = x;
	x->parent = y;
}

void SplayTree::rotateRight(SplayTree::Node *x)
{
	Node *y = x->left;
	x->left = y->right;
	if (y->right)
	{
		y->right->parent = x;
	}

	y->parent = x->parent;

	if (x->parent == nullptr)
	{
		mRoot = y;
	}
	else if (x == x->parent->left)
	{
		x->parent->left = y;
	}
	else
	{
		x->parent->right = y;
	}

	y->right = x;
	x->parent = y;
}

void SplayTree::zig(SplayTree::Node *x)
{
	if (x->parent->left == x)
	{
		rotateRight(x->parent);
	}
	else
	{
		rotateLeft(x->parent);
	}
	mRoot = x;
}

void SplayTree::deleteSubDetour(SplayTree::Node *current)
{
	if (current == nullptr)
	{
		return;
	}

	deleteSubDetour(current->left);
	deleteSubDetour(current->right);
	delete current;
}

void SplayTree::splay(SplayTree::Node *x)
{
	while(x->parent != nullptr)
	{
		if (x->parent->parent == nullptr)
		{
			zig(x);
			return;
		}
		// zig-zig
		if (x->parent->left == x && x->parent->parent->left == x->parent)
		{
			rotateRight(x->parent->parent);
			rotateRight(x->parent);
			return;
		}
		if (x->parent->right == x && x->parent->parent->right == x->parent)
		{
			rotateLeft(x->parent->parent);
			rotateLeft(x->parent);
			return;
		} // zig-zig

		// zig-zag
		if (x->parent->left == x && x->parent->parent->right == x->parent)
		{
			rotateRight(x->parent);
			rotateLeft(x->parent);
		}
		else
		{
			rotateLeft(x->parent);
			rotateRight(x->parent);
		} // zig-zag
	}
}

void SplayTree::replace(SplayTree::Node *u, SplayTree::Node *v)
{
	if (u->parent == nullptr)
	{
		mRoot = v;
	}
	else if (u == u->parent->left)
	{
		u->parent->left = v;
	}
	else
	{
		u->parent->right = v;
	}

	if (v != nullptr)
	{
		v->parent = u->parent;
	}
}

SplayTree::Node *SplayTree::subtreeMinimum(SplayTree::Node *u)
{
	while(u->left)
	{
		u = u->left;
	}
	return u;
}

SplayTree::Node *SplayTree::subtreeMaximum(SplayTree::Node *u)
{
	while(u->right)
	{
		u = u->right;
	}
	return u;
}

