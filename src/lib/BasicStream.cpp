//==============================================================================
// BasicStream.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Stream_FIFO
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Stream_FIFO : public Stream {
public:
	Stream_FIFO() : Stream(Flag::Readable | Flag::Writable) {}
public:
	virtual const char* GetName() const override { return "FIFO"; };
	virtual const char* GetIdentifier() const override { return ""; }
	virtual bool DoClose() override { return true; }
	virtual int DoGetChar() override { return 0; }
	virtual bool DoPutChar(char ch) override { return true; }
	virtual size_t DoRead(void* buff, size_t len) override;
	virtual bool DoWrite(const void* buff, size_t len) override;
	virtual bool DoFlush() override { return true; }
};

size_t Stream_FIFO::DoRead(void* buff, size_t len)
{
	return 0;
}

bool Stream_FIFO::DoWrite(const void* buff, size_t len)
{
	return false;
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

Stream_Binary::Stream_Binary(Flags flags) : Stream_Binary(flags, new BinaryReferable(), 0)
{
	Binary& buffTgt = _pBuff->GetBinary();
	buffTgt.reserve(1024);
}

size_t Stream_Binary::DoGetBytes()
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

bool Stream_Binary::DoWrite(const void* buff, size_t len)
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
	return true;
}

bool Stream_Binary::DoSeek(size_t offset, size_t offsetPrev)
{
	// nothing to do here
	return true;
}

#if 0
//------------------------------------------------------------------------------
// Stream_Pointer
//------------------------------------------------------------------------------
Stream_Pointer::Stream_Pointer(Flags flags, Pointer* pPointer) :
	Stream(flags | Flag::BwdSeekable | Flag::FwdSeekable, offset),
	_pPointer(pPointer)
{
}

Stream_Pointer::Stream_Pointer(Flags flags) : Stream_Pointer(flags, new PointerReferable(), 0)
{
	Pointer& buffTgt = _pBuff->GetPointer();
	buffTgt.reserve(1024);
}

size_t Stream_Pointer::DoGetBytes()
{
	Pointer& buffTgt = _pBuff->GetPointer();
	return buffTgt.size();
}

int Stream_Pointer::DoGetChar()
{
	Pointer& buffTgt = _pBuff->GetPointer();
	return (_offset < buffTgt.size())? buffTgt[_offset++] : -1;
}

bool Stream_Pointer::DoPutChar(char ch)
{
	Pointer& buffTgt = _pBuff->GetPointer();
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

size_t Stream_Pointer::DoRead(void* buff, size_t len)
{
	Pointer& buffTgt = _pBuff->GetPointer();
	if (_offset > buffTgt.size()) {
		Error::Issue(ErrorType::RangeError, "the offset is out of range");
		return 0;
	}
	size_t lenRead = buffTgt.copy(reinterpret_cast<UInt8*>(buff), len, _offset);
	_offset += lenRead;
	return lenRead;
}

bool Stream_Pointer::DoWrite(const void* buff, size_t len)
{
	Pointer& buffTgt = _pBuff->GetPointer();
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
	return true;
}

bool Stream_Pointer::DoSeek(size_t offset, size_t offsetPrev)
{
	// nothing to do here
	return true;
}
#endif

}
