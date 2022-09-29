//==============================================================================
// Document.h
//==============================================================================
#ifndef GURAX_MODULE_XML_DOCUMENT_H
#define GURAX_MODULE_XML_DOCUMENT_H
#include <gurax.h>
#include "Element.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// Document
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Document : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Document);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("xml.Document");
private:
	RefPtr<Element> _pElementRoot;
public:
	// Constructor
	Document() {}
	// Copy constructor/operator
	Document(const Document& src) = delete;
	Document& operator=(const Document& src) = delete;
	// Move constructor/operator
	Document(Document&& src) noexcept = delete;
	Document& operator=(Document&& src) noexcept = delete;
protected:
	~Document() = default;
public:
	void SetElementRoot(Element* pElement) { _pElementRoot.reset(pElement); }
	Element& GetElementRoot() { return *_pElementRoot; }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Document& other) const { return this == &other; }
	bool IsEqualTo(const Document& other) const { return IsIdentical(other); }
	bool IsLessThan(const Document& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(xml)

#endif
