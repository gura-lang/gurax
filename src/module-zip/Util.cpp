//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"
#include "ZIPFormat.h"

Gurax_BeginModuleScope(zip)

UInt16 SymbolToMethod(const Symbol* pSymbol)
{
	return SymbolAssoc_Method::GetInstance().ToAssociated(pSymbol);
}

UInt16 GetDosTime(const DateTime& dt)
{
	return
		(static_cast<UInt16>(dt.GetHour()) << 11) |
		(static_cast<UInt16>(dt.GetMin()) << 5) |
		(static_cast<UInt16>(dt.GetSec() / 2) << 0);
}

UInt16 GetDosDate(const DateTime& dt)
{
	return
		(static_cast<UInt16>(dt.GetYear() - 1980) << 9) |
		(static_cast<UInt16>(dt.GetMonth()) << 5) |
		(static_cast<UInt16>(dt.GetDay()) << 0);
}

DateTime* MakeDateTimeFromDos(UInt16 dosDate, UInt16 dosTime)
{
	Int16 year = static_cast<Int16>((dosDate >> 9) + 1980);
	Int8 month = static_cast<Int8>((dosDate >> 5) & 0xf);
	Int8 day = static_cast<Int8>((dosDate >> 0) & 0x1f);
	Int32 secPacked = static_cast<Int32>(
		(dosTime >> 11) * 3600 + ((dosTime >> 5) & 0x3f) * 60 + ((dosTime >> 0) & 0x1f) * 2);
	Int32 usecPacked = 0;
	return new DateTime(year, month, day, secPacked, usecPacked);
}

Directory* ReadCentralDirectory(Stream& streamSrc, Directory* pDirectoryParent,
								const char** pPathName, Directory::Type typeWouldBe)
{
	RefPtr<Stream> pStreamSrc(streamSrc.Reference());
	if (!pStreamSrc->IsBwdSeekable()) {
		RefPtr<BinaryReferable> pBuff(new BinaryReferable(true));
		pStreamSrc->ReadAll(pBuff->GetBinary());
		if (Error::IsIssued()) return nullptr;
		pStreamSrc.reset(new Stream_Binary(Stream::Flag::Readable, pBuff.release()));
	}
	RefPtr<Directory_CustomContainer> pDirectory(
		new Directory_CustomContainer(pDirectoryParent, "", Directory::Type::BoundaryContainer,
								PathName::SepPlatform, PathName::CaseFlagPlatform));
	UInt32 offsetCentralDirectory = SeekCentralDirectory(*pStreamSrc);
	if (Error::IsIssued()) return nullptr;
	if (!pStreamSrc->Seek(offsetCentralDirectory, Stream::SeekMode::Set)) return nullptr;
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
			std::unique_ptr<CentralFileHeader> pHdr(new CentralFileHeader());
			if (!pHdr->Read(*pStreamSrc)) return nullptr;
			pHdr->Print();
			::printf("%s\n", pHdr->GetFileName());
			//pDirectory->AddChildInTree(pHdr->GetFileName(), new Directory_ZIPFile(pDirectory.get(), pHdr.release()));
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
			Error::Issue(ErrorType::FormatError, "unknown signature %08x", signature);
			return nullptr;
		}
	}
	return Error::IsIssued()? nullptr : pDirectory.release();
}

UInt32 SeekCentralDirectory(Stream& streamSrc)
{
	size_t bytesZIPFile = streamSrc.GetSize();
	if (bytesZIPFile == -1) {
		Error::Issue(ErrorType::IOError, "can't seek end of file");
		return 0;
	}
	if (bytesZIPFile < EndOfCentralDirectoryRecord::MinSize) {
		Error::Issue(ErrorType::FormatError, "can't find central directory record");
		return 0;
	}
	size_t bytesBuff = 0;
	if (bytesZIPFile <= EndOfCentralDirectoryRecord::MaxSize) {
		bytesBuff = bytesZIPFile;
	} else {
		long offsetStart = static_cast<long>(bytesZIPFile - EndOfCentralDirectoryRecord::MaxSize);
		if (!streamSrc.Seek(offsetStart, Stream::SeekMode::Set)) {
			return 0;
		}
		bytesBuff = EndOfCentralDirectoryRecord::MaxSize;
	}
	RefPtr<Memory> pMemory(new MemoryHeap(bytesBuff));
	char* buff = reinterpret_cast<char*>(pMemory->GetPointer());
	streamSrc.Read(buff, bytesBuff);
	if (Error::IsIssued()) return 0;
	char* buffAnchor = nullptr;
	for (size_t i = 0; i <= bytesBuff - EndOfCentralDirectoryRecord::MinSize; i++) {
		if (::memcmp(buff + i, "\x50\x4b\x05\x06", 4) == 0) {
			buffAnchor = buff + i;
		}
	}
	if (!buffAnchor) {
		Error::Issue(ErrorType::FormatError, "can't find central directory record");
		return 0;
	}
	EndOfCentralDirectoryRecord record;
	::memcpy(&record, buffAnchor, EndOfCentralDirectoryRecord::MinSize);
	return Gurax_UnpackUInt32(record.GetFields().
			OffsetOfStartOfCentralDirectoryWithRespectToTheStartingDiskNumber);
}

Stream* CreateStream(Stream& streamSrc, const CentralFileHeader* pHdr)
{
	RefPtr<Stream_reader> pStream;
	long offset = static_cast<long>(pHdr->GetRelativeOffsetOfLocalHeader());
	streamSrc.Seek(offset, Stream::SeekMode::Set);
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
	//const char* name = pHdr->GetFileName();
	UInt16 compressionMethod = pHdr->GetCompressionMethod();
	//size_t bytesUncompressed = pHdr->GetUncompressedSize();
	//size_t bytesCompressed = pHdr->GetCompressedSize();
	//UInt32 crc32Expected = pHdr->GetCrc32();
	if (compressionMethod == Method::Store) {
		pStream.reset(new Stream_reader_Store(streamSrc.Reference(), *pHdr));
	} else if (compressionMethod == Method::Shrink) {
		// unsupported
	} else if (compressionMethod == Method::Factor1) {
		// unsupported
	} else if (compressionMethod == Method::Factor2) {
		// unsupported
	} else if (compressionMethod == Method::Factor3) {
		// unsupported
	} else if (compressionMethod == Method::Factor4) {
		// unsupported
	} else if (compressionMethod == Method::Implode) {
		// unsupported
	} else if (compressionMethod == Method::Factor1) {
		// unsupported
	} else if (compressionMethod == Method::Deflate) {
		pStream.reset(new Stream_reader_Deflate(streamSrc.Reference(), *pHdr));
	} else if (compressionMethod == Method::Deflate64) {
		pStream.reset(new Stream_reader_Deflate64(streamSrc.Reference(), *pHdr));
	} else if (compressionMethod == Method::PKWARE) {
		// unsupported
	} else if (compressionMethod == Method::BZIP2) {
		pStream.reset(new Stream_reader_BZIP2(streamSrc.Reference(), *pHdr));
	} else if (compressionMethod == Method::LZMA) {
		// unsupported
	} else if (compressionMethod == Method::TERSA) {
		// unsupported
	} else if (compressionMethod == Method::LZ77) {
		// unsupported
	} else if (compressionMethod == Method::WavPack) {
		// unsupported
	} else if (compressionMethod == Method::PPMd) {
		// unsupported
	}
	if (!pStream) {
		Error::Issue(ErrorType::FormatError, "unsupported compression method %d", compressionMethod);
		return nullptr;
	}
	if (!pStream->Initialize()) return nullptr;
	return pStream.release();
}

bool SkipStream(Stream& stream, size_t bytes)
{
	return stream.Seek(static_cast<long>(bytes), Stream::SeekMode::Cur);
}

bool ReadStream(Stream& stream, void* buff, size_t bytes, size_t offset)
{
	if (bytes == 0) return true;
	size_t bytesRead = stream.Read(reinterpret_cast<char*>(buff) + offset, bytes);
	if (Error::IsIssued()) return false;
	if (bytesRead < bytes) {
		Error::Issue(ErrorType::FormatError, "invalid ZIP format");
		return false;
	}
	return true;
}

bool ReadStream(Stream& stream, UInt32* pSignature)
{
	struct {
		Gurax_PackedUInt32_LE(Signature);
	} buff;
	if (!ReadStream(stream, &buff, 4)) return false;
	*pSignature = Gurax_UnpackUInt32(buff.Signature);
	return true;
}

bool ReadStream(Stream& stream, Binary& binary, size_t bytes)
{
	if (bytes == 0) {
		binary = Binary();
		return true;
	}
	char* buff = new char[bytes];
	if (!ReadStream(stream, buff, bytes)) {
		delete[] buff;
		return false;
	}
	binary = Binary(true, buff, bytes);
	delete[] buff;
	return true;
}

bool WriteStream(Stream& stream, void* buff, size_t bytes)
{
	stream.Write(buff, bytes);
	return !Error::IsIssued();
}

bool WriteStream(Stream& stream, Binary& binary)
{
	stream.Write(binary.data(), binary.size());
	return !Error::IsIssued();
}

Gurax_EndModuleScope(zip)
