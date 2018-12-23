//=============================================================================
// MemoryPool
//=============================================================================
#include "stdafx.h"

namespace Gurax {

//-----------------------------------------------------------------------------
// MemoryPool
//-----------------------------------------------------------------------------
MemoryPool MemoryPool::_memoryPool;

MemoryPool::MemoryPool() :
	_chunkFixed1(64, 20), _chunkFixed2(192, 20), _chunkVariable()
{
}

void* MemoryPool::Allocate(size_t bytes, const char* ownerName)
{
	//::printf("MemoryPool::DoAllocate(%ldbytes, \"%s\")\n", bytes, ownerName);
	if (bytes <= _chunkFixed1.GetBytesBlock()) {
		return _chunkFixed1.Allocate(ownerName);
	} else if (bytes <= _chunkFixed2.GetBytesBlock()) {
		return _chunkFixed2.Allocate(ownerName);
	} else {
		return _chunkVariable.Allocate(bytes, ownerName);
	}
}

void MemoryPool::Deallocate(void* p)
{
	char* pHeaderRaw = reinterpret_cast<char*>(p) - sizeof(Header);
	Header* pHeader = reinterpret_cast<Header*>(pHeaderRaw);
	pHeader->u.pChunk->Deallocate(p);
}

void MemoryPool::Print() const
{
	_chunkFixed1.Print();
	//_chunkFixed2.Print();
}

//-----------------------------------------------------------------------------
// MemoryPool::ChunkFixed
//-----------------------------------------------------------------------------
void* MemoryPool::ChunkFixed::Allocate(const char* ownerName)
{
	char* pHeaderRaw = nullptr;
	if (_pHeaderVacantHead) {
		pHeaderRaw = reinterpret_cast<char*>(_pHeaderVacantHead);
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
		pHeaderRaw = _pPool->buff + bytesFrame * _iBlockNext;
		_iBlockNext++;
	}
	Header* pHeader = reinterpret_cast<Header*>(pHeaderRaw);
	pHeader->u.pChunk = this;
	pHeader->ownerName = ownerName;
	return pHeaderRaw + sizeof(Header);
}

void MemoryPool::ChunkFixed::Deallocate(void* p)
{
	char* pHeaderRaw = reinterpret_cast<char*>(p) - sizeof(Header);
	Header* pHeader = reinterpret_cast<Header*>(pHeaderRaw);
	pHeader->u.pHeaderVacantNext = _pHeaderVacantHead;
	pHeader->ownerName = nullptr;
	_pHeaderVacantHead = pHeader;
}

void MemoryPool::ChunkFixed::Print() const
{
	::printf("[ChunkFixed:%ldbytes/block]\n", _bytesBlock);
	size_t bytesFrame = sizeof(Header) + _bytesBlock;
	PoolList poolList;
	for (Pool* pPool = _pPool; pPool; pPool = pPool->pPoolPrev) poolList.push_back(pPool);
	for (auto ppPool = poolList.rbegin(); ppPool != poolList.rend(); ++ppPool) {
		Pool *pPool = *ppPool;
		size_t nBlocks = (pPool == _pPool)? _iBlockNext : _nBlocks;
		const char* pHeaderRaw = pPool->buff;
		for (size_t iBlock = 0; iBlock < nBlocks; ++iBlock, pHeaderRaw += bytesFrame) {
			const Header* pHeader = reinterpret_cast<const Header*>(pHeaderRaw);
			::printf("%c", pHeader->ownerName? '*' : '.');
		}
		::printf("\n");
	}
	//::printf("\n");
}

//-----------------------------------------------------------------------------
// MemoryPool::ChunkVariable
//-----------------------------------------------------------------------------
void* MemoryPool::ChunkVariable::Allocate(size_t bytes, const char* ownerName)
{
	size_t bytesFrame = sizeof(Header) + bytes;
	char* pHeaderRaw = reinterpret_cast<char*>(::malloc(bytesFrame));
	if (!pHeaderRaw) return nullptr;
	Header* pHeader = reinterpret_cast<Header*>(pHeaderRaw);
	pHeader->u.pChunk = this;
	pHeader->ownerName = ownerName;
	return pHeaderRaw + sizeof(Header);
}

void MemoryPool::ChunkVariable::Deallocate(void* p)
{
	char* pHeaderRaw = reinterpret_cast<char*>(p) - sizeof(Header);
	::free(pHeaderRaw);
}

}
