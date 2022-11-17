//==============================================================================
// BasicStream.cpp
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

Stream_Binary::Stream_Binary(Flags flags, Codec* pCodec, BinaryReferable* pBuff, size_t offset) :
	Stream(flags | Flag::BwdSeekable | Flag::FwdSeekable, pCodec, offset),
	_pBuff(pBuff)
{
}

Stream_Binary::Stream_Binary(Flags flags) : Stream_Binary(flags, new BinaryReferable(), 0)
{
	Binary& buffTgt = _pBuff->GetBinary();
	buffTgt.reserve(1024);
}

Stream_Binary::Stream_Binary(Flags flags, Codec* pCodec) : Stream_Binary(flags, pCodec, new BinaryReferable(), 0)
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

//------------------------------------------------------------------------------
// Stream_StringReader
//------------------------------------------------------------------------------
Stream_StringReader::Stream_StringReader(StringReferable* pStr) :
	Stream(Flag::Readable | Flag::BwdSeekable | Flag::FwdSeekable), _pStr(pStr)
{
}

size_t Stream_StringReader::DoGetBytes()
{
	const String& strTgt = _pStr->GetString();
	return strTgt.size();
}

int Stream_StringReader::DoGetChar()
{
	const String& strTgt = _pStr->GetString();
	return (_offset < strTgt.size())? static_cast<UInt8>(strTgt[_offset++]) : -1;
}

size_t Stream_StringReader::DoRead(void* buff, size_t len)
{
	const String& strTgt = _pStr->GetString();
	if (_offset > strTgt.size()) {
		Error::Issue(ErrorType::RangeError, "the offset is out of range");
		return 0;
	}
	size_t lenRead = strTgt.copy(reinterpret_cast<char*>(buff), len, _offset);
	_offset += lenRead;
	return lenRead;
}

bool Stream_StringReader::DoSeek(size_t offset, size_t offsetPrev)
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

//------------------------------------------------------------------------------
// Stream_FIFO
//------------------------------------------------------------------------------
Stream_FIFO::Stream_FIFO(size_t bytesBuff) : Stream(Flag::Readable | Flag::Writable),
	_pMemory(new MemoryHeap(bytesBuff)), _offsetWrite(0), _offsetRead(0), _bytesAvail(0),
	_brokenFlag(false)
{
}

size_t Stream_FIFO::DoRead(void* buff, size_t len)
{
	char *buffp = reinterpret_cast<char *>(buff);
	_semaphore.Wait();
	//::printf("+DoRead(%zu) bytesAvail=%zu\n", len, _bytesAvail);
	if (_brokenFlag && _bytesAvail == 0) {
		_semaphore.Release();
		return 0;
	}
	size_t offset = 0;
	while (offset < len) {
		size_t bytesSpace = len - offset;
		while (_bytesAvail == 0 && !_brokenFlag) {
			_semaphore.Release();
			OAL::Sleep(.001); // sleep for 1 msec
			_semaphore.Wait();
		}
		if (_bytesAvail > 0) {
			size_t bytesCopy = std::min(bytesSpace, _bytesAvail);
			if (_offsetRead + bytesCopy <= _pMemory->GetBytes()) {
				::memcpy(buffp + offset, _pMemory->GetPointerC<void>(_offsetRead), bytesCopy);
				offset += bytesCopy;
				_offsetRead += bytesCopy;
				_bytesAvail -= bytesCopy;
				if (_offsetRead == _pMemory->GetBytes()) _offsetRead = 0;
			} else {
				size_t bytesPart = _pMemory->GetBytes() - _offsetRead;
				::memcpy(buffp + offset, _pMemory->GetPointerC<void>(_offsetRead), bytesPart);
				::memcpy(buffp + offset + bytesPart, _pMemory->GetPointerC<void>(), bytesCopy - bytesPart);
				offset += bytesCopy;
				_offsetRead = bytesCopy - bytesPart;
				_bytesAvail -= bytesCopy;
			}
		}
		if (_brokenFlag) {
			//::printf("-DoRead(%zu) rtn=%zu\n", len, offset);
			_semaphore.Release();
			return offset;
		}
	}
	//::printf("-DoRead(%zu) rtn=%zu\n", len, offset);
	_semaphore.Release();
	return offset;
}

bool Stream_FIFO::DoWrite(const void* buff, size_t len)
{
	const char* buffp = reinterpret_cast<const char*>(buff);
	_semaphore.Wait();
	//::printf("DoWrite(%zu) bytesAvail=%zu\n", len, _bytesAvail);
	for (size_t offset = 0; offset < len; ) {
		size_t bytesRest = len - offset;
		while (_bytesAvail == _pMemory->GetBytes()) {
			_semaphore.Release();
			OAL::Sleep(.001); // sleep for 1 msec
			_semaphore.Wait();
		}
		size_t bytesSpace = _pMemory->GetBytes() - _bytesAvail;
		size_t bytesCopy = std::min(bytesRest, bytesSpace);
		if (_offsetWrite + bytesCopy <= _pMemory->GetBytes()) {
			::memcpy(_pMemory->GetPointerC<void>(_offsetWrite), buffp + offset, bytesCopy);
			offset += bytesCopy;
			_offsetWrite += bytesCopy;
			_bytesAvail += bytesCopy;
			if (_offsetRead == _pMemory->GetBytes()) _offsetRead = 0;
		} else {
			size_t bytesPart = _pMemory->GetBytes() - _offsetWrite;
			::memcpy(_pMemory->GetPointerC<void>(_offsetWrite), buffp + offset, bytesPart);
			::memcpy(_pMemory->GetPointerC<void>(), buffp + offset + bytesPart, bytesCopy - bytesPart);
			offset += bytesCopy;
			_offsetWrite = bytesCopy - bytesPart;
			_bytesAvail += bytesCopy;
		}
	}
	_semaphore.Release();
	return true;
}

}
