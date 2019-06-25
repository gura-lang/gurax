//==============================================================================
// Streams.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Stream_File
//------------------------------------------------------------------------------
Stream* Stream_File::Open(const char* fileName, const char* mode)
{
	FILE* fp = ::fopen(fileName, mode);
	return fp? new Stream_File(fp, true, fileName, fileName) : nullptr;
}

//------------------------------------------------------------------------------
// Stream_Binary
//------------------------------------------------------------------------------
Stream_Binary::Stream_Binary(BinaryReferable* pBuff, size_t offset) : _pBuff(pBuff), _offset(offset)
{
}

Stream_Binary::Stream_Binary() : _pBuff(new BinaryReferable()), _offset(0)
{
	Binary& buffTgt = _pBuff->GetBinary();
	buffTgt.reserve(1024);
}

int Stream_Binary::GetChar()
{
	Binary& buffTgt = _pBuff->GetBinary();
	return (_offset < buffTgt.size())? buffTgt[_offset++] : -1;
}

bool Stream_Binary::PutChar(char ch)
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

size_t Stream_Binary::Read(void* buff, size_t len)
{
	Binary& buffTgt = _pBuff->GetBinary();
	size_t lenRead = buffTgt.copy(reinterpret_cast<UInt8*>(buff), len, _offset);
	_offset += lenRead;
	return lenRead;
}

size_t Stream_Binary::Write(const void* buff, size_t len)
{
	Binary& buffTgt = _pBuff->GetBinary();
	if (_offset < buffTgt.size()) {
		
	} else {
		size_t bytesGap = buffTgt.size() - _offset;
		if (bytesGap > 0) buffTgt.assign(bytesGap, '\0');
		buffTgt.insert(Binary::npos, reinterpret_cast<const UInt8*>(buff), len);
		_offset = buffTgt.size();
	}
	return len;
}

}
