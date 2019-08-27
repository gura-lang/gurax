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
	void Next() { if (_pArgSlot) _pArgSlot = _pArgSlot->GetNext(); }
public:
	Value& PeekValue();
	Value& PickValue();
	Bool PickBool()					{ return PickValue().GetBool(); }
	template<typename T_Num> T_Num PickNumber() {
		return Value_Number::GetNumber<T_Num>(PickValue());
	}
	template<typename T_Num> T_Num PickNumberRanged(T_Num numMin, T_Num numMax) {
		return Value_Number::GetNumberRanged<T_Num>(PickValue(), numMin, numMax);
	}
	template<typename T_Num> T_Num PickNumberNonNeg() {
		return Value_Number::GetNumberNonNeg<T_Num>(PickValue());
	}
	template<typename T_Num> T_Num PickNumberPos() {
		return Value_Number::GetNumberPos<T_Num>(PickValue());
	}
	const Symbol* PickSymbol()		{ return Value_Symbol::GetSymbol(PickValue()); }
	const char* PickString()		{ return Value_String::GetString(PickValue()); }
	const String& PickStringSTL()	{ return Value_String::GetStringSTL(PickValue()); }
	const ValueList& PickList()		{ return Value_List::GetValueOwner(PickValue()); }
	const Expr& PickExpr()			{ return Value_Expr::GetExpr(PickValue()); }
	DateTime& PickDateTime()		{ return Value_DateTime::GetDateTime(PickValue()); }
	TimeDelta& PickTimeDelta()		{ return Value_TimeDelta::GetTimeDelta(PickValue()); }
	Stream& PickStream();
	Iterator& PickIterator();
};

}

#endif
