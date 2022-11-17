//==============================================================================
// VType_Text.h
//==============================================================================
#ifndef GURAX_MODULE_XML_VTYPE_TEXT_H
#define GURAX_MODULE_XML_VTYPE_TEXT_H
#include <gurax.h>
#include "Text.h"
#include "VType_Node.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// VType_Text
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Text : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Text VTYPE_Text;

//------------------------------------------------------------------------------
// Value_Text
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Text : public Value_Node {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Text);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Text");
public:
	static VType& vtype;
public:
	// Constructor
	Value_Text() = delete;
	explicit Value_Text(Text* pText, VType& vtype = VTYPE_Text) : Value_Node(pText, vtype) {}
	// Copy constructor/operator
	Value_Text(const Value_Text& src) : Value_Node(src) {}
	Value_Text& operator=(const Value_Text& src) = delete;
	// Move constructor/operator
	Value_Text(Value_Text&& src) noexcept = delete;
	Value_Text& operator=(Value_Text&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Text() = default;
public:
	Text& GetText() { return dynamic_cast<Text&>(GetNode()); }
	const Text& GetText() const { return dynamic_cast<const Text&>(GetNode()); }
public:
	static Text& GetText(Value& value) {
		return dynamic_cast<Value_Text&>(value).GetText();
	}
	static const Text& GetText(const Value& value) {
		return dynamic_cast<const Value_Text&>(value).GetText();
	}
	static Text* GetEntityPtr(Value& value) { return &GetText(value); }
	static const Text* GetEntityPtr(const Value& value) { return &GetText(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetText().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetText().IsEqualTo(Value_Text::GetText(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetText().IsLessThan(Value_Text::GetText(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(xml)

#endif
