//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(base64)

//------------------------------------------------------------------------------
// Decoder
//------------------------------------------------------------------------------
Decoder::Decoder(Stream* pStreamOut) :
	_pStreamOut(pStreamOut), _nCharsAccum(0), _nBars(0), _accum(0)
{
}

bool Decoder::Decode(const void* buff, size_t bytes)
{
	const char* buffp = reinterpret_cast<const char*>(buff);
	const char* buffpEnd = buffp + bytes;
	for ( ; buffp != buffpEnd; buffp++) {
		char ch = *buffp;
		if (String::IsUpper(ch)) {
			_accum = (_accum << 6) + (ch - 'A');
		} else if (String::IsLower(ch)) {
			_accum = (_accum << 6) + (ch - 'a') + 26;
		} else if (String::IsDigit(ch)) {
			_accum = (_accum << 6) + (ch - '0') + 52;
		} else if (ch == '+') {
			_accum = (_accum << 6) + 62;
		} else if (ch == '/') {
			_accum = (_accum << 6) + 63;
		} else if (ch == '=') {
			_nBars++;
			_accum = (_accum << 6);
		} else if (String::IsSpace(ch)) {
			continue;
		} else {
			Error::Issue(ErrorType::FormatError, "invalid base64 format");
			return false;
		}
		_nCharsAccum++;
		if (_nCharsAccum == 4) {
			UInt8 buffOut[4];
			size_t bytesOut = 3 - _nBars;
			_accum >>= 8 * _nBars;
			buffOut[0] = static_cast<UInt8>((_accum >> 0) & 0xff);
			buffOut[1] = static_cast<UInt8>((_accum >> 8) & 0xff);
			buffOut[2] = static_cast<UInt8>((_accum >> 16) & 0xff);
			if (bytesOut > 0 && !_pStreamOut->Write(buffOut, 3 - _nBars)) return false;
			_nCharsAccum = 0, _nBars = 0, _accum = 0;
		}
	}
	return true;
}

bool Decoder::DecodeStream(Stream& streamSrc)
{
	return true;
}

//------------------------------------------------------------------------------
// Encoder
//------------------------------------------------------------------------------
const char Encoder::_charTbl[] =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

Encoder::Encoder(Stream* pStreamOut, int nCharsPerLine) :
	_pStreamOut(pStreamOut), _nCharsPerLine((nCharsPerLine + 3) / 4 * 4),
	_nCharsOut(0), _bytesAccum(0), _accum(0)
{
}

bool Encoder::Encode(const void* buff, size_t bytes)
{
	const UInt8* buffp = reinterpret_cast<const UInt8*>(buff);
	const UInt8* buffpEnd = buffp + bytes;
	for ( ; buffp != buffpEnd; buffp++) {
		_accum = (_accum << 8) + *buffp;
		_bytesAccum++;
		if (_bytesAccum == 3) {
			// 00000000 aaaaaabb bbbbcccc ccdddddd
			char buffOut[8];
			size_t bytesOut = 0;
			buffOut[bytesOut++] = _charTbl[(_accum >> 18) & 0x3f];
			buffOut[bytesOut++] = _charTbl[(_accum >> 12) & 0x3f];
			buffOut[bytesOut++] = _charTbl[(_accum >> 6) & 0x3f];
			buffOut[bytesOut++] = _charTbl[(_accum >> 0) & 0x3f];
			_nCharsOut += 4;
			if (_nCharsPerLine > 0 && _nCharsOut >= _nCharsPerLine) {
				if (_pStreamOut->GetCodec().GetAddcrFlag()) buffOut[bytesOut++] = '\r';
				buffOut[bytesOut++] = '\n';
				_nCharsOut = 0;
			}
			if (!_pStreamOut->Write(buffOut, bytesOut)) return false;
			_bytesAccum = 0, _accum = 0;
		}
	}
	return true;
}

bool Encoder::EncodeStream(Stream& streamSrc)
{
	return true;
}

bool Encoder::Finish()
{
	UInt8 buffOut[8];
	size_t bytesOut = 0;
	if (_bytesAccum == 0) {
		// nothing to do
	} else if (_bytesAccum == 1) {
		// 00000000 aaaaaabb 00000000 00000000
		_accum <<= 16;
		buffOut[bytesOut++] = _charTbl[(_accum >> 18) & 0x3f];
		buffOut[bytesOut++] = _charTbl[(_accum >> 12) & 0x3f];
		buffOut[bytesOut++] = '=';
		buffOut[bytesOut++] = '=';
		_nCharsOut += 4;
	} else if (_bytesAccum == 2) {
		// 00000000 aaaaaabb bbbbcccc 00000000
		_accum <<= 8;
		buffOut[bytesOut++] = _charTbl[(_accum >> 18) & 0x3f];
		buffOut[bytesOut++] = _charTbl[(_accum >> 12) & 0x3f];
		buffOut[bytesOut++] = _charTbl[(_accum >> 6) & 0x3f];
		buffOut[bytesOut++] = '=';
		_nCharsOut += 4;
	} else if (_bytesAccum == 3) {
		// 00000000 aaaaaabb bbbbcccc ccdddddd
		buffOut[bytesOut++] = _charTbl[(_accum >> 18) & 0x3f];
		buffOut[bytesOut++] = _charTbl[(_accum >> 12) & 0x3f];
		buffOut[bytesOut++] = _charTbl[(_accum >> 6) & 0x3f];
		buffOut[bytesOut++] = _charTbl[(_accum >> 0) & 0x3f];
		_nCharsOut += 4;
	}
	if (_nCharsPerLine > 0 && _nCharsOut > 0) {
		if (_pStreamOut->GetCodec().GetAddcrFlag()) buffOut[bytesOut++] = '\r';
		buffOut[bytesOut++] = '\n';
		_nCharsOut = 0;
	}
	if (bytesOut > 0 && !_pStreamOut->Write(buffOut, bytesOut)) return false;
	_nCharsOut = 0, _bytesAccum = 0, _accum = 0;
	return true;
}

Gurax_EndModuleScope(base64)
