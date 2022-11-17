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

${help.ComposePropertyHelp(xml.Comment, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(xml.Comment, `en)}

${help.ComposeMethodHelp(xml.Comment, `en)}
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
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates a `xml.Comment` instance.
)**");
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
// xml.Comment#Textize()
Gurax_DeclareMethod(Comment, Textize)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(Comment, Textize)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return new Value_String(valueThis.GetComment().Textize());
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// xml.Comment#propSkeleton
Gurax_DeclareProperty_R(Comment, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
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
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Node, Flag::Immutable, Gurax_CreateConstructor(Comment));
	// Assignment of method
	Assign(Gurax_CreateMethod(Comment, Textize));
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
