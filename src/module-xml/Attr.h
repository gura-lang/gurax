//==============================================================================
// Attr.h
//==============================================================================
#ifndef GURAX_MODULE_XML_ATTR_H
#define GURAX_MODULE_XML_ATTR_H
#include <gurax.h>

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// Attr
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Attr : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Attr);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("xml.Attr");
public:
	// Constructor
	Attr() {}
	// Copy constructor/operator
	Attr(const Attr& src) = delete;
	Attr& operator=(const Attr& src) = delete;
	// Move constructor/operator
	Attr(Attr&& src) noexcept = delete;
	Attr& operator=(Attr&& src) noexcept = delete;
protected:
	~Attr() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Attr& other) const { return this == &other; }
	bool IsEqualTo(const Attr& other) const { return IsIdentical(other); }
	bool IsLessThan(const Attr& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// AttrList
//------------------------------------------------------------------------------
class AttrList : public ListBase<Attr*> {
};

//------------------------------------------------------------------------------
// AttrOwner
//------------------------------------------------------------------------------
class AttrOwner : public AttrList, public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(AttrOwner);
public:
	AttrOwner() {}
	~AttrOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(xml)

#endif
