//==============================================================================
// Writer.h
//==============================================================================
#ifndef GURAX_MODULE_TAR_WRITER_H
#define GURAX_MODULE_TAR_WRITER_H
#include <gurax.h>

Gurax_BeginModuleScope(tar)

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
			level(Z_DEFAULT_COMPRESSION), windowBits(31),
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
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("tar.Writer");
public:
	static GzipInfo gzipInfo;
	static Bzip2Info bzip2Info;
private:
	RefPtr<Stream> _pStreamDst;
public:
	// Constructor
	Writer(Stream* pStreamDst);
	// Copy constructor/operator
	Writer(const Writer& src) = delete;
	Writer& operator=(const Writer& src) = delete;
	// Move constructor/operator
	Writer(Writer&& src) noexcept = delete;
	Writer& operator=(Writer&& src) noexcept = delete;
protected:
	~Writer() = default;
public:
	bool Add(Stream& stream, const char* fileName, RefPtr<DateTime> pDateTimeM,
					RefPtr<DateTime> pDateTimeA, RefPtr<DateTime> pDateTimeC);
	bool Add(Stream& stream, const Header& hdr);
	void Close();
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Writer& other) const { return this == &other; }
	bool IsEqualTo(const Writer& other) const { return IsIdentical(other); }
	bool IsLessThan(const Writer& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(tar)

#endif
