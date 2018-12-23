//==============================================================================
// test-MemoryPool.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

static MemoryPool g_memoryPoolTest;

class A {
public:
	static void *operator new(size_t size) {
		return g_memoryPoolTest.Allocate(size, "A");
	}
	static void operator delete(void* p) {
		g_memoryPoolTest.Deallocate(p);
	}
private:
	int _x;
public:
	A() : _x(3) {}
	int Get() const { return _x; }
};

Gurax_TesterEntry(MemoryPool)
{
	g_memoryPoolTest.Print();
	for (int i = 0; i < 100; ++i) {
		new A();
	}
	g_memoryPoolTest.Print();
}

}
