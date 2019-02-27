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
	Bool GetBool()				{ return GetValue()->GetBool(); }
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
	const Symbol* GetSymbol()	{ return dynamic_cast<Value_Symbol*>(GetValue())->GetSymbol(); }
	const char* GetString()		{ return dynamic_cast<Value_String*>(GetValue())->GetString(); }
	const String& GetStringSTL() { return dynamic_cast<Value_String*>(GetValue())->GetStringSTL(); }
	Stream& GetStream()			{ return dynamic_cast<Value_Stream*>(GetValue())->GetStream(); }
	ValueTypedOwner& GetList()	{ return dynamic_cast<Value_List*>(GetValue())->GetValueTypedOwner(); }
	Iterator& GetIterator()		{ return dynamic_cast<Value_Iterator*>(GetValue())->GetIterator(); }
	const Expr& GetExpr()		{ return dynamic_cast<Value_Expr*>(GetValue())->GetExpr(); }
	DateTime& GetDateTime()		{ return dynamic_cast<Value_DateTime*>(GetValue())->GetDateTime(); }
	TimeDelta& GetTimeDelta()	{ return dynamic_cast<Value_TimeDelta*>(GetValue())->GetTimeDelta(); }
};

#define Gurax_DeclareFunctionAlias(name, strName) \
class Function_##name : public Function { \
public: \
	Function_##name(const char* name_ = strName); \
	virtual Value* Eval(const Argument& argument) const override; \
}; \
Function_##name::Function_##name(const char* name_) : Function(name_) \

#define Gurax_DeclareFunction(name) Gurax_DeclareFunctionAlias(name, #name)

#define Gurax_ImplementFunction(name) \
Value* Function_##name::Eval(const Argument& argument) const

#define Gurax_AssignFunction(name) \
frame.AssignFunction(new Function_##name())

#define Gurax_DeclareStatementAlias(name, strName) \
class Statement_##name : public Function { \
public: \
	Statement_##name(const char* name_ = strName); \
	virtual void Compose(Composer& composer, const Expr_Caller* pExprCaller) const override; \
}; \
Statement_##name::Statement_##name(const char* name_) : Function(name_) \

#define Gurax_DeclareStatement(name) Gurax_DeclareStatementAlias(name, #name)

#define Gurax_ImplementStatement(name) \
void Statement_##name::Compose(Composer& composer, const Expr_Caller* pExprCaller) const

#define Gurax_AssignStatement(name) \
frame.AssignFunction(new Statement_##name())

// if (cond) {block}
Gurax_DeclareStatementAlias(if_, "if")
{
}

Gurax_ImplementStatement(if_)
{
	do {
		const Expr* pExpr = pExprCaller->GetExprCdrHead();
		pExpr->Compose(composer);
	} while (0);
	auto pPUnit = composer.Add_BranchIfNot(pExprCaller);
	pExprCaller->GetExprBlock()->Compose(composer);
	pPUnit->SetPUnitAtMerging(composer.GetPUnitLast());
}

// repeat (cond) {block}
Gurax_DeclareStatement(repeat)
{
}

Gurax_ImplementStatement(repeat)
{
	do {
		const Expr* pExpr = pExprCaller->GetExprCdrHead();
		pExpr->Compose(composer);
	} while (0);
	auto pPUnit = composer.Add_BranchIfNot(pExprCaller);
	pExprCaller->GetExprBlock()->Compose(composer);
	composer.Add_Jump(pExprCaller, nullptr);
	pPUnit->SetPUnitAtMerging(composer.GetPUnitLast());
}

// Print(str:String):void
Gurax_DeclareFunction(Print)
{
	DeclareCaller(VTYPE_Nil, DeclCaller::Flag::None);
	DeclareArg("str", VTYPE_String, DeclArg::OccurPattern::Once, DeclArg::Flag::None, nullptr);
}

Gurax_ImplementFunction(Print)
{
	ArgAccessor args(argument);
	const char* str = args.GetString();
	Stream::COut->Print(str);
	return Value::nil();
}

void AssignFunctions(Frame& frame)
{
	Gurax_AssignStatement(if_);
	Gurax_AssignStatement(repeat);
	Gurax_AssignFunction(Print);
}

}
