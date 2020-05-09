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
// Stream_ReaderBase64
//------------------------------------------------------------------------------
Stream_ReaderBase64::Stream_ReaderBase64(Stream* pStreamSrc) :
	Stream(Flag::Readable), _pStreamSrc(pStreamSrc),
	_nChars(0), _nInvalid(0), _accum(0), _iBuffWork(0)
{
}

size_t Stream_ReaderBase64::DoRead(void* buff, size_t len)
{
	UInt8* buffp = reinterpret_cast<UInt8*>(buff);
	size_t lenRead = 0;
	while (lenRead < len) {
		if (_iBuffWork > 0) {
			_iBuffWork--;
			buffp[lenRead++] = _buffWork[_iBuffWork];
			continue;
		}
		char ch;
		size_t bytes = _pStreamSrc->Read(&ch, 1);
		if (bytes == 0) break;
		if ('A' <= ch && ch <= 'Z') {
			_accum = (_accum << 6) | (ch - 'A');
		} else if ('a' <= ch && ch <= 'z') {
			_accum = (_accum << 6) | (ch - 'a' + 26);
		} else if ('0' <= ch && ch <= '9') {
			_accum = (_accum << 6) | (ch - '0' + 52);
		} else if (ch == '+') {
			_accum = (_accum << 6) | 62;
		} else if (ch == '/') {
			_accum = (_accum << 6) | 63;
		} else if (ch == '=') {
			_nInvalid++;
			_accum = (_accum << 6);
		} else if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n') {
			continue;
		} else {
			Error::Issue(ErrorType::FormatError, "invalid base64 format");
			return 0;
		}
		_nChars++;
		if (_nChars < 4) continue;
		if (_nInvalid == 0) {
			_buffWork[0] = static_cast<UInt8>(_accum & 0xff); _accum >>= 8;
			_buffWork[1] = static_cast<UInt8>(_accum & 0xff); _accum >>= 8;
			_buffWork[2] = static_cast<UInt8>(_accum & 0xff);
			_iBuffWork = 3;
		} else if (_nInvalid == 1) {
			_accum >>= 8;
			_buffWork[0] = static_cast<UInt8>(_accum & 0xff); _accum >>= 8;
			_buffWork[1] = static_cast<UInt8>(_accum & 0xff);
			_iBuffWork = 2;
		} else if (_nInvalid == 2) {
			_accum >>= 8;
			_accum >>= 8;
			_buffWork[0] = static_cast<UInt8>(_accum & 0xff);
			_iBuffWork = 1;
		} else {
			_iBuffWork = 0;
		}
		_nChars = 0, _nInvalid = 0, _accum = 0;
	}
	return lenRead;
}

//------------------------------------------------------------------------------
// Stream_WriterBase64
//------------------------------------------------------------------------------
const char Stream_WriterBase64::_chars[] =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

Stream_WriterBase64::Stream_WriterBase64(Stream* pStreamDst, int nCharsPerLine) :
	Stream(Flag::Writable), _pStreamDst(pStreamDst),
	_nCharsPerLine((nCharsPerLine + 3) / 4 * 4), _nChars(0), _iBuffWork(0)
{
}

bool Stream_WriterBase64::DoWrite(const void* buff, size_t len)
{
	const UInt8* buffp = reinterpret_cast<const UInt8*>(buff);
	size_t lenWritten = 0;
	bool addcrFlag = _pStreamDst->GetCodec().GetEncoder().GetAddcrFlag();
	for ( ; lenWritten < len; lenWritten++) {
		_buffWork[_iBuffWork++] = buffp[lenWritten];
		if (_iBuffWork < 3) continue;
		UInt32 accum =
			(static_cast<UInt32>(_buffWork[0]) << 16) |
			(static_cast<UInt32>(_buffWork[1]) << 8) |
			(static_cast<UInt32>(_buffWork[2]) << 0);
		char buffDst[8];
		char* pBuffDst = buffDst;
		*pBuffDst++ = _chars[(accum >> 18) & 0x3f];
		*pBuffDst++ = _chars[(accum >> 12) & 0x3f];
		*pBuffDst++ = _chars[(accum >> 6) & 0x3f];
		*pBuffDst++ = _chars[(accum >> 0) & 0x3f];
		_nChars += 4;
		if (_nCharsPerLine > 0 && _nChars >= _nCharsPerLine) {
			if (addcrFlag) *pBuffDst++ = '\r';
			*pBuffDst++ = '\n';
			_nChars = 0;
		}
		if (!_pStreamDst->Write(buffDst, pBuffDst - buffDst)) return false;
		_iBuffWork = 0;
	}
	return true;
}

bool Stream_WriterBase64::DoFlush()
{
		char buffDst[8];
	char* pBuffDst = buffDst;
	bool addcrFlag = _pStreamDst->GetCodec().GetEncoder().GetAddcrFlag();
	if (_iBuffWork == 0) {
		if (_nChars > 0 && _nCharsPerLine > 0) {
			if (addcrFlag) *pBuffDst++ = '\r';
			*pBuffDst++ = '\n';
			if (!_pStreamDst->Write(buffDst, pBuffDst - buffDst)) return false;
		}
		_nChars = 0;
		_iBuffWork = 0;
	} else if (_iBuffWork == 1) {
		UInt32 accum = static_cast<UInt32>(_buffWork[0]) << 16;
		*pBuffDst++ = _chars[(accum >> 18) & 0x3f];
		*pBuffDst++ = _chars[(accum >> 12) & 0x3f];
		*pBuffDst++ = '=';
		*pBuffDst++ = '=';
	} else if (_iBuffWork == 2) {
		UInt32 accum =
			(static_cast<UInt32>(_buffWork[0]) << 16) |
			(static_cast<UInt32>(_buffWork[1]) << 8);
		*pBuffDst++ = _chars[(accum >> 18) & 0x3f];
		*pBuffDst++ = _chars[(accum >> 12) & 0x3f];
		*pBuffDst++ = _chars[(accum >> 6) & 0x3f];
		*pBuffDst++ = '=';
	} else { // _iBuffWork == 3
		UInt32 accum =
			(static_cast<UInt32>(_buffWork[0]) << 16) |
			(static_cast<UInt32>(_buffWork[1]) << 8) |
			(static_cast<UInt32>(_buffWork[2]) << 0);
		*pBuffDst++ = _chars[(accum >> 18) & 0x3f];
		*pBuffDst++ = _chars[(accum >> 12) & 0x3f];
		*pBuffDst++ = _chars[(accum >> 6) & 0x3f];
		*pBuffDst++ = _chars[(accum >> 0) & 0x3f];
	}
	if (_nCharsPerLine > 0) {
		if (addcrFlag) *pBuffDst++ = '\r';
		*pBuffDst++ = '\n';
	}
	if (!_pStreamDst->Write(buffDst, pBuffDst - buffDst)) return false;
	_nChars = 0;
	_iBuffWork = 0;
	return true;

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

}
