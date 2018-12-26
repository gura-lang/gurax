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

class AList : public std::vector<A*> {
public:
	void Delete(size_t idx) {
		iterator pp = begin() + idx;
		delete *pp;
		erase(pp);
	}
};

Gurax_TesterEntry(MemoryPool)
{
	AList aList;
	g_memoryPoolTest.Print();
	for (int i = 0; i < 100; ++i) {
		aList.push_back(new A());
	}
	g_memoryPoolTest.Print();
	for (int j = 0; j < 10000; ++j) {
		int n = Random::Global().Range(30) + 1;
		for (int i = 0; i < n; ++i) {
			size_t idx = Random::Global().Range(aList.size());
			aList.Delete(idx);
		}
		g_memoryPoolTest.Print();
		for (int i = 0; i < n; ++i) {
			aList.push_back(new A());
		}
		g_memoryPoolTest.Print();
	}
}

}
