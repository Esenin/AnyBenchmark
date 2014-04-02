#pragma once

#include "../../src/testObject.h"

class ITree : public TestObject
{
public:
	ITree();
	virtual ~ITree();

	virtual void insert(unsigned long long key) = 0;
	virtual bool lookup(unsigned long long const &key) = 0;
	virtual bool empty() const = 0;

	virtual void setParam(int const &param)
	{
		int n = param;
		n++;
	}
	virtual void prepare(){}
	virtual void run(){}
	virtual void clear(){}
};
