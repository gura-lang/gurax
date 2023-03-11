//==============================================================================
// VType_NumberTrait.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(NumberTrait, `en)}

${help.ComposeConstructorHelp(NumberTrait, `en)}

${help.ComposeMethodHelp(NumberTrait, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// NumberTrait#bytes
Gurax_DeclareProperty_R(NumberTrait, bytes)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(NumberTrait, bytes)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetBytes());
}

//------------------------------------------------------------------------------
// VType_NumberTrait
//------------------------------------------------------------------------------
VType_NumberTrait VTYPE_NumberTrait("NumberTrait");

void VType_NumberTrait::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(NumberTrait, bytes));
	// Assignment of constant
	pValue_int8.reset(new Value_NumberTrait(sizeof(Int8), Number<Int8>::Min, Number<Int8>::Max));
	pValue_uint8.reset(new Value_NumberTrait(sizeof(UInt8), Number<UInt8>::Min, Number<UInt8>::Max));
	pValue_int16.reset(new Value_NumberTrait(sizeof(Int16), Number<Int16>::Min, Number<Int16>::Max));
	pValue_uint16.reset(new Value_NumberTrait(sizeof(UInt16), Number<UInt16>::Min, Number<UInt16>::Max));
	pValue_int32.reset(new Value_NumberTrait(sizeof(Int32), Number<Int32>::Min, Number<Int32>::Max));
	pValue_uint32.reset(new Value_NumberTrait(sizeof(UInt32), Number<UInt32>::Min, Number<UInt32>::Max));
	pValue_int64.reset(new Value_NumberTrait(sizeof(Int64), Number<Int64>::Min, Number<Int64>::Max));
	pValue_uint64.reset(new Value_NumberTrait(sizeof(UInt64), Number<UInt64>::Min, Number<UInt64>::Max));
	pValue_half.reset(new Value_NumberTrait(sizeof(Half), 0, 0));
	pValue_float.reset(new Value_NumberTrait(sizeof(Float), Number<Float>::Min, Number<Float>::Max));
	pValue_double.reset(new Value_NumberTrait(sizeof(Double), Number<Double>::Min, Number<Double>::Max));
}

//------------------------------------------------------------------------------
// Value_NumberTrait
//------------------------------------------------------------------------------
VType& Value_NumberTrait::vtype = VTYPE_NumberTrait;

String Value_NumberTrait::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "NumberTrait");
}

}
