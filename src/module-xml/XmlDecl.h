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
	std::unique_ptr<String> _pVersion;
	std::unique_ptr<String> _pEncoding;
	int _standalone;
public:
	// Constructor
	XmlDecl(const char* version, const char* encoding, int standalone) : Node(Type::XmlDecl),
		_pVersion(version? new String(version) : nullptr), _pEncoding(encoding? new String(encoding) : nullptr),
		_standalone(standalone) {}
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
	const char* GetVersion() const { return _pVersion? _pVersion->c_str() : nullptr; }
	const char* GetEncoding() const { return _pEncoding? _pEncoding->c_str() : nullptr; }
	bool HasStandalone() const { return _standalone >= 0; }
	bool GetStandalone() const { return static_cast<bool>(_standalone); }
	virtual bool CheckTypeMask(UInt32 typeMask, const char* tagName) const {
		return typeMask & TypeMask::XmlDecl;
	}
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
