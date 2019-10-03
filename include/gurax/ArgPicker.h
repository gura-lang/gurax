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
	template<typename T_Value>
	T_Value& Peek()					{ return dynamic_cast<T_Value&>(PeekValue()); }
	template<typename T_Value>
	T_Value& Pick()					{ return dynamic_cast<T_Value&>(PickValue()); }
	Bool PickBool()					{ return PickValue().GetBool(); }
	template<typename T_Num> T_Num PickNumber() {
		return Pick<Value_Number>().GetNumber<T_Num>();
	}
	template<typename T_Num> T_Num PickNumberRanged(T_Num numMin, T_Num numMax) {
		return Pick<Value_Number>().GetNumberRanged<T_Num>(numMin, numMax);
	}
	template<typename T_Num> T_Num PickNumberNonNeg() {
		return Pick<Value_Number>().GetNumberNonNeg<T_Num>();
	}
	template<typename T_Num> T_Num PickNumberPos() {
		return Pick<Value_Number>().GetNumberPos<T_Num>();
	}
	const Symbol* PickSymbol()		{ return Pick<Value_Symbol>().GetSymbol(); }
	const char* PickString()		{ return Pick<Value_String>().GetString(); }
	const String& PickStringSTL()	{ return Pick<Value_String>().GetStringSTL(); }
	const ValueList& PickList()		{ return Pick<Value_List>().GetValueOwner(); }
	const Expr& PickExpr()			{ return Pick<Value_Expr>().GetExpr(); }
	DateTime& PickDateTime()		{ return Pick<Value_DateTime>().GetDateTime(); }
	TimeDelta& PickTimeDelta()		{ return Pick<Value_TimeDelta>().GetTimeDelta(); }
	Stream& PickStream();
	Iterator& PickIterator();
	template<typename T_Num>
	NumList<T_Num> PickNumList() {
		return Value_Number::GetNumList<T_Num>(Pick<Value_List>().GetValueOwner());
	}
	StringList PickStringList() {
		return Value_String::GetStringList(Pick<Value_List>().GetValueOwner());
	}
};

}

#endif
