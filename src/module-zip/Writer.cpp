//==============================================================================
// Writer.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(zip)

//------------------------------------------------------------------------------
// Writer
//------------------------------------------------------------------------------
Writer::GzipInfo Writer::gzipInfo;
Writer::Bzip2Info Writer::bzip2Info;

Writer::~Writer()
{
	Finish();
}

bool Writer::Add(Stream& streamSrc, const char* fileName, UInt16 compressionMethod, RefPtr<DateTime> pDateTime)
{
	const size_t bytesThreshold = 256;
	RefPtr<Stat> pStat(streamSrc.CreateStat());
	if (!pDateTime) {
		pDateTime.reset(pStat? pStat->GetDateTimeM().Reference() : OAL::CreateDateTimeCur(false));
	}
	if (pStat && (pStat->GetBytes() < bytesThreshold)) compressionMethod = CompressionMethod::Store;
	if (!AddParentFolders(fileName, *pDateTime)) return false;
	UInt16 version = (0 << 8) | (2 * 10 + 0);	// MS-DOS, 2.0
	UInt16 generalPurposeBitFlag = (1 << 3);	// ExistDataDescriptor
	UInt16 lastModFileTime = GetDosTime(*pDateTime);
	UInt16 lastModFileDate = GetDosDate(*pDateTime);
	UInt16 internalFileAttributes = 0;
	UInt32 externalFileAttributes = (1 << 5);
	UInt32 relativeOffsetOfLocalHeader = static_cast<UInt32>(_pStreamDst->GetOffset());
	std::unique_ptr<CentralFileHeader> pCentralFileHeader(new CentralFileHeader());
	do {
		CentralFileHeader::Fields& fields = pCentralFileHeader->GetFields();
		Gurax_PackUInt16(fields.VersionMadeBy,					version);
		Gurax_PackUInt16(fields.VersionNeededToExtract,			version);
		Gurax_PackUInt16(fields.GeneralPurposeBitFlag,			generalPurposeBitFlag);
		Gurax_PackUInt16(fields.CompressionMethod,				compressionMethod);
		Gurax_PackUInt16(fields.LastModFileTime,				lastModFileTime);
		Gurax_PackUInt16(fields.LastModFileDate,				lastModFileDate);
		Gurax_PackUInt32(fields.Crc32,							0x00000000);
		Gurax_PackUInt32(fields.CompressedSize,					0);
		Gurax_PackUInt32(fields.UncompressedSize,				0);
		Gurax_PackUInt16(fields.FileNameLength,					::strlen(fileName));
		Gurax_PackUInt16(fields.ExtraFieldLength,				0x0000);
		Gurax_PackUInt16(fields.FileCommentLength,				0x0000);
		Gurax_PackUInt16(fields.DiskNumberStart,				0x0000);
		Gurax_PackUInt16(fields.InternalFileAttributes,			internalFileAttributes);
		Gurax_PackUInt32(fields.ExternalFileAttributes,			externalFileAttributes);
		Gurax_PackUInt32(fields.RelativeOffsetOfLocalHeader,	relativeOffsetOfLocalHeader);
		pCentralFileHeader->SetFileName(fileName);
		if (!pCentralFileHeader->WriteAsLocalFileHeader(*_pStreamDst)) return false;
	} while (0);
	RefPtr<Stream> pStreamContent;
	size_t offsetDst = _pStreamDst->GetOffset();
	size_t offsetSrc = streamSrc.GetOffset();
	if (compressionMethod == CompressionMethod::Store) {
		pStreamContent.reset(_pStreamDst->Reference());
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
		const GzipInfo& v = gzipInfo;
		RefPtr<ZLib::Stream_Writer> pStream(new ZLib::Stream_Writer(_pStreamDst->Reference()));
		if (!pStream->Initialize(v.level, v.windowBits, v.memLevel, v.strategy)) return false;
		pStreamContent.reset(pStream.release());
	} else if (compressionMethod == CompressionMethod::Deflate64) {
		// unsupported
	} else if (compressionMethod == CompressionMethod::PKWARE) {
		// unsupported
	} else if (compressionMethod == CompressionMethod::BZIP2) {
		const Bzip2Info& v = bzip2Info;
		RefPtr<BZLib::Stream_Writer> pStream(new BZLib::Stream_Writer(_pStreamDst->Reference()));
		if (!pStream->Initialize(v.blockSize100k, v.verbosity, v.workFactor)) return false;
		pStreamContent.reset(pStream.release());
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
	if (!pStreamContent) {
		Error::Issue(ErrorType::FormatError, "unsupported compression method %d", compressionMethod);
		return false;
	}
	CRC32 crc32;
	RefPtr<Memory> pMemory(new MemoryHeap(32768));
	void* buff = pMemory->GetPointerC<void>();
	for (;;) {
		size_t bytesRead = streamSrc.Read(buff, pMemory->GetBytes());
		if (Error::IsIssued()) break;
		if (bytesRead == 0) break;
		crc32.Update(buff, bytesRead);
		pStreamContent->Write(buff, bytesRead);
		if (Error::IsIssued()) break;
	}
	pStreamContent.reset(nullptr);	// don't use Stream::Close() as pStreamContent may hold
									// a reference to _pStreamDst
	if (Error::IsIssued()) return false;
	UInt32 crc32num = crc32.GetResult();
	UInt32 compressedSize = static_cast<UInt32>(_pStreamDst->GetOffset() - offsetDst);
	UInt32 uncompressedSize = static_cast<UInt32>(streamSrc.GetOffset() - offsetSrc);
	do {
		DataDescriptor desc;
		DataDescriptor::Fields& fields = desc.GetFields();
		Gurax_PackUInt32(fields.Crc32,				crc32num);
		Gurax_PackUInt32(fields.CompressedSize,		compressedSize);
		Gurax_PackUInt32(fields.UncompressedSize,	uncompressedSize);
		if (!desc.Write(*_pStreamDst)) return false;
	} while (0);
	do {
		CentralFileHeader::Fields& fields = pCentralFileHeader->GetFields();
		Gurax_PackUInt32(fields.Crc32,				crc32num);
		Gurax_PackUInt32(fields.CompressedSize,		compressedSize);
		Gurax_PackUInt32(fields.UncompressedSize,	uncompressedSize);
	} while (0);
	if (pCentralFileHeader->IsFolder()) {
		_statExOwner_Folder.push_back(new StatEx(pCentralFileHeader.release()));
	} else {
		_statExOwner_File.push_back(new StatEx(pCentralFileHeader.release()));
	}
	return true;
}

bool Writer::AddParentFolders(const char* fileName, const DateTime& dateTime)
{
	UInt16 version = (0 << 8) | (2 * 10 + 0);	// MS-DOS, 2.0
	UInt16 generalPurposeBitFlag = (1 << 3);	// ExistDataDescriptor
	UInt16 compressionMethod = CompressionMethod::Store;
	UInt32 compressedSize = 0;
	UInt32 uncompressedSize = 0;
	UInt16 lastModFileTime = GetDosTime(dateTime);
	UInt16 lastModFileDate = GetDosDate(dateTime);
	UInt16 internalFileAttributes = 0;
	UInt32 externalFileAttributes = (1 << 5);
	UInt32 relativeOffsetOfLocalHeader = static_cast<UInt32>(_pStreamDst->GetOffset());
	String fileNameAccum;
	for (const char* p = fileName; *p; ) {
		if (*p == '\0') {
			// nothing to do
		} else if (PathName::IsSep(*p)) {
			fileNameAccum += *p++;
		} else {
			fileNameAccum += *p++;
			continue;
		}
		if (*p == '\0') break;
		if (_statExOwner_Folder.FindByName(fileNameAccum.c_str())) continue;
		std::unique_ptr<CentralFileHeader> pCentralFileHeader(new CentralFileHeader());
		do {
			CentralFileHeader::Fields& fields = pCentralFileHeader->GetFields();
			Gurax_PackUInt16(fields.VersionMadeBy,					version);
			Gurax_PackUInt16(fields.VersionNeededToExtract,			version);
			Gurax_PackUInt16(fields.GeneralPurposeBitFlag,			generalPurposeBitFlag);
			Gurax_PackUInt16(fields.CompressionMethod,				compressionMethod);
			Gurax_PackUInt16(fields.LastModFileTime,				lastModFileTime);
			Gurax_PackUInt16(fields.LastModFileDate,				lastModFileDate);
			Gurax_PackUInt32(fields.Crc32,							0x00000000);
			Gurax_PackUInt32(fields.CompressedSize,					compressedSize);
			Gurax_PackUInt32(fields.UncompressedSize,				uncompressedSize);
			Gurax_PackUInt16(fields.FileNameLength,					static_cast<UInt16>(fileNameAccum.size()));
			Gurax_PackUInt16(fields.ExtraFieldLength,				0x0000);
			Gurax_PackUInt16(fields.FileCommentLength,				0x0000);
			Gurax_PackUInt16(fields.DiskNumberStart,				0x0000);
			Gurax_PackUInt16(fields.InternalFileAttributes,			internalFileAttributes);
			Gurax_PackUInt32(fields.ExternalFileAttributes,			externalFileAttributes);
			Gurax_PackUInt32(fields.RelativeOffsetOfLocalHeader,	relativeOffsetOfLocalHeader);
			pCentralFileHeader->SetFileName(fileNameAccum.c_str());
			if (!pCentralFileHeader->WriteAsLocalFileHeader(*_pStreamDst)) return false;
		} while (0);
		UInt32 crc32num = 0x00000000;
		do {
			DataDescriptor desc;
			DataDescriptor::Fields &fields = desc.GetFields();
			Gurax_PackUInt32(fields.Crc32,				crc32num);
			Gurax_PackUInt32(fields.CompressedSize,		compressedSize);
			Gurax_PackUInt32(fields.UncompressedSize,	uncompressedSize);
			if (!desc.Write(*_pStreamDst)) return false;
		} while (0);
		do {
			CentralFileHeader::Fields &fields = pCentralFileHeader->GetFields();
			Gurax_PackUInt32(fields.Crc32,				crc32num);
			Gurax_PackUInt32(fields.CompressedSize,		compressedSize);
			Gurax_PackUInt32(fields.UncompressedSize,	uncompressedSize);
		} while (0);
		_statExOwner_Folder.push_back(new StatEx(pCentralFileHeader.release()));
	}
	return true;
}
	
bool Writer::Finish()
{
	if (!_pStreamDst) return true;
	size_t offset = _pStreamDst->GetOffset();
	if (!_statExOwner_Folder.Write(*_pStreamDst)) return false;
	if (!_statExOwner_File.Write(*_pStreamDst)) return false;
	UInt32 offsetOfCentralDirectory = static_cast<UInt32>(offset);
	UInt32 sizeOfTheCentralDirectory = static_cast<UInt32>(_pStreamDst->GetOffset() - offset);
	UInt16 nCentralFileHeaders = static_cast<UInt16>(_statExOwner_Folder.size() + _statExOwner_File.size());
	do {
		EndOfCentralDirectoryRecord rec;
		EndOfCentralDirectoryRecord::Fields &fields = rec.GetFields();
		Gurax_PackUInt16(fields.NumberOfThisDisk,										0x0000);
		Gurax_PackUInt16(fields.NumberOfTheDiskWithTheStartOfTheCentralDirectory,		0x0000);
		Gurax_PackUInt16(fields.TotalNumberOfEntriesInTheCentralDirectoryOnThisDisk,	nCentralFileHeaders);
		Gurax_PackUInt16(fields.TotalNumberOfEntriesInTheCentralDirectory,				nCentralFileHeaders);
		Gurax_PackUInt32(fields.SizeOfTheCentralDirectory,								sizeOfTheCentralDirectory);
		Gurax_PackUInt32(fields.OffsetOfStartOfCentralDirectoryWithRespectToTheStartingDiskNumber,
																						offsetOfCentralDirectory);
		Gurax_PackUInt16(fields.ZIPFileCommentLength,									0x0000);
		if (!rec.Write(*_pStreamDst)) return false;
	} while (0);
	_pStreamDst->Close();
	_pStreamDst.reset(nullptr);
	return !Error::IsIssued();
}

String Writer::ToString(const StringStyle& ss) const
{
	return "Writer";
}

Gurax_EndModuleScope(zip)
