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
// Pointer#Pack(format:String, args*):reduce
Gurax_DeclareMethod(Pointer, Pack)
{
	Declare(VTYPE_Pointer, Flag::Reduce);
	DeclareArg("format", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
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
	// Function body
	valueThis.GetPointer().Pack(format, valListArg);
	return valueThis.Reference();
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
Gurax_DeclareProperty_R(Pointer, offset)
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

// Pointer#uint32:[be,stay]
Gurax_DeclareProperty_RW(Pointer, uint32)
{
	Declare(VTYPE_Number, Flag::None);
	//DeclareAttrOpt(Gurax_Symbol(be));
	AddHelp(
		Gurax_Symbol(en),
		"read or write a number stored in a format of unsigned 32-bits integer.");
}

Gurax_ImplementPropertyGetter(Pointer, uint32)
{
	bool stayFlag = attr.IsSet(Gurax_Symbol(stay));
	bool bigEndianFlag = attr.IsSet(Gurax_Symbol(be));
	Pointer& pointer = GetValueThis(valueTarget).GetPointer();
	UInt32 num;
	if (stayFlag) {
		if (!(bigEndianFlag? pointer.GetStay<UInt32, true>(&num, true) : pointer.GetStay<UInt32, false>(&num, true))) {
			return Value::nil();
		}
	} else {
		if (!(bigEndianFlag? pointer.Get<UInt32, true>(&num, true) : pointer.Get<UInt32, false>(&num, true))) {
			return Value::nil();
		}
	}
	return new Value_Number(num);
}

Gurax_ImplementPropertySetter(Pointer, uint32)
{
	bool stayFlag = attr.IsSet(Gurax_Symbol(stay));
	bool bigEndianFlag = attr.IsSet(Gurax_Symbol(be));
	Pointer& pointer = GetValueThis(valueTarget).GetPointer();
	UInt32 num = Value_Number::GetNumber<UInt32>(value);
	if (stayFlag) {
		if (bigEndianFlag) { pointer.PutStay<UInt32, true>(num); } else { pointer.PutStay<UInt32, false>(num); }
	} else {
		if (bigEndianFlag) { pointer.Put<UInt32, true>(num); } else { pointer.Put<UInt32, false>(num); }
	}
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
	// Assignment of property
	Assign(Gurax_CreateProperty(Pointer, bytesAvail));
	Assign(Gurax_CreateProperty(Pointer, bytesEntire));
	Assign(Gurax_CreateProperty(Pointer, offset));
	Assign(Gurax_CreateProperty(Pointer, uint32));
	// Assignment of operator
	Gurax_AssignOpBinary(Add, Pointer, Number);
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

}
