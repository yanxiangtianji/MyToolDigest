#pragma once
#include <string>

struct B{
	virtual int fun() { return 0; }
};

struct D1 : public B{
	virtual int fun() { return 1; }
};

struct D2 : public B{
	virtual int fun() { return 2; }
};

