//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"
#include "ZIPFormat.h"

Gurax_BeginModuleScope(zip)

UInt16 SymbolToCompressionMethod(const Symbol* pSymbol)
{
	return SymbolAssoc_CompressionMethod::GetInstance().ToAssociated(pSymbol);
}

const Symbol* CompressionMethodToSymbol(UInt16 compressionMethod)
{
	return SymbolAssoc_CompressionMethod::GetInstance().ToSymbol(compressionMethod);
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

class DirectoryItem : public Directory {
private:
	RefPtr<Stream> _pStreamSrc;
	RefPtr<StatEx> _pStatEx;
public:
	DirectoryItem(Type type, Stream* pStreamSrc, StatEx* pStatEx) :
		Directory(type, PathName::SepPlatform, PathName::CaseFlagPlatform),
		_pStreamSrc(pStreamSrc), _pStatEx(pStatEx) {}
};

class DirectoryTop : public Directory {
public:
	class FactoryEx : public Factory {
	private:
		Type _type;
		RefPtr<Stream> _pStreamSrc;
		RefPtr<StatEx> _pStatEx;
	public:
		FactoryEx(Type type, Stream* pStreamSrc, StatEx* pStatEx) :
			Factory(new FactoryOwner(), PathName::CaseFlagPlatform),
			_type(type), _pStreamSrc(pStreamSrc), _pStatEx(pStatEx) {}
		virtual Directory* GenerateDirectory() {
			return new DirectoryItem(_type, _pStreamSrc->Reference(), _pStatEx->Reference());
		}
	};
private:
	RefPtr<Stream> _pStreamSrc;
	RefPtr<Factory> _pFactoryTop;
public:
	DirectoryTop(Stream* pStreamSrc) :
		Directory(Directory::Type::Boundary, PathName::SepPlatform, PathName::CaseFlagPlatform),
		_pStreamSrc(pStreamSrc), _pFactoryTop(new Factory(new FactoryOwner(), PathName::CaseFlagPlatform)) {}
	bool ReadCentralDirectory();
};

bool DirectoryTop::ReadCentralDirectory()
{
	StatExOwner statExOwner;
	if (!statExOwner.ReadCentralDirectory(*_pStreamSrc)) return false;
	for (StatEx* pStatEx : statExOwner) {
		const char* pathName = pStatEx->GetCentralFileHeader().GetFileName();
		Type type = String::EndsWithPathSep(pathName)? Type::Container : Type::Item;
		_pFactoryTop->AddChildInTree(pathName, new FactoryEx(type, _pStreamSrc->Reference(), pStatEx->Reference()));
	}
	return true;
}

Directory* CreateTopDirectory(Stream& streamSrc)
{
	RefPtr<DirectoryTop> pDirectory(new DirectoryTop(streamSrc.Reference()));
	return pDirectory->ReadCentralDirectory()? pDirectory.release() : nullptr;
}

Stream* CreateStream(Stream& streamSrc, const StatEx& statEx)
{
	const CentralFileHeader& hdr = statEx.GetCentralFileHeader();
	long offset = static_cast<long>(hdr.GetRelativeOffsetOfLocalHeader());
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
