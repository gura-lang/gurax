//==============================================================================
// ArgPicker.h
//==============================================================================
#ifndef GURAX_ARGPICKER_H
#define GURAX_ARGPICKER_H
#include "Argument.h"
#include "VType_Codec.h"
#include "VType_Color.h"
#include "VType_Complex.h"
#include "VType_Dict.h"
#include "VType_Directory.h"
#include "VType_Error.h"
#include "VType_ErrorType.h"
#include "VType_Frame.h"
#include "VType_Help.h"
#include "VType_Image.h"
#include "VType_Palette.h"
#include "VType_Pixel.h"
#include "VType_Pointer.h"
#include "VType_Random.h"
#include "VType_Stat.h"
#include "VType_Template.h"
#include "VType_DateTime.h"
#include "VType_Expr.h"
#include "VType_List.h"
#include "VType_Number.h"
#include "VType_String.h"
#include "VType_Symbol.h"
#include "VType_TimeDelta.h"

namespace Gurax {

class Function;
class Iterator;
class Stream;

//------------------------------------------------------------------------------
// ArgPicker
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ArgPicker {
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
	template<typename T_Num>
	NumList<T_Num> PickNumList() {
		return IsValid()? PickList().ToNumList<T_Num>() : NumList<T_Num>();
	}
	template<typename T_Num>
	NumList<T_Num> PickNumListRanged(T_Num numMin, T_Num numMax) {
		return IsValid()? PickList().ToNumListRanged<T_Num>(numMin, numMax) : NumList<T_Num>();
	}
	template<typename T_Num>
	NumList<T_Num> PickNumListNonNeg() {
		return IsValid()? PickList().ToNumListNonNeg<T_Num>() : NumList<T_Num>();
	}
	template<typename T_Num>
	NumList<T_Num> PickNumListPos() {
		return IsValid()? PickList().ToNumListPos<T_Num>() : NumList<T_Num>();
	}
	template<typename T>
	ListBase<T> PickListT(std::function<T(Value& value)> fn) {
		return IsValid()? PickList().ToListT<T>(fn) : ListBase<T>();
	}
	Codec& PickCodec()				{ return Pick<Value_Codec>().GetCodec(); }
	Color& PickColor()				{ return Pick<Value_Color>().GetColor(); }
	const Complex& PickComplex()	{ return Pick<Value_Complex>().GetComplex(); }
	DateTime& PickDateTime()		{ return Pick<Value_DateTime>().GetDateTime(); }
	Directory& PickDirectory()		{ return Pick<Value_Directory>().GetDirectory(); }
	const Expr& PickExpr()			{ return Pick<Value_Expr>().GetExpr(); }
	const Error& PickError()		{ return Pick<Value_Error>().GetError(); }
	const ErrorType& PickErrorType(){ return Pick<Value_ErrorType>().GetErrorType(); }
	Function& PickFunction();
	Help& PickHelp()				{ return Pick<Value_Help>().GetHelp(); }
	Image& PickImage()				{ return Pick<Value_Image>().GetImage(); }
	Iterator& PickIterator();
	const ValueList& PickList()		{ return IsValid()? Pick<Value_List>().GetValueOwner() : ValueList::Empty; }
	StringList PickStringList() {
		return Value_String::GetStringList(IsValid()? Pick<Value_List>().GetValueOwner() : ValueList::Empty);
	}
	Palette& PickPalette()			{ return Pick<Value_Palette>().GetPalette(); }
	Pixel& PickPixel()				{ return Pick<Value_Pixel>().GetPixel(); }
	Pointer& PickPointer()			{ return Pick<Value_Pointer>().GetPointer(); }
	Random& PickRandom()			{ return Pick<Value_Random>().GetRandom(); }
	Stat& PickStat()				{ return Pick<Value_Stat>().GetStat(); }
	Stream& PickStream();
	const char* PickString()		{ return Pick<Value_String>().GetString(); }
	const String& PickStringSTL()	{ return Pick<Value_String>().GetStringSTL(); }
	const StringReferable& PickStringReferable() { return Pick<Value_String>().GetStringReferable(); }
	const Symbol* PickSymbol()		{ return Pick<Value_Symbol>().GetSymbol(); }
	Template& PickTemplate()		{ return Pick<Value_Template>().GetTemplate(); }
	TimeDelta& PickTimeDelta()		{ return Pick<Value_TimeDelta>().GetTimeDelta(); }
	ValueDict& PickValueDict()		{ return Pick<Value_Dict>().GetValueDict(); }
};

}

#endif
