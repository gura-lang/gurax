//==============================================================================
// VType_CommentExtension.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(gif)

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

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// gif.CommentExtension#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(CommentExtension, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(CommentExtension, MethodSkeleton)
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
// Implementation of class property
//-----------------------------------------------------------------------------
// gif.CommentExtension#default
Gurax_DeclareClassPropertyAlias_R(CommentExtension, default_, "default")
{
	Declare(VTYPE_CommentExtension, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementClassPropertyGetter(CommentExtension, default_)
{
	return new Value_CommentExtension(Content::extensionsDefault.commentExtension, nullptr);
}

//------------------------------------------------------------------------------
// VType_CommentExtension
//------------------------------------------------------------------------------
VType_CommentExtension VTYPE_CommentExtension("CommentExtension");

void VType_CommentExtension::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(CommentExtension, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(CommentExtension, default_));
}

//------------------------------------------------------------------------------
// Value_CommentExtension
//------------------------------------------------------------------------------
VType& Value_CommentExtension::vtype = VTYPE_CommentExtension;

String Value_CommentExtension::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "gif.CommentExtension");
}

Gurax_EndModuleScope(gif)
