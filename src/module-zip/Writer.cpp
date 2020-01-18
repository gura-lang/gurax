//==============================================================================
// Writer.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(zip)

//------------------------------------------------------------------------------
// Writer
//------------------------------------------------------------------------------
bool Writer::Add(Stream& streamSrc, const char* fileName, UInt16 compressionMethod)
{
	const int memLevel = 8;
	//_statExOwner.push_back(pStatEx);
	UInt16 version = (0 << 8) | (2 * 10 + 0);	// MS-DOS, 2.0
	UInt16 generalPurposeBitFlag = (1 << 3);	// ExistDataDescriptor
	RefPtr<DateTime> pDateTime;
	RefPtr<Stat> pStat(streamSrc.CreateStat());
	if (pStat) {
		pDateTime.reset(pStat->GetDateTimeM().Reference());
	} else {
		pDateTime.reset();
	}
#if 0
	Stream::Attribute attr;
	if (streamSrc.GetExtribute(attr)) {
		dt = attr.mtime;
	} else {
		dt = OAL::GetCurDateTime(false);
	}
	UInt16 lastModFileTime = GetDosTime(dt);
	UInt16 lastModFileDate = GetDosDate(dt);
	UInt32 compressedSize = 0;
	UInt32 uncompressedSize = 0;
	UInt32 externalFileAttributes = (1 << 5);
	UInt32 relativeOffsetOfLocalHeader =
							static_cast<UInt32>(_pStreamDst->Tell());
	do {
		CentralFileHeader::Fields &fields = pHdr->GetFields();
		Gura_PackUInt16(fields.VersionMadeBy,				version);
		Gura_PackUInt16(fields.VersionNeededToExtract,		version);
		Gura_PackUInt16(fields.GeneralPurposeBitFlag,		generalPurposeBitFlag);
		Gura_PackUInt16(fields.CompressionMethod,			compressionMethod);
		Gura_PackUInt16(fields.LastModFileTime,				lastModFileTime);
		Gura_PackUInt16(fields.LastModFileDate,				lastModFileDate);
		Gura_PackUInt32(fields.Crc32,						0x00000000);
		Gura_PackUInt32(fields.CompressedSize,				compressedSize);
		Gura_PackUInt32(fields.UncompressedSize,			uncompressedSize);
		Gura_PackUInt16(fields.FileNameLength,				0x0000);
		Gura_PackUInt16(fields.ExtraFieldLength,			0x0000);
		Gura_PackUInt16(fields.FileCommentLength,			0x0000);
		Gura_PackUInt16(fields.DiskNumberStart,				0x0000);
		Gura_PackUInt16(fields.InternalFileAttributes,		0x0000);
		Gura_PackUInt32(fields.ExternalFileAttributes,		externalFileAttributes);
		Gura_PackUInt32(fields.RelativeOffsetOfLocalHeader,	relativeOffsetOfLocalHeader);
		pHdr->SetFileName(fileName);
		if (!pHdr->WriteAsLocalFileHeader(sig, *_pStreamDst)) return false;
	} while (0);
	AutoPtr<Stream> pStreamOut;
	size_t offsetDst = _pStreamDst->Tell();
	size_t offsetSrc = streamSrc.Tell();
	if (compressionMethod == CompressionMethod::Store) {
		pStreamOut.reset(Stream::Reference(_pStreamDst.get()));
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
		AutoPtr<ZLib::Stream_Deflater> pStreamDeflater(
			new ZLib::Stream_Deflater(env, Stream::Reference(_pStreamDst.get())));
		if (!pStreamDeflater->Initialize(sig, Z_DEFAULT_COMPRESSION,
					-MAX_WBITS, memLevel, Z_DEFAULT_STRATEGY)) return false;
		pStreamOut.reset(pStreamDeflater.release());
	} else if (compressionMethod == CompressionMethod::Deflate64) {
		// unsupported
	} else if (compressionMethod == CompressionMethod::PKWARE) {
		// unsupported
	} else if (compressionMethod == CompressionMethod::BZIP2) {
		AutoPtr<BZLib::Stream_Compressor> pStreamCompressor(
			new BZLib::Stream_Compressor(env, Stream::Reference(_pStreamDst.get())));
		int blockSize100k = 9, verbosity = 0, workFactor = 0;
		if (!pStreamCompressor->Initialize(sig,
							blockSize100k, verbosity, workFactor)) return false;
		pStreamOut.reset(pStreamCompressor.release());
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
	if (pStreamOut.IsNull()) {
		sig.SetError(ERR_IOError,
				"unsupported compression method %d", compressionMethod);
		return false;
	}
	CRC32 crc32;
	AutoPtr<Memory> pMemory(new MemoryHeap(32768));
	void *buff = pMemory->GetPointer();
	for (;;) {
		size_t bytesRead = streamSrc.Read(sig, buff, pMemory->GetSize());
		if (sig.IsSignalled()) break;
		if (bytesRead == 0) break;
		crc32.Update(buff, bytesRead);
		pStreamOut->Write(sig, buff, bytesRead);
		if (sig.IsSignalled()) break;
	}
	pStreamOut->Flush(sig);
	if (sig.IsSignalled()) return false;
	UInt32 crc32num = crc32.GetResult();
	compressedSize = static_cast<UInt32>(_pStreamDst->Tell() - offsetDst);
	uncompressedSize = static_cast<UInt32>(streamSrc.Tell() - offsetSrc);
	do {
		DataDescriptor desc;
		DataDescriptor::Fields &fields = desc.GetFields();
		Gura_PackUInt32(fields.Crc32,			crc32num);
		Gura_PackUInt32(fields.CompressedSize,	compressedSize);
		Gura_PackUInt32(fields.UncompressedSize,	uncompressedSize);
		if (!desc.Write(sig, *_pStreamDst)) return false;
	} while (0);
	do {
		CentralFileHeader::Fields &fields = pHdr->GetFields();
		Gura_PackUInt32(fields.Crc32,			crc32num);
		Gura_PackUInt32(fields.CompressedSize,	compressedSize);
		Gura_PackUInt32(fields.UncompressedSize,	uncompressedSize);
	} while (0);
#endif
	return true;
}

bool Writer::Finish()
{
#if 0
	if (_pStreamDst.IsNull()) return true;
	size_t offset = _pStreamDst->Tell();
	foreach (CentralFileHeaderList, ppHdr, _hdrList) {
		CentralFileHeader *pHdr = *ppHdr;
		if (!pHdr->Write(_sig, *_pStreamDst)) return false;
		//pHdr->Print();
	}
	UInt32 offsetOfCentralDirectory = static_cast<UInt32>(offset);
	UInt32 sizeOfTheCentralDirectory =
							static_cast<UInt32>(_pStreamDst->Tell() - offset);
	UInt16 nCentralFileHeaders = static_cast<UInt16>(_hdrList.size());
	do {
		EndOfCentralDirectoryRecord rec;
		EndOfCentralDirectoryRecord::Fields &fields = rec.GetFields();
		Gura_PackUInt16(fields.NumberOfThisDisk,									0x0000);
		Gura_PackUInt16(fields.NumberOfTheDiskWithTheStartOfTheCentralDirectory,	0x0000);
		Gura_PackUInt16(fields.TotalNumberOfEntriesInTheCentralDirectoryOnThisDisk,	nCentralFileHeaders);
		Gura_PackUInt16(fields.TotalNumberOfEntriesInTheCentralDirectory,			nCentralFileHeaders);
		Gura_PackUInt32(fields.SizeOfTheCentralDirectory,							sizeOfTheCentralDirectory);
		Gura_PackUInt32(fields.OffsetOfStartOfCentralDirectoryWithRespectToTheStartingDiskNumber,
															offsetOfCentralDirectory);
		Gura_PackUInt16(fields.ZIPFileCommentLength,								0x0000);
		if (!rec.Write(_sig, *_pStreamDst)) return false;
	} while (0);
	_pStreamDst->Close();
	_pStreamDst.reset(nullptr);
	return !_sig.IsSignalled();
#endif
	return false;
}

String Writer::ToString(const StringStyle& ss) const
{
	return "Writer";
}

Gurax_EndModuleScope(zip)
