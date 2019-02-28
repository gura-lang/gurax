//==============================================================================
// MemoryPool
//==============================================================================
#ifndef GURAX_MEMORYPOOL_H
#define GURAX_MEMORYPOOL_H
#include "String.h"

//-----------------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------------
#define Gurax_MemoryPoolAllocator(ownerName) \
static void *operator new(size_t size) { \
	return MemoryPool::Global().Allocate(size, ownerName);	\
} \
static void operator delete(void* p) { \
	MemoryPool::Deallocate(p); \
}

#define Gurax_MemoryPoolAllocator_PUnit() \
static void *operator new(size_t size) { \
	return MemoryPool::Global().chunkPUnit.Allocate();	\
} \
static void operator delete(void* p) { \
	MemoryPool::Deallocate(p);	\
}

#define Gurax_MemoryPoolAllocator_Small(ownerName) \
static void *operator new(size_t size) { \
	return MemoryPool::Global().chunkSmall.Allocate(ownerName);	\
} \
static void operator delete(void* p) { \
	MemoryPool::Deallocate(p);	\
}

#define Gurax_MemoryPoolAllocator_Medium(ownerName) \
static void *operator new(size_t size) { \
	return MemoryPool::Global().chunkMedium.Allocate(ownerName);	\
} \
static void operator delete(void* p) { \
	MemoryPool::Deallocate(p);	\
}

#define Gurax_MemoryPoolAllocator_Large(ownerName) \
static void *operator new(size_t size) { \
	return MemoryPool::Global().chunkLarge.Allocate(ownerName);	\
} \
static void operator delete(void* p) { \
	MemoryPool::Deallocate(p);	\
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
	struct Header {
		union {
			Chunk* pChunk;
			Header* pHeaderVacantNext;
		} u;
		const char* ownerName;
	};
	class ChunkImmortal : public Chunk {
	public:
		struct Pool {
			Pool* pPoolNext;
			char buff[0];
		};
	protected:
		size_t _bytesBlock;
		size_t _bytesFrame;
		size_t _bytesPool;
		size_t _nBlocks;
		size_t _iBlockNext;
		Pool* _pPoolTop;
		Pool* _pPoolCur;
	public:
		ChunkImmortal(size_t bytesBlock, size_t nBlocks, size_t bytesExtra = 0) :
			_bytesBlock(bytesBlock), _bytesFrame(bytesBlock + bytesExtra),
			_bytesPool(sizeof(Pool) + (bytesBlock + bytesExtra) * nBlocks),
			_nBlocks(nBlocks), _iBlockNext(nBlocks), _pPoolTop(nullptr), _pPoolCur(nullptr) {}
		size_t GetBytesBlock() const { return _bytesBlock; }
		size_t CountPools() const;
		size_t GetIndex(const void* p) const;
		void* Allocate();
		virtual void Deallocate(void* p) {}
		String ToString(const StringStyle& ss = StringStyle::Empty) const;
	};
	class ChunkFixed : public ChunkImmortal {
	private:
		Header* _pHeaderVacantHead;
	public:
		ChunkFixed(size_t bytesBlock, size_t nBlocks) :
			ChunkImmortal(bytesBlock, nBlocks, sizeof(Header)), _pHeaderVacantHead(nullptr) {}
		void* Allocate(const char* ownerName);
		virtual void Deallocate(void* p);
		String ToString(const StringStyle& ss = StringStyle::Empty) const;
	};
	class ChunkVariable : public Chunk {
	public:
		inline ChunkVariable() {}
		void* Allocate(size_t bytes, const char* ownerName);
		virtual void Deallocate(void* p);
	};
private:
	static MemoryPool _memoryPoolGlobal;
public:
	ChunkImmortal chunkPUnit;
	ChunkFixed chunkSmall;
	ChunkFixed chunkMedium;
	ChunkFixed chunkLarge;
	ChunkVariable chunkVariable;
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
	static MemoryPool& Global() { return _memoryPoolGlobal; }
	void* Allocate(size_t bytes, const char* ownerName);
	static void Deallocate(void* p);
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
		return static_cast<_Tp*>(MemoryPool::Global().Allocate(num * sizeof(_Tp), "Allocator"));
	}
	void deallocate(_Tp* p, size_t num) {
		MemoryPool::Global().Deallocate(p);
	}
};

}

#endif
