//==============================================================================
// Reader.h
//==============================================================================
#ifndef GURAX_MODULE_ZIP_READER_H
#define GURAX_MODULE_ZIP_READER_H
#include <gurax.h>

Gurax_BeginModuleScope(zip)

//------------------------------------------------------------------------------
// Reader
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Reader : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Reader);
public:
	// Constructor
	Reader() {}
	// Copy constructor/operator
	Reader(const Reader& src) = delete;
	Reader& operator=(const Reader& src) = delete;
	// Move constructor/operator
	Reader(Reader&& src) = delete;
	Reader& operator=(Reader&& src) noexcept = delete;
protected:
	~Reader() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Reader& other) const { return this == &other; }
	bool IsEqualTo(const Reader& other) const { return IsIdentical(other); }
	bool IsLessThan(const Reader& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(zip)

#endif
