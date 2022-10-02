//==============================================================================
// VType_Comment.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(xml)

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
// xml.Comment(data as String) {block?}
Gurax_DeclareConstructor(Comment)
{
	Declare(VTYPE_Comment, Flag::None);
	DeclareArg("data", VTYPE_String, DeclArg::Occur::Once, DeclArg::Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `xml.Comment` instance.");
}

Gurax_ImplementConstructor(Comment)
{
	// Arguments
	ArgPicker args(argument);
	const char* data = args.PickString();
	// Function body
	RefPtr<Comment> pComment(new Comment(data));
	return argument.ReturnValue(processor, new Value_Comment(pComment.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// xml.Comment#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Comment, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Comment, MethodSkeleton)
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
// xml.Comment#propSkeleton
Gurax_DeclareProperty_R(Comment, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Comment, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Comment
//------------------------------------------------------------------------------
VType_Comment VTYPE_Comment("Comment");

void VType_Comment::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Node, Flag::Immutable, Gurax_CreateConstructor(Comment));
	// Assignment of method
	Assign(Gurax_CreateMethod(Comment, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Comment, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Comment
//------------------------------------------------------------------------------
VType& Value_Comment::vtype = VTYPE_Comment;

String Value_Comment::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetComment().ToString(ss));
}

Gurax_EndModuleScope(xml)
