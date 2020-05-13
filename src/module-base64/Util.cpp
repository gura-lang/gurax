//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(base64)

//------------------------------------------------------------------------------
// Decoder
//------------------------------------------------------------------------------
Decoder::Decoder(Stream* pStreamOut) :
	_pStreamOut(pStreamOut), _nCharsAccum(0), _nPads(0), _accum(0)
{
}

bool Decoder::Decode(const void* buff, size_t bytes)
{
	constexpr int SPC = -1;
	constexpr int PAD = -2;
	constexpr int ERR = -3;
	static const int tbl[] = {
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,SPC,SPC,ERR,ERR,SPC,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		SPC,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR, 62,ERR, 62,ERR, 63,
		52, 53, 54, 55, 56, 57, 58, 59, 60, 61,ERR,ERR,ERR,PAD,ERR,ERR,
		ERR,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
		15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,ERR,ERR,ERR,ERR, 63,
		ERR, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
		41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
	};
	const UInt8* buffp = reinterpret_cast<const UInt8*>(buff);
	const UInt8* buffpEnd = buffp + bytes;
	for ( ; buffp != buffpEnd; buffp++) {
		int num = tbl[*buffp];
		if (num >= 0) {
			_accum = (_accum << 6) + num;
		} else if (num == SPC) {
			continue;
		} else if (num == PAD) {
			_accum = (_accum << 6);
			_nPads++;
		} else if (num == ERR) {
			Error::Issue(ErrorType::FormatError, "invalid base64 format");
			return false;
		}
		_nCharsAccum++;
		if (_nCharsAccum == 4) {
			UInt8 buffOut[4];
			size_t bytesOut = 3 - _nPads;
			buffOut[0] = static_cast<UInt8>((_accum >> 16) & 0xff);
			buffOut[1] = static_cast<UInt8>((_accum >> 8) & 0xff);
			buffOut[2] = static_cast<UInt8>((_accum >> 0) & 0xff);
			if (bytesOut > 0 && !_pStreamOut->Write(buffOut, bytesOut)) return false;
			_nCharsAccum = 0, _nPads = 0, _accum = 0;
		}
	}
	return true;
}

bool Decoder::DecodeStream(Stream& streamSrc, size_t bytesUnit)
{
	RefPtr<Memory> pMemory(new MemoryHeap(bytesUnit));
	UInt8* buffWork = pMemory->GetPointer<UInt8>();
	size_t bytesRead;
	while ((bytesRead = streamSrc.Read(buffWork, bytesUnit)) > 0) {
		if (!Decode(buffWork, bytesRead)) break;
	}
	return !Error::IsIssued();
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

bool Encoder::EncodeStream(Stream& streamSrc, size_t bytesUnit)
{
	RefPtr<Memory> pMemory(new MemoryHeap(bytesUnit));
	UInt8* buffWork = pMemory->GetPointer<UInt8>();
	size_t bytesRead;
	while ((bytesRead = streamSrc.Read(buffWork, bytesUnit)) > 0) {
		if (!Encode(buffWork, bytesRead)) break;
	}
	return !Error::IsIssued();
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
