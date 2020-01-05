//==============================================================================
// Streams.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Stream_Prefetch
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Stream_Prefetch : public Stream {
private:
	RefPtr<Stream> _pStreamSrc;
	size_t _offset;
	size_t _bytesAll;
	size_t _bytesUnit;
	MemoryOwner _memoryOwner;
public:
	Stream_Prefetch(Stream* pStreamSrc, size_t bytesUnit);
public:
	virtual const char* GetName() const override { return _pStreamSrc->GetName(); };
	virtual const char* GetIdentifier() const override { return _pStreamSrc->GetIdentifier(); }
	virtual size_t DoGetSize() override { return _bytesAll; }
	virtual bool DoClose() override { return true; }
	virtual size_t DoRead(void* buff, size_t len) override;
	virtual size_t DoWrite(const void* buff, size_t len) override { return 0; }
	virtual bool DoFlush() override { return false; }
	virtual bool DoSeek(size_t offset, size_t offsetPrev) override;
public:
	bool DoPrefetch();
};

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
#if 0
	size_t iMemory = _offset / _bytesUnit;
	if (iMemory >= _memoryOwner.size()) {
		sig.SetError(ERR_IndexError, "out of range");
		return 0;
	}
	MemoryList::iterator ppMemory = _memoryOwner.begin() + iMemory;
	char *buffDst = reinterpret_cast<char *>(buff);
	size_t offsetUnit = _offset % _bytesUnit;
	size_t bytesCopied = 0;
	size_t bytesRest = len;
	for ( ; ppMemory != _memoryOwner.end() && bytesRest > 0; ppMemory++) {
		Memory *pMemory = *ppMemory;
		size_t bytesToCopy = _bytesUnit - offsetUnit;
		bytesToCopy = ChooseMin(bytesToCopy, bytesRest);
		::memcpy(buffDst + bytesCopied, pMemory->GetPointer(offsetUnit), bytesToCopy);
		offsetUnit = 0;
		_offset += bytesToCopy;
		bytesCopied += bytesToCopy;
		bytesRest -= bytesToCopy;
	}
	return bytesCopied;
#endif
	return 0;
}

bool Stream_Prefetch::DoSeek(size_t offset, size_t offsetPrev)
{
	_offset = static_cast<size_t>(offset);
	return true;
}

bool Stream_Prefetch::DoPrefetch()
{
#if 0
	_bytesAll = 0;
	for (;;) {
		AutoPtr<Memory> pMemory(new MemoryHeap(_bytesUnit));
		size_t bytes = _pStreamSrc->Read(sig, pMemory->GetPointer(), _bytesUnit);
		if (sig.IsSignalled()) {
			return false;
		} else if (bytes == 0 || sig.IsSignalled()) {
			break;
		}
		_memoryOwner.push_back(pMemory.release());
		_bytesAll += bytes;
		if (bytes < _bytesUnit) break;
	}
#endif
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
