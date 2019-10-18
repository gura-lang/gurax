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
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern VType_Color VTYPE_Color;

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
	RefPtr<Color> _pColor;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Color() = delete;
	Value_Color(Color* pColor, VType& vtype = VTYPE_Color) : Value_Object(vtype), _pColor(pColor) {}
	// Copy constructor/operator
	Value_Color(const Value_Color& src) : Value_Object(src), _pColor(src._pColor.Reference()) {}
	Value_Color& operator=(const Value_Color& src) = delete;
	// Move constructor/operator
	Value_Color(Value_Color&& src) = delete;
	Value_Color& operator=(Value_Color&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Color() = default;
public:
	Color& GetColor() { return *_pColor; }
	const Color& GetColor() const { return *_pColor; }
public:
	static Color& GetColor(Value& value) {
		return dynamic_cast<Value_Color&>(value).GetColor();
	}
	static const Color& GetColor(const Value& value) {
		return dynamic_cast<const Value_Color&>(value).GetColor();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetColor().CalcHash();
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetColor().IsEqualTo(Value_Color::GetColor(*pValue));
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetColor().IsLessThan(Value_Color::GetColor(*pValue)) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDetail(const StringStyle& ss) const override {
		return GetColor().ToString(ss);
	}
};

}

#endif
