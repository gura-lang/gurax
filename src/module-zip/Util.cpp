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

UInt32 SeekCentralDirectory(Stream& streamSrc, EndOfCentralDirectoryRecord* pRecord)
{
	size_t bytesZIPFile = streamSrc.GetBytes();
	if (bytesZIPFile == static_cast<size_t>(-1)) {
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
		size_t offsetStart = bytesZIPFile - EndOfCentralDirectoryRecord::MaxSize;
		if (!streamSrc.SetOffset(offsetStart)) {
			return 0;
		}
		bytesBuff = EndOfCentralDirectoryRecord::MaxSize;
	}
	RefPtr<Memory> pMemory(new MemoryHeap(bytesBuff));
	char* buff = pMemory->GetPointerC<char>();
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
	::memcpy(reinterpret_cast<void*>(&record), buffAnchor, EndOfCentralDirectoryRecord::MinSize);
	if (pRecord) *pRecord = record;
	return Gurax_UnpackUInt32(record.GetFields().OffsetOfStartOfCentralDirectoryWithRespectToTheStartingDiskNumber);
}

bool InspectDescriptor(Stream& streamCon, Stream& streamSrc)
{
	EndOfCentralDirectoryRecord rec;
	UInt32 offsetCentralDirectory = SeekCentralDirectory(streamSrc, &rec);
	if (Error::IsIssued()) return false;
	rec.Print(streamCon);
	if (!streamSrc.SetOffset(offsetCentralDirectory)) return false;
	UInt32 signature;
	while (ReadStream(streamSrc, &signature)) {
		streamCon.Printf("\n");
		if (signature == LocalFileHeader::Signature) {
			LocalFileHeader hdr;
			if (!hdr.Read(streamSrc)) return false;
			if (!hdr.SkipFileData(streamSrc)) return false;
		} else if (signature == ArchiveExtraDataRecord::Signature) {
			ArchiveExtraDataRecord record;
			if (!record.Read(streamSrc)) return false;
		} else if (signature == CentralFileHeader::Signature) {
			CentralFileHeader hdr;
			if (!hdr.Read(streamSrc)) return false;
			hdr.Print(streamCon);
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
			streamCon.Printf("unknown signature %08x\n", signature);
			return false;
		}
	}
	return true;
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
	binary = Binary(buff, bytes);
	delete[] buff;
	return true;
}

bool WriteStream(Stream& stream, const void* buff, size_t bytes)
{
	return stream.Write(buff, bytes);
}

bool WriteStream(Stream& stream, const Binary& binary)
{
	return stream.Write(binary.data(), binary.size());
}

Gurax_EndModuleScope(zip)
