//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(base64)

//------------------------------------------------------------------------------
// Decoder
//------------------------------------------------------------------------------
const Decoder::Info Decoder::info_Base16 = {
	"base16",
	{
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,SPC,SPC,ERR,ERR,SPC,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		SPC,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR, 26, 27, 28, 29, 30, 31,ERR,ERR,ERR,ERR,ERR,PAD,ERR,ERR,
		ERR,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
		15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
	},	// numTbl
	{
	},	// bytesOutTbl
	1,	// bytesPerGroup
	2,	// nCharsPerGroup
	4,	// bitsPerChar
};

const Decoder::Info Decoder::info_Base32 = {
	"base32",
	{
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,SPC,SPC,ERR,ERR,SPC,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		SPC,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR, 26, 27, 28, 29, 30, 31,ERR,ERR,ERR,ERR,ERR,PAD,ERR,ERR,
		ERR,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
		15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
	},	// numTbl
	{
		5,	// padding = 0
		4,	// padding = 1
		0,	// padding = 2 (invalid)
		3,	// padding = 3
		2,	// padding = 4
		0,	// padding = 5 (invalid)
		1,	// padding = 6
		0,	// padding = 7 (invalid)
		0,	// padding = 8 (invalid)
	},	// bytesOutTbl
	5,	// bytesPerGroup
	8,	// nCharsPerGroup
	5,	// bitsPerChar
};

const Decoder::Info Decoder::info_Base32hex = {
	"base32hex",
	{
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,SPC,SPC,ERR,ERR,SPC,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		SPC,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR, 26, 27, 28, 29, 30, 31,ERR,ERR,ERR,ERR,ERR,PAD,ERR,ERR,
		ERR,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
		15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
		ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,
	},	// numTbl
	{
		5,	// padding = 0
		4,	// padding = 1
		0,	// padding = 2 (invalid)
		3,	// padding = 3
		2,	// padding = 4
		0,	// padding = 5 (invalid)
		1,	// padding = 6
		0,	// padding = 7 (invalid)
		0,	// padding = 8 (invalid)
	},	// bytesOutTbl
	5,	// bytesPerGroup
	8,	// nCharsPerGroup
	5,	// bitsPerChar
};

const Decoder::Info Decoder::info_Base64 = {
	"base64",
	{
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
	},	// numTbl
	{
		3,	// padding = 0
		2,	// padding = 1
		1,	// padding = 2
		0,	// padding = 3 (invalid)
	},	// bytesOutTbl
	3,	// bytesPerGroup
	4,	// nCharsPerGroup
	6,	// bitsPerChar
};

Decoder::Decoder(Stream* pStreamOut, const Info& info) :
	_pStreamOut(pStreamOut), _nCharsAccum(0), _nPads(0), _accum(0), _info(info)
{
}

bool Decoder::Decode(const void* buff, size_t bytes)
{
	const UInt8* buffp = reinterpret_cast<const UInt8*>(buff);
	const UInt8* buffpEnd = buffp + bytes;
	for ( ; buffp != buffpEnd; buffp++) {
		int num = _info.numTbl[*buffp];
		if (num >= 0) {
			_accum = (_accum << _info.bitsPerChar) + num;
		} else if (num == SPC) {
			continue;
		} else if (num == PAD) {
			_accum = (_accum << _info.bitsPerChar);
			_nPads++;
		} else if (num == ERR) {
			Error::Issue(ErrorType::FormatError, "invalid %s format", _info.name);
			return false;
		}
		_nCharsAccum++;
		if (_nCharsAccum == _info.nCharsPerGroup) {
			UInt8 buffOut[8];
			size_t bytesOut = _info.bytesOutTbl[_nPads];
			for (size_t i = 0; i < _info.bytesPerGroup; i++, _accum >>= 8) {
				buffOut[_info.bytesPerGroup - i - 1] = static_cast<UInt8>(_accum & 0xff);
			}
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

const int bytesOutTbl[] = {
	3,	// padding = 0
	2,	// padding = 1
	1,	// padding = 2
	0,	// padding = 3 (invalid)
};	// bytesOutTbl
size_t bytesPerGroup = 3;	// bytesPerGroup
size_t nCharsPerGroup = 4;	// nCharsPerGroup
size_t bitsPerChar = 6;		// bitsPerChar
UInt8 mask = 0x3f;

bool Encoder::Encode(const void* buff, size_t bytes)
{
	const UInt8* buffp = reinterpret_cast<const UInt8*>(buff);
	const UInt8* buffpEnd = buffp + bytes;
	for ( ; buffp != buffpEnd; buffp++) {
		_accum = (_accum << 8) + *buffp;
		_bytesAccum++;
		if (_bytesAccum == bytesPerGroup) {
			// 00000000 aaaaaabb bbbbcccc ccdddddd
			char buffOut[16];
			for (size_t i = 0; i < nCharsPerGroup; i++) {
				buffOut[nCharsPerGroup - i - 1] = _charTbl[_accum & mask];
				_accum >>= bitsPerChar;
			}
			// buffOut[bytesOut++] = _charTbl[(_accum >> 18) & 0x3f];
			// buffOut[bytesOut++] = _charTbl[(_accum >> 12) & 0x3f];
			// buffOut[bytesOut++] = _charTbl[(_accum >> 6) & 0x3f];
			// buffOut[bytesOut++] = _charTbl[(_accum >> 0) & 0x3f];
			_nCharsOut += nCharsPerGroup;
			size_t bytesOut = nCharsPerGroup;
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
#if 0
	size_t bytesOut = bytesOutTbl[_bytesAccum];
#endif	
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
