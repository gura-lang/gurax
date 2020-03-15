//==============================================================================
// IFD.h
//==============================================================================
#ifndef GURAX_MODULE_JPEG_IFD_H
#define GURAX_MODULE_JPEG_IFD_H
#include <gurax.h>
#include "Tag.h"

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// IFD
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE IFD : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(IFD);
protected:
	TagOwner _tagOwner;
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
	TagOwner& GetTagOwner() { return _tagOwner; }
	const TagOwner& GetTagOwner() const { return _tagOwner; }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const IFD& other) const { return this == &other; }
	bool IsEqualTo(const IFD& other) const { return IsIdentical(other); }
	bool IsLessThan(const IFD& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// IFDList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE IFDList : public std::vector<IFD*> {
};

//------------------------------------------------------------------------------
// IFDOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE IFDOwner : public IFDList {
public:
	~IFDOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(jpeg)

#endif
