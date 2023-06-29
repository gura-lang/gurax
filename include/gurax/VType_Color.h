//==============================================================================
// VType_Color.h
//==============================================================================
#ifndef GURAX_VTYPE_COLOR_H
#define GURAX_VTYPE_COLOR_H
#include "VType_Object.h"
#include "Color.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Color
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Color : public VType {
public:
	static const SerialId serialId = 0x00000003;
public:
	VType_Color() : VType(serialId) {}
	explicit VType_Color(const Symbol* pSymbol) : VType(serialId) {}
	explicit VType_Color(const char* name) : VType(name, serialId) {}
	virtual void DoPrepare(Frame& frameOuter) override;
	virtual Value* DoCastFrom(const Value& value, DeclArg::Flags flags) const override;
};

extern GURAX_DLLDECLARE VType_Color VTYPE_Color;

//------------------------------------------------------------------------------
// Value_Color
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Color : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Color);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Color");
protected:
	Color _color;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Color() = delete;
	Value_Color(const Color& color, VType& vtype = VTYPE_Color) : Value_Object(vtype), _color(color) {}
	// Copy constructor/operator
	Value_Color(const Value_Color& src) : Value_Object(src), _color(src._color) {}
	Value_Color& operator=(const Value_Color& src) = delete;
	// Move constructor/operator
	Value_Color(Value_Color&& src) = delete;
	Value_Color& operator=(Value_Color&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Color() = default;
public:
	Color& GetColor() { return _color; }
	const Color& GetColor() const { return _color; }
public:
	static Color& GetColor(Value& value) {
		return dynamic_cast<Value_Color&>(value).GetColor();
	}
	static const Color& GetColor(const Value& value) {
		return dynamic_cast<const Value_Color&>(value).GetColor();
	}
	static Color* ValueForVector(Value& value) { return &GetColor(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetColor().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetColor().IsEqualTo(Value_Color::GetColor(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetColor().IsLessThan(Value_Color::GetColor(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif
