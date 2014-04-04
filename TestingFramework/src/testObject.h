#pragma once

//! @class TestObject is an interface for objects taking part in benchmark
class TestObject
{
public:
	class Error{};

	virtual ~TestObject() {}

	//! set main param of test
	virtual void setParam(int const &param) = 0;

	//! called each time before "run", won't be considered by timer
	virtual void prepare() = 0;

	//! actual test content must be here
	virtual void run() throw(Error) = 0;

	//! clears after run-test
	virtual void clear() = 0;
};
