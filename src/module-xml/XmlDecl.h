//==============================================================================
// XmlDecl.h
//==============================================================================
#ifndef GURAX_MODULE_XML_XMLDECL_H
#define GURAX_MODULE_XML_XMLDECL_H
#include <gurax.h>
#include "Node.h"
#include "Text.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// XmlDecl
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE XmlDecl : public Node {
public:
	// Referable declaration
	Gurax_DeclareReferable(XmlDecl);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("xml.XmlDecl");
public:
	String _version;
	String _encoding;
	int _standalone;
public:
	// Constructor
	XmlDecl(String version, String encoding, int standalone) : Node(Type::XmlDecl),
		_version(version), _encoding(encoding), _standalone(standalone) {}
	// Copy constructor/operator
	XmlDecl(const XmlDecl& src) = delete;
	XmlDecl& operator=(const XmlDecl& src) = delete;
	// Move constructor/operator
	XmlDecl(XmlDecl&& src) noexcept = delete;
	XmlDecl& operator=(XmlDecl&& src) noexcept = delete;
protected:
	~XmlDecl() = default;
public:
	String Textize() const;
	virtual Value* CreateValue() const override;
	virtual bool Compose(Stream& stream) const override;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const XmlDecl& other) const { return this == &other; }
	bool IsEqualTo(const XmlDecl& other) const { return IsIdentical(other); }
	bool IsLessThan(const XmlDecl& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(xml)

#endif
