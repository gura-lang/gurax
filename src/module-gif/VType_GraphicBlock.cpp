//==============================================================================
// VType_GraphicBlock.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(gif)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(gif.GraphicBlock, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(gif.GraphicBlock, `en)}

${help.ComposeMethodHelp(gif.GraphicBlock, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// gif.GraphicBlock#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(GraphicBlock, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(GraphicBlock, MethodSkeleton)
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
// gif.GraphicBlock#GraphicControlExtension
Gurax_DeclareProperty_R(GraphicBlock, GraphicControlExtension)
{
	Declare(VTYPE_GraphicControlExtension, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(GraphicBlock, GraphicControlExtension)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_GraphicControlExtension(valueThis.GetGraphicBlock().Reference());
}

// gif.GraphicBlock#ImageDescriptor
Gurax_DeclareProperty_R(GraphicBlock, ImageDescriptor)
{
	Declare(VTYPE_ImageDescriptor, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(GraphicBlock, ImageDescriptor)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_ImageDescriptor(valueThis.GetGraphicBlock().Reference());
}

//------------------------------------------------------------------------------
// VType_GraphicBlock
//------------------------------------------------------------------------------
VType_GraphicBlock VTYPE_GraphicBlock("GraphicBlock");

void VType_GraphicBlock::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(GraphicBlock, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(GraphicBlock, GraphicControlExtension));
	Assign(Gurax_CreateProperty(GraphicBlock, ImageDescriptor));
}

//------------------------------------------------------------------------------
// Value_GraphicBlock
//------------------------------------------------------------------------------
VType& Value_GraphicBlock::vtype = VTYPE_GraphicBlock;

String Value_GraphicBlock::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "gif.GraphicBlock");
}

Gurax_EndModuleScope(gif)
