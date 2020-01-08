//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"
#include "ZIPFormat.h"

Gurax_BeginModuleScope(zip)

//-----------------------------------------------------------------------------
// Directory_File
//-----------------------------------------------------------------------------
class GURAX_DLLDECLARE Directory_File : public Directory {
private:
	std::unique_ptr<CentralFileHeader> _pHdr;
public:
	Directory_File(Directory* pDirectoryParent, CentralFileHeader* pHdr) :
		Directory(pDirectoryParent, pHdr->GetFileName(), Directory::Type::Item,
				  PathName::SepPlatform, PathName::CaseFlagPlatform), _pHdr(pHdr) {}
	virtual Directory* DoNextChild() override;
	virtual Directory* DoFindChild(const char* name) override;
	virtual Stream* DoOpenStream(Stream::OpenFlags openFlags) override;
	virtual Value* DoGetStatValue() override;
};

Directory* Directory_File::DoNextChild()
{
	return nullptr;
}

Directory* Directory_File::DoFindChild(const char* name)
{
	return nullptr;
}

Stream* Directory_File::DoOpenStream(Stream::OpenFlags openFlags)
{
	return nullptr;
}

Value* Directory_File::DoGetStatValue()
{
	return nullptr;
}

class SymbolAssoc_Method : public SymbolAssoc<UInt16, Method::Invalid> {
public:
	SymbolAssoc_Method() {
		Assoc(Gurax_Symbol(store),		Method::Store);
		Assoc(Gurax_Symbol(shrink),		Method::Shrink);
		Assoc(Gurax_Symbol(factor1),	Method::Factor1);
		Assoc(Gurax_Symbol(factor2),	Method::Factor2);
		Assoc(Gurax_Symbol(factor3),	Method::Factor3);
		Assoc(Gurax_Symbol(factor4),	Method::Factor4);
		Assoc(Gurax_Symbol(implode),	Method::Implode);
		Assoc(Gurax_Symbol(deflate),	Method::Deflate);
		Assoc(Gurax_Symbol(deflate64),	Method::Deflate64);
		Assoc(Gurax_Symbol(pkware),		Method::PKWARE);
		Assoc(Gurax_Symbol(bzip2),		Method::BZIP2);
		Assoc(Gurax_Symbol(lzma),		Method::LZMA);
		Assoc(Gurax_Symbol(tersa),		Method::TERSA);
		Assoc(Gurax_Symbol(lz77),		Method::LZ77);
		Assoc(Gurax_Symbol(wavpack),	Method::WavPack);
		Assoc(Gurax_Symbol(ppmd),		Method::PPMd);
	}
	static const SymbolAssoc& GetInstance() {
		static SymbolAssoc* pSymbolAssoc = nullptr;
		return pSymbolAssoc? *pSymbolAssoc : *(pSymbolAssoc = new SymbolAssoc_Method());
	}
};

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

bool IsMatchedName(const char* name1, const char* name2)
{
	const char* p1 = name1;
	const char* p2 = name2;
	for ( ; ; p1++, p2++) {
		char ch1 = *p1, ch2 = *p2;
		if (PathName::IsSep(ch1) && PathName::IsSep(ch2)) {
			// nothing to do
		} else if (ch1 != ch2) {
			return false;
		} else if (ch1 == '\0') {
			break;
		}
	}
	return true;
}

UInt32 SeekCentralDirectory(Stream& streamSrc)
{
	size_t bytesZIPFile = streamSrc.GetSize();
	if (bytesZIPFile == -1) {
		Error::Issue(ErrorType::IOError, "can't seek end of file");
		return 0;
	}
	//UInt32 offsetCentralDirectory = 0;
	if (bytesZIPFile < EndOfCentralDirectoryRecord::MinSize) {
		Error::Issue(ErrorType::FormatError, "can't find central directory record");
		return 0;
	}
	size_t bytesBuff = 0;
	if (bytesZIPFile <= EndOfCentralDirectoryRecord::MaxSize) {
		bytesBuff = bytesZIPFile;
	} else {
		long offsetStart = static_cast<long>(bytesZIPFile -
									EndOfCentralDirectoryRecord::MaxSize);
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
	if (buffAnchor == nullptr) {
		Error::Issue(ErrorType::FormatError, "can't find central directory record");
		return 0;
	}
	EndOfCentralDirectoryRecord record;
	::memcpy(&record, buffAnchor, EndOfCentralDirectoryRecord::MinSize);
	return Gurax_UnpackUInt32(record.GetFields().
			OffsetOfStartOfCentralDirectoryWithRespectToTheStartingDiskNumber);
}

Directory* CreateDirectory(Stream& streamSrc, Directory* pDirectoryParent,
						   const char** pPathName, Directory::Type typeWouldBe)
{
#if 0
	RefPtr<Stream> pStreamSrc(streamSrc.Reference());
	if (!pStreamSrc->IsBwdSeekable()) {
		RefPtr<BinaryReferable> pBuff(new BinaryReferable(true));
		pStreamSrc->ReadAll(pBuff->GetBinary());
		if (Error::IsIssued()) return nullptr;
		pStreamSrc.reset(new Stream_Binary(Stream::Flag::Readable, pBuff.release()));
	}
#endif
	RefPtr<Directory_Container> pDirectory(
		new Directory_Container(pDirectoryParent, "", Directory::Type::Container,
								PathName::SepPlatform, PathName::CaseFlagPlatform));
	UInt32 offsetCentralDirectory = SeekCentralDirectory(streamSrc);
	if (Error::IsIssued()) return nullptr;
	if (!streamSrc.Seek(offsetCentralDirectory, Stream::SeekMode::Set)) return nullptr;
	UInt32 signature;
	while (ReadStream(streamSrc, &signature)) {
		//::printf("%08x\n", signature);
		if (signature == LocalFileHeader::Signature) {
			LocalFileHeader hdr;
			if (!hdr.Read(streamSrc)) return nullptr;
			if (!hdr.SkipFileData(streamSrc)) return nullptr;
		} else if (signature == ArchiveExtraDataRecord::Signature) {
			ArchiveExtraDataRecord record;
			if (!record.Read(streamSrc)) return nullptr;
		} else if (signature == CentralFileHeader::Signature) {
			std::unique_ptr<CentralFileHeader> pHdr(new CentralFileHeader());
			if (!pHdr->Read(streamSrc)) return nullptr;
			pDirectory->GetDirectoryOwner().push_back(new Directory_File(pDirectoryParent, pHdr.release()));
		} else if (signature == DigitalSignature::Signature) {
			DigitalSignature signature;
			if (!signature.Read(streamSrc)) return nullptr;
		} else if (signature == Zip64EndOfCentralDirectory::Signature) {
			Zip64EndOfCentralDirectory dir;
			if (!dir.Read(streamSrc)) return nullptr;
		} else if (signature == Zip64EndOfCentralDirectoryLocator::Signature) {
			Zip64EndOfCentralDirectoryLocator loc;
			if (!loc.Read(streamSrc)) return nullptr;
		} else if (signature == EndOfCentralDirectoryRecord::Signature) {
			EndOfCentralDirectoryRecord record;
			if (!record.Read(streamSrc)) return nullptr;
			break;
		} else {
			Error::Issue(ErrorType::FormatError, "unknown signature %08x", signature);
			return nullptr;
		}
	}
	if (Error::IsIssued()) return nullptr;
	return pDirectory.release();
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
	stream.Write(buff, bytes);
	return !Error::IsIssued();
}

bool WriteStream(Stream& stream, Binary& binary)
{
	stream.Write(binary.data(), binary.size());
	return !Error::IsIssued();
}

Gurax_EndModuleScope(zip)
