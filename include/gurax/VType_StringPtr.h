//==============================================================================
// VType_StringPtr.h
// This object type is designed to be used with Formatter.
//==============================================================================
#ifndef GURAX_VTYPE_STRINGPTR_H
#define GURAX_VTYPE_STRINGPTR_H
#include "VType_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_StringPtr
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_StringPtr : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_StringPtr VTYPE_StringPtr;

//------------------------------------------------------------------------------
// Value_StringPtr
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_StringPtr : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_StringPtr);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_StringPtr");
protected:
	const char* _str;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_StringPtr(VType& vtype = VTYPE_StringPtr) :
		Value_StringPtr("", vtype) {}
	explicit Value_StringPtr(const char* str, VType& vtype = VTYPE_StringPtr) :
		Value_Object(vtype), _str(str) {}
	// Copy constructor/operator
	Value_StringPtr(const Value_StringPtr& src) :
		Value_Object(src), _str(src._str) {}
	Value_StringPtr& operator=(const Value_StringPtr& src) = delete;
	// Move constructor/operator
	Value_StringPtr(Value_StringPtr&& src) = delete;
	Value_StringPtr& operator=(Value_StringPtr&& src) noexcept = delete;
protected:
	// Destructor
	~Value_StringPtr() = default;
public:
	const char* GetString() const { return _str; }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return String::CalcHash(GetString());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			String::IsEqualTo(GetString(), dynamic_cast<const Value_StringPtr&>(value).GetString());
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			String::IsLessThan(GetString(), dynamic_cast<const Value_StringPtr&>(value).GetString()) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
	virtual bool Format_s(Formatter& formatter, FormatterFlags& formatterFlags) const override;
};

}

#endif
