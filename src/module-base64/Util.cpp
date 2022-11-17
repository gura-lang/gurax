//==============================================================================
// Util.cpp
// Specification: https://tools.ietf.org/html/rfc4648
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(base64)

//------------------------------------------------------------------------------
// Info
//------------------------------------------------------------------------------
const Info Info::Base16 = {
	"base16",
	"0123456789ABCDEF", // charTbl
	{
		1	// nPaddings = 0
	},		// bytesOutTbl
	{
		1	// bytesAccum = 0
	},		// nPaddingsTbl
	1,		// bytesPerGroup
	2,		// nCharsPerGroup
	4,		// bitsPerChar
	76,		// nCharsPerLineDefault
};

const Info Info::Base32 = {
	"base32",
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ234567", // charTbl
	{
		5,	// nPaddings = 0
		4,	// nPaddings = 1
		0,	// nPaddings = 2 (invalid)
		3,	// nPaddings = 3
		2,	// nPaddings = 4
		0,	// nPaddings = 5 (invalid)
		1,	// nPaddings = 6
		0,	// nPaddings = 7 (invalid)
		0,	// nPaddings = 8 (invalid)
	},		// bytesOutTbl
	{
		0,	// bytesAccum = 0 (invalid)
		6,	// bytesAccum = 1
		4,	// bytesAccum = 2
		3,	// bytesAccum = 3
		1,	// bytesAccum = 4
		0,	// bytesAccum = 5
	},		// nPaddingsTbl
	5,		// bytesPerGroup
	8,		// nCharsPerGroup
	5,		// bitsPerChar
	64,		// nCharsPerLineDefault
};

const Info Info::Base32hex = {
	"base32hex",
	"0123456789ABCDEFGHIJKLMNOPQRSTUV", // charTbl
	{
		5,	// nPaddings = 0
		4,	// nPaddings = 1
		0,	// nPaddings = 2 (invalid)
		3,	// nPaddings = 3
		2,	// nPaddings = 4
		0,	// nPaddings = 5 (invalid)
		1,	// nPaddings = 6
		0,	// nPaddings = 7 (invalid)
		0,	// nPaddings = 8 (invalid)
	},		// bytesOutTbl
	{
		0,	// bytesAccum = 0 (invalid)
		6,	// bytesAccum = 1
		4,	// bytesAccum = 2
		3,	// bytesAccum = 3
		1,	// bytesAccum = 4
		0,	// bytesAccum = 5
	},		// nPaddingsTbl
	5,		// bytesPerGroup
	8,		// nCharsPerGroup
	5,		// bitsPerChar
	64,		// nCharsPerLineDefault
};

const Info Info::Base64 = {
	"base64",
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/", // charTbl
	{
		3,	// nPaddings = 0
		2,	// nPaddings = 1
		1,	// nPaddings = 2
		0,	// nPaddings = 3 (invalid)
	},		// bytesOutTbl
	{
		0,	// bytesAccum = 0 (invalid)
		2,	// bytesAccum = 1
		1,	// bytesAccum = 2
		0,	// bytesAccum = 3
	},		// nPaddingsTbl
	3,		// bytesPerGroup
	4,		// nCharsPerGroup
	6,		// bitsPerChar
	76,		// nCharsPerLineDefault
};

//------------------------------------------------------------------------------
// Decoder
//------------------------------------------------------------------------------
Decoder::Decoder(Stream* pStreamDst, const Info& info) :
	_pStreamDst(pStreamDst), _nCharsAccum(0), _nPaddings(0), _accum(0), _info(info)
{
	for (size_t i = 0; i < Gurax_ArraySizeOf(_numTbl); i++) _numTbl[i] = Code::Error;
	int num = 0;
	for (const UInt8* p = reinterpret_cast<const UInt8*>(_info.charTbl); *p; p++, num++) {
		_numTbl[*p] = num;
	}
	_numTbl['\n'] = _numTbl['\r'] = _numTbl['\t'] = _numTbl[' '] = Code::Space;
	_numTbl['='] = Code::Padding;
}

bool Decoder::Decode(const void* buff, size_t bytes)
{
	const UInt8* buffp = reinterpret_cast<const UInt8*>(buff);
	const UInt8* buffpEnd = buffp + bytes;
	for ( ; buffp != buffpEnd; buffp++) {
		int num = _numTbl[*buffp];
		if (num >= 0) {
			_accum = (_accum << _info.bitsPerChar) + num;
		} else if (num == Code::Space) {
			continue;
		} else if (num == Code::Padding) {
			_accum = (_accum << _info.bitsPerChar);
			_nPaddings++;
		} else if (num == Code::Error) {
			Error::Issue(ErrorType::FormatError, "invalid %s format", _info.name);
			return false;
		}
		_nCharsAccum++;
		if (_nCharsAccum == _info.nCharsPerGroup) {
			UInt8 buffOut[8];
			size_t bytesOut = _info.bytesOutTbl[_nPaddings];
			for (size_t i = 0; i < _info.bytesPerGroup; i++, _accum >>= 8) {
				buffOut[_info.bytesPerGroup - i - 1] = static_cast<UInt8>(_accum & 0xff);
			}
			if (bytesOut > 0 && !_pStreamDst->Write(buffOut, bytesOut)) return false;
			_nCharsAccum = 0, _nPaddings = 0, _accum = 0;
		}
	}
	return true;
}

bool Decoder::DecodeStream(Stream& streamSrc, size_t bytesUnit)
{
	RefPtr<Memory> pMemory(new MemoryHeap(bytesUnit));
	UInt8* buffWork = pMemory->GetPointerC<UInt8>();
	size_t bytesRead;
	while ((bytesRead = streamSrc.Read(buffWork, bytesUnit)) > 0) {
		if (!Decode(buffWork, bytesRead)) break;
	}
	return !Error::IsIssued();
}

bool Decoder::Decode(BinaryReferable& buffDst, const void* buff, size_t bytes, const Info& info)
{
	RefPtr<Stream> pStreamDst(new Stream_Binary(Stream::Flag::Writable, buffDst.Reference()));
	RefPtr<Decoder> pDecoder(new Decoder(pStreamDst->Reference(), info));
	return pDecoder->Decode(buff, bytes);
}

//------------------------------------------------------------------------------
// Encoder
//------------------------------------------------------------------------------
Encoder::Encoder(Stream* pStreamDst, int nCharsPerLine, const Info& info) :
	_pStreamDst(pStreamDst), _nCharsPerLine(CalcAlign(nCharsPerLine, info.nCharsPerGroup)),
	_iCol(0), _bytesAccum(0), _accum(0), _info(info)
{
}

bool Encoder::Encode(const void* buff, size_t bytes)
{
	UInt8 mask = (1 << _info.bitsPerChar) - 1;
	const UInt8* buffp = reinterpret_cast<const UInt8*>(buff);
	const UInt8* buffpEnd = buffp + bytes;
	for ( ; buffp != buffpEnd; buffp++) {
		_accum = (_accum << 8) + *buffp;
		_bytesAccum++;
		if (_bytesAccum == _info.bytesPerGroup) {
			char buffOut[16];
			for (size_t i = 0; i < _info.nCharsPerGroup; i++) {
				buffOut[_info.nCharsPerGroup - i - 1] = _info.charTbl[_accum & mask];
				_accum >>= _info.bitsPerChar;
			}
			_iCol += _info.nCharsPerGroup;
			size_t bytesOut = _info.nCharsPerGroup;
			if (_nCharsPerLine > 0 && _iCol >= _nCharsPerLine) {
				if (_pStreamDst->GetCodec().GetAddcrFlag()) buffOut[bytesOut++] = '\r';
				buffOut[bytesOut++] = '\n';
				_iCol = 0;
			}
			if (!_pStreamDst->Write(buffOut, bytesOut)) return false;
			_bytesAccum = 0, _accum = 0;
		}
	}
	return true;
}

bool Encoder::EncodeStream(Stream& streamSrc, size_t bytesUnit)
{
	RefPtr<Memory> pMemory(new MemoryHeap(bytesUnit));
	UInt8* buffWork = pMemory->GetPointerC<UInt8>();
	size_t bytesRead;
	while ((bytesRead = streamSrc.Read(buffWork, bytesUnit)) > 0) {
		if (!Encode(buffWork, bytesRead)) break;
	}
	return !Error::IsIssued();
}

bool Encoder::Finish()
{
	UInt8 mask = (1 << _info.bitsPerChar) - 1;
	char buffOut[16];
	size_t nCharsOut = 0;
	if (_bytesAccum > 0) {
		size_t nPaddings = _info.nPaddingsTbl[_bytesAccum];
		_accum <<= 8 * (_info.bytesPerGroup - _bytesAccum);
		size_t i = 0;
		for ( ; i < nPaddings; i++, _accum >>= _info.bitsPerChar) {
			buffOut[_info.nCharsPerGroup - i - 1] = '=';
		}
		for ( ; i < _info.nCharsPerGroup; i++, _accum >>= _info.bitsPerChar) {
			buffOut[_info.nCharsPerGroup - i - 1] = _info.charTbl[_accum & mask];
		}
		nCharsOut = _info.nCharsPerGroup;
		_iCol += nCharsOut;
	}
	if (_nCharsPerLine > 0 && _iCol > 0) {
		if (_pStreamDst->GetCodec().GetAddcrFlag()) buffOut[nCharsOut++] = '\r';
		buffOut[nCharsOut++] = '\n';
		_iCol = 0;
	}
	if (nCharsOut > 0 && !_pStreamDst->Write(buffOut, nCharsOut)) return false;
	_iCol = 0, _bytesAccum = 0, _accum = 0;
	return true;
}

//------------------------------------------------------------------------------
// Stream_Reader
//------------------------------------------------------------------------------
Stream_Reader::Stream_Reader(Stream* pStreamSrc, const Info& info) :
	Stream(Flag::Readable), _pStreamSrc(pStreamSrc),
	_pStreamMid(new Stream_Binary(Stream::Flag::Writable)),
	_pDecoder(new Decoder(_pStreamMid->Reference(), info)), _offsetMid(0)
{
}

size_t Stream_Reader::DoRead(void* buff, size_t bytes)
{
	UInt8* pBuff = reinterpret_cast<UInt8*>(buff);
	size_t bytesOut = 0;
	Binary& buffMid = _pStreamMid->GetBuff();
	while (bytesOut < bytes) {
		if (_offsetMid >= buffMid.size()) {
			UInt8 buffRead[1024];
			size_t bytesRead = _pStreamSrc->Read(buffRead, sizeof(buffRead));
			_pStreamMid->ClearBuff();
			if (!_pDecoder->Decode(buffRead, bytesRead) || buffMid.empty()) break;
			_offsetMid = 0;
		}
		size_t bytesCopy = std::min(buffMid.size() - _offsetMid, bytes - bytesOut);
		::memcpy(pBuff + bytesOut, buffMid.data() + _offsetMid, bytesCopy);
		bytesOut += bytesCopy;
		_offsetMid += bytesCopy;
	}
	return bytesOut;
}

//------------------------------------------------------------------------------
// Stream_Writer
//------------------------------------------------------------------------------
Stream_Writer::Stream_Writer(Stream* pStreamDst, size_t nCharsPerLine, const Info& info) :
	Stream(Flag::Writable), _pEncoder(new Encoder(pStreamDst, nCharsPerLine, info))
{
}

Gurax_EndModuleScope(base64)
