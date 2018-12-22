//==============================================================================
// test-MemoryPool.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

class A {
public:
	Gurax_MemoryPoolAllocator("A");
private:
	int _x;
public:
	A() : _x(3) {}
	int Get() const { return _x; }
};

Gurax_TesterEntry(MemoryPool)
{
	MemoryPool::Print();
	//for (int i = 0; i < 100; ++i) {
	//	::printf("%p\n", MemoryPool::Allocate(16, "hoge"));
	//}
	MemoryPool::Print();
}

}
