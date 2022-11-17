//==============================================================================
// VType_Element.h
//==============================================================================
#ifndef GURAX_MODULE_XML_VTYPE_ELEMENT_H
#define GURAX_MODULE_XML_VTYPE_ELEMENT_H
#include <gurax.h>
#include "Element.h"
#include "VType_Node.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// VType_Element
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Element : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Element VTYPE_Element;

//------------------------------------------------------------------------------
// Value_Element
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Element : public Value_Node {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Element);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Element");
public:
	static VType& vtype;
public:
	// Constructor
	Value_Element() = delete;
	explicit Value_Element(Element* pElement, VType& vtype = VTYPE_Element) : Value_Node(pElement, vtype) {}
	// Copy constructor/operator
	Value_Element(const Value_Element& src) : Value_Node(src) {}
	Value_Element& operator=(const Value_Element& src) = delete;
	// Move constructor/operator
	Value_Element(Value_Element&& src) noexcept = delete;
	Value_Element& operator=(Value_Element&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Element() = default;
public:
	Element& GetElement() { return dynamic_cast<Element&>(GetNode()); }
	const Element& GetElement() const { return dynamic_cast<const Element&>(GetNode()); }
public:
	static Element& GetElement(Value& value) {
		return dynamic_cast<Value_Element&>(value).GetElement();
	}
	static const Element& GetElement(const Value& value) {
		return dynamic_cast<const Value_Element&>(value).GetElement();
	}
	static Element* GetEntityPtr(Value& value) { return &GetElement(value); }
	static const Element* GetEntityPtr(const Value& value) { return &GetElement(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetElement().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetElement().IsEqualTo(Value_Element::GetElement(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetElement().IsLessThan(Value_Element::GetElement(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
public:
	virtual bool DoSingleIndexGet(const Value& valueIndex, Value** ppValue) const;
};

Gurax_EndModuleScope(xml)

#endif
