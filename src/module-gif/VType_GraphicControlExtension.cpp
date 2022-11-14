//==============================================================================
// VType_GraphicControlExtension.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(gif)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(gif.GraphicControlExtension, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(gif.GraphicControlExtension, `en)}

${help.ComposeMethodHelp(gif.GraphicControlExtension, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// gif.GraphicControlExtension#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(GraphicControlExtension, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(GraphicControlExtension, MethodSkeleton)
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
// gif.GraphicControlExtension#BlockSize
Gurax_DeclareProperty_R(GraphicControlExtension, BlockSize)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(GraphicControlExtension, BlockSize)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& graphicControlExtension = valueThis.GetGraphicBlock().GetGraphicControl();
	return new Value_Number(graphicControlExtension.BlockSize);
}

// gif.GraphicControlExtension#DelayTime
Gurax_DeclareProperty_R(GraphicControlExtension, DelayTime)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(GraphicControlExtension, DelayTime)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& graphicControlExtension = valueThis.GetGraphicBlock().GetGraphicControl();
	return new Value_Number(Gurax_UnpackUInt16(graphicControlExtension.DelayTime));
}

// gif.GraphicControlExtension#TransparentColorIndex
Gurax_DeclareProperty_R(GraphicControlExtension, TransparentColorIndex)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(GraphicControlExtension, TransparentColorIndex)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& graphicControlExtension = valueThis.GetGraphicBlock().GetGraphicControl();
	return new Value_Number(graphicControlExtension.TransparentColorIndex);
}

// gif.GraphicControlExtension#DisposalMethod
Gurax_DeclareProperty_R(GraphicControlExtension, DisposalMethod)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(GraphicControlExtension, DisposalMethod)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& graphicControlExtension = valueThis.GetGraphicBlock().GetGraphicControl();
	return new Value_Number(graphicControlExtension.GetDisposalMethod());
}

// gif.GraphicControlExtension#UserInputFlag
Gurax_DeclareProperty_R(GraphicControlExtension, UserInputFlag)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(GraphicControlExtension, UserInputFlag)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& graphicControlExtension = valueThis.GetGraphicBlock().GetGraphicControl();
	return new Value_Bool(graphicControlExtension.GetUserInputFlag());
}

// gif.GraphicControlExtension#TransparentColorFlag
Gurax_DeclareProperty_R(GraphicControlExtension, TransparentColorFlag)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(GraphicControlExtension, TransparentColorFlag)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& graphicControlExtension = valueThis.GetGraphicBlock().GetGraphicControl();
	return new Value_Bool(graphicControlExtension.GetTransparentColorFlag());
}

//------------------------------------------------------------------------------
// VType_GraphicControlExtension
//------------------------------------------------------------------------------
VType_GraphicControlExtension VTYPE_GraphicControlExtension("GraphicControlExtension");

void VType_GraphicControlExtension::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(GraphicControlExtension, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(GraphicControlExtension, BlockSize));
	Assign(Gurax_CreateProperty(GraphicControlExtension, DelayTime));
	Assign(Gurax_CreateProperty(GraphicControlExtension, TransparentColorIndex));
	Assign(Gurax_CreateProperty(GraphicControlExtension, DisposalMethod));
	Assign(Gurax_CreateProperty(GraphicControlExtension, UserInputFlag));
	Assign(Gurax_CreateProperty(GraphicControlExtension, TransparentColorFlag));
}

//------------------------------------------------------------------------------
// Value_GraphicControlExtension
//------------------------------------------------------------------------------
VType& Value_GraphicControlExtension::vtype = VTYPE_GraphicControlExtension;

String Value_GraphicControlExtension::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "gif.GraphicControlExtension");
}

Gurax_EndModuleScope(gif)
