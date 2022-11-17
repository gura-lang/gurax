//==============================================================================
// MemoryPool
//==============================================================================
#ifndef GURAX_MEMORYPOOL_H
#define GURAX_MEMORYPOOL_H
#include "String.h"
#include "StringStyle.h"


//-----------------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------------
#define Gurax_MemoryPoolAllocator(ownerName) \
static void *operator new(size_t bytes) { \
	return MemoryPool::Global().Allocate(bytes, ownerName); \
} \
static void operator delete(void* p) { \
	MemoryPool::Deallocate(p); \
}

#define Gurax_MemoryPoolAllocator_PUnit() \
static void *operator new(size_t bytes) { \
	return MemoryPool::Global().GetChunkPUnit().Allocate(bytes); \
} \
static void operator delete(void* p) {}

#define Gurax_MemoryPoolAllocator_Small(ownerName) \
static void *operator new(size_t bytes) { \
	return MemoryPool::Global().GetChunkSmall().Allocate(ownerName); \
} \
static void operator delete(void* p) { \
	MemoryPool::Deallocate(p); \
}

#define Gurax_MemoryPoolAllocator_Medium(ownerName) \
static void *operator new(size_t bytes) { \
	return MemoryPool::Global().GetChunkMedium().Allocate(ownerName); \
} \
static void operator delete(void* p) { \
	MemoryPool::Deallocate(p); \
}

#define Gurax_MemoryPoolAllocator_Large(ownerName) \
static void *operator new(size_t bytes) { \
	return MemoryPool::Global().GetChunkLarge().Allocate(ownerName); \
} \
static void operator delete(void* p) { \
	MemoryPool::Deallocate(p); \
}

namespace Gurax {

class PUnit;

//-----------------------------------------------------------------------------
// MemoryPool
//-----------------------------------------------------------------------------
class GURAX_DLLDECLARE MemoryPool {
public:
	class Chunk;
	struct Header {
		union {
			Chunk* pChunk;
			Header* pHeaderVacantNext;
		} u;
		const char* ownerName;
	};
	class GURAX_DLLDECLARE Chunk {
	public:
		// Constructor
		Chunk() = default;
		// Copy constructor/operator
		Chunk(const Chunk& src) = delete;
		Chunk& operator=(const Chunk& src) = delete;
		// Move constructor/operator
		Chunk(Chunk&& src) = delete;
		Chunk& operator=(Chunk&& src) noexcept = delete;
		// Destructor
		~Chunk() = default;
	public:
		virtual void Deallocate(void* p) = 0;
	};
	class GURAX_DLLDECLARE ChunkPUnit : public Chunk {
	public:
		struct Pool {
			size_t offsetNext;
			Pool* pPoolNext;
			size_t nPUnits;
			char buff[0];
			static Pool* Create(size_t bytesPerPool);
			bool IsWithin(const PUnit* pPUnit) const {
				const char *p = reinterpret_cast<const char *>(pPUnit);
				return buff <= p && p - buff < offsetNext;
			}
		};
	protected:
		size_t _bytesPerPool;
		size_t _bytesMargin;
		Pool* _pPoolTop;
		Pool* _pPoolCur;
		void* _pReserved;
	public:
		ChunkPUnit(size_t bytesPerPool, size_t bytesMargin);
		size_t CountPools() const;
		void Reserve(size_t bytes);
		void* Allocate(size_t bytes);
		void* AllocateGhost();
		UInt32 CalcSeqId(const PUnit* pPUnit) const;
		virtual void Deallocate(void* p) {}
		void* PeekPointer() { return _pPoolCur->buff + _pPoolCur->offsetNext; }
		const void* PeekPointer() const { return _pPoolCur->buff + _pPoolCur->offsetNext; }
		const PUnit* PeekPUnitCont() const {
			return reinterpret_cast<const PUnit*>(PeekPointer());
		}
		const PUnit* GetPUnitFirst() const {
			return reinterpret_cast<const PUnit*>(_pPoolTop->buff);
		}
		String ToString(const StringStyle& ss = StringStyle::Empty) const;
	private:
		void* DoAllocate(size_t bytes);
	};
	class GURAX_DLLDECLARE ChunkFixed : public Chunk {
	public:
		struct Pool {
			Pool* pPoolNext;
			char buff[0];
			static Pool* Create(size_t bytesPerPool);
		};
	private:
		size_t _bytesBlock;
		size_t _bytesFrame;
		size_t _bytesPerPool;
		size_t _nBlocksPerPool;
		size_t _iBlockNext;
		Pool* _pPoolTop;
		Pool* _pPoolCur;
		Header* _pHeaderVacantFirst;
	public:
		ChunkFixed(size_t bytesBlock, size_t nBlocksPerPool);
	public:
		size_t GetBytesBlock() const { return _bytesBlock; }
		size_t CountPools() const;
		void* Allocate(const char* ownerName);
		virtual void Deallocate(void* p);
		size_t CountBlocksAllocated() const;
		String ToString(const StringStyle& ss = StringStyle::Empty) const;
	};
	class GURAX_DLLDECLARE ChunkVariable : public Chunk {
	public:
		inline ChunkVariable() {}
		void* Allocate(size_t bytes, const char* ownerName);
		virtual void Deallocate(void* p);
	};
private:
	static MemoryPool _memoryPoolGlobal;
public:
	ChunkPUnit* _pChunkPUnit;
	ChunkPUnit _chunkPUnitCode;
	ChunkPUnit _chunkPUnitREPL;
	ChunkFixed _chunkSmall;
	ChunkFixed _chunkMedium;
	ChunkFixed _chunkLarge;
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
	static MemoryPool& Global() { return _memoryPoolGlobal; }
	void* Allocate(size_t bytes, const char* ownerName);
	static void Deallocate(void* p);
	void SwitchChunkPUnit(bool replFlag) {
		_pChunkPUnit = replFlag? &_chunkPUnitREPL : &_chunkPUnitCode;
	}
	void SetChunkPUnit(ChunkPUnit* pChunkPUnit) { _pChunkPUnit = pChunkPUnit; }
	ChunkPUnit& GetChunkPUnit() { return *_pChunkPUnit; }
	ChunkFixed& GetChunkSmall() { return _chunkSmall; }
	ChunkFixed& GetChunkMedium() { return _chunkMedium; }
	ChunkFixed& GetChunkLarge() { return _chunkLarge; }
	ChunkVariable& GetChunkVariable() { return _chunkVariable; }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const MemoryPool& memoryPool) const { return this == &memoryPool; }
	bool IsEqualTo(const MemoryPool& memoryPool) const { return IsIdentical(memoryPool); }
	bool IsLessThan(const MemoryPool& memoryPool) const { return this < &memoryPool; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
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
