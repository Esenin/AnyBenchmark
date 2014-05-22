#include "vEBLayoutBinTree.h"

using namespace Tree;

Tree::VEBLayoutBinTree::VEBLayoutBinTree()
	: mRoot(nullptr)
{
}

VEBLayoutBinTree::~VEBLayoutBinTree()
{
	delete mRoot;
}

void VEBLayoutBinTree::insert(Type const &key)
{
	mData.push_back(key);
}

bool VEBLayoutBinTree::lookup(Type const &key) const
{
	return findIn(mRoot, key);
}

bool VEBLayoutBinTree::isEmpty() const
{
	return mData.empty();
}

void VEBLayoutBinTree::buildTree()
{
	if (isEmpty())
	{
		return;
	}
	std::sort(mData.begin(), mData.end());
	makeSubTree(mRoot, 0, mData.size() - 1);
}

bool VEBLayoutBinTree::isBuildable() const
{
	return true;
}

void VEBLayoutBinTree::makeSubTree(VEBLayoutBinTree::Page* &locRoot, int const leftBound, int const rightBound)
{
	locRoot = new Page();
	if (mRoot == nullptr)
	{
		mRoot = locRoot;
	}
	int middle = (leftBound + rightBound) / 2;
	locRoot->key = mData.at(middle);

	// left half
	if (middle - leftBound > 0)
	{
		int leftPivot = (leftBound + middle) / 2;
		locRoot->leftKey = mData.at(leftPivot);
		locRoot->hasLeftChild = true;

		if (leftPivot - leftBound > 0)
		{
			makeSubTree(locRoot->children[leftLeftChild], leftBound, leftPivot - 1);
		}


		if (middle - leftPivot - 1 > 0)
		{
			makeSubTree(locRoot->children[leftRightChild], leftPivot + 1, middle - 1);
		}
	}

	// right
	if (rightBound - middle > 0)
	{
		int rightPivot = (rightBound + middle) / 2;
		if (rightPivot == middle)
		{
			rightPivot++;
		}
		locRoot->rightKey = mData.at(rightPivot);
		locRoot->hasRightChild = true;

		if (rightBound - rightPivot > 0)
		{
			makeSubTree(locRoot->children[rightRightChild], rightPivot + 1, rightBound);
		}


		if (rightPivot - middle - 1 > 0)
		{
			makeSubTree(locRoot->children[rightLeftChild], middle + 1, rightPivot - 1);
		}
	}
}

bool VEBLayoutBinTree::findIn(VEBLayoutBinTree::Page *subTree, Type const &key) const
{
	if (subTree == nullptr)
	{
		return false;
	}

	if (key < subTree->key)
	{
		if (!subTree->hasLeftChild)
		{
			return false;
		}
		if (key == subTree->leftKey)
		{
			return true;
		}
		ChildIndex index = (key < subTree->leftKey)? leftLeftChild : leftRightChild;
		return findIn(subTree->children[index], key);
	}

	if (key > subTree->key)
	{
		if (!subTree->hasRightChild)
		{
			return false;
		}
		if (key == subTree->rightKey)
		{
			return true;
		}
		ChildIndex index = (key < subTree->rightKey)? rightLeftChild : rightRightChild;
		return findIn(subTree->children[index], key);
	}

	return true;
}
