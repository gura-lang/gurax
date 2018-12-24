//==============================================================================
// MemoryPool
//==============================================================================
#ifndef GURAX_MEMORYPOOL_H
#define GURAX_MEMORYPOOL_H
#include "Common.h"

#define Gurax_MemoryPoolAllocator(ownerName) \
static void *operator new(size_t size) { \
	return MemoryPool::Global().Allocate(size, ownerName);	\
} \
static void operator delete(void* p) { \
	MemoryPool::Global().Deallocate(p); \
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
		char buff[0];
	};
	class PoolList : public std::vector<Pool*> {
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
	static MemoryPool _memoryPool;
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
	static MemoryPool& Global() { return _memoryPool; }
	void* Allocate(size_t bytes, const char* ownerName);
	void Deallocate(void* p);
	void Print() const;
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
	Allocator(const Allocator& src) throw() {}
	Allocator& operator=(const Allocator& src) = delete;
	// Move constructor/operator
	Allocator(Allocator&& src) = delete;
	Allocator& operator=(Allocator&& src) noexcept = delete;
	// Destructor
	~Allocator() = default;
public:
	_Tp* allocate(size_t num, std::allocator<void>::const_pointer hint = nullptr) {
		return reinterpret_cast<_Tp*>(MemoryPool::Global().Allocate(num * sizeof(_Tp), "Allocator"));
	}
	void deallocate(_Tp* p, size_t num) {
		MemoryPool::Global().Deallocate(p);
	}
};

}

#endif
