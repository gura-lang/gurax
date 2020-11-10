//==============================================================================
// PathExtention.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(curl)

#if 0
//------------------------------------------------------------------------------
// PathMgrEx
//------------------------------------------------------------------------------
bool PathMgrEx::IsResponsible(Directory* pDirectoryParent, const char* pathName)
{
	return !pDirectoryParent &&
		(String::StartsWith<CharCase>(pDirectoryParent->GetName(), "http:") ||
		 String::StartsWith<CharCase>(pDirectoryParent->GetName(), "https:") ||
		 String::StartsWith<CharCase>(pDirectoryParent->GetName(), "ftp:") ||
		 String::StartsWith<CharCase>(pDirectoryParent->GetName(), "ftps:"));
}

Directory* PathMgrEx::DoOpenDirectory(Directory* pDirectoryParent, const char** pPathName, Directory::Type typeWouldBe)
{
	const char* pathName = *pPathName;
	if (!pDirectoryParent) return nullptr;
	RefPtr<Stream> pStream(pDirectoryParent->OpenStream(Stream::OpenFlag::Read));
	if (!pStream) return nullptr;
	pStream.reset(pStream->CreateBwdSeekable());
	if (!pStream) return nullptr;
	RefPtr<Directory> pDirectory(DirectoryEx::CreateTop(*pStream));
	if (!pDirectory) return nullptr;
	pDirectory->SetDirectoryParent(Directory::Reference(pDirectoryParent));
	Directory* pDirectoryFound = (**pPathName == '\0')? pDirectory.get() : pDirectory->SearchInTree(pPathName);
	if (!pDirectoryFound) {
		Error::Issue(ErrorType::PathError, "specified path is not found: %s", pathName);
		return nullptr;
	}
	return pDirectoryFound->Reference();
}

PathMgr::Existence PathMgrEx::DoCheckExistence(Directory* pDirectoryParent, const char** pPathName)
{
	RefPtr<Directory> pDirectory(DoOpenDirectory(pDirectoryParent, pPathName, Directory::Type::None));
	Error::Clear();
	return pDirectory? Existence::Exist : Existence::None;
}

//------------------------------------------------------------------------------
// StatEx
//------------------------------------------------------------------------------
StatEx::StatEx(CentralFileHeader* pCentralFileHeader) :
	Stat(pCentralFileHeader->MakeLastModDateTime(), pCentralFileHeader->GetFileName(),
		 pCentralFileHeader->IsFolder()? Flag::Dir : Flag::Reg,
		 0666, pCentralFileHeader->GetUncompressedSize(), 0, 0),
	_pCentralFileHeader(pCentralFileHeader)
{
}

String StatEx::ToString(const StringStyle& ss) const
{
	String str = Stat::ToString(ss);
	str += ":curl";
	str += ":";
	const Symbol* pSymbol = CompressionMethodToSymbol(_pCentralFileHeader->GetCompressionMethod());
	str += pSymbol->GetName();
	return str;
}

//------------------------------------------------------------------------------
// StatExList
//------------------------------------------------------------------------------
StatEx* StatExList::FindByName(const char* fileName) const
{
	PathName pathName(fileName);
	for (StatEx* pStatEx : *this) {
		if (pathName.DoesMatch(pStatEx->GetCentralFileHeader().GetFileName())) return pStatEx;
	}
	return nullptr;
}

bool StatExList::Write(Stream& streamDst) const
{
	for (StatEx* pStatEx : *this) {
		if (!pStatEx->GetCentralFileHeader().Write(streamDst)) return false;
	}
	return true;
}

//------------------------------------------------------------------------------
// StatExOwner
//------------------------------------------------------------------------------
void StatExOwner::Clear()
{
	for (StatEx* pStatEx : *this) StatEx::Delete(pStatEx);
	clear();
}

bool StatExOwner::ReadCentralDirectory(Stream& streamSrc)
{
	UInt32 offsetCentralDirectory = SeekCentralDirectory(streamSrc);
	if (Error::IsIssued()) return false;
	if (!streamSrc.SetOffset(offsetCentralDirectory)) return false;
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
			std::unique_ptr<CentralFileHeader> pCentralFileHeader(new CentralFileHeader());
			if (!pCentralFileHeader->Read(streamSrc)) return false;
			push_back(new StatEx(pCentralFileHeader.release()));
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

//-----------------------------------------------------------------------------
// DirectoryEx
//-----------------------------------------------------------------------------
Directory* DirectoryEx::CreateTop(Stream& streamSrc)
{
	RefPtr<DirectoryEx> pDirectoryEx(
		new DirectoryEx(new CoreEx(Type::Boundary, streamSrc.Reference(), nullptr)));
	return pDirectoryEx->ReadCentralDirectory()? pDirectoryEx.release() : nullptr;
}

bool DirectoryEx::ReadCentralDirectory()
{
	StatExOwner statExOwner;
	if (!statExOwner.ReadCentralDirectory(GetStreamSrc())) return false;
	for (StatEx* pStatEx : statExOwner) {
		const char* pathName = pStatEx->GetCentralFileHeader().GetFileName();
		Type type = String::EndsWithPathSep(pathName)? Type::Folder : Type::Item;
		GetCoreEx().AddChildInTree(pathName, new CoreEx(type, GetStreamSrc().Reference(), pStatEx->Reference()));
		//pStatEx->GetCentralFileHeader().Print(*Stream::COut);
	}
	//GetCoreEx().Print(*Stream::COut);
	return true;
}

void DirectoryEx::DoRewindChild()
{
	_idxChild = 0;
}

Directory* DirectoryEx::DoNextChild()
{
	CoreOwner& coreOwner = GetCoreEx().GetCoreOwner();
	if (_idxChild >= coreOwner.size()) return nullptr;
	RefPtr<Directory> pDirectory(new DirectoryEx(dynamic_cast<CoreEx*>(coreOwner[_idxChild++]->Reference())));
	pDirectory->SetDirectoryParent(Reference());
	return pDirectory.release();
}

Stream* DirectoryEx::DoOpenStream(Stream::OpenFlags openFlags)
{
	if (openFlags & (Stream::OpenFlag::Write | Stream::OpenFlag::Append)) return nullptr;
	StatEx* pStatEx = GetCoreEx().GetStatEx();
	return pStatEx? Stream_Reader::Create(GetStreamSrc(), *pStatEx) : nullptr;
}

Value_Stat* DirectoryEx::DoCreateStatValue()
{
	StatEx* pStatEx = GetCoreEx().GetStatEx();
	return pStatEx? new Value_StatEx(pStatEx->Reference()) : nullptr;
}

//-----------------------------------------------------------------------------
// Stream_Reader
//-----------------------------------------------------------------------------
Stream_Reader::Stream_Reader(Stream* pStreamSrc, StatEx* pStatEx) :
	Stream(Flag::Readable), _pStreamSrc(pStreamSrc), _pStatEx(pStatEx),
	_name(pStatEx->GetCentralFileHeader().GetFileName()),
	_bytesUncompressed(pStatEx->GetCentralFileHeader().GetUncompressedSize()),
	_bytesCompressed(pStatEx->GetCentralFileHeader().GetCompressedSize()),
	_crc32Expected(pStatEx->GetCentralFileHeader().GetCrc32()),
	_seekedFlag(false)
{
}

Stream* Stream_Reader::Create(Stream& streamSrc, const StatEx& statEx)
{
	const CentralFileHeader& hdr = statEx.GetCentralFileHeader();
	size_t offset = hdr.GetRelativeOffsetOfLocalHeader();
	streamSrc.SetOffset(offset);
	if (Error::IsIssued()) return nullptr;
	do {
		UInt32 signature;
		if (!ReadStream(streamSrc, &signature)) return nullptr;
		if (signature != LocalFileHeader::Signature) {
			Error::Issue(ErrorType::FormatError, "invalid ZIP format");
			return nullptr;
		}
		LocalFileHeader hdr;
		if (!hdr.Read(streamSrc)) return nullptr;
	} while (0);
	UInt16 compressionMethod = hdr.GetCompressionMethod();
	RefPtr<Stream_Reader> pStream;
	if (compressionMethod == CompressionMethod::Store) {
		pStream.reset(new Stream_Reader_Store(streamSrc.Reference(), statEx.Reference()));
	} else if (compressionMethod == CompressionMethod::Shrink) {
		// unsupported
	} else if (compressionMethod == CompressionMethod::Factor1) {
		// unsupported
	} else if (compressionMethod == CompressionMethod::Factor2) {
		// unsupported
	} else if (compressionMethod == CompressionMethod::Factor3) {
		// unsupported
	} else if (compressionMethod == CompressionMethod::Factor4) {
		// unsupported
	} else if (compressionMethod == CompressionMethod::Implode) {
		// unsupported
	} else if (compressionMethod == CompressionMethod::Factor1) {
		// unsupported
	} else if (compressionMethod == CompressionMethod::Deflate) {
		pStream.reset(new Stream_Reader_Deflate(streamSrc.Reference(), statEx.Reference()));
	} else if (compressionMethod == CompressionMethod::Deflate64) {
		pStream.reset(new Stream_Reader_Deflate64(streamSrc.Reference(), statEx.Reference()));
	} else if (compressionMethod == CompressionMethod::PKWARE) {
		// unsupported
	} else if (compressionMethod == CompressionMethod::BZIP2) {
		pStream.reset(new Stream_Reader_BZIP2(streamSrc.Reference(), statEx.Reference()));
	} else if (compressionMethod == CompressionMethod::LZMA) {
		// unsupported
	} else if (compressionMethod == CompressionMethod::TERSA) {
		// unsupported
	} else if (compressionMethod == CompressionMethod::LZ77) {
		// unsupported
	} else if (compressionMethod == CompressionMethod::WavPack) {
		// unsupported
	} else if (compressionMethod == CompressionMethod::PPMd) {
		// unsupported
	}
	if (!pStream) {
		Error::Issue(ErrorType::FormatError, "unsupported compression method %d", compressionMethod);
		return nullptr;
	}
	if (!pStream->Initialize()) return nullptr;
	return pStream.release();
}

size_t Stream_Reader::CheckCRC32(const void* buff, size_t bytesRead)
{
	if (_seekedFlag) return bytesRead;
	_crc32.Update(buff, bytesRead);
	if (bytesRead == 0 && _crc32Expected != _crc32.GetResult()) {
		Error::Issue(ErrorType::FormatError, "CRC error");
		return 0;
	}
	return bytesRead;
}

Value_Stat* Stream_Reader::DoCreateStatValue()
{
	return new Value_StatEx(_pStatEx->Reference());
}

#endif

Gurax_EndModuleScope(curl)
