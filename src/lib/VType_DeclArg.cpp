//==============================================================================
// VType_DeclArg.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(DeclArg, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(DeclArg, `en)}

${help.ComposeMethodHelp(DeclArg, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// DeclArg#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(DeclArg, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(DeclArg, MethodSkeleton)
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
// DeclArg#occur
Gurax_DeclareProperty_R(DeclArg, occur)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(DeclArg, occur)
{
	const DeclArg& declArg = GetValueThis(valueTarget).GetDeclArg();
	return new Value_Symbol(
		declArg.IsOccurZeroOrOnce()? Gurax_SymbolMark(Question) :
		declArg.IsOccurZeroOrMore()? Gurax_SymbolMark(Mul) :
		declArg.IsOccurOnceOrMore()? Gurax_SymbolMark(Add) : Symbol::Empty);
}

// DeclArg#symbol
Gurax_DeclareProperty_R(DeclArg, symbol)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(DeclArg, symbol)
{
	const DeclArg& declArg = GetValueThis(valueTarget).GetDeclArg();
	return new Value_Symbol(declArg.GetSymbol());
}

// DeclArg#vtype
Gurax_DeclareProperty_R(DeclArg, vtype)
{
	Declare(VTYPE_VType, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(DeclArg, vtype)
{
	//DeclArg& declArg = GetValueThis(valueTarget).GetDeclArg();
	//return new Value_VType(declArg.GetVType());
	return Value::nil();
}

//------------------------------------------------------------------------------
// VType_DeclArg
//------------------------------------------------------------------------------
VType_DeclArg VTYPE_DeclArg("DeclArg");

void VType_DeclArg::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(DeclArg, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(DeclArg, occur));
	Assign(Gurax_CreateProperty(DeclArg, symbol));
	Assign(Gurax_CreateProperty(DeclArg, vtype));
}

//------------------------------------------------------------------------------
// Value_DeclArg
//------------------------------------------------------------------------------
VType& Value_DeclArg::vtype = VTYPE_DeclArg;

String Value_DeclArg::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetDeclArg().ToString(ss));
}

}
