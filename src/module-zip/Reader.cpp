//==============================================================================
// Reader.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(zip)

//------------------------------------------------------------------------------
// Reader
//------------------------------------------------------------------------------
bool Reader::ReadDirectory()
{
#if 0
	Signal &sig = env.GetSignal();
	if (!_pStreamSrc->IsBwdSeekable()) {
		Stream *pStreamPrefetch = Stream::Prefetch(env, _pStreamSrc.release(), true);
		if (sig.IsSignalled()) return false;
		_pStreamSrc.reset(pStreamPrefetch);
	}
	UInt32 offsetCentralDirectory = SeekCentralDirectory(sig, _pStreamSrc.get());
	if (sig.IsSignalled()) return false;
	if (!_pStreamSrc->Seek(sig, offsetCentralDirectory, Stream::SeekSet)) return false;
	UInt32 signature;
	while (ReadStream(sig, *_pStreamSrc, &signature)) {
		//::printf("%08x\n", signature);
		if (signature == LocalFileHeader::Signature) {
			LocalFileHeader hdr;
			if (!hdr.Read(sig, *_pStreamSrc)) return false;
			if (!hdr.SkipFileData(sig, *_pStreamSrc)) return false;
		} else if (signature == ArchiveExtraDataRecord::Signature) {
			ArchiveExtraDataRecord record;
			if (!record.Read(sig, *_pStreamSrc)) return false;
		} else if (signature == CentralFileHeader::Signature) {
			CentralFileHeader *pHdr = new CentralFileHeader();
			if (!pHdr->Read(sig, *_pStreamSrc)) {
				delete pHdr;
				return false;
			}
			_hdrList.push_back(pHdr);
		} else if (signature == DigitalSignature::Signature) {
			DigitalSignature signature;
			if (!signature.Read(sig, *_pStreamSrc)) return false;
		} else if (signature == Zip64EndOfCentralDirectory::Signature) {
			Zip64EndOfCentralDirectory dir;
			if (!dir.Read(sig, *_pStreamSrc)) return false;
		} else if (signature == Zip64EndOfCentralDirectoryLocator::Signature) {
			Zip64EndOfCentralDirectoryLocator loc;
			if (!loc.Read(sig, *_pStreamSrc)) return false;
		} else if (signature == EndOfCentralDirectoryRecord::Signature) {
			EndOfCentralDirectoryRecord record;
			if (!record.Read(sig, *_pStreamSrc)) return false;
			break;
		} else {
			sig.SetError(ERR_FormatError, "unknown signature %08x", signature);
			return false;
		}
	}
#endif
	return true;
}

String Reader::ToString(const StringStyle& ss) const
{
	return "Reader";
}

Gurax_EndModuleScope(zip)
