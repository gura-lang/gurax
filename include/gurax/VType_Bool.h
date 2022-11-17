//==============================================================================
// VType_Bool.h
//==============================================================================
#ifndef GURAX_VTYPE_BOOL_H
#define GURAX_VTYPE_BOOL_H
#include "VType_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Bool
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Bool : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Bool VTYPE_Bool;

//------------------------------------------------------------------------------
// Value_Bool
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Bool : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Bool);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Bool");
protected:
	bool _flag;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_Bool(VType& vtype = VTYPE_Bool) :
		Value_Bool(false, vtype) {}
	explicit Value_Bool(bool flag, VType& vtype = VTYPE_Bool) :
		Value_Object(vtype), _flag(flag) {}
	// Copy constructor/operator
	Value_Bool(const Value_Bool& src) :
		Value_Object(src), _flag(src._flag) {}
	Value_Bool& operator=(const Value_Bool& src) = delete;
	// Move constructor/operator
	Value_Bool(Value_Bool&& src) = delete;
	Value_Bool& operator=(Value_Bool&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Bool() = default;
public:
	static bool GetBool(const Value& value) { return dynamic_cast<const Value_Bool&>(value).GetBool_(); }
	static bool ValueForVector(Value& value) { return GetBool(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return static_cast<size_t>(GetBool_());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) && GetBool_() == dynamic_cast<const Value_Bool&>(value).GetBool_();
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetBool_() < dynamic_cast<const Value_Bool&>(value).GetBool_() :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual bool Format_d(Formatter& formatter, FormatterFlags& formatterFlags) const override;
	virtual String ToString(const StringStyle& ss) const override;
	virtual bool GetBool() const override { return GetBool_(); }
protected:
	bool GetBool_() const { return _flag; }
};

}

#endif
