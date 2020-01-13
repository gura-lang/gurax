//------------------------------------------------------------------------------
// ZIPFormat.h
// specification: http://www.pkware.com/documents/casestudies/APPNOTE.TXT
//------------------------------------------------------------------------------
#ifndef GURAX_MODULE_ZIPFORMAT_H
#define GURAX_MODULE_ZIPFORMAT_H
#include <gurax.h>
#include <gurax/helper/ZLibHelper.h>
#include <gurax/helper/BZLibHelper.h>
#include "Util.h"

Gurax_BeginModuleScope(zip)

//------------------------------------------------------------------------------
// Symbol
//------------------------------------------------------------------------------
Gurax_DeclareSymbol(store);
Gurax_DeclareSymbol(shrink);
Gurax_DeclareSymbol(factor1);
Gurax_DeclareSymbol(factor2);
Gurax_DeclareSymbol(factor3);
Gurax_DeclareSymbol(factor4);
Gurax_DeclareSymbol(implode);
Gurax_DeclareSymbol(deflate);
Gurax_DeclareSymbol(deflate64);
Gurax_DeclareSymbol(pkware);
Gurax_DeclareSymbol(bzip2);
Gurax_DeclareSymbol(lzma);
Gurax_DeclareSymbol(tersa);
Gurax_DeclareSymbol(lz77);
Gurax_DeclareSymbol(wavpack);
Gurax_DeclareSymbol(ppmd);

//------------------------------------------------------------------------------
// Method
//------------------------------------------------------------------------------
struct Method {
	static const UInt16 Invalid		= 0xffff;
	static const UInt16 Store		= 0;	// The file is stored (no compression)
	static const UInt16 Shrink		= 1;	// The file is Shrunk
	static const UInt16 Factor1		= 2;	// The file is Reduced with compression factor 1
	static const UInt16 Factor2		= 3;	// The file is Reduced with compression factor 2
	static const UInt16 Factor3		= 4;	// The file is Reduced with compression factor 3
	static const UInt16 Factor4		= 5;	// The file is Reduced with compression factor 4
	static const UInt16 Implode		= 6;	// The file is Imploded
	static const UInt16 Deflate		= 8;	// The file is Deflated
	static const UInt16 Deflate64	= 9;	// Enhanced Deflating using Deflate64(tm)
	static const UInt16 PKWARE		= 10;	// PKWARE Data Compression Library Imploding (old IBM TERSE)
	static const UInt16 BZIP2		= 12;	// File is compressed using BZIP2 algorithm
	static const UInt16 LZMA		= 14;	// LZMA (EFS)
	static const UInt16 TERSA		= 18;	// File is compressed using IBM TERSE (new)
	static const UInt16 LZ77		= 19;	// IBM LZ77 z Architecture (PFS)
	static const UInt16 WavPack		= 97;	// WavPack compressed data
	static const UInt16 PPMd		= 99;	// PPMd version I, Rev 1
};

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

//------------------------------------------------------------------------------
// DOSATTR
//------------------------------------------------------------------------------
struct DOSATTR {
	static const UInt16 ReadOnly		= (1 << 0);
	static const UInt16 Hidden			= (1 << 1);
	static const UInt16 System			= (1 << 2);
	static const UInt16 VolumeLabel		= (1 << 3);
	static const UInt16 Subdirectory	= (1 << 4);
	static const UInt16 Archive			= (1 << 5);
	static const UInt16 Device			= (1 << 6);
	static const UInt16 Unused			= (1 << 7);
};

//------------------------------------------------------------------------------
// A. Local file header
//------------------------------------------------------------------------------
class LocalFileHeader {
public:
	static const UInt32 Signature = 0x04034b50;
	struct Fields {
		Gurax_PackedUInt32_LE(Signature);
		Gurax_PackedUInt16_LE(VersionNeededToExtract);
		Gurax_PackedUInt16_LE(GeneralPurposeBitFlag);
		Gurax_PackedUInt16_LE(CompressionMethod);
		Gurax_PackedUInt16_LE(LastModFileTime);
		Gurax_PackedUInt16_LE(LastModFileDate);
		Gurax_PackedUInt32_LE(Crc32);				// zero if Data Descriptor exists
		Gurax_PackedUInt32_LE(CompressedSize);	// zero if Data Descriptor exists
		Gurax_PackedUInt32_LE(UncompressedSize);	// zero if Data Descriptor exists
		Gurax_PackedUInt16_LE(FileNameLength);
		Gurax_PackedUInt16_LE(ExtraFieldLength);
		// FileName (FileNameLength bytes)
		// ExtraField (ExtraFieldLength bytes)
	};
private:
	Fields _fields;
	Binary _fileName;
	Binary _extraField;
public:
	LocalFileHeader() { Gurax_PackUInt32(_fields.Signature, Signature); }
	Fields& GetFields() { return _fields; }
	const Fields& GetFields() const { return _fields; }
	bool Read(Stream& stream) {
		if (!ReadStream(stream, &_fields, 30 - 4, 4)) return false;
		if (!ReadStream(stream, _fileName,
						Gurax_UnpackUInt16(_fields.FileNameLength))) return false;
		if (!ReadStream(stream, _extraField,
						Gurax_UnpackUInt16(_fields.ExtraFieldLength))) return false;
		return true;
	}
	bool SkipOver(Stream& stream);
	bool Write(Stream& stream) {
		Gurax_PackUInt16(_fields.FileNameLength, _fileName.size());
		Gurax_PackUInt16(_fields.FileNameLength, _extraField.size());
		if (!WriteStream(stream, &_fields, 30)) return false;
		if (!WriteStream(stream, _fileName)) return false;
		if (!WriteStream(stream, _extraField)) return false;
		return true;
	}
	bool SkipFileData(Stream& stream) {
		return SkipStream(stream, Gurax_UnpackUInt32(_fields.CompressedSize));
	}
	void SetFileName(const char* fileName) { _fileName = fileName; }
	const char* GetFileName() const { return reinterpret_cast<const char*>(_fileName.c_str()); }
	bool IsEncrypted() const {
		return (Gurax_UnpackUInt16(_fields.GeneralPurposeBitFlag) & (1 << 0)) != 0;
	}
	bool IsExistDataDescriptor() const {
		return (Gurax_UnpackUInt16(_fields.GeneralPurposeBitFlag) & (1 << 3)) != 0;
	}
	bool IsStrongEncrypted() const {
		return (Gurax_UnpackUInt16(_fields.GeneralPurposeBitFlag) & (1 << 6)) != 0;
	}
	bool IsUtf8() const {
		return (Gurax_UnpackUInt16(_fields.GeneralPurposeBitFlag) & (1 << 11)) != 0;
	}
	DateTime* MakeLastModDateTime() const {
		UInt16 dosTime = Gurax_UnpackUInt16(_fields.LastModFileTime);
		UInt16 dosDate = Gurax_UnpackUInt16(_fields.LastModFileDate);
		return MakeDateTimeFromDos(dosDate, dosTime);
	}
	void Print() const {
		::printf("Signature              %08x\n", Gurax_UnpackUInt32(_fields.Signature));
		::printf("VersionNeededToExtract %04x\n", Gurax_UnpackUInt16(_fields.VersionNeededToExtract));
		::printf("GeneralPurposeBitFlag  %04x\n", Gurax_UnpackUInt16(_fields.GeneralPurposeBitFlag));
		::printf("CompressionMethod      %04x\n", Gurax_UnpackUInt16(_fields.CompressionMethod));
		::printf("LastModFileTime        %04x\n", Gurax_UnpackUInt16(_fields.LastModFileTime));
		::printf("LastModFileDate        %04x\n", Gurax_UnpackUInt16(_fields.LastModFileDate));
		::printf("Crc32                  %08x\n", Gurax_UnpackUInt32(_fields.Crc32));
		::printf("CompressedSize         %08x\n", Gurax_UnpackUInt32(_fields.CompressedSize));
		::printf("UncompressedSize       %08x\n", Gurax_UnpackUInt32(_fields.UncompressedSize));
		::printf("FileNameLength         %04x\n", Gurax_UnpackUInt16(_fields.FileNameLength));
		::printf("ExtraFieldLength       %04x\n", Gurax_UnpackUInt16(_fields.ExtraFieldLength));
	}
};

//------------------------------------------------------------------------------
// B. File data
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// C. Data descriptor
//------------------------------------------------------------------------------
class DataDescriptor {
public:
	struct Fields {
		Gurax_PackedUInt32_LE(Crc32);
		Gurax_PackedUInt32_LE(CompressedSize);
		Gurax_PackedUInt32_LE(UncompressedSize);
	};
private:
	Fields _fields;
public:
	DataDescriptor() {}
	Fields& GetFields() { return _fields; }
	const Fields& GetFields() const { return _fields; }
	bool Read(Stream& stream) {
		return ReadStream(stream, &_fields, 12);
	}
	bool Write(Stream& stream) {
		return WriteStream(stream, &_fields, 12);
	}
};

//------------------------------------------------------------------------------
// D. Archive decryption header
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// E. Archive extra data record
//------------------------------------------------------------------------------
class ArchiveExtraDataRecord {
public:
	static const UInt32 Signature = 0x08064b50;
	struct Fields {
		Gurax_PackedUInt32_LE(Signature);
		Gurax_PackedUInt32_LE(ExtraFieldLength);
		// ExtraField (ExtraFieldLength bytes)
	};
private:
	Fields _fields;
	Binary _extraField;
public:
	ArchiveExtraDataRecord() { Gurax_PackUInt32(_fields.Signature, Signature); }
	Fields& GetFields() { return _fields; }
	const Fields& GetFields() const { return _fields; }
	bool Read(Stream& stream) {
		if (!ReadStream(stream, &_fields, 8 - 4, 4)) return false;
		if (!ReadStream(stream, _extraField,
						Gurax_UnpackUInt32(_fields.ExtraFieldLength))) return false;
		return true;
	}
	bool Write(Stream& stream) {
		Gurax_PackUInt32(_fields.ExtraFieldLength, _extraField.size());
		if (!WriteStream(stream, &_fields, 8)) return false;
		if (!WriteStream(stream, _extraField)) return false;
		return true;
	}
};

//------------------------------------------------------------------------------
// F. Central directory structure
//------------------------------------------------------------------------------
class CentralFileHeader : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(CentralFileHeader);
public:
	static const UInt32 Signature = 0x02014b50;
	struct Fields {
		Gurax_PackedUInt32_LE(Signature);
		Gurax_PackedUInt16_LE(VersionMadeBy);				// only in CentralFileHeader
		Gurax_PackedUInt16_LE(VersionNeededToExtract);
		Gurax_PackedUInt16_LE(GeneralPurposeBitFlag);
		Gurax_PackedUInt16_LE(CompressionMethod);
		Gurax_PackedUInt16_LE(LastModFileTime);
		Gurax_PackedUInt16_LE(LastModFileDate);
		Gurax_PackedUInt32_LE(Crc32);
		Gurax_PackedUInt32_LE(CompressedSize);
		Gurax_PackedUInt32_LE(UncompressedSize);
		Gurax_PackedUInt16_LE(FileNameLength);
		Gurax_PackedUInt16_LE(ExtraFieldLength);
		Gurax_PackedUInt16_LE(FileCommentLength);			// only in CentralFileHeader
		Gurax_PackedUInt16_LE(DiskNumberStart);				// only in CentralFileHeader
		Gurax_PackedUInt16_LE(InternalFileAttributes);		// only in CentralFileHeader
		Gurax_PackedUInt32_LE(ExternalFileAttributes);		// only in CentralFileHeader
		Gurax_PackedUInt32_LE(RelativeOffsetOfLocalHeader);	// only in CentralFileHeader
		// FileName (FileNameLength bytes)
		// ExtraField (ExtraFieldLength bytes)
		// FileComment (FileCommentLength bytes)
	};
private:
	Fields _fields;
	Binary _fileName;
	Binary _extraField;
	Binary _fileComment;
public:
	CentralFileHeader() { Gurax_PackUInt32(_fields.Signature, Signature); }
	CentralFileHeader(const CentralFileHeader& hdr) :
		_fields(hdr._fields), _fileName(hdr._fileName),
		_extraField(hdr._extraField), _fileComment(hdr._fileComment) {}
	Fields& GetFields() { return _fields; }
	const Fields& GetFields() const { return _fields; }
	bool Read(Stream& stream) {
		if (!ReadStream(stream, &_fields, 46 - 4, 4)) return false;
		if (!ReadStream(stream, _fileName,
						Gurax_UnpackUInt16(_fields.FileNameLength))) return false;
		if (!ReadStream(stream, _extraField,
						Gurax_UnpackUInt16(_fields.ExtraFieldLength))) return false;
		if (!ReadStream(stream, _fileComment,
						Gurax_UnpackUInt16(_fields.FileCommentLength))) return false;
		return true;
	}
	bool Write(Stream& stream) {
		Gurax_PackUInt16(_fields.FileNameLength, _fileName.size());
		Gurax_PackUInt16(_fields.ExtraFieldLength, _extraField.size());
		Gurax_PackUInt16(_fields.FileCommentLength, _fileComment.size());
		if (!WriteStream(stream, &_fields, 46)) return false;
		if (!WriteStream(stream, _fileName)) return false;
		if (!WriteStream(stream, _extraField)) return false;
		if (!WriteStream(stream, _fileComment)) return false;
		return true;
	}
	bool WriteAsLocalFileHeader(Stream& stream) {
		LocalFileHeader hdr;
		LocalFileHeader::Fields& fields = hdr.GetFields();
		Gurax_PackUInt16(fields.VersionNeededToExtract,
						Gurax_UnpackUInt16(_fields.VersionNeededToExtract));
		Gurax_PackUInt16(fields.GeneralPurposeBitFlag,
						Gurax_UnpackUInt16(_fields.GeneralPurposeBitFlag));
		Gurax_PackUInt16(fields.CompressionMethod,
						Gurax_UnpackUInt16(_fields.CompressionMethod));
		Gurax_PackUInt16(fields.LastModFileTime,
						Gurax_UnpackUInt16(_fields.LastModFileTime));
		Gurax_PackUInt16(fields.LastModFileDate,
						Gurax_UnpackUInt16(_fields.LastModFileDate));
		Gurax_PackUInt32(fields.Crc32,
						Gurax_UnpackUInt32(_fields.Crc32));
		Gurax_PackUInt32(fields.CompressedSize,
						Gurax_UnpackUInt32(_fields.CompressedSize));
		Gurax_PackUInt32(fields.UncompressedSize,
						Gurax_UnpackUInt32(_fields.UncompressedSize));
		UInt16 fileNameLength = static_cast<UInt16>(_fileName.size());
		Gurax_PackUInt16(fields.FileNameLength, fileNameLength);
		UInt16 extraFieldLength = static_cast<UInt16>(_extraField.size());
		Gurax_PackUInt16(fields.ExtraFieldLength, extraFieldLength);
		if (!WriteStream(stream, &fields, 30)) return false;
		if (!WriteStream(stream, _fileName)) return false;
		if (!WriteStream(stream, _extraField)) return false;
		return true;
	}
	void SetFileName(const char* fileName) { _fileName = fileName; }
	const char* GetFileName() const { return reinterpret_cast<const char*>(_fileName.c_str()); }
	const char* GetFileComment() const { return reinterpret_cast<const char*>(_fileComment.c_str()); }
	bool IsEncrypted() const {
		return (Gurax_UnpackUInt16(_fields.GeneralPurposeBitFlag) & (1 << 0)) != 0;
	}
	bool IsExistDataDescriptor() const {
		return (Gurax_UnpackUInt16(_fields.GeneralPurposeBitFlag) & (1 << 3)) != 0;
	}
	bool IsStrongEncrypted() const {
		return (Gurax_UnpackUInt16(_fields.GeneralPurposeBitFlag) & (1 << 6)) != 0;
	}
	bool IsUtf8() const {
		return (Gurax_UnpackUInt16(_fields.GeneralPurposeBitFlag) & (1 << 11)) != 0;
	}
	UInt32 GetRelativeOffsetOfLocalHeader() const {
		return Gurax_UnpackUInt32(_fields.RelativeOffsetOfLocalHeader);
	}
	UInt16 GetCompressionMethod() const {
		return Gurax_UnpackUInt16(_fields.CompressionMethod);
	}
	DateTime* MakeLastModDateTime() const {
		UInt16 dosTime = Gurax_UnpackUInt16(_fields.LastModFileTime);
		UInt16 dosDate = Gurax_UnpackUInt16(_fields.LastModFileDate);
		return MakeDateTimeFromDos(dosDate, dosTime);
	}
	UInt32 GetCrc32() const {
		return Gurax_UnpackUInt32(_fields.Crc32);
	}
	UInt32 GetCompressedSize() const {
		return Gurax_UnpackUInt32(_fields.CompressedSize);
	}
	UInt32 GetUncompressedSize() const {
		return Gurax_UnpackUInt32(_fields.UncompressedSize);
	}
	UInt32 GetExternalFileAttributes() const {
		return Gurax_UnpackUInt32(_fields.ExternalFileAttributes);
	}
	void Print() const {
		::printf("Signature              %08x\n", Gurax_UnpackUInt32(_fields.Signature));
		::printf("VersionMadeBy          %04x\n", Gurax_UnpackUInt16(_fields.VersionMadeBy));
		::printf("VersionNeededToExtract %04x\n", Gurax_UnpackUInt16(_fields.VersionNeededToExtract));
		::printf("GeneralPurposeBitFlag  %04x\n", Gurax_UnpackUInt16(_fields.GeneralPurposeBitFlag));
		::printf("CompressionMethod      %04x\n", Gurax_UnpackUInt16(_fields.CompressionMethod));
		::printf("LastModFileTime        %04x\n", Gurax_UnpackUInt16(_fields.LastModFileTime));
		::printf("LastModFileDate        %04x\n", Gurax_UnpackUInt16(_fields.LastModFileDate));
		::printf("Crc32                  %08x\n", Gurax_UnpackUInt32(_fields.Crc32));
		::printf("CompressedSize         %08x\n", Gurax_UnpackUInt32(_fields.CompressedSize));
		::printf("UncompressedSize       %08x\n", Gurax_UnpackUInt32(_fields.UncompressedSize));
		::printf("FileNameLength         %04x\n", Gurax_UnpackUInt16(_fields.FileNameLength));
		::printf("ExtraFieldLength       %04x\n", Gurax_UnpackUInt16(_fields.ExtraFieldLength));
		::printf("FileCommentLength      %04x\n", Gurax_UnpackUInt16(_fields.FileCommentLength));
		::printf("DiskNumberStart        %04x\n", Gurax_UnpackUInt16(_fields.DiskNumberStart));
		::printf("InternalFileAttributes %04x\n", Gurax_UnpackUInt16(_fields.InternalFileAttributes));
		::printf("ExternalFileAttributes %08x\n", Gurax_UnpackUInt32(_fields.ExternalFileAttributes));
		::printf("RelativeOffsetOfLocalHeader %08x\n", Gurax_UnpackUInt32(_fields.RelativeOffsetOfLocalHeader));
	}
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const CentralFileHeader& other) const { return this == &other; }
	bool IsEqualTo(const CentralFileHeader& other) const { return IsIdentical(other); }
	bool IsLessThan(const CentralFileHeader& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const {
		return "CentralFileHeader";
	}
};

class DigitalSignature {
public:
	static const UInt32 Signature = 0x05054b50;
	struct Fields {
		Gurax_PackedUInt32_LE(Signature);
		Gurax_PackedUInt16_LE(SizeOfData);
		// Data (SizeOfData bytes)
	};
private:
	Fields _fields;
	Binary _data;
public:
	DigitalSignature() { Gurax_PackUInt32(_fields.Signature, Signature); }
	const Fields& GetFields() const { return _fields; }
	bool Read(Stream& stream) {
		if (!ReadStream(stream, &_fields, 8 - 4, 4)) return false;
		if (!ReadStream(stream, _data,
						Gurax_UnpackUInt16(_fields.SizeOfData))) return false;
		return true;
	}
	bool Write(Stream& stream) {
		Gurax_PackUInt16(_fields.SizeOfData, _data.size());
		if (!WriteStream(stream, &_fields, 8)) return false;
		if (!WriteStream(stream, _data)) return false;
		return true;
	}
};

//------------------------------------------------------------------------------
// G. Zip64 end of central directory record
//------------------------------------------------------------------------------
class Zip64EndOfCentralDirectory {
public:
	static const UInt32 Signature = 0x06064b50;
	struct Fields {
		Gurax_PackedUInt32_LE(Signature);
		Gurax_PackedUInt64_LE(SizeOfZip64EndOfCentralDirectoryRecord);
		Gurax_PackedUInt16_LE(VersionMadeBy);
		Gurax_PackedUInt16_LE(VersionNeededToExtract);
		Gurax_PackedUInt32_LE(NumberOfThisDisk);
		Gurax_PackedUInt32_LE(NumberOfTheDiskWithTheStartOfTheCentralDirectory);
		Gurax_PackedUInt64_LE(TotalNumberOfEntriesInTheCentralDirectoryOnThisDisk);
		Gurax_PackedUInt64_LE(TotalNumberOfEntriesInTheCentralDirectory);
		Gurax_PackedUInt64_LE(SizeOfTheCentralDirectory);
		Gurax_PackedUInt64_LE(OffsetOfStartOfCentralDirectoryWithRespectToTheStartingDiskNumber);
		// Zip64ExtensibleDataSector (... bytes)
	};
private:
	Fields _fields;
public:
	Zip64EndOfCentralDirectory() { Gurax_PackUInt32(_fields.Signature, Signature); }
	const Fields& GetFields() const { return _fields; }
	bool Read(Stream& stream) {
		if (!ReadStream(stream, &_fields, 56 - 4, 4)) return false;
		return true;
	}
	bool Write(Stream& stream) {
		if (!WriteStream(stream, &_fields, 56)) return false;
		return true;
	}
};

//------------------------------------------------------------------------------
// H. Zip64 end of central directory locator
//------------------------------------------------------------------------------
class Zip64EndOfCentralDirectoryLocator {
public:
	static const UInt32 Signature = 0x07064b50;
	struct Fields {
		Gurax_PackedUInt32_LE(Signature);
		Gurax_PackedUInt32_LE(NumberOfTheDiskWithTheStartOfTheZip64EndOfCentralDirectory);
		Gurax_PackedUInt64_LE(RelativeOffsetOfTheZip64EndOfCentralDirectoryRecord);
		Gurax_PackedUInt32_LE(TotalNumberOfDisks);
	};
private:
	Fields _fields;
public:
	Zip64EndOfCentralDirectoryLocator() { Gurax_PackUInt32(_fields.Signature, Signature); }
	const Fields& GetFields() const { return _fields; }
	bool Read(Stream& stream) {
		return ReadStream(stream, &_fields, 20 - 4, 4);
	}
	bool Write(Stream& stream) {
		return WriteStream(stream, &_fields, 20);
	}
};

//------------------------------------------------------------------------------
// I. End of central directory record
//------------------------------------------------------------------------------
class EndOfCentralDirectoryRecord {
public:
	static const UInt32 Signature = 0x06054b50;
	static const int MinSize = 22;
	static const Int MaxSize = 22 + 65536;
	struct Fields {
		Gurax_PackedUInt32_LE(Signature);
		Gurax_PackedUInt16_LE(NumberOfThisDisk);
		Gurax_PackedUInt16_LE(NumberOfTheDiskWithTheStartOfTheCentralDirectory);
		Gurax_PackedUInt16_LE(TotalNumberOfEntriesInTheCentralDirectoryOnThisDisk);
		Gurax_PackedUInt16_LE(TotalNumberOfEntriesInTheCentralDirectory);
		Gurax_PackedUInt32_LE(SizeOfTheCentralDirectory);
		Gurax_PackedUInt32_LE(OffsetOfStartOfCentralDirectoryWithRespectToTheStartingDiskNumber);
		Gurax_PackedUInt16_LE(ZIPFileCommentLength);
		// ZIPFileComment (ZIPFileCommentLength bytes)
	};
private:
	Fields _fields;
	Binary _zipFileComment;
public:
	EndOfCentralDirectoryRecord() { Gurax_PackUInt32(_fields.Signature, Signature); }
	Fields& GetFields() { return _fields; }
	const Fields& GetFields() const { return _fields; }
	bool Read(Stream& stream) {
		if (!ReadStream(stream, &_fields, 22 - 4, 4)) return false;
		if (!ReadStream(stream, _zipFileComment,
						Gurax_UnpackUInt16(_fields.ZIPFileCommentLength))) return false;
		return true;
	}
	bool Write(Stream& stream) {
		Gurax_PackUInt16(_fields.ZIPFileCommentLength, _zipFileComment.size());
		if (!WriteStream(stream, &_fields, 22)) return false;
		if (!WriteStream(stream, _zipFileComment)) return false;
		return true;
	}
	void Print() const {
		::printf("Signature                                                         %08x\n", Gurax_UnpackUInt32(_fields.Signature));
		::printf("NumberOfThisDisk                                                  %04x\n", Gurax_UnpackUInt16(_fields.NumberOfThisDisk));
		::printf("NumberOfTheDiskWithTheStartOfTheCentralDirectory                  %04x\n", Gurax_UnpackUInt16(_fields.NumberOfTheDiskWithTheStartOfTheCentralDirectory));
		::printf("TotalNumberOfEntriesInTheCentralDirectoryOnThisDisk               %04x\n", Gurax_UnpackUInt16(_fields.TotalNumberOfEntriesInTheCentralDirectoryOnThisDisk));
		::printf("TotalNumberOfEntriesInTheCentralDirectory                         %04x\n", Gurax_UnpackUInt16(_fields.TotalNumberOfEntriesInTheCentralDirectory));
		::printf("SizeOfTheCentralDirectory                                         %08x\n", Gurax_UnpackUInt32(_fields.SizeOfTheCentralDirectory));
		::printf("OffsetOfStartOfCentralDirectoryWithRespectToTheStartingDiskNumber %08x\n", Gurax_UnpackUInt32(_fields.OffsetOfStartOfCentralDirectoryWithRespectToTheStartingDiskNumber));
		::printf("ZIPFileCommentLength                                              %04x\n", Gurax_UnpackUInt16(_fields.ZIPFileCommentLength));
	}
};

//-----------------------------------------------------------------------------
// Directory_ZIPFile
//-----------------------------------------------------------------------------
class GURAX_DLLDECLARE Directory_ZIPFile : public Directory {
private:
	RefPtr<CentralFileHeader> _pHdr;
public:
	Directory_ZIPFile(CentralFileHeader* pHdr) :
		Directory(Directory::Type::Item,
				  PathName::SepPlatform, PathName::CaseFlagPlatform), _pHdr(pHdr) {}
	virtual Directory* DoNextChild() override;
	virtual Stream* DoOpenStream(Stream::OpenFlags openFlags) override;
	virtual Value* DoGetStatValue() override;
};

//-----------------------------------------------------------------------------
// Directory_ZIPFolder
//-----------------------------------------------------------------------------
class GURAX_DLLDECLARE Directory_ZIPFolder : public Directory_CustomContainer {
private:
	RefPtr<CentralFileHeader> _pHdr;
public:
	Directory_ZIPFolder(CentralFileHeader* pHdr) :
		Directory_CustomContainer(Directory::Type::Container,
								  PathName::SepPlatform, PathName::CaseFlagPlatform), _pHdr(pHdr) {}
	virtual Stream* DoOpenStream(Stream::OpenFlags openFlags) override;
	virtual Value* DoGetStatValue() override;
};

#if 0
// Zip64 Extended Information Extra Field (0x0001)
class Extra_ZIP64 {
public:
	static const UInt16 Tag = 0x0001;
	struct Fields {
		Gurax_PackedUInt16_LE(Tag);
		Gurax_PackedUInt16_LE(Size);
		Gurax_PackedUInt64_LE(OriginalSize);
		Gurax_PackedUInt64_LE(CompressedSize);
		Gurax_PackedUInt64_LE(RelativeHeaderOffset);
		Gurax_PackedUInt32_LE(DiskStartNumber);
	};
};

// OS/2 Extra Field (0x0009)
class Extra_OS2 {
public:
	static const UInt16 Tag = 0x0009;
	struct Fields {
		Gurax_PackedUInt16_LE(Tag);
		Gurax_PackedUInt16_LE(TSize);
		Gurax_PackedUInt32_LE(BSize);
		Gurax_PackedUInt16_LE(CType);
		Gurax_PackedUInt32_LE(EACRC);
		// CompressedBlock
	};
};

// NTFS Extra Field (0x000a)
class Extra_NTFS {
public:
	static const UInt16 Tag = 0x000a;
	struct Fields {
		Gurax_PackedUInt16_LE(Tag);
		Gurax_PackedUInt16_LE(TSize);
		// Tag1, Size1, ...
	};
};

// OpenVMS Extra Field (0x000c)
class Extra_VMS {
public:
	static const UInt16 Tag = 0x000c;
	struct Fields {
		Gurax_PackedUInt16_LE(Tag);
		Gurax_PackedUInt16_LE(TSize);
		Gurax_PackedUInt32_LE(CRC);
		// Tag1, Size1, ...
	};
};

// UNIX Extra Field (0x000d)
class Extra_UNIX {
public:
	static const UInt16 Tag = 0x000d;
	struct Fields {
		Gurax_PackedUInt16_LE(Tag);
		Gurax_PackedUInt16_LE(TSize);
		Gurax_PackedUInt32_LE(Atime);
		Gurax_PackedUInt32_LE(Mtime);
		Gurax_PackedUInt16_LE(Uid);
		Gurax_PackedUInt16_LE(Gid);
		// VariableLengthDataField
	};
};

// PATCH Descriptor Extra Field (0x000f)
class Extra_Patch {
public:
	static const UInt16 Tag = 0x000f;
	struct Fields {
		Gurax_PackedUInt16_LE(Tag);
		Gurax_PackedUInt16_LE(TSize);
		Gurax_PackedUInt16_LE(Version);
		Gurax_PackedUInt32_LE(Flags);
		Gurax_PackedUInt32_LE(OldSize);
		Gurax_PackedUInt32_LE(OldCRC);
		Gurax_PackedUInt32_LE(NewSize);
		Gurax_PackedUInt32_LE(NewCRC);
	};
};

// PKCS#7 Store for X.509 Certificates (0x0014)
class Extra_Store {
public:
	static const UInt16 Tag = 0x0014;
	struct Fields {
		Gurax_PackedUInt16_LE(Tag);
		Gurax_PackedUInt16_LE(TSize);
		// TData (TSize bytes)
	};
};

// X.509 Certificate ID and Signature for individual file (0x0015)
class Extra_CID {
public:
	static const UInt16 Tag = 0x0015;
	struct Fields {
		Gurax_PackedUInt16_LE(Tag);
		Gurax_PackedUInt16_LE(TSize);
		// TData (TSize bytes)
	};
};

// X.509 Certificate ID and Signature for central directory (0x0016)
class Extra_CDID {
public:
	static const UInt16 Tag = 0x0016;
	struct Fields {
		Gurax_PackedUInt16_LE(Tag);
		Gurax_PackedUInt16_LE(TSize);
		// TData (TSize bytes)
	};
};

// Record Management Controls (0x0018)
class Extra_RecCTL {
public:
	static const UInt16 Tag = 0x0018;
	struct Fields {
		Gurax_PackedUInt16_LE(Tag);
		Gurax_PackedUInt16_LE(CSize);
		// Tag1, Size1, Data1, ..
	};
};

// PKCS#7 Encryption Recipient Certificate List (0x0019)
class Extra_CStore {
public:
	static const UInt16 Tag = 0x0019;
	struct Fields {
		Gurax_PackedUInt16_LE(Tag);
		Gurax_PackedUInt16_LE(TSize);
		// TData (TSize bytes)
	};
};

// MVS Extra Field (0x0065)
class Extra_MVS {
public:
	static const UInt16 Tag = 0x0065;
	struct Fields {
		Gurax_PackedUInt16_LE(Tag);
		Gurax_PackedUInt16_LE(TSize);
		Gurax_PackedUInt64_LE(ID);
		// AttributeData ((TSize - 4) bytes)
	};
};

// OS/400 Extra Field (0x0065)
class Extra_OS400 {
public:
	static const UInt16 Tag = 0x0065;
	struct Fields {
		Gurax_PackedUInt16_LE(Tag);
		Gurax_PackedUInt16_LE(Size);
		Gurax_PackedUInt64_LE(ID);
		// AttributeData ((TSize - 4) bytes)
	};
};

// ZipIt Macintosh Extra Field (long) (0x2605)
class Extra_Mac2 {
public:
	static const UInt16 Tag = 0x2605;
	struct Fields {
		Gurax_PackedUInt16_LE(Tag);
		Gurax_PackedUInt16_LE(TSize);
		Gurax_PackedUInt32_BE(Signature);	// "ZPIT"
		UChar FnLen;
		// FileName, FileType, Creator
	};
};

// ZipIt Macintosh Extra Field (short, for files) (0x2705)
class Extra_Mac2b {
public:
	static const UInt16 Tag = 0x2705;
	struct Fields {
		Gurax_PackedUInt16_LE(Tag);
		Gurax_PackedUInt16_LE(TSize);
		Gurax_PackedUInt32_BE(Signature);	// "ZPIT"
		// FileType, Creator, fdFlags, reserved
	};
};

// ZipIt Macintosh Extra Field (short, for directories) (0x2805)
class Extra_Mac2c {
public:
	static const UInt16 Tag = 0x2805;
	struct Fields {
		Gurax_PackedUInt16_LE(Tag);
		Gurax_PackedUInt16_LE(TSize);
		Gurax_PackedUInt32_BE(Signature);	// "ZPIT"
		// frFlags, View
	};
};

// Info-ZIP Unicode Comment Extra Field (0x6375)
class Extra_UCom {
public:
	static const UInt16 Tag = 0x6375;
	struct Fields {
		Gurax_PackedUInt16_LE(Tag);
		Gurax_PackedUInt16_LE(TSize);
		UChar Version;
		Gurax_PackedUInt32_LE(ComCRC32);
		// UnicodeCom
	};
};

// Info-ZIP Unicode Path Extra Field (0x7075)
class Extra_UPath {
public:
	static const UInt16 Tag = 0x7075;
	struct Fields {
		Gurax_PackedUInt16_LE(Tag);
		Gurax_PackedUInt16_LE(TSize);
		UChar Version;
		Gurax_PackedUInt32_LE(NameCRC32);
		// UnicodeName
	};
};

// Microsoft Open Packaging Growth Hint (0xa220)
class Extra_MSOpen {
public:
	static const UInt16 Tag = 0xa220;
	struct Fields {
		Gurax_PackedUInt16_LE(Tag);
		Gurax_PackedUInt16_LE(TSize);
		Gurax_PackedUInt16_LE(Signature);
		Gurax_PackedUInt16_LE(PadVal);
		// Padding
	};
};

//-----------------------------------------------------------------------------
// CentralFileHeaderList
//-----------------------------------------------------------------------------
class CentralFileHeaderList : public std::vector<CentralFileHeader*> {
};

//-----------------------------------------------------------------------------
// Object_Reader
//-----------------------------------------------------------------------------
Gurax_DeclareUserClass(Reader);

class Object_reader : public Object {
private:
	AutoPtr<Stream> _pStreamSrc;
	CentralFileHeaderList _hdrList;
public:
	Gurax_DeclareObjectAccessor(reader)
public:
	Object_reader(Stream* pStreamSrc);
	CentralFileHeaderList& GetHeaderList() { return _hdrList; }
	virtual ~Object_reader();
	virtual Object* Clone() const;
	virtual String ToString(bool exprFlag);
	Stream* GetStreamSrc() { return _pStreamSrc.get(); }
	bool ReadDirectory();
};

//-----------------------------------------------------------------------------
// Object_writer
//-----------------------------------------------------------------------------
Gurax_DeclareUserClass(writer);

class Object_writer : public Object {
private:
	AutoPtr<Stream> _pStreamDst;
	UInt16 _compressionMethod;
	CentralFileHeaderList _hdrList;
public:
	Gurax_DeclareObjectAccessor(writer)
public:
	Object_writer(Stream* pStreamDst, UInt16 compressionMethod);
	CentralFileHeaderList& GetHeaderList() { return _hdrList; }
	virtual ~Object_writer();
	virtual Object* Clone() const;
	virtual String ToString(bool exprFlag);
	Stream* GetStreamDst() { return _pStreamDst.get(); }
	bool Add(Stream& streamSrc,
					const char* fileName, UInt16 compressionMethod);
	bool Finish();
	UInt16 GetCompressionMethod() const { return _compressionMethod; }
};

//-----------------------------------------------------------------------------
// Iterator_Entry
//-----------------------------------------------------------------------------
class Iterator_Entry : public Iterator {
private:
	AutoPtr<Object_reader> _pObjZipR;
	CentralFileHeaderList::iterator _ppHdr;
public:
	Iterator_Entry(Object_reader* pObjZipR);
	virtual ~Iterator_Entry();
	virtual Iterator* GetSource();
	virtual bool DoNext(Value& value);
	virtual String ToString() const;
};

//-----------------------------------------------------------------------------
// PathMgr_ZIP
//-----------------------------------------------------------------------------
class PathMgr_ZIP : public PathMgr {
public:
	virtual bool IsResponsible(const Directory* pParent, const char* pathName);
	virtual Directory* DoOpenDirectory(
		Directory* pParent, const char** pPathName, NotFoundMode notFoundMode);
};

#endif

//-----------------------------------------------------------------------------
// Stream_Reader
//-----------------------------------------------------------------------------
class Stream_Reader : public Stream {
protected:
	RefPtr<Stream> _pStreamSrc;
	RefPtr<CentralFileHeader> _pHdr;
	String _name;
	size_t _bytesUncompressed;
	size_t _bytesCompressed;
	UInt32 _crc32Expected;
	bool _seekedFlag;
	CRC32 _crc32;
public:
	Stream_Reader(Stream* pStreamSrc, CentralFileHeader* pHdr);
public:
	size_t CheckCRC32(const void* buff, size_t bytesRead);
public:
	virtual bool Initialize() = 0;
	virtual const char* GetName() const override { return _name.c_str(); }
	virtual const char* GetIdentifier() const override { return _name.c_str(); }
	virtual size_t DoWrite(const void* buff, size_t len) override { return 0; }
	virtual bool DoFlush() override { return false; }
	virtual bool DoClose() override { return true; }
	virtual size_t DoGetSize() override { return _bytesUncompressed; }
};

//-----------------------------------------------------------------------------
// Stream_Reader_Store
// Compression method #0: stored (no compression)
//-----------------------------------------------------------------------------
class Stream_Reader_Store : public Stream_Reader {
private:
	size_t _offsetTop;
public:
	Stream_Reader_Store(Stream* pStreamSrc, CentralFileHeader* pHdr);
	virtual bool Initialize() override;
	virtual size_t DoRead(void* buff, size_t bytes) override;
	virtual bool DoSeek(size_t offset, size_t offsetPrev) override;
};

//-----------------------------------------------------------------------------
// Stream_Reader_Deflate
// Compression method #8: Deflated
//-----------------------------------------------------------------------------
class Stream_Reader_Deflate : public Stream_Reader {
private:
	RefPtr<ZLib::Stream_Reader> _pStreamReader;
public:
	Stream_Reader_Deflate(Stream* pStreamSrc, CentralFileHeader* pHdr);
	virtual bool Initialize() override;
	virtual size_t DoRead(void* buff, size_t len) override;
	virtual bool DoSeek(size_t offset, size_t offsetPrev) override;
};

//-----------------------------------------------------------------------------
// Stream_Reader_BZIP2
// Compression method #12: BZIP2
//-----------------------------------------------------------------------------
class Stream_Reader_BZIP2 : public Stream_Reader {
private:
	RefPtr<BZLib::Stream_Reader> _pStreamReader;
public:
	Stream_Reader_BZIP2(Stream* pStreamSrc, CentralFileHeader* pHdr);
	virtual bool Initialize() override;
	virtual size_t DoRead(void* buff, size_t len) override;
	virtual bool DoSeek(size_t offset, size_t offsetPrev) override;
};

//-----------------------------------------------------------------------------
// Stream_Reader_Deflate64
// Compression method #9: Enhanced Deflating using Deflate64(tm)
//-----------------------------------------------------------------------------
class Stream_Reader_Deflate64 : public Stream_Reader {
public:
	Stream_Reader_Deflate64(Stream* pStreamSrc, CentralFileHeader* pHdr);
	virtual bool Initialize() override;
	virtual size_t DoRead(void* buff, size_t len) override;
	virtual bool DoSeek(size_t offset, size_t offsetPrev) override;
};

Gurax_EndModuleScope(zip)

#endif
