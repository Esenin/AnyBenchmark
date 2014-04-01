#pragma once

//! @class TestObject is an interface for objects taking part in benchmarking
class TestObject
{
public:
	TestObject() {}
	virtual ~TestObject() {}

	virtual void setParam(int const &param) = 0;
	virtual void prepare() = 0;
	virtual void run() = 0;
	virtual void clear() = 0;
};
