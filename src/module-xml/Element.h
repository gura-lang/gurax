//==============================================================================
// Element.h
//==============================================================================
#ifndef GURAX_MODULE_XML_ELEMENT_H
#define GURAX_MODULE_XML_ELEMENT_H
#include <gurax.h>
#include "Attr.h"

Gurax_BeginModuleScope(xml)

class ElementOwner;

//------------------------------------------------------------------------------
// Element
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Element : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Element);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("xml.Element");
private:
	RefPtr<ElementOwner> _pElementsChild;
public:
	// Constructor
	Element() {}
	// Copy constructor/operator
	Element(const Element& src) = delete;
	Element& operator=(const Element& src) = delete;
	// Move constructor/operator
	Element(Element&& src) noexcept = delete;
	Element& operator=(Element&& src) noexcept = delete;
protected:
	~Element() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Element& other) const { return this == &other; }
	bool IsEqualTo(const Element& other) const { return IsIdentical(other); }
	bool IsLessThan(const Element& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// ElementList
//------------------------------------------------------------------------------
class ElementList : public ListBase<Element*> {
};

//------------------------------------------------------------------------------
// ElementOwner
//------------------------------------------------------------------------------
class ElementOwner : public ElementList, public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(ElementOwner);
public:
	ElementOwner() {}
	~ElementOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(xml)

#endif
