//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"
#include "ZIPFormat.h"

Gurax_BeginModuleScope(zip)

UInt16 SymbolToCompressionMethod(const Symbol* pSymbol)
{
#if 0
	if (pSymbol->IsIdentical(Gura_UserSymbol(store))) {
		return METHOD_Store;
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(shrink))) {
		return METHOD_Shrink;
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(factor1))) {
		return METHOD_Factor1;
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(factor2))) {
		return METHOD_Factor2;
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(factor3))) {
		return METHOD_Factor3;
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(factor4))) {
		return METHOD_Factor4;
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(implode))) {
		return METHOD_Implode;
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(deflate))) {
		return METHOD_Deflate;
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(deflate64))) {
		return METHOD_Deflate64;
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(pkware))) {
		return METHOD_PKWARE;
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(bzip2))) {
		return METHOD_BZIP2;
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(lzma))) {
		return METHOD_LZMA;
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(tersa))) {
		return METHOD_TERSA;
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(lz77))) {
		return METHOD_LZ77;
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(wavpack))) {
		return METHOD_WavPack;
	} else if (pSymbol->IsIdentical(Gura_UserSymbol(ppmd))) {
		return METHOD_PPMd;
	} else {
		return METHOD_Invalid;
	}
#endif
	return 0;
}

UInt16 GetDosTime(const DateTime& dt)
{
#if 0
	return (static_cast<UInt16>(dt.GetHour()) << 11) |
			(static_cast<UInt16>(dt.GetMin()) << 5) |
			(static_cast<UInt16>(dt.GetSec() / 2) << 0);
#endif
	return 0;
}

UInt16 GetDosDate(const DateTime& dt)
{
#if 0
	return (static_cast<UInt16>(dt.GetYear() - 1980) << 9) |
			(static_cast<UInt16>(dt.GetMonth()) << 5) |
			(static_cast<UInt16>(dt.GetDay()) << 0);
#endif
	return 0;
}

DateTime* MakeDateTimeFromDos(UInt16 dosDate, UInt16 dosTime)
{
#if 0
	short year = static_cast<short>((dosDate >> 9) + 1980);
	char month = static_cast<char>((dosDate >> 5) & 0xf);
	char day = static_cast<char>((dosDate >> 0) & 0x1f);
	long sec = static_cast<long>((dosTime >> 11) * 3600 +
				((dosTime >> 5) & 0x3f) * 60 + ((dosTime >> 0) & 0x1f) * 2);
	return DateTime(year, month, day, sec, 0);
#endif
	return nullptr;
}

bool IsMatchedName(const char* name1, const char* name2)
{
#if 0
	const char* p1 = name1,* p2 = name2;
	for ( ; ; p1++, p2++) {
		char ch1 = *p1, ch2 = *p2;
		if (IsFileSeparator(ch1) && IsFileSeparator(ch2)) {
			// nothing to do
		} else if (ch1 != ch2) {
			return false;
		} else if (ch1 == '\0') {
			break;
		}
	}
#endif
	return true;
}

UInt32 SeekCentralDirectory(Stream* pStream)
{
#if 0
	size_t bytesZIPFile = pStream->GetSize();
	if (bytesZIPFile == InvalidSize) {
		sig.SetError(ERR_IOError, "can't seek end of file");
		return 0;
	}
	UInt32 offsetCentralDirectory = 0;
	if (bytesZIPFile < EndOfCentralDirectoryRecord::MinSize) {
		sig.SetError(ERR_FormatError, "can't find central directory record");
		return 0;
	}
	size_t bytesBuff = 0;
	if (bytesZIPFile <= EndOfCentralDirectoryRecord::MaxSize) {
		bytesBuff = bytesZIPFile;
	} else {
		long offsetStart = static_cast<long>(bytesZIPFile -
									EndOfCentralDirectoryRecord::MaxSize);
		if (!pStream->Seek(offsetStart, Stream::SeekSet)) {
			return 0;
		}
		bytesBuff = EndOfCentralDirectoryRecord::MaxSize;
	}
	AutoPtr<Memory> pMemory(new MemoryHeap(bytesBuff));
	char* buff = reinterpret_cast<char*>(pMemory->GetPointer());
	pStream->Read(buff, bytesBuff);
	if (Error::IsIssued()) return 0;
	char* buffAnchor = nullptr;
	for (size_t i = 0; i <= bytesBuff - EndOfCentralDirectoryRecord::MinSize; i++) {
		if (::memcmp(buff + i, "\x50\x4b\x05\x06", 4) == 0) {
			buffAnchor = buff + i;
		}
	}
	if (buffAnchor == nullptr) {
		sig.SetError(ERR_FormatError, "can't find central directory record");
		return 0;
	}
	EndOfCentralDirectoryRecord record;
	::memcpy(&record, buffAnchor, EndOfCentralDirectoryRecord::MinSize);
	return Gura_UnpackUInt32(record.GetFields().
			OffsetOfStartOfCentralDirectoryWithRespectToTheStartingDiskNumber);
#endif
	return 0;
}

Directory* CreateDirectory(Stream* pStreamSrc,
						   Directory* pParent, const char** pPathName, Directory::Type typeWouldBe)
{
#if 0
	if (!pStreamSrc->IsBwdSeekable()) {
		Stream* pStreamPrefetch = Stream::Prefetch(env, pStreamSrc, true);
		if (Error::IsIssued()) return nullptr;
		pStreamSrc = pStreamPrefetch;
	}
	AutoPtr<DirBuilder::Structure> pStructure(new DirBuilder::Structure());
	pStructure->SetRoot(new Record_ZIP(pStructure.get(), nullptr, "", true));
	UInt32 offsetCentralDirectory = SeekCentralDirectory(pStreamSrc);
	if (Error::IsIssued()) return nullptr;
	if (!pStreamSrc->Seek(offsetCentralDirectory, Stream::SeekSet)) return nullptr;
	UInt32 signature;
	while (ReadStream(*pStreamSrc, &signature)) {
		//::printf("%08x\n", signature);
		if (signature == LocalFileHeader::Signature) {
			LocalFileHeader hdr;
			if (!hdr.Read(*pStreamSrc)) return nullptr;
			if (!hdr.SkipFileData(*pStreamSrc)) return nullptr;
		} else if (signature == ArchiveExtraDataRecord::Signature) {
			ArchiveExtraDataRecord record;
			if (!record.Read(*pStreamSrc)) return nullptr;
		} else if (signature == CentralFileHeader::Signature) {
			CentralFileHeader* pHdr = new CentralFileHeader();
			if (!pHdr->Read(*pStreamSrc)) {
				delete pHdr;
				return nullptr;
			}
			Record_ZIP* pRecord = dynamic_cast<Record_ZIP*>(
									pStructure->AddRecord(pHdr->GetFileName()));
			pRecord->SetCentralFileHeader(pHdr);
		} else if (signature == DigitalSignature::Signature) {
			DigitalSignature signature;
			if (!signature.Read(*pStreamSrc)) return nullptr;
		} else if (signature == Zip64EndOfCentralDirectory::Signature) {
			Zip64EndOfCentralDirectory dir;
			if (!dir.Read(*pStreamSrc)) return nullptr;
		} else if (signature == Zip64EndOfCentralDirectoryLocator::Signature) {
			Zip64EndOfCentralDirectoryLocator loc;
			if (!loc.Read(*pStreamSrc)) return nullptr;
		} else if (signature == EndOfCentralDirectoryRecord::Signature) {
			EndOfCentralDirectoryRecord record;
			if (!record.Read(*pStreamSrc)) return nullptr;
			break;
		} else {
			sig.SetError(ERR_FormatError, "unknown signature %08x", signature);
			return nullptr;
		}
	}
	if (Error::IsIssued()) return nullptr;
	//pStreamSrc->Close();
	return pStructure->GenerateDirectory(pParent, pPathName, notFoundMode);
#endif
	return nullptr;
}

Stream* CreateStream(Stream* pStreamSrc, const CentralFileHeader* pHdr)
{
#if 0
	AutoPtr<Stream_reader> pStream;
	long offset = static_cast<long>(pHdr->GetRelativeOffsetOfLocalHeader());
	pStreamSrc->Seek(offset, Stream::SeekSet);
	if (Error::IsIssued()) return nullptr;
	do {
		UInt32 signature;
		if (!ReadStream(*pStreamSrc, &signature)) return nullptr;
		if (signature != LocalFileHeader::Signature) {
			sig.SetError(ERR_FormatError, "invalid ZIP format");
			return nullptr;
		}
		LocalFileHeader hdr;
		if (!hdr.Read(*pStreamSrc)) return nullptr;
	} while (0);
	//const char* name = pHdr->GetFileName();
	UInt16 compressionMethod = pHdr->GetCompressionMethod();
	//size_t bytesUncompressed = pHdr->GetUncompressedSize();
	//size_t bytesCompressed = pHdr->GetCompressedSize();
	//UInt32 crc32Expected = pHdr->GetCrc32();
	if (compressionMethod == METHOD_Store) {
		pStream.reset(new Stream_reader_Store(env, Stream::Reference(pStreamSrc), *pHdr));
	} else if (compressionMethod == METHOD_Shrink) {
		// unsupported
	} else if (compressionMethod == METHOD_Factor1) {
		// unsupported
	} else if (compressionMethod == METHOD_Factor2) {
		// unsupported
	} else if (compressionMethod == METHOD_Factor3) {
		// unsupported
	} else if (compressionMethod == METHOD_Factor4) {
		// unsupported
	} else if (compressionMethod == METHOD_Implode) {
		// unsupported
	} else if (compressionMethod == METHOD_Factor1) {
		// unsupported
	} else if (compressionMethod == METHOD_Deflate) {
		pStream.reset(new Stream_reader_Deflate(env, Stream::Reference(pStreamSrc), *pHdr));
	} else if (compressionMethod == METHOD_Deflate64) {
		pStream.reset(new Stream_reader_Deflate64(env, Stream::Reference(pStreamSrc), *pHdr));
	} else if (compressionMethod == METHOD_PKWARE) {
		// unsupported
	} else if (compressionMethod == METHOD_BZIP2) {
		pStream.reset(new Stream_reader_BZIP2(env, Stream::Reference(pStreamSrc), *pHdr));
	} else if (compressionMethod == METHOD_LZMA) {
		// unsupported
	} else if (compressionMethod == METHOD_TERSA) {
		// unsupported
	} else if (compressionMethod == METHOD_LZ77) {
		// unsupported
	} else if (compressionMethod == METHOD_WavPack) {
		// unsupported
	} else if (compressionMethod == METHOD_PPMd) {
		// unsupported
	}
	if (pStream.IsNull()) {
		sig.SetError(ERR_FormatError,
				"unsupported compression method %d", compressionMethod);
		return nullptr;
	}
	if (!pStream->Initialize(env)) return nullptr;
	return pStream.release();
#endif
	return nullptr;
}

bool SkipStream(Stream& stream, size_t bytes)
{
#if 0
	return stream.Seek(static_cast<long>(bytes), Stream::SeekCur);
#endif
	return false;
}

bool ReadStream(Stream& stream, void* buff, size_t bytes, size_t offset)
{
#if 0
	if (bytes == 0) return true;
	size_t bytesRead = stream.Read(reinterpret_cast<char*>(buff) + offset, bytes);
	if (Error::IsIssued()) return false;
	if (bytesRead < bytes) {
		sig.SetError(ERR_FormatError, "invalid ZIP format");
		return false;
	}
#endif
	return true;
}

bool ReadStream(Stream& stream, UInt32* pSignature)
{
#if 0
	struct {
		Gura_PackedUInt32_LE(Signature);
	} buff;
	if (!ReadStream(stream, &buff, 4)) return false;
	*pSignature = Gura_UnpackUInt32(buff.Signature);
#endif
	return true;
}

bool ReadStream(Stream& stream, Binary& binary, size_t bytes)
{
#if 0
	if (bytes == 0) {
		binary = Binary();
		return true;
	}
	char* buff = new char[bytes];
	if (!ReadStream(stream, buff, bytes)) {
		delete[] buff;
		return false;
	}
	binary = Binary(buff, bytes);
	delete[] buff;
#endif
	return true;
}

bool WriteStream(Stream& stream, void* buff, size_t bytes)
{
#if 0
	stream.Write(buff, bytes);
#endif
	return !Error::IsIssued();
}

bool WriteStream(Stream& stream, Binary& binary)
{
#if 0
	stream.Write(binary.data(), binary.size());
#endif
	return !Error::IsIssued();
}

Gurax_EndModuleScope(zip)
