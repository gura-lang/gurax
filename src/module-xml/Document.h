//==============================================================================
// Document.h
//==============================================================================
#ifndef GURAX_MODULE_XML_DOCUMENT_H
#define GURAX_MODULE_XML_DOCUMENT_H
#include <gurax.h>
#include "Element.h"
#include "XmlDecl.h"

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
	RefPtr<XmlDecl> _pXmlDecl;
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
	bool HasXmlDecl() const { return !!_pXmlDecl; }
	void SetXmlDecl(XmlDecl* pXmlDecl) { _pXmlDecl.reset(pXmlDecl); }
	XmlDecl& GetXmlDecl() { return *_pXmlDecl; }
	const XmlDecl& GetXmlDecl() const { return *_pXmlDecl; }
public:
	bool HasElementRoot() const { return !!_pElementRoot; }
	void SetElementRoot(Element* pElement) { _pElementRoot.reset(pElement); }
	Element& GetElementRoot() { return *_pElementRoot; }
	const Element& GetElementRoot() const { return *_pElementRoot; }
	Value* Path(const char* path) const;
public:
	bool Compose(Stream& stream) const;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Document& other) const { return this == &other; }
	bool IsEqualTo(const Document& other) const { return IsIdentical(other); }
	bool IsLessThan(const Document& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(xml)

#endif
