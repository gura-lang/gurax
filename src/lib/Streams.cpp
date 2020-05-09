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
// Stream_Base64Reader
//------------------------------------------------------------------------------
Stream_Base64Reader::Stream_Base64Reader(Stream* pStreamSrc) :
	Stream(Flag::Readable), _pStreamSrc(pStreamSrc),
	_nChars(0), _nInvalid(0), _accum(0), _iBuffWork(0)
{
}

size_t Stream_Base64Reader::DoRead(void* buff, size_t len)
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

#if 0
//------------------------------------------------------------------------------
// Stream_Base64Writer
//------------------------------------------------------------------------------
const char Stream_Base64Writer::_chars[] =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

Stream_Base64Writer::Stream_Base64Writer(Environment &env, Stream *pStreamDst, int nCharsPerLine) :
			Stream(env, ATTR_Writable), _pStreamDst(pStreamDst),
			_nCharsPerLine(nCharsPerLine), _nChars(0), _iBuffWork(0)
{
	CopyCodec(pStreamDst);
	_nCharsPerLine = (_nCharsPerLine + 3) / 4 * 4;
}

const char *Stream_Base64Writer::GetName() const
{
	return _pStreamDst->GetName();
}

const char *Stream_Base64Writer::GetIdentifier() const
{
	return _pStreamDst->GetIdentifier();
}

bool Stream_Base64Writer::GetAttribute(Attribute &attr)
{
	return _pStreamDst->GetAttribute(attr);
}

bool Stream_Base64Writer::SetAttribute(const Attribute &attr)
{
	return _pStreamDst->SetAttribute(attr);
}

size_t Stream_Base64Writer::DoRead(Signal &sig, void *buff, size_t len)
{
	return 0;
}

size_t Stream_Base64Writer::DoWrite(Signal &sig, const void *buff, size_t len)
{
	const UInt8 *buffp = reinterpret_cast<const UInt8 *>(buff);
	size_t lenWritten = 0;
	bool addcrFlag = _pStreamDst->GetCodec()->GetEncoder()->GetAddcrFlag();
	for ( ; lenWritten < len; lenWritten++) {
		_buffWork[_iBuffWork++] = buffp[lenWritten];
		if (_iBuffWork < 3) continue;
		UInt32 accum =
			(static_cast<UInt32>(_buffWork[0]) << 16) |
			(static_cast<UInt32>(_buffWork[1]) << 8) |
			(static_cast<UInt32>(_buffWork[2]) << 0);
		char buffDst[8];
		buffDst[0] = _chars[(accum >> 18) & 0x3f];
		buffDst[1] = _chars[(accum >> 12) & 0x3f];
		buffDst[2] = _chars[(accum >> 6) & 0x3f];
		buffDst[3] = _chars[(accum >> 0) & 0x3f];
		_nChars += 4;
		if (_nCharsPerLine > 0 && _nChars >= _nCharsPerLine) {
			size_t bytes = 4;
			if (addcrFlag) buffDst[bytes++] = '\r';
			buffDst[bytes++] = '\n';
			_pStreamDst->Write(sig, buffDst, bytes);
			_nChars = 0;
		} else {
			_pStreamDst->Write(sig, buffDst, 4);
		}
		if (sig.IsSignalled()) return 0;
		_iBuffWork = 0;
	}
	return lenWritten;
}

bool Stream_Base64Writer::DoSeek(Signal &sig, long offset, size_t offsetPrev, SeekMode seekMode)
{
	return false;
}

bool Stream_Base64Writer::DoFlush(Signal &sig)
{
	char buffDst[8];
	bool addcrFlag = _pStreamDst->GetCodec()->GetEncoder()->GetAddcrFlag();
	if (_iBuffWork == 0) {
		if (_nChars > 0 && _nCharsPerLine > 0) {
			size_t bytes = 0;
			if (addcrFlag) buffDst[bytes++] = '\r';
			buffDst[bytes++] = '\n';
			_pStreamDst->Write(sig, buffDst, bytes);
		}
		_nChars = 0;
		_iBuffWork = 0;
		return !sig.IsSignalled();
	} else if (_iBuffWork == 1) {
		UInt32 accum = static_cast<UInt32>(_buffWork[0]) << 16;
		buffDst[0] = _chars[(accum >> 18) & 0x3f];
		buffDst[1] = _chars[(accum >> 12) & 0x3f];
		buffDst[2] = '=';
		buffDst[3] = '=';
	} else if (_iBuffWork == 2) {
		UInt32 accum =
			(static_cast<UInt32>(_buffWork[0]) << 16) |
			(static_cast<UInt32>(_buffWork[1]) << 8);
		buffDst[0] = _chars[(accum >> 18) & 0x3f];
		buffDst[1] = _chars[(accum >> 12) & 0x3f];
		buffDst[2] = _chars[(accum >> 6) & 0x3f];
		buffDst[3] = '=';
	} else { // _iBuffWork == 3
		UInt32 accum =
			(static_cast<UInt32>(_buffWork[0]) << 16) |
			(static_cast<UInt32>(_buffWork[1]) << 8) |
			(static_cast<UInt32>(_buffWork[2]) << 0);
		buffDst[0] = _chars[(accum >> 18) & 0x3f];
		buffDst[1] = _chars[(accum >> 12) & 0x3f];
		buffDst[2] = _chars[(accum >> 6) & 0x3f];
		buffDst[3] = _chars[(accum >> 0) & 0x3f];
	}
	if (_nCharsPerLine > 0) {
		size_t bytes = 4;
		if (addcrFlag) buffDst[bytes++] = '\r';
		buffDst[bytes++] = '\n';
		_pStreamDst->Write(sig, buffDst, bytes);
	} else {
		_pStreamDst->Write(sig, buffDst, 4);
	}
	_nChars = 0;
	_iBuffWork = 0;
	return !sig.IsSignalled();
}

bool Stream_Base64Writer::DoClose(Signal &sig)
{
	if (!DoFlush(sig)) return false;
	return Stream::DoClose(sig);
}

size_t Stream_Base64Writer::DoGetSize()
{
	return 0;
}
#endif

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
