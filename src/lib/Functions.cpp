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
	bool IsValid() { return _pArgSlot != nullptr; }
	Value* GetValue() {
		if (!_pArgSlot) return nullptr;
		Value* pValue = _pArgSlot->GetValue();
		_pArgSlot = _pArgSlot->GetNext();
		return pValue;
	}
	const char* GetString() { return dynamic_cast<Value_String*>(GetValue())->GetString(); }
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
