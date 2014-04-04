#pragma once

namespace Tree
{
class ITree
{
public:
	ITree(){}
	virtual ~ITree(){}

	virtual void insert(unsigned long long key) = 0;
	virtual bool lookup(unsigned long long const &key) = 0;
	virtual bool empty() const = 0;
};
}
