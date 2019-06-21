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
	bool _peekedFlag;
public:
	// Constructor
	ArgPicker(Argument& argument) : _pArgSlot(argument.GetArgSlotFirst()), _peekedFlag(false) {}
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
	bool IsUndefined() const { return !IsDefined(); }
	bool IsValid();
public:
	Value& PeekValue();
	Value& PickValue();
	Bool PickBool()					{ return PickValue().GetBool(); }
	size_t PickSizeT()				{ return Value_Number::GetSizeT(PickValue()); }
	Char PickChar()					{ return Value_Number::GetChar(PickValue()); }
	UChar PickUChar()				{ return Value_Number::GetUChar(PickValue()); }
	Short PickShort()				{ return Value_Number::GetShort(PickValue()); }
	UShort PickUShort()				{ return Value_Number::GetUShort(PickValue()); }
	Int PickInt()					{ return Value_Number::GetInt(PickValue()); }
	UInt PickUInt()					{ return Value_Number::GetUInt(PickValue()); }
	Long PickLong()					{ return Value_Number::GetLong(PickValue()); }
	ULong PickULong()				{ return Value_Number::GetULong(PickValue()); }
	Int8 PickInt8()					{ return Value_Number::GetInt8(PickValue()); }
	UInt8 PickUInt8()				{ return Value_Number::GetUInt8(PickValue()); }
	Int16 PickInt16()				{ return Value_Number::GetInt16(PickValue()); }
	UInt16 PickUInt16()				{ return Value_Number::GetUInt16(PickValue()); }
	Int32 PickInt32()				{ return Value_Number::GetInt32(PickValue()); }
	UInt32 PickUInt32()				{ return Value_Number::GetUInt32(PickValue()); }
	Int64 PickInt64()				{ return Value_Number::GetInt64(PickValue()); }
	UInt64 PickUInt64()				{ return Value_Number::GetUInt64(PickValue()); }
	Float PickFloat()				{ return Value_Number::GetFloat(PickValue()); }
	Double PickDouble()				{ return Value_Number::GetDouble(PickValue()); }
	const Symbol* PickSymbol()		{ return Value_Symbol::GetSymbol(PickValue()); }
	const char* PickString()		{ return Value_String::GetString(PickValue()); }
	const String& PickStringSTL()	{ return Value_String::GetStringSTL(PickValue()); }
	const ValueList& PickList()		{ return Value_List::GetValueOwner(PickValue()); }
	const Expr& PickExpr()			{ return Value_Expr::GetExpr(PickValue()); }
	DateTime& PickDateTime()		{ return Value_DateTime::GetDateTime(PickValue()); }
	TimeDelta& PickTimeDelta()		{ return Value_TimeDelta::GetTimeDelta(PickValue()); }
	Stream& PickStream();
	Iterator& PickIterator();
public:
	template<typename T_Num> T_Num PickRanged(Int numMin, Int numMax) {
		return Value_Number::GetRanged<T_Num>(PickValue(), numMin, numMax);
	}
};

}

#endif
