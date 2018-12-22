//==============================================================================
// MemoryPool
//==============================================================================
#ifndef GURAX_MEMORYPOOL_H
#define GURAX_MEMORYPOOL_H
#include "Common.h"

#define Gurax_MemoryPoolAllocator(ownerName) \
static void *operator new(size_t size) { \
	return MemoryPool::Allocate(size, ownerName); \
} \
static void operator delete(void* p) { \
	MemoryPool::Deallocate(p); \
}

namespace Gurax {

//-----------------------------------------------------------------------------
// MemoryPool
//-----------------------------------------------------------------------------
class GURAX_DLLDECLARE MemoryPool {
public:
	class Chunk {
	public:
		virtual void Deallocate(void* p) = 0;
	};
	struct Pool {
		Pool* pPoolPrev;
		char buff[1];
	};
	struct Header {
		union {
			Chunk* pChunk;
			Header* pHeaderVacantNext;
		} u;
		const char* ownerName;
	};
	class ChunkFixed : public Chunk {
	private:
		size_t _bytesBlock;
		size_t _nBlocks;
		size_t _iBlockNext;
		Pool* _pPool;
		Header* _pHeaderVacantHead;
	public:
		ChunkFixed(size_t bytesBlock, size_t nBlocks) :
			_bytesBlock(bytesBlock), _nBlocks(nBlocks), _iBlockNext(nBlocks),
			_pPool(nullptr), _pHeaderVacantHead(nullptr) {}
		size_t GetBytesBlock() const { return _bytesBlock; }
		void Print() const;
		void* Allocate(const char* ownerName);
		virtual void Deallocate(void* p);
	};
	class ChunkVariable : public Chunk {
	public:
		inline ChunkVariable() {}
		void* Allocate(size_t bytes, const char* ownerName);
		virtual void Deallocate(void* p);
	};
private:
	static MemoryPool _inst;
private:
	ChunkFixed _chunkFixed1;
	ChunkFixed _chunkFixed2;
	ChunkVariable _chunkVariable;
public:
	// Constructor
	MemoryPool();
	// Copy constructor/operator
	MemoryPool(const MemoryPool& src) = delete;
	MemoryPool& operator=(const MemoryPool& src) = delete;
	// Move constructor/operator
	MemoryPool(MemoryPool&& src) = delete;
	MemoryPool& operator=(MemoryPool&& src) noexcept = delete;
	// Destructor
	~MemoryPool() = default;
public:
	static void* Allocate(size_t bytes, const char* ownerName = "") {
		return _inst.DoAllocate(bytes, ownerName);
	}
	static void Deallocate(void* p) { _inst.DoDeallocate(p); }
	static void Print() { _inst.DoPrint(); }
private:
	void* DoAllocate(size_t bytes, const char* ownerName);
	void DoDeallocate(void* p);
	void DoPrint() const;
};

//-----------------------------------------------------------------------------
// Allocator
//-----------------------------------------------------------------------------
template<typename _Tp> class Allocator : public std::allocator<_Tp> {
public:
	template<typename _Tp1> struct rebind {
		typedef Allocator<_Tp1> other;
	};
public:
	// Constructor
	Allocator() {}
	template<typename _Tp1> Allocator(const Allocator<_Tp1>& a) throw() {}
	// Copy constructor/operator
	Allocator(const Allocator& a) throw() {}
	Allocator& operator=(const Allocator& src) = delete;
	// Move constructor/operator
	Allocator(Allocator&& src) = delete;
	Allocator& operator=(Allocator&& src) noexcept = delete;
	// Destructor
	~Allocator() = default;
public:
	_Tp* allocate(size_t num, std::allocator<void>::const_pointer hint = nullptr) {
		return reinterpret_cast<_Tp*>(MemoryPool::Allocate(num * sizeof(_Tp), "Allocator"));
	}
	void deallocate(_Tp* p, size_t num) {
		MemoryPool::Deallocate(p);
	}
};

}

#endif
