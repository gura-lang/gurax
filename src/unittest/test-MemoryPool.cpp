//==============================================================================
// test-MemoryPool.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

static MemoryPool::ChunkFixed g_chunkTest(64, 20);

class A {
public:
	static void *operator new(size_t size) {
		return g_chunkTest.Allocate("A");
	}
	static void operator delete(void* p) {
		MemoryPool::Deallocate(p);
	}
private:
	int _x;
public:
	A() : _x(3) {}
	int Get() const { return _x; }
};

class AList : public ListBase<A*> {
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
	std::cout << g_chunkTest.ToString() << std::endl;
	for (int i = 0; i < 100; ++i) {
		aList.push_back(new A());
	}
	std::cout << g_chunkTest.ToString() << std::endl;
	for (int j = 0; j < 10000; ++j) {
		int n = Random::Global().GenInt(30) + 1;
		for (int i = 0; i < n; ++i) {
			size_t idx = Random::Global().GenInt(aList.size());
			aList.Delete(idx);
		}
		std::cout << g_chunkTest.ToString() << std::endl;
		for (int i = 0; i < n; ++i) {
			aList.push_back(new A());
		}
		std::cout << g_chunkTest.ToString() << std::endl;
	}
}

}
