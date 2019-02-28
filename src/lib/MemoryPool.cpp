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
	chunkPUnit(64, 20), chunkSmall(64, 20), chunkMedium(128, 20), chunkLarge(192, 20), chunkVariable()
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
void* MemoryPool::ChunkImmortal::Allocate()
{
	char* pAllocated = nullptr;
	//::printf("_iBlockNext=%zu, _nBlocks=%zu\n", _iBlockNext, _nBlocks);
	if (_iBlockNext >= _nBlocks) {
		_iBlockNext = 0;
		Pool* pPool = reinterpret_cast<Pool*>(::malloc(sizeof(Pool) + _bytesBlock * _nBlocks));
		pPool->pPoolPrev = _pPool;
		_pPool = pPool;
	}
	pAllocated = _pPool->buff + _bytesBlock * _iBlockNext;
	_iBlockNext++;
	return pAllocated;
}

String MemoryPool::ChunkImmortal::ToString(const StringStyle& ss) const
{
	String str;
	size_t nPools = 0;
	for (Pool* pPool = _pPool; pPool; pPool = pPool->pPoolPrev) nPools++;
	char buff[256];
	::sprintf(buff, "[ChunkImmortal:%ldbytes/block,%zupools]", _bytesBlock, nPools);
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
		size_t bytesFrame = sizeof(Header) + _bytesBlock;
		//::printf("_iBlockNext=%zu, _nBlocks=%zu\n", _iBlockNext, _nBlocks);
		if (_iBlockNext >= _nBlocks) {
			_iBlockNext = 0;
			Pool* pPool = reinterpret_cast<Pool*>(::malloc(sizeof(Pool) + bytesFrame * _nBlocks));
			pPool->pPoolPrev = _pPool;
			_pPool = pPool;
		}
		pAllocated = _pPool->buff + bytesFrame * _iBlockNext;
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
	pHeader->u.pHeaderVacantNext = _pHeaderVacantHead;
	pHeader->ownerName = nullptr;
	_pHeaderVacantHead = pHeader;
}

String MemoryPool::ChunkFixed::ToString(const StringStyle& ss) const
{
	String str;
	PoolList poolList;
	for (Pool* pPool = _pPool; pPool; pPool = pPool->pPoolPrev) poolList.push_back(pPool);
	do {
		char buff[256];
		::sprintf(buff, "[ChunkFixed:%ldbytes/block,%zupools]", _bytesBlock, poolList.size());
		str += buff;
	} while (0);
	if (!ss.IsDigest()) {
		size_t bytesFrame = sizeof(Header) + _bytesBlock;
		str += "\n";
		for (auto ppPool = poolList.rbegin(); ppPool != poolList.rend(); ++ppPool) {
			Pool *pPool = *ppPool;
			size_t nBlocks = (pPool == _pPool)? _iBlockNext : _nBlocks;
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
