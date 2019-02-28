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
	chunkPUnit(64, 65536), chunkSmall(64, 65536),
	chunkMedium(128, 65536), chunkLarge(192, 65536), chunkVariable()
{
}

void* MemoryPool::Allocate(size_t bytes, const char* ownerName)
{
	//::printf("MemoryPool::DoAllocate(%ldbytes, \"%s\")\n", bytes, ownerName);
	if (bytes <= chunkSmall.GetBytesBlock()) {
		return chunkSmall.Allocate(ownerName);
	} else if (bytes <= chunkMedium.GetBytesBlock()) {
		return chunkMedium.Allocate(ownerName);
	} else if (bytes <= chunkLarge.GetBytesBlock()) {
		return chunkLarge.Allocate(ownerName);
	} else {
		return chunkVariable.Allocate(bytes, ownerName);
	}
}

void MemoryPool::Deallocate(void* p)
{
	char* pHeaderRaw = reinterpret_cast<char*>(p) - sizeof(Header);
	Header* pHeader = reinterpret_cast<Header*>(pHeaderRaw);
	pHeader->u.pChunk->Deallocate(p);
}

//-----------------------------------------------------------------------------
// MemoryPool::ChunkImmortal
//-----------------------------------------------------------------------------
size_t MemoryPool::ChunkImmortal::CountPools() const
{
	size_t nPools = 0;
	for (Pool* pPool = _pPoolTop; pPool; pPool = pPool->pPoolNext) nPools++;
	return nPools;
}

size_t MemoryPool::ChunkImmortal::GetIndex(const void* p) const
{
	const char* p1 = reinterpret_cast<const char*>(p);
	size_t idxBase = 0;
	for (const Pool* pPool = _pPoolTop; pPool; pPool = pPool->pPoolNext, idxBase += _nBlocks) {
		const char *p2 = reinterpret_cast<const char*>(pPool);
		if (p1 >= p2 && p1 - p2 < _bytesPool) {
			return (p1 - p2 - sizeof(Pool)) / _bytesFrame + idxBase;
		}
	}
	return 0;
}

void* MemoryPool::ChunkImmortal::Allocate()
{
	if (_iBlockNext >= _nBlocks) {
		Pool* pPool = reinterpret_cast<Pool*>(::malloc(_bytesPool));
		if (_pPoolCur) {
			_pPoolCur->pPoolNext = pPool;
		} else {
			_pPoolTop = pPool;
		}
		_iBlockNext = 0;
		_pPoolCur = pPool;
	}
	char* pAllocated = _pPoolCur->buff + _bytesFrame * _iBlockNext;
	_iBlockNext++;
	return pAllocated;
}

String MemoryPool::ChunkImmortal::ToString(const StringStyle& ss) const
{
	String str;
	char buff[256];
	::sprintf(buff, "[ChunkImmortal:%ldbytes/block,%zupools]", _bytesBlock, CountPools());
	str += buff;
	return str;
}

//-----------------------------------------------------------------------------
// MemoryPool::ChunkFixed
//-----------------------------------------------------------------------------
void* MemoryPool::ChunkFixed::Allocate(const char* ownerName)
{
	char* pAllocated = nullptr;
	if (_pHeaderVacantHead) {
		pAllocated = reinterpret_cast<char*>(_pHeaderVacantHead);
		_pHeaderVacantHead = _pHeaderVacantHead->u.pHeaderVacantNext;
	} else {
		pAllocated = reinterpret_cast<char*>(ChunkImmortal::Allocate());
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
	pHeader->u.pHeaderVacantNext = _pHeaderVacantHead;
	pHeader->ownerName = nullptr;
	_pHeaderVacantHead = pHeader;
}

String MemoryPool::ChunkFixed::ToString(const StringStyle& ss) const
{
	String str;
	do {
		char buff[256];
		::sprintf(buff, "[ChunkFixed:%ldbytes/block,%zupools]", _bytesBlock, CountPools());
		str += buff;
	} while (0);
	if (!ss.IsDigest()) {
		size_t bytesFrame = sizeof(Header) + _bytesBlock;
		str += "\n";
		for (Pool* pPool = _pPoolTop; pPool; pPool = pPool->pPoolNext) {
			size_t nBlocks = (pPool == _pPoolCur)? _iBlockNext : _nBlocks;
			const char* pAllocated = pPool->buff;
			for (size_t iBlock = 0; iBlock < nBlocks; ++iBlock, pAllocated += bytesFrame) {
				const Header* pHeader = reinterpret_cast<const Header*>(pAllocated);
				str += pHeader->ownerName? '*' : '.';
			}
			str += "\n";
		}
	}
	return str;
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
