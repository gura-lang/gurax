//==============================================================================
// Reader.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(tar)

//------------------------------------------------------------------------------
// Reader
//------------------------------------------------------------------------------
String Reader::ToString(const StringStyle& ss) const
{
	return String().Format("tar.Reader");
}

//------------------------------------------------------------------------------
// Iterator_Entry
//------------------------------------------------------------------------------
Iterator_Entry::Iterator_Entry(Reader* pReader, bool skipDirFlag) :
	_doneFlag(false), _pReader(pReader), _skipDirFlag(skipDirFlag),
	_offsetNext(pReader->GetStreamSrc().GetOffset())
{}

Value* Iterator_Entry::DoNextValue()
{
	if (_doneFlag) return nullptr;
	Stream& streamSrc = _pReader->GetStreamSrc();
	RefPtr<StatEx> pStatEx;
	do {
		streamSrc.Seek(_offsetNext, Stream::SeekMode::Set);
		pStatEx.reset(StatEx::ReadDirectory(streamSrc));
		if (!pStatEx) {
			_doneFlag = true;
			return nullptr;
		}
		_offsetNext = streamSrc.GetOffset() + pStatEx->GetHeader().CalcBlocks() * Header::BLOCKSIZE;
	} while (_skipDirFlag && pStatEx->IsDir());
	RefPtr<Stream> pStream(Stream_Reader::Create(streamSrc, *pStatEx));
	if (!pStream) {
		_doneFlag = true;
		return nullptr;
	}
	return new Value_Stream(pStream.release());
}

String Iterator_Entry::ToString(const StringStyle& ss) const
{
	return "tar.Entry";
}

Gurax_EndModuleScope(tar)
