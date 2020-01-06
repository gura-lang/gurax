//==============================================================================
// Streams.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Stream_Prefetch
//------------------------------------------------------------------------------
Stream_Prefetch::Stream_Prefetch(Stream* pStreamSrc, size_t bytesUnit) :
	Stream(Flag::Readable), _pStreamSrc(pStreamSrc), _offset(0), _bytesAll(0), _bytesUnit(bytesUnit)
{
	SetCodec(pStreamSrc->GetCodec().Duplicate());
}

size_t Stream_Prefetch::DoRead(void* buff, size_t len)
{
	size_t iMemory = _offset / _bytesUnit;
	if (iMemory >= _memoryOwner.size()) {
		Error::Issue(ErrorType::RangeError, "out of range");
		return 0;
	}
	MemoryList::iterator ppMemory = _memoryOwner.begin() + iMemory;
	char *buffDst = reinterpret_cast<char*>(buff);
	size_t offsetUnit = _offset % _bytesUnit;
	size_t bytesCopied = 0;
	size_t bytesRest = len;
	for ( ; ppMemory != _memoryOwner.end() && bytesRest > 0; ppMemory++) {
		Memory *pMemory = *ppMemory;
		size_t bytesToCopy = _bytesUnit - offsetUnit;
		bytesToCopy = std::min(bytesToCopy, bytesRest);
		::memcpy(buffDst + bytesCopied, pMemory->GetPointer(offsetUnit), bytesToCopy);
		offsetUnit = 0;
		_offset += bytesToCopy;
		bytesCopied += bytesToCopy;
		bytesRest -= bytesToCopy;
	}
	return bytesCopied;
}

bool Stream_Prefetch::DoSeek(size_t offset, size_t offsetPrev)
{
	_offset = static_cast<size_t>(offset);
	return true;
}

bool Stream_Prefetch::Prefetch()
{
	_bytesAll = 0;
	for (;;) {
		RefPtr<Memory> pMemory(new MemoryHeap(_bytesUnit));
		size_t bytes = _pStreamSrc->Read(pMemory->GetPointer(), _bytesUnit);
		if (Error::IsIssued()) return false;
		if (bytes == 0) break;
		_memoryOwner.push_back(pMemory.release());
		_bytesAll += bytes;
		if (bytes < _bytesUnit) break;
	}
	return true;
}

//------------------------------------------------------------------------------
// Stream_Console
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Stream_Binary
//------------------------------------------------------------------------------
Stream_Binary::Stream_Binary(Flags flags, BinaryReferable* pBuff, size_t offset) :
	Stream(flags | Flag::BwdSeekable | Flag::FwdSeekable, offset),
	_pBuff(pBuff)
{
}

Stream_Binary::Stream_Binary(Flags flags) : Stream_Binary(flags, new BinaryReferable(true), 0)
{
	Binary& buffTgt = _pBuff->GetBinary();
	buffTgt.reserve(1024);
}

size_t Stream_Binary::DoGetSize()
{
	Binary& buffTgt = _pBuff->GetBinary();
	return buffTgt.size();
}

int Stream_Binary::DoGetChar()
{
	Binary& buffTgt = _pBuff->GetBinary();
	return (_offset < buffTgt.size())? buffTgt[_offset++] : -1;
}

bool Stream_Binary::DoPutChar(char ch)
{
	Binary& buffTgt = _pBuff->GetBinary();
	if (_offset < buffTgt.size()) {
		buffTgt[_offset++] = ch;
	} else {
		size_t bytesGap = buffTgt.size() - _offset;
		if (bytesGap > 0) buffTgt.assign(bytesGap, '\0');
		buffTgt += ch;
		_offset = buffTgt.size();
	}
	return true;
}

size_t Stream_Binary::DoRead(void* buff, size_t len)
{
	Binary& buffTgt = _pBuff->GetBinary();
	if (_offset > buffTgt.size()) {
		Error::Issue(ErrorType::RangeError, "the offset is out of range");
		return 0;
	}
	size_t lenRead = buffTgt.copy(reinterpret_cast<UInt8*>(buff), len, _offset);
	_offset += lenRead;
	return lenRead;
}

size_t Stream_Binary::DoWrite(const void* buff, size_t len)
{
	Binary& buffTgt = _pBuff->GetBinary();
	if (_offset < buffTgt.size()) {
		size_t bytesGap = buffTgt.size() - _offset;
		buffTgt.replace(_offset, std::min(bytesGap, len), reinterpret_cast<const UInt8*>(buff), len);
		_offset += len;
	} else {
		size_t bytesGap = _offset - buffTgt.size();
		if (bytesGap > 0) buffTgt.assign(bytesGap, '\0');
		buffTgt.append(reinterpret_cast<const UInt8*>(buff), len);
		_offset = buffTgt.size();
	}
	return len;
}

bool Stream_Binary::DoSeek(size_t offset, size_t offsetPrev)
{
	// nothing to do here
	return true;
}

}
