#pragma once

namespace Tree
{
//! @class ITree is an interface for tree-like datastructures
//! which have no remove method, because it doesnt necessary
class ITree
{
public:
	ITree(){}
	virtual ~ITree(){}

	virtual void insert(unsigned long long key) = 0;

	//! @return true case the key was found in tree
	virtual bool lookup(unsigned long long const &key) = 0;
	virtual bool isEmpty() const = 0;
};
}
