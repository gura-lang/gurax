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
	// Referable declaration
	Gurax_DeclareReferable(Writer);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("tar.Writer");
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
	bool Add(const char* fileName, Stream& stream);
	bool Add(const Header& hdr, Stream& stream);
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
