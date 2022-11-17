//==============================================================================
// Writer.h
//==============================================================================
#ifndef GURAX_MODULE_ZIP_WRITER_H
#define GURAX_MODULE_ZIP_WRITER_H
#include <gurax.h>
#include "PathExtension.h"

Gurax_BeginModuleScope(zip)

//------------------------------------------------------------------------------
// Writer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Writer : public Referable {
public:
	struct GzipInfo {
		int level;
		int windowBits;
		int memLevel;
		int strategy;
		GzipInfo() :
			level(Z_DEFAULT_COMPRESSION), windowBits(-MAX_WBITS),
			memLevel(8), strategy(Z_DEFAULT_STRATEGY) {}
	};
	struct Bzip2Info {
		int blockSize100k;
		int verbosity;
		int workFactor;
		Bzip2Info() : blockSize100k(9), verbosity(0), workFactor(0) {}
	};
public:
	// Referable declaration
	Gurax_DeclareReferable(Writer);
public:
	static GzipInfo gzipInfo;
	static Bzip2Info bzip2Info;
private:
	RefPtr<Stream> _pStreamDst;
	UInt16 _compressionMethod;
	StatExOwner _statExOwner_Folder;
	StatExOwner _statExOwner_File;
public:
	// Constructor
	Writer(Stream* pStreamDst, UInt16 compressionMethod) :
		_pStreamDst(pStreamDst), _compressionMethod(compressionMethod) {}
	// Copy constructor/operator
	Writer(const Writer& src) = delete;
	Writer& operator=(const Writer& src) = delete;
	// Move constructor/operator
	Writer(Writer&& src) = delete;
	Writer& operator=(Writer&& src) noexcept = delete;
protected:
	~Writer();
public:
	UInt16 GetCompressionMethod() { return _compressionMethod; }
	StatExOwner& GetStatExOwner_Folder() { return _statExOwner_Folder; }
	StatExOwner& GetStatExOwner_File() { return _statExOwner_File; }
	bool Add(Stream& streamSrc, const char* fileName, UInt16 compressionMethod, RefPtr<DateTime> pDateTime);
	bool AddParentFolders(const char* fileName, const DateTime& dateTime);
	bool Finish();
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Writer& other) const { return this == &other; }
	bool IsEqualTo(const Writer& other) const { return IsIdentical(other); }
	bool IsLessThan(const Writer& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(zip)

#endif
