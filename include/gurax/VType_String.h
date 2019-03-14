//==============================================================================
// VType_String.h
//==============================================================================
#ifndef GURAX_VTYPE_STRING_H
#define GURAX_VTYPE_STRING_H
#include "VType_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_String
//------------------------------------------------------------------------------
class VType_String : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frame) override;
	virtual Value* DoCastFrom(const Value& value) const override;
};

extern VType_String VTYPE_String;

//------------------------------------------------------------------------------
// Value_String
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_String : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_String);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_String");
private:
	RefPtr<StringReferable> _pStr;
public:
	// Constructor
	explicit Value_String(VType& vtype = VTYPE_String) :
		Value_String(new StringReferable(), vtype) {}
	explicit Value_String(String str, VType& vtype = VTYPE_String) :
		Value_String(new StringReferable(std::move(str)), vtype) {}
	explicit Value_String(StringReferable* pStr, VType& vtype = VTYPE_String) :
		Value_Object(vtype), _pStr(pStr) {}
	// Copy constructor/operator
	Value_String(const Value_String& src) :
		Value_Object(src), _pStr(src._pStr->Reference()) {}
	Value_String& operator=(const Value_String& src) = delete;
	// Move constructor/operator
	Value_String(Value_String&& src) = delete;
	Value_String& operator=(Value_String&& src) noexcept = delete;
protected:
	// Destructor
	~Value_String() = default;
public:
	const char* GetString() const { return _pStr->GetString(); }
	const String& GetStringSTL() const { return _pStr->GetStringSTL(); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return String::CalcHash(GetString());
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			String::IsEqualTo(GetString(), dynamic_cast<const Value_String*>(pValue)->GetString());
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			String::IsLessThan(GetString(), dynamic_cast<const Value_String*>(pValue)->GetString()) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDetail(const StringStyle& ss) const override {
		return _pStr->GetStringSTL().MakeQuoted(true);
	}
	virtual bool Format_s(Formatter& formatter, FormatterFlags& formatterFlags) const override;
};

}

#endif
