//==============================================================================
// Functions.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// ArgAccessor
//------------------------------------------------------------------------------
class ArgAccessor {
private:
	const ArgSlot* _pArgSlot;
public:
	// Constructor
	ArgAccessor(const Argument& argument) : _pArgSlot(argument.GetArgSlotTop()) {}
	// Copy constructor/operator
	ArgAccessor(const ArgAccessor& src) = delete;
	ArgAccessor& operator=(const ArgAccessor& src) = delete;
	// Move constructor/operator
	ArgAccessor(ArgAccessor&& src) = delete;
	ArgAccessor& operator=(ArgAccessor&& src) noexcept = delete;
	// Destructor
	~ArgAccessor() = default;
public:
	bool IsInvalid() { return _pArgSlot == nullptr; }
	bool IsValid() { return _pArgSlot != nullptr; }
	Value* GetValue() {
		if (!_pArgSlot) return nullptr;
		Value* pValue = _pArgSlot->GetValue();
		_pArgSlot = _pArgSlot->GetNext();
		return pValue;
	}
	size_t GetSizeT()			{ return dynamic_cast<Value_Number*>(GetValue())->GetSizeT(); }
	Char GetChar()				{ return dynamic_cast<Value_Number*>(GetValue())->GetChar(); }
	UChar GetUChar()			{ return dynamic_cast<Value_Number*>(GetValue())->GetUChar(); }
	Short GetShort()			{ return dynamic_cast<Value_Number*>(GetValue())->GetShort(); }
	UShort GetUShort()			{ return dynamic_cast<Value_Number*>(GetValue())->GetUShort(); }
	Int GetInt()				{ return dynamic_cast<Value_Number*>(GetValue())->GetInt(); }
	UInt GetUInt()				{ return dynamic_cast<Value_Number*>(GetValue())->GetUInt(); }
	Long GetLong()				{ return dynamic_cast<Value_Number*>(GetValue())->GetLong(); }
	ULong GetULong()			{ return dynamic_cast<Value_Number*>(GetValue())->GetULong(); }
	Int8 GetInt8()				{ return dynamic_cast<Value_Number*>(GetValue())->GetInt8(); }
	UInt8 GetUInt8()			{ return dynamic_cast<Value_Number*>(GetValue())->GetUInt8(); }
	Int16 GetInt16()			{ return dynamic_cast<Value_Number*>(GetValue())->GetInt16(); }
	UInt16 GetUInt16()			{ return dynamic_cast<Value_Number*>(GetValue())->GetUInt16(); }
	Int32 GetInt32()			{ return dynamic_cast<Value_Number*>(GetValue())->GetInt32(); }
	UInt32 GetUInt32()			{ return dynamic_cast<Value_Number*>(GetValue())->GetUInt32(); }
	Int64 GetInt64()			{ return dynamic_cast<Value_Number*>(GetValue())->GetInt64(); }
	UInt64 GetUInt64()			{ return dynamic_cast<Value_Number*>(GetValue())->GetUInt64(); }
	Float GetFloat()			{ return dynamic_cast<Value_Number*>(GetValue())->GetFloat(); }
	Double GetDouble()			{ return dynamic_cast<Value_Number*>(GetValue())->GetDouble(); }
	const char* GetString()		{ return dynamic_cast<Value_String*>(GetValue())->GetString(); }
};

//------------------------------------------------------------------------------
// Function_Print
//------------------------------------------------------------------------------
class Function_Print : public Function {
public:
	Function_Print();
	// Virtual functions of Function
	virtual Value* Eval(const Argument& argument) const override;
};

Function_Print::Function_Print() : Function("Print")
{
	DeclareCaller(VTYPE_Nil, DeclCaller::Flag::None);
	DeclareArg("str", VTYPE_String, DeclArg::OccurPattern::Once, DeclArg::Flag::None, nullptr);
	DeclareAttrOpt("list");
}

Value* Function_Print::Eval(const Argument& argument) const
{
	ArgAccessor argAccessor(argument);
	const char* str = argAccessor.GetString();
	::printf("%s", str);
	return Value::nil();
}

}
