//==============================================================================
// VType_Attrs.h
//==============================================================================
#ifndef GURAX_MODULE_XML_VTYPE_ATTRS_H
#define GURAX_MODULE_XML_VTYPE_ATTRS_H
#include <gurax.h>
#include "Attr.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// VType_Attrs
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Attrs : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Attrs VTYPE_Attrs;

//------------------------------------------------------------------------------
// Value_Attrs
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Attrs : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Attrs);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Attrs");
protected:
	RefPtr<AttrOwner> _pAttrs;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Attrs() = delete;
	explicit Value_Attrs(AttrOwner* pAttrs, VType& vtype = VTYPE_Attrs) :
		Value_Object(vtype), _pAttrs(pAttrs) {}
	// Copy constructor/operator
	Value_Attrs(const Value_Attrs& src) :
		Value_Object(src), _pAttrs(src._pAttrs->Reference()) {}
	Value_Attrs& operator=(const Value_Attrs& src) = delete;
	// Move constructor/operator
	Value_Attrs(Value_Attrs&& src) noexcept = delete;
	Value_Attrs& operator=(Value_Attrs&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Attrs() = default;
public:
	AttrOwner& GetAttrs() { return *_pAttrs; }
	const AttrOwner& GetAttrs() const { return *_pAttrs; }
public:
	static AttrOwner& GetAttrs(Value& value) {
		return dynamic_cast<Value_Attrs&>(value).GetAttrs();
	}
	static const AttrOwner& GetAttrs(const Value& value) {
		return dynamic_cast<const Value_Attrs&>(value).GetAttrs();
	}
	static AttrOwner* GetEntityPtr(Value& value) { return &GetAttrs(value); }
	static const AttrOwner* GetEntityPtr(const Value& value) { return &GetAttrs(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return 0; }
	virtual bool IsEqualTo(const Value& value) const override { return false; }
	virtual bool IsLessThan(const Value& value) const override { return false; }
	virtual bool DoSingleIndexGet(const Value& valueIndex, Value** ppValue) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(xml)

#endif
