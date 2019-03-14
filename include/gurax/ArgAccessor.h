//==============================================================================
// ArgAccessor.h
//==============================================================================
#ifndef GURAX_ARGACCESSOR_H
#define GURAX_ARGACCESSOR_H
#include "Argument.h"
#include "VType_DateTime.h"
#include "VType_Expr.h"
#include "VType_List.h"
#include "VType_Number.h"
#include "VType_String.h"
#include "VType_Symbol.h"
#include "VType_TimeDelta.h"

namespace Gurax {

class Iterator;
class Stream;

//------------------------------------------------------------------------------
// ArgAccessor
//------------------------------------------------------------------------------
class ArgAccessor {
private:
	ArgSlot* _pArgSlot;
public:
	// Constructor
	ArgAccessor(Argument& argument) : _pArgSlot(argument.GetArgSlotFirst()) {}
	// Copy constructor/operator
	ArgAccessor(const ArgAccessor& src) = delete;
	ArgAccessor& operator=(const ArgAccessor& src) = delete;
	// Move constructor/operator
	ArgAccessor(ArgAccessor&& src) = delete;
	ArgAccessor& operator=(ArgAccessor&& src) noexcept = delete;
	// Destructor
	~ArgAccessor() = default;
public:
	bool IsValid() const { return _pArgSlot != nullptr; }
	bool IsDefined() const { return _pArgSlot && _pArgSlot->IsDefined(); }
public:
	bool FeedValue(Value* pValue);
public:
	Value* GetValue();
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
	Stream& GetStream();
	const ValueList& GetList()	{ return dynamic_cast<Value_List*>(GetValue())->GetValueOwner(); }
	Iterator& GetIterator();
	const Expr& GetExpr()		{ return dynamic_cast<Value_Expr*>(GetValue())->GetExpr(); }
	DateTime& GetDateTime()		{ return dynamic_cast<Value_DateTime*>(GetValue())->GetDateTime(); }
	TimeDelta& GetTimeDelta()	{ return dynamic_cast<Value_TimeDelta*>(GetValue())->GetTimeDelta(); }
};

}

#endif
