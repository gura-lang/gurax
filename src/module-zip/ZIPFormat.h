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
// CompressionMethod
//------------------------------------------------------------------------------
struct CompressionMethod {
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

class SymbolAssoc_CompressionMethod : public SymbolAssoc<UInt16, CompressionMethod::Invalid> {
public:
	SymbolAssoc_CompressionMethod() {
		Assoc(Gurax_Symbol(store),		CompressionMethod::Store);
		Assoc(Gurax_Symbol(shrink),		CompressionMethod::Shrink);
		Assoc(Gurax_Symbol(factor1),	CompressionMethod::Factor1);
		Assoc(Gurax_Symbol(factor2),	CompressionMethod::Factor2);
		Assoc(Gurax_Symbol(factor3),	CompressionMethod::Factor3);
		Assoc(Gurax_Symbol(factor4),	CompressionMethod::Factor4);
		Assoc(Gurax_Symbol(implode),	CompressionMethod::Implode);
		Assoc(Gurax_Symbol(deflate),	CompressionMethod::Deflate);
		Assoc(Gurax_Symbol(deflate64),	CompressionMethod::Deflate64);
		Assoc(Gurax_Symbol(pkware),		CompressionMethod::PKWARE);
		Assoc(Gurax_Symbol(bzip2),		CompressionMethod::BZIP2);
		Assoc(Gurax_Symbol(lzma),		CompressionMethod::LZMA);
		Assoc(Gurax_Symbol(tersa),		CompressionMethod::TERSA);
		Assoc(Gurax_Symbol(lz77),		CompressionMethod::LZ77);
		Assoc(Gurax_Symbol(wavpack),	CompressionMethod::WavPack);
		Assoc(Gurax_Symbol(ppmd),		CompressionMethod::PPMd);
	}
	static const SymbolAssoc& GetInstance() {
		static SymbolAssoc* pSymbolAssoc = nullptr;
		return pSymbolAssoc? *pSymbolAssoc : *(pSymbolAssoc = new SymbolAssoc_CompressionMethod());
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
		Gurax_PackedUInt32_LE(CompressedSize);		// zero if Data Descriptor exists
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
	LocalFileHeader() {
		Gurax_PackUInt32(_fields.Signature, Signature);
	}
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
	bool Write(Stream& stream) const {
		if (!WriteStream(stream, &_fields, 30)) return false;
		if (!WriteStream(stream, _fileName)) return false;
		if (!WriteStream(stream, _extraField)) return false;
		return true;
	}
	bool SkipFileData(Stream& stream) {
		return SkipStream(stream, Gurax_UnpackUInt32(_fields.CompressedSize));
	}
	void SetFileName(const char* fileName) {
		_fileName = Binary(reinterpret_cast<const UInt8*>(fileName), ::strlen(fileName));
	}
	const char* GetFileName() const { return reinterpret_cast<const char*>(_fileName.c_str()); }
	bool IsEncrypted() const {
		return (Gurax_UnpackUInt16(_fields.GeneralPurposeBitFlag) & (1 << 0)) != 0;
	}
	bool DoesExistDataDescriptor() const {
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
	void Print(Stream& stream) const {
		Stream& s = stream;
		s.Printf("Signature              %08x\n", Gurax_UnpackUInt32(_fields.Signature));
		s.Printf("VersionNeededToExtract %04x\n", Gurax_UnpackUInt16(_fields.VersionNeededToExtract));
		s.Printf("GeneralPurposeBitFlag  %04x\n", Gurax_UnpackUInt16(_fields.GeneralPurposeBitFlag));
		s.Printf("CompressionMethod      %04x\n", Gurax_UnpackUInt16(_fields.CompressionMethod));
		s.Printf("LastModFileTime        %04x\n", Gurax_UnpackUInt16(_fields.LastModFileTime));
		s.Printf("LastModFileDate        %04x\n", Gurax_UnpackUInt16(_fields.LastModFileDate));
		s.Printf("Crc32                  %08x\n", Gurax_UnpackUInt32(_fields.Crc32));
		s.Printf("CompressedSize         %08x\n", Gurax_UnpackUInt32(_fields.CompressedSize));
		s.Printf("UncompressedSize       %08x\n", Gurax_UnpackUInt32(_fields.UncompressedSize));
		s.Printf("FileNameLength         %04x\n", Gurax_UnpackUInt16(_fields.FileNameLength));
		s.Printf("ExtraFieldLength       %04x\n", Gurax_UnpackUInt16(_fields.ExtraFieldLength));
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
class CentralFileHeader {
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
	CentralFileHeader() {
		Gurax_PackUInt32(_fields.Signature, Signature);
	}
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
	bool Write(Stream& stream) const {
		if (!WriteStream(stream, &_fields, 46)) return false;
		if (!WriteStream(stream, _fileName)) return false;
		if (!WriteStream(stream, _extraField)) return false;
		if (!WriteStream(stream, _fileComment)) return false;
		return true;
	}
	bool WriteAsLocalFileHeader(Stream& stream) const {
		LocalFileHeader hdr;
		LocalFileHeader::Fields& fields = hdr.GetFields();
		Gurax_PackUInt16(fields.VersionNeededToExtract, Gurax_UnpackUInt16(_fields.VersionNeededToExtract));
		Gurax_PackUInt16(fields.GeneralPurposeBitFlag, Gurax_UnpackUInt16(_fields.GeneralPurposeBitFlag));
		Gurax_PackUInt16(fields.CompressionMethod, Gurax_UnpackUInt16(_fields.CompressionMethod));
		Gurax_PackUInt16(fields.LastModFileTime, Gurax_UnpackUInt16(_fields.LastModFileTime));
		Gurax_PackUInt16(fields.LastModFileDate, Gurax_UnpackUInt16(_fields.LastModFileDate));
		Gurax_PackUInt32(fields.Crc32, Gurax_UnpackUInt32(_fields.Crc32));
		Gurax_PackUInt32(fields.CompressedSize, Gurax_UnpackUInt32(_fields.CompressedSize));
		Gurax_PackUInt32(fields.UncompressedSize, Gurax_UnpackUInt32(_fields.UncompressedSize));
		UInt16 fileNameLength = static_cast<UInt16>(_fileName.size());
		Gurax_PackUInt16(fields.FileNameLength, fileNameLength);
		UInt16 extraFieldLength = static_cast<UInt16>(_extraField.size());
		Gurax_PackUInt16(fields.ExtraFieldLength, extraFieldLength);
		if (!WriteStream(stream, &fields, 30)) return false;
		if (!WriteStream(stream, _fileName)) return false;
		if (!WriteStream(stream, _extraField)) return false;
		return true;
	}
	void SetFileName(const char* fileName) {
		_fileName = Binary(reinterpret_cast<const UInt8*>(fileName), ::strlen(fileName));
	}
	const char* GetFileName() const { return reinterpret_cast<const char*>(_fileName.c_str()); }
	const char* GetFileComment() const { return reinterpret_cast<const char*>(_fileComment.c_str()); }
	bool IsEncrypted() const {
		return (Gurax_UnpackUInt16(_fields.GeneralPurposeBitFlag) & (1 << 0)) != 0;
	}
	bool DoesExistDataDescriptor() const {
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
	bool IsFolder() const { return String::EndsWithPathSep(GetFileName()); }
	void Print(Stream& stream) const {
		Stream& s = stream;
		s.Printf("Signature                   %08x\n", Gurax_UnpackUInt32(_fields.Signature));
		s.Printf("VersionMadeBy               %04x\n", Gurax_UnpackUInt16(_fields.VersionMadeBy));
		s.Printf("VersionNeededToExtract      %04x\n", Gurax_UnpackUInt16(_fields.VersionNeededToExtract));
		s.Printf("GeneralPurposeBitFlag       %04x\n", Gurax_UnpackUInt16(_fields.GeneralPurposeBitFlag));
		s.Printf("CompressionMethod           %04x\n", Gurax_UnpackUInt16(_fields.CompressionMethod));
		s.Printf("LastModFileTime             %04x\n", Gurax_UnpackUInt16(_fields.LastModFileTime));
		s.Printf("LastModFileDate             %04x\n", Gurax_UnpackUInt16(_fields.LastModFileDate));
		s.Printf("Crc32                       %08x\n", Gurax_UnpackUInt32(_fields.Crc32));
		s.Printf("CompressedSize              %08x\n", Gurax_UnpackUInt32(_fields.CompressedSize));
		s.Printf("UncompressedSize            %08x\n", Gurax_UnpackUInt32(_fields.UncompressedSize));
		s.Printf("FileNameLength              %04x\n", Gurax_UnpackUInt16(_fields.FileNameLength));
		s.Printf("ExtraFieldLength            %04x\n", Gurax_UnpackUInt16(_fields.ExtraFieldLength));
		s.Printf("FileCommentLength           %04x\n", Gurax_UnpackUInt16(_fields.FileCommentLength));
		s.Printf("DiskNumberStart             %04x\n", Gurax_UnpackUInt16(_fields.DiskNumberStart));
		s.Printf("InternalFileAttributes      %04x\n", Gurax_UnpackUInt16(_fields.InternalFileAttributes));
		s.Printf("ExternalFileAttributes      %08x\n", Gurax_UnpackUInt32(_fields.ExternalFileAttributes));
		s.Printf("RelativeOffsetOfLocalHeader %08x\n", Gurax_UnpackUInt32(_fields.RelativeOffsetOfLocalHeader));
		s.Printf("File Name\n");
		s.Dump(_fileName.data(), _fileName.size());
		s.Printf("External Fields\n");
		s.Dump(_extraField.data(), _extraField.size());
		s.Printf("File Comment\n");
		s.Dump(_fileComment.data(), _fileComment.size());
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
	void Print(Stream& stream) const {
		Stream& s = stream;
		s.Printf("Signature                                                         %08x\n", Gurax_UnpackUInt32(_fields.Signature));
		s.Printf("NumberOfThisDisk                                                  %04x\n", Gurax_UnpackUInt16(_fields.NumberOfThisDisk));
		s.Printf("NumberOfTheDiskWithTheStartOfTheCentralDirectory                  %04x\n", Gurax_UnpackUInt16(_fields.NumberOfTheDiskWithTheStartOfTheCentralDirectory));
		s.Printf("TotalNumberOfEntriesInTheCentralDirectoryOnThisDisk               %04x\n", Gurax_UnpackUInt16(_fields.TotalNumberOfEntriesInTheCentralDirectoryOnThisDisk));
		s.Printf("TotalNumberOfEntriesInTheCentralDirectory                         %04x\n", Gurax_UnpackUInt16(_fields.TotalNumberOfEntriesInTheCentralDirectory));
		s.Printf("SizeOfTheCentralDirectory                                         %08x\n", Gurax_UnpackUInt32(_fields.SizeOfTheCentralDirectory));
		s.Printf("OffsetOfStartOfCentralDirectoryWithRespectToTheStartingDiskNumber %08x\n", Gurax_UnpackUInt32(_fields.OffsetOfStartOfCentralDirectoryWithRespectToTheStartingDiskNumber));
		s.Printf("ZIPFileCommentLength                                              %04x\n", Gurax_UnpackUInt16(_fields.ZIPFileCommentLength));
	}
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
class CentralFileHeaderList : public ListBase<CentralFileHeader*> {
};

#endif

Gurax_EndModuleScope(zip)

#endif
