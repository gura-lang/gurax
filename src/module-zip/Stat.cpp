//==============================================================================
// Stat.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(zip)

//------------------------------------------------------------------------------
// Stat
//------------------------------------------------------------------------------
String Stat::ToString(const StringStyle& ss) const
{
	return "Stat";
}

//------------------------------------------------------------------------------
// StatList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// StatOwner
//------------------------------------------------------------------------------
void StatOwner::Clear()
{
	for (Stat* pStat : *this) Stat::Delete(pStat);
	clear();
}

bool StatOwner::ReadCentralDirectory(Stream& streamSrc)
{
	UInt32 offsetCentralDirectory = SeekCentralDirectory(streamSrc);
	if (Error::IsIssued()) return false;
	if (!streamSrc.Seek(offsetCentralDirectory, Stream::SeekMode::Set)) return false;
	UInt32 signature;
	while (ReadStream(streamSrc, &signature)) {
		//::printf("%08x\n", signature);
		if (signature == LocalFileHeader::Signature) {
			LocalFileHeader hdr;
			if (!hdr.Read(streamSrc)) return false;
			if (!hdr.SkipFileData(streamSrc)) return false;
		} else if (signature == ArchiveExtraDataRecord::Signature) {
			ArchiveExtraDataRecord record;
			if (!record.Read(streamSrc)) return false;
		} else if (signature == CentralFileHeader::Signature) {
			RefPtr<Stat> pStat(new Stat());
			if (!pStat->GetCentralFileHeader().Read(streamSrc)) return false;
			push_back(pStat.release());
		} else if (signature == DigitalSignature::Signature) {
			DigitalSignature signature;
			if (!signature.Read(streamSrc)) return false;
		} else if (signature == Zip64EndOfCentralDirectory::Signature) {
			Zip64EndOfCentralDirectory dir;
			if (!dir.Read(streamSrc)) return false;
		} else if (signature == Zip64EndOfCentralDirectoryLocator::Signature) {
			Zip64EndOfCentralDirectoryLocator loc;
			if (!loc.Read(streamSrc)) return false;
		} else if (signature == EndOfCentralDirectoryRecord::Signature) {
			EndOfCentralDirectoryRecord record;
			if (!record.Read(streamSrc)) return false;
			break;
		} else {
			Error::Issue(ErrorType::FormatError, "unknown signature %08x", signature);
			return false;
		}
	}
	return true;
}

Gurax_EndModuleScope(zip)
