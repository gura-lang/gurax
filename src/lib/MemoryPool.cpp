//=============================================================================
// MemoryPool
//=============================================================================
#include "stdafx.h"

namespace Gurax {

//-----------------------------------------------------------------------------
// MemoryPool
//-----------------------------------------------------------------------------
MemoryPool MemoryPool::_memoryPoolGlobal;

MemoryPool::MemoryPool() :
	_chunkPUnitCode(64 * 65536, 64 * 2), _chunkPUnitREPL(64 * 256, 64 * 2),
	_chunkSmall(64, 65536), _chunkMedium(128, 65536), _chunkLarge(192, 65536),
	_chunkVariable()
{
	SwitchChunkPUnit(false);
}

void* MemoryPool::Allocate(size_t bytes, const char* ownerName)
{
	//Stream::COut->Printf("MemoryPool::DoAllocate(%ldbytes, \"%s\")\n", bytes, ownerName);
	if (bytes <= GetChunkSmall().GetBytesBlock()) {
		return GetChunkSmall().Allocate(ownerName);
	} else if (bytes <= GetChunkMedium().GetBytesBlock()) {
		return GetChunkMedium().Allocate(ownerName);
	} else if (bytes <= GetChunkLarge().GetBytesBlock()) {
		return GetChunkLarge().Allocate(ownerName);
	} else {
		return GetChunkVariable().Allocate(bytes, ownerName);
	}
}

void MemoryPool::Deallocate(void* p)
{
	char* pHeaderRaw = reinterpret_cast<char*>(p) - sizeof(Header);
	Header* pHeader = reinterpret_cast<Header*>(pHeaderRaw);
	pHeader->u.pChunk->Deallocate(p);
}

String MemoryPool::ToString(const StringStyle& ss) const
{
	return "MemoryPool";
}

//-----------------------------------------------------------------------------
// MemoryPool::Chunk
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// MemoryPool::ChunkPUnit
//-----------------------------------------------------------------------------
MemoryPool::ChunkPUnit::ChunkPUnit(size_t bytesPerPool, size_t bytesMargin) :
	_bytesPerPool(bytesPerPool), _bytesMargin(bytesMargin),
	_pPoolTop(Pool::Create(_bytesPerPool)), _pPoolCur(_pPoolTop), _pReserved(nullptr)
{}

size_t MemoryPool::ChunkPUnit::CountPools() const
{
	size_t nPools = 0;
	for (Pool* pPool = _pPoolTop; pPool; pPool = pPool->pPoolNext) nPools++;
	return nPools;
}

void MemoryPool::ChunkPUnit::Reserve(size_t bytes)
{
	_pReserved = DoAllocate(bytes);
}

void* MemoryPool::ChunkPUnit::Allocate(size_t bytes)
{
	if (_pReserved) {
		void* pAllocated = _pReserved;
		_pReserved = nullptr;
		return pAllocated;
	}
	return DoAllocate(bytes);
}

void* MemoryPool::ChunkPUnit::DoAllocate(size_t bytes)
{
	void* pAllocated = PeekPointer();
	_pPoolCur->nPUnits++;
	_pPoolCur->offsetNext += bytes;
	if (_pPoolCur->offsetNext + _bytesMargin > _bytesPerPool) {
		auto pPUnitBridge = new PUnit_Bridge();
		Pool* pPool = Pool::Create(_bytesPerPool);
		_pPoolCur->pPoolNext = pPool;
		_pPoolCur = pPool;
		pPUnitBridge->SetPUnitCont(reinterpret_cast<const PUnit*>(PeekPointer()));
	}
	return pAllocated;
}

// Allocator that is exclusively used for PUnit_REPLEnd and PUnit_Bridge
void* MemoryPool::ChunkPUnit::AllocateGhost()
{
	return PeekPointer();
}

//---------
// Improvement of performance is necessary.
//---------
UInt32 MemoryPool::ChunkPUnit::CalcSeqId(const PUnit* pPUnit) const
{
	static const PUnit* pPUnitHint = nullptr;
	static UInt32 seqIdHint = 0;
	UInt32 seqId = 0;
	for (Pool* pPool = _pPoolTop; pPool; seqId += pPool->nPUnits, pPool = pPool->pPoolNext) {
		if (!pPool->IsWithin(pPUnit)) continue;
		const PUnit* pPUnitSeek = reinterpret_cast<const PUnit*>(pPool->buff);
		if (pPUnitSeek <= pPUnitHint && pPUnitHint <= pPUnit) {
			pPUnitSeek = pPUnitHint;
			seqId = seqIdHint;
		}
		for ( ; pPUnitSeek <= pPUnit; pPUnitSeek = pPUnitSeek->GetPUnitAdjacent(), seqId++) {
			if (pPUnitSeek == pPUnit) {
				pPUnitHint = pPUnitSeek;
				seqIdHint = seqId;
				return seqId;
			}
		}
		return 0;
	}
	return 0;
}

String MemoryPool::ChunkPUnit::ToString(const StringStyle& ss) const
{
	String str;
	str.Format("[ChunkPUnit:%ldbytes/pool,%zupools]", _bytesPerPool, CountPools());
	return str;
}

//-----------------------------------------------------------------------------
// MemoryPool::ChunkPUnit::Pool
//-----------------------------------------------------------------------------
MemoryPool::ChunkPUnit::Pool* MemoryPool::ChunkPUnit::Pool::Create(size_t bytesPerPool)
{
	Pool* pPool = reinterpret_cast<Pool*>(::malloc(sizeof(Pool) + bytesPerPool));
	pPool->offsetNext = 0;
	pPool->pPoolNext = nullptr;
	pPool->nPUnits = 0;
	return pPool;
}

//-----------------------------------------------------------------------------
// MemoryPool::ChunkFixed
//-----------------------------------------------------------------------------
MemoryPool::ChunkFixed::ChunkFixed(size_t bytesBlock, size_t nBlocksPerPool) :
	_bytesBlock(bytesBlock), _bytesFrame(sizeof(Header) + bytesBlock),
	_bytesPerPool(_bytesFrame * nBlocksPerPool),
	_nBlocksPerPool(nBlocksPerPool), _iBlockNext(0),
	_pPoolTop(Pool::Create(_bytesPerPool)), _pPoolCur(_pPoolTop),
	_pHeaderVacantFirst(nullptr)
{}

size_t MemoryPool::ChunkFixed::CountPools() const
{
	size_t nPools = 0;
	for (Pool* pPool = _pPoolTop; pPool; pPool = pPool->pPoolNext) nPools++;
	return nPools;
}

void* MemoryPool::ChunkFixed::Allocate(const char* ownerName)
{
	char* pAllocated = nullptr;
	if (_pHeaderVacantFirst) {
		pAllocated = reinterpret_cast<char*>(_pHeaderVacantFirst);
		_pHeaderVacantFirst = _pHeaderVacantFirst->u.pHeaderVacantNext;
	} else {
		if (_iBlockNext >= _nBlocksPerPool) {
			Pool* pPool = Pool::Create(_bytesPerPool);
			_pPoolCur->pPoolNext = pPool;
			_iBlockNext = 0;
			_pPoolCur = pPool;
		}
		pAllocated = _pPoolCur->buff + _bytesFrame * _iBlockNext;
		_iBlockNext++;
	}
	Header* pHeader = reinterpret_cast<Header*>(pAllocated);
	pHeader->u.pChunk = this;
	pHeader->ownerName = ownerName;
	return pAllocated + sizeof(Header);
}

void MemoryPool::ChunkFixed::Deallocate(void* p)
{
	char* pAllocated = reinterpret_cast<char*>(p) - sizeof(Header);
	Header* pHeader = reinterpret_cast<Header*>(pAllocated);
	pHeader->u.pHeaderVacantNext = _pHeaderVacantFirst;
	pHeader->ownerName = nullptr;
	_pHeaderVacantFirst = pHeader;
}

size_t MemoryPool::ChunkFixed::CountBlocksAllocated() const
{
	size_t nBlocksAllocated = 0;
	for (Pool* pPool = _pPoolTop; pPool; pPool = pPool->pPoolNext) {
		size_t nBlocks = (pPool == _pPoolCur)? _iBlockNext : _nBlocksPerPool;
		const char* pAllocated = pPool->buff;
		for (size_t iBlock = 0; iBlock < nBlocks; ++iBlock, pAllocated += _bytesFrame) {
			const Header* pHeader = reinterpret_cast<const Header*>(pAllocated);
			if (pHeader->ownerName) nBlocksAllocated++;
		}
	}
	return nBlocksAllocated;
}

String MemoryPool::ChunkFixed::ToString(const StringStyle& ss) const
{
	String str;
	str.Format("[ChunkFixed:%ldbytes/block,%zupools]", _bytesBlock, CountPools());
#if 0
	str += "\n";
	for (Pool* pPool = _pPoolTop; pPool; pPool = pPool->pPoolNext) {
		size_t nBlocks = (pPool == _pPoolCur)? _iBlockNext : _nBlocksPerPool;
		const char* pAllocated = pPool->buff;
		for (size_t iBlock = 0; iBlock < nBlocks; ++iBlock, pAllocated += _bytesFrame) {
			const Header* pHeader = reinterpret_cast<const Header*>(pAllocated);
			str += pHeader->ownerName? '*' : '.';
		}
		str += "\n";
	}
#endif
	return str;
}

//-----------------------------------------------------------------------------
// MemoryPool::ChunkFixed::Pool
//-----------------------------------------------------------------------------
MemoryPool::ChunkFixed::Pool* MemoryPool::ChunkFixed::Pool::Create(size_t bytesPerPool)
{
	Pool* pPool = reinterpret_cast<Pool*>(::malloc(sizeof(Pool) + bytesPerPool));
	pPool->pPoolNext = nullptr;
	return pPool;
}

//-----------------------------------------------------------------------------
// MemoryPool::ChunkVariable
//-----------------------------------------------------------------------------
void* MemoryPool::ChunkVariable::Allocate(size_t bytes, const char* ownerName)
{
	size_t bytesFrame = sizeof(Header) + bytes;
	char* pAllocated = reinterpret_cast<char*>(::malloc(bytesFrame));
	if (!pAllocated) return nullptr;
	Header* pHeader = reinterpret_cast<Header*>(pAllocated);
	pHeader->u.pChunk = this;
	pHeader->ownerName = ownerName;
	return pAllocated + sizeof(Header);
}

void MemoryPool::ChunkVariable::Deallocate(void* p)
{
	char* pAllocated = reinterpret_cast<char*>(p) - sizeof(Header);
	::free(pAllocated);
}

}
