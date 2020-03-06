//==============================================================================
// IFD.h
//==============================================================================
#ifndef GURAX_MODULE_JPEG_IFD_H
#define GURAX_MODULE_JPEG_IFD_H
#include <gurax.h>

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// IFD
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE IFD : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(IFD);
public:
	// Constructor
	IFD() {}
	// Copy constructor/operator
	IFD(const IFD& src) = delete;
	IFD& operator=(const IFD& src) = delete;
	// Move constructor/operator
	IFD(IFD&& src) = delete;
	IFD& operator=(IFD&& src) noexcept = delete;
protected:
	~IFD() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const IFD& other) const { return this == &other; }
	bool IsEqualTo(const IFD& other) const { return IsIdentical(other); }
	bool IsLessThan(const IFD& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(jpeg)

#endif
