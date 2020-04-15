//==============================================================================
// VType_DiffLine.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(diff)

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
// diff.DiffLine(src1, src2):[icase] {block?}
Gurax_DeclareConstructor(DiffLine)
{
	Declare(VTYPE_DiffLine, Flag::None);
	DeclareArg("src1", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareArg("src2", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(icase));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `diff.DiffLine` instance.");
}

Gurax_ImplementConstructor(DiffLine)
{
	// Arguments
	ArgPicker args(argument);
	const Value& src1 = args.PeekValue();
	const Value& src2 = args.PeekValue();
	// Function body
	bool icaseFlag = argument.IsSet(Gurax_Symbol(icase));
	RefPtr<DiffLine> pDiffLine(new DiffLine(icaseFlag));
	if (!pDiffLine->Compose(src1, src2)) return Value::nil();
	return argument.ReturnValue(processor, new Value_DiffLine(pDiffLine.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// diff.DiffLine#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(DiffLine, MethodSkeleton)
{
	Declare(VTYPE_List, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(DiffLine, MethodSkeleton)
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
// diff.DiffLine#propSkeleton
Gurax_DeclareProperty_R(DiffLine, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(DiffLine, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_DiffLine
//------------------------------------------------------------------------------
VType_DiffLine VTYPE_DiffLine("DiffLine");

void VType_DiffLine::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(DiffLine));
	// Assignment of method
	Assign(Gurax_CreateMethod(DiffLine, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(DiffLine, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_DiffLine
//------------------------------------------------------------------------------
VType& Value_DiffLine::vtype = VTYPE_DiffLine;

Gurax_EndModuleScope(diff)
