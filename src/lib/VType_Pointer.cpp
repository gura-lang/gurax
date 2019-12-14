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
// Pointer#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(Pointer, MethodSkeleton)
{
	Declare(VTYPE_List, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Pointer, MethodSkeleton)
{
	// Target
	//auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Double num1 = args.PickNumber<Double>();
	Double num2 = args.PickNumber<Double>();
	// Function body
	return new Value_Number(num1 + num2);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
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
	Assign(Gurax_CreateMethod(Pointer, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Pointer, offset));
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
