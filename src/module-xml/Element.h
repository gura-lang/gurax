//==============================================================================
// Element.h
//==============================================================================
#ifndef GURAX_MODULE_XML_ELEMENT_H
#define GURAX_MODULE_XML_ELEMENT_H
#include <gurax.h>
#include "Node.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// Element
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Element : public Node {
public:
	// Referable declaration
	Gurax_DeclareReferable(Element);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("xml.Element");
private:
	String _name;
	RefPtr<AttrOwner> _pAttrs;
	RefPtr<NodeOwner> _pNodesChild;
public:
	// Constructor
	Element(String name);
	// Copy constructor/operator
	Element(const Element& src) = delete;
	Element& operator=(const Element& src) = delete;
	// Move constructor/operator
	Element(Element&& src) noexcept = delete;
	Element& operator=(Element&& src) noexcept = delete;
protected:
	~Element() = default;
public:
	AttrOwner& GetAttrs() { return *_pAttrs; }
	NodeOwner& GetNodesChild() { return *_pNodesChild; }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Element& other) const { return this == &other; }
	bool IsEqualTo(const Element& other) const { return IsIdentical(other); }
	bool IsLessThan(const Element& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// ElementStack
//------------------------------------------------------------------------------
class ElementStack : public ListBase<Element*> {
};

Gurax_EndModuleScope(xml)

#endif
