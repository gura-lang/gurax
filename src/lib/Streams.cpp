//==============================================================================
// Streams.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

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
