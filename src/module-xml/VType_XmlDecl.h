//==============================================================================
// VType_XmlDecl.h
//==============================================================================
#ifndef GURAX_MODULE_XML_VTYPE_XMLDECL_H
#define GURAX_MODULE_XML_VTYPE_XMLDECL_H
#include <gurax.h>
#include "XmlDecl.h"
#include "VType_Node.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// VType_XmlDecl
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_XmlDecl : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_XmlDecl VTYPE_XmlDecl;

//------------------------------------------------------------------------------
// Value_XmlDecl
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_XmlDecl : public Value_Node {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_XmlDecl);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_XmlDecl");
public:
	static VType& vtype;
public:
	// Constructor
	Value_XmlDecl() = delete;
	explicit Value_XmlDecl(XmlDecl* pXmlDecl, VType& vtype = VTYPE_XmlDecl) : Value_Node(pXmlDecl, vtype) {}
	// Copy constructor/operator
	Value_XmlDecl(const Value_XmlDecl& src) : Value_Node(src) {}
	Value_XmlDecl& operator=(const Value_XmlDecl& src) = delete;
	// Move constructor/operator
	Value_XmlDecl(Value_XmlDecl&& src) noexcept = delete;
	Value_XmlDecl& operator=(Value_XmlDecl&& src) noexcept = delete;
protected:
	// Destructor
	~Value_XmlDecl() = default;
public:
	XmlDecl& GetXmlDecl() { return dynamic_cast<XmlDecl&>(GetNode()); }
	const XmlDecl& GetXmlDecl() const { return dynamic_cast<const XmlDecl&>(GetNode()); }
public:
	static XmlDecl& GetXmlDecl(Value& value) {
		return dynamic_cast<Value_XmlDecl&>(value).GetXmlDecl();
	}
	static const XmlDecl& GetXmlDecl(const Value& value) {
		return dynamic_cast<const Value_XmlDecl&>(value).GetXmlDecl();
	}
	static XmlDecl* GetEntityPtr(Value& value) { return &GetXmlDecl(value); }
	static const XmlDecl* GetEntityPtr(const Value& value) { return &GetXmlDecl(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetXmlDecl().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetXmlDecl().IsEqualTo(Value_XmlDecl::GetXmlDecl(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetXmlDecl().IsLessThan(Value_XmlDecl::GetXmlDecl(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(xml)

#endif
