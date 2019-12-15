//==============================================================================
// VType_Pointer.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//------------------------------------------------------------------------------
// Template function
//------------------------------------------------------------------------------
template<typename T_Num>
Value* PointerGetTmpl(Value_Pointer& valueTarget, const Attribute& attr)
{
	bool stayFlag = attr.IsSet(Gurax_Symbol(stay));
	bool bigEndianFlag = attr.IsSet(Gurax_Symbol(be));
	Pointer& pointer = valueTarget.GetPointer();
	T_Num num;
	if (stayFlag) {
		if (!(bigEndianFlag? pointer.GetStay<T_Num, true>(&num, true) : pointer.GetStay<T_Num, false>(&num, true))) {
			return Value::nil();
		}
	} else {
		if (!(bigEndianFlag? pointer.Get<T_Num, true>(&num, true) : pointer.Get<T_Num, false>(&num, true))) {
			return Value::nil();
		}
	}
	return new Value_Number(num);
}

template<typename T_Num>
void PointerPutTmpl(Value_Pointer& valueTarget, const Attribute& attr, const Value& value)
{
	bool stayFlag = attr.IsSet(Gurax_Symbol(stay));
	bool bigEndianFlag = attr.IsSet(Gurax_Symbol(be));
	Pointer& pointer = valueTarget.GetPointer();
	T_Num num = Value_Number::GetNumber<T_Num>(value);
	if (stayFlag) {
		if (bigEndianFlag) { pointer.PutStay<T_Num, true>(num); } else { pointer.PutStay<T_Num, false>(num); }
	} else {
		if (bigEndianFlag) { pointer.Put<T_Num, true>(num); } else { pointer.Put<T_Num, false>(num); }
	}
}

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Pointer() {block?}
Gurax_DeclareConstructor(Pointer)
{
	Declare(VTYPE_Pointer, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Pointer` instance.");
}

Gurax_ImplementConstructor(Pointer)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	//RefPtr<Pointer> pPointer(new Pointer(0));
	//return argument.ReturnValue(processor, new Value_Pointer(pPointer.release()));
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// Pointer#Pack(format:String, args*):reduce:[stay]
Gurax_DeclareMethod(Pointer, Pack)
{
	Declare(VTYPE_Pointer, Flag::Reduce);
	DeclareArg("format", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(stay));
	AddHelp(
		Gurax_Symbol(en),
		"Stores the given data into memory pointed by the pointer.\n");
}

Gurax_ImplementMethod(Pointer, Pack)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const char* format = args.PickString();
	const ValueList& valListArg = args.PickList();
	bool stayFlag = argument.IsSet(Gurax_Symbol(stay));
	// Function body
	if (stayFlag) {
		valueThis.GetPointer().PackStay(format, valListArg);
	} else {
		valueThis.GetPointer().Pack(format, valListArg);
	}
	return valueThis.Reference();
}

// Pointer#Unpack(format:String):[nil,stay]
Gurax_DeclareMethod(Pointer, Unpack)
{
	Declare(VTYPE_Pointer, Flag::None);
	DeclareArg("format", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(nil));
	DeclareAttrOpt(Gurax_Symbol(stay));
	AddHelp(
		Gurax_Symbol(en),
		"Extracts values from the memory based on the given format.\n");
}

Gurax_ImplementMethod(Pointer, Unpack)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const char* format = args.PickString();
	const ValueList& valListArg = args.PickList();
	bool stayFlag = argument.IsSet(Gurax_Symbol(stay));
	bool exceedErrorFlag = !argument.IsSet(Gurax_Symbol(nil));
	// Function body
	return stayFlag?
		valueThis.GetPointer().UnpackStay(format, valListArg, exceedErrorFlag) :
		valueThis.GetPointer().Unpack(format, valListArg, exceedErrorFlag);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// Pointer#bytesAvail
Gurax_DeclareProperty_R(Pointer, bytesAvail)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"the data size available from the current pointer position.");
}

Gurax_ImplementPropertyGetter(Pointer, bytesAvail)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetPointer().GetSizeAvailable());
}

// Pointer#bytesEntire
Gurax_DeclareProperty_R(Pointer, bytesEntire)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"the entire size of the memory that the pointer covers.");
}

Gurax_ImplementPropertyGetter(Pointer, bytesEntire)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetPointer().GetSizeEntire());
}

// Pointer#offset
Gurax_DeclareProperty_RW(Pointer, offset)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"the offset of the pointer.");
}

Gurax_ImplementPropertyGetter(Pointer, offset)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetPointer().GetOffset());
}

Gurax_ImplementPropertySetter(Pointer, offset)
{
	auto& valueThis = GetValueThis(valueTarget);
	size_t offset = Value_Number::GetNumberNonNeg<size_t>(value);
	if (Error::IsIssued()) return;
	valueThis.GetPointer().SetOffset(offset);
}

// Pointer#int8:[be,stay]
Gurax_DeclareProperty_RW(Pointer, int8)
{
	Declare(VTYPE_Number, Flag::None);
	//DeclareAttrOpt(Gurax_Symbol(be));
	AddHelp(
		Gurax_Symbol(en),
		"read or write a number stored in a format of signed 8-bit integer.");
}

Gurax_ImplementPropertyGetter(Pointer, int8)
{
	return PointerGetTmpl<Int8>(GetValueThis(valueTarget), attr);
}

Gurax_ImplementPropertySetter(Pointer, int8)
{
	PointerPutTmpl<Int8>(GetValueThis(valueTarget), attr, value);
}

// Pointer#int16:[be,stay]
Gurax_DeclareProperty_RW(Pointer, int16)
{
	Declare(VTYPE_Number, Flag::None);
	//DeclareAttrOpt(Gurax_Symbol(be));
	AddHelp(
		Gurax_Symbol(en),
		"read or write a number stored in a format of signed 16-bit integer.");
}

Gurax_ImplementPropertyGetter(Pointer, int16)
{
	return PointerGetTmpl<Int16>(GetValueThis(valueTarget), attr);
}

Gurax_ImplementPropertySetter(Pointer, int16)
{
	PointerPutTmpl<Int16>(GetValueThis(valueTarget), attr, value);
}

// Pointer#int32:[be,stay]
Gurax_DeclareProperty_RW(Pointer, int32)
{
	Declare(VTYPE_Number, Flag::None);
	//DeclareAttrOpt(Gurax_Symbol(be));
	AddHelp(
		Gurax_Symbol(en),
		"read or write a number stored in a format of signed 32-bit integer.");
}

Gurax_ImplementPropertyGetter(Pointer, int32)
{
	return PointerGetTmpl<Int32>(GetValueThis(valueTarget), attr);
}

Gurax_ImplementPropertySetter(Pointer, int32)
{
	PointerPutTmpl<Int32>(GetValueThis(valueTarget), attr, value);
}

// Pointer#int64:[be,stay]
Gurax_DeclareProperty_RW(Pointer, int64)
{
	Declare(VTYPE_Number, Flag::None);
	//DeclareAttrOpt(Gurax_Symbol(be));
	AddHelp(
		Gurax_Symbol(en),
		"read or write a number stored in a format of signed 64-bit integer.");
}

Gurax_ImplementPropertyGetter(Pointer, int64)
{
	return PointerGetTmpl<Int64>(GetValueThis(valueTarget), attr);
}

Gurax_ImplementPropertySetter(Pointer, int64)
{
	PointerPutTmpl<Int64>(GetValueThis(valueTarget), attr, value);
}

// Pointer#uint8:[be,stay]
Gurax_DeclareProperty_RW(Pointer, uint8)
{
	Declare(VTYPE_Number, Flag::None);
	//DeclareAttrOpt(Gurax_Symbol(be));
	AddHelp(
		Gurax_Symbol(en),
		"read or write a number stored in a format of unsigned 8-bit integer.");
}

Gurax_ImplementPropertyGetter(Pointer, uint8)
{
	return PointerGetTmpl<UInt8>(GetValueThis(valueTarget), attr);
}

Gurax_ImplementPropertySetter(Pointer, uint8)
{
	PointerPutTmpl<UInt8>(GetValueThis(valueTarget), attr, value);
}

// Pointer#uint16:[be,stay]
Gurax_DeclareProperty_RW(Pointer, uint16)
{
	Declare(VTYPE_Number, Flag::None);
	//DeclareAttrOpt(Gurax_Symbol(be));
	AddHelp(
		Gurax_Symbol(en),
		"read or write a number stored in a format of unsigned 16-bit integer.");
}

Gurax_ImplementPropertyGetter(Pointer, uint16)
{
	return PointerGetTmpl<UInt16>(GetValueThis(valueTarget), attr);
}

Gurax_ImplementPropertySetter(Pointer, uint16)
{
	PointerPutTmpl<UInt16>(GetValueThis(valueTarget), attr, value);
}

// Pointer#uint32:[be,stay]
Gurax_DeclareProperty_RW(Pointer, uint32)
{
	Declare(VTYPE_Number, Flag::None);
	//DeclareAttrOpt(Gurax_Symbol(be));
	AddHelp(
		Gurax_Symbol(en),
		"read or write a number stored in a format of unsigned 32-bit integer.");
}

Gurax_ImplementPropertyGetter(Pointer, uint32)
{
	return PointerGetTmpl<UInt32>(GetValueThis(valueTarget), attr);
}

Gurax_ImplementPropertySetter(Pointer, uint32)
{
	PointerPutTmpl<UInt32>(GetValueThis(valueTarget), attr, value);
}

// Pointer#uint64:[be,stay]
Gurax_DeclareProperty_RW(Pointer, uint64)
{
	Declare(VTYPE_Number, Flag::None);
	//DeclareAttrOpt(Gurax_Symbol(be));
	AddHelp(
		Gurax_Symbol(en),
		"read or write a number stored in a format of unsigned 64-bit integer.");
}

Gurax_ImplementPropertyGetter(Pointer, uint64)
{
	return PointerGetTmpl<UInt64>(GetValueThis(valueTarget), attr);
}

Gurax_ImplementPropertySetter(Pointer, uint64)
{
	PointerPutTmpl<UInt64>(GetValueThis(valueTarget), attr, value);
}

// Pointer#float:[be,stay]
Gurax_DeclarePropertyAlias_RW(Pointer, float_, "float")
{
	Declare(VTYPE_Number, Flag::None);
	//DeclareAttrOpt(Gurax_Symbol(be));
	AddHelp(
		Gurax_Symbol(en),
		"read or write a number stored in a format of unsigned 64-bit integer.");
}

Gurax_ImplementPropertyGetter(Pointer, float_)
{
	return PointerGetTmpl<Float>(GetValueThis(valueTarget), attr);
}

Gurax_ImplementPropertySetter(Pointer, float_)
{
	PointerPutTmpl<Float>(GetValueThis(valueTarget), attr, value);
}

// Pointer#double:[be,stay]
Gurax_DeclarePropertyAlias_RW(Pointer, double_, "double")
{
	Declare(VTYPE_Number, Flag::None);
	//DeclareAttrOpt(Gurax_Symbol(be));
	AddHelp(
		Gurax_Symbol(en),
		"read or write a number stored in a format of unsigned 64-bit integer.");
}

Gurax_ImplementPropertyGetter(Pointer, double_)
{
	return PointerGetTmpl<Double>(GetValueThis(valueTarget), attr);
}

Gurax_ImplementPropertySetter(Pointer, double_)
{
	PointerPutTmpl<Double>(GetValueThis(valueTarget), attr, value);
}

//------------------------------------------------------------------------------
// Implementation of operator
//------------------------------------------------------------------------------
// Pointer + Number
Gurax_ImplementOpBinary(Add, Pointer, Number)
{
	RefPtr<Pointer> pPointer(Value_Pointer::GetPointer(valueL).Clone());
	long offset = Value_Number::GetNumber<long>(valueR);
	if (!pPointer->Advance(offset)) return Value::nil();
	return new Value_Pointer(pPointer.release());
}

// Number + Pointer
Gurax_ImplementOpBinary(Add, Number, Pointer)
{
	long offset = Value_Number::GetNumber<long>(valueL);
	RefPtr<Pointer> pPointer(Value_Pointer::GetPointer(valueR).Clone());
	if (!pPointer->Advance(offset)) return Value::nil();
	return new Value_Pointer(pPointer.release());
}

// Pointer - Number
Gurax_ImplementOpBinary(Sub, Pointer, Number)
{
	RefPtr<Pointer> pPointer(Value_Pointer::GetPointer(valueL).Clone());
	long offset = Value_Number::GetNumber<long>(valueR);
	if (!pPointer->Advance(-offset)) return Value::nil();
	return new Value_Pointer(pPointer.release());
}

// Pointer - Pointer
Gurax_ImplementOpBinary(Sub, Pointer, Pointer)
{
	const Pointer& pointerL = Value_Pointer::GetPointer(valueL);
	const Pointer& pointerR = Value_Pointer::GetPointer(valueR);
	if (!pointerL.GetTarget().IsIdentical(&pointerR.GetTarget())) {
		Error::Issue(ErrorType::ValueError,
					 "pointers must have the same target when the offset difference is calculated");
		return Value::nil();
	}
	return new Value_Number(static_cast<Int64>(pointerL.GetOffset()) - static_cast<Int64>(pointerR.GetOffset()));
}

//------------------------------------------------------------------------------
// VType_Pointer
//------------------------------------------------------------------------------
VType_Pointer VTYPE_Pointer("Pointer");

void VType_Pointer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Pointer));
	// Assignment of method
	Assign(Gurax_CreateMethod(Pointer, Pack));
	Assign(Gurax_CreateMethod(Pointer, Unpack));
	// Assignment of property
	Assign(Gurax_CreateProperty(Pointer, bytesAvail));
	Assign(Gurax_CreateProperty(Pointer, bytesEntire));
	Assign(Gurax_CreateProperty(Pointer, offset));
	Assign(Gurax_CreateProperty(Pointer, int8));
	Assign(Gurax_CreateProperty(Pointer, int16));
	Assign(Gurax_CreateProperty(Pointer, int32));
	Assign(Gurax_CreateProperty(Pointer, int64));
	Assign(Gurax_CreateProperty(Pointer, uint8));
	Assign(Gurax_CreateProperty(Pointer, uint16));
	Assign(Gurax_CreateProperty(Pointer, uint32));
	Assign(Gurax_CreateProperty(Pointer, uint64));
	Assign(Gurax_CreateProperty(Pointer, float_));
	Assign(Gurax_CreateProperty(Pointer, double_));
	// Assignment of operator
	Gurax_AssignOpBinary(Add, Pointer, Number);
	Gurax_AssignOpBinary(Add, Number, Pointer);
	Gurax_AssignOpBinary(Sub, Pointer, Number);
	Gurax_AssignOpBinary(Sub, Pointer, Pointer);
}

Value* VType_Pointer::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	if (value.IsType(VTYPE_Binary)) {
		return new Value_Pointer(new Pointer_Binary(0, dynamic_cast<Value_Binary*>(value.Reference())));
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Value_Pointer
//------------------------------------------------------------------------------
VType& Value_Pointer::vtype = VTYPE_Pointer;

String Value_Pointer::ToStringDigest(const StringStyle& ss) const
{
	String str;
	str += "<";
	str += GetPointer().ToString(ss);
	str += ">";
	return str;
}

String Value_Pointer::ToStringDetail(const StringStyle& ss) const
{
	return ToStringDigest(ss);
}

}
