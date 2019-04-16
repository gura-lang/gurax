//==============================================================================
// ArgPicker.h
//==============================================================================
#ifndef GURAX_ARGPICKER_H
#define GURAX_ARGPICKER_H
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
// ArgPicker
//------------------------------------------------------------------------------
class ArgPicker {
private:
	ArgSlot* _pArgSlot;
	RefPtr<Value> _pValuePicked;
public:
	// Constructor
	ArgPicker(Argument& argument) : _pArgSlot(argument.GetArgSlotFirst()) {}
	// Copy constructor/operator
	ArgPicker(const ArgPicker& src) = delete;
	ArgPicker& operator=(const ArgPicker& src) = delete;
	// Move constructor/operator
	ArgPicker(ArgPicker&& src) = delete;
	ArgPicker& operator=(ArgPicker&& src) noexcept = delete;
	// Destructor
	~ArgPicker() = default;
public:
	bool IsDefined() const { return _pArgSlot && _pArgSlot->IsDefined(); }
public:
	Value* PickValue();
	Bool PickBool()				{ return PickValue()->GetBool(); }
	size_t PickSizeT()			{ return dynamic_cast<Value_Number*>(PickValue())->GetSizeT(); }
	Char PickChar()				{ return dynamic_cast<Value_Number*>(PickValue())->GetChar(); }
	UChar PickUChar()			{ return dynamic_cast<Value_Number*>(PickValue())->GetUChar(); }
	Short PickShort()			{ return dynamic_cast<Value_Number*>(PickValue())->GetShort(); }
	UShort PickUShort()			{ return dynamic_cast<Value_Number*>(PickValue())->GetUShort(); }
	Int PickInt()				{ return dynamic_cast<Value_Number*>(PickValue())->GetInt(); }
	UInt PickUInt()				{ return dynamic_cast<Value_Number*>(PickValue())->GetUInt(); }
	Long PickLong()				{ return dynamic_cast<Value_Number*>(PickValue())->GetLong(); }
	ULong PickULong()			{ return dynamic_cast<Value_Number*>(PickValue())->GetULong(); }
	Int8 PickInt8()				{ return dynamic_cast<Value_Number*>(PickValue())->GetInt8(); }
	UInt8 PickUInt8()			{ return dynamic_cast<Value_Number*>(PickValue())->GetUInt8(); }
	Int16 PickInt16()			{ return dynamic_cast<Value_Number*>(PickValue())->GetInt16(); }
	UInt16 PickUInt16()			{ return dynamic_cast<Value_Number*>(PickValue())->GetUInt16(); }
	Int32 PickInt32()			{ return dynamic_cast<Value_Number*>(PickValue())->GetInt32(); }
	UInt32 PickUInt32()			{ return dynamic_cast<Value_Number*>(PickValue())->GetUInt32(); }
	Int64 PickInt64()			{ return dynamic_cast<Value_Number*>(PickValue())->GetInt64(); }
	UInt64 PickUInt64()			{ return dynamic_cast<Value_Number*>(PickValue())->GetUInt64(); }
	Float PickFloat()			{ return dynamic_cast<Value_Number*>(PickValue())->GetFloat(); }
	Double PickDouble()			{ return dynamic_cast<Value_Number*>(PickValue())->GetDouble(); }
	const Symbol* PickSymbol()	{ return dynamic_cast<Value_Symbol*>(PickValue())->GetSymbol(); }
	const char* PickString()		{ return dynamic_cast<Value_String*>(PickValue())->GetString(); }
	const String& PickStringSTL() { return dynamic_cast<Value_String*>(PickValue())->GetStringSTL(); }
	Stream& PickStream();
	const ValueList& PickList()	{ return dynamic_cast<Value_List*>(PickValue())->GetValueOwner(); }
	Iterator& PickIterator();
	const Expr& PickExpr()		{ return dynamic_cast<Value_Expr*>(PickValue())->GetExpr(); }
	DateTime& PickDateTime()		{ return dynamic_cast<Value_DateTime*>(PickValue())->GetDateTime(); }
	TimeDelta& PickTimeDelta()	{ return dynamic_cast<Value_TimeDelta*>(PickValue())->GetTimeDelta(); }
};

}

#endif
