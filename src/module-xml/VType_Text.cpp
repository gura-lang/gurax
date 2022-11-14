//==============================================================================
// VType_Text.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(xml.Text, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(xml.Text, `en)}

${help.ComposeMethodHelp(xml.Text, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// xml.Text(text as String) {block?}
Gurax_DeclareConstructor(Text)
{
	Declare(VTYPE_Text, Flag::None);
	DeclareArg("text", VTYPE_String, DeclArg::Occur::Once, DeclArg::Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates a `xml.Text` instance.
)**");
}

Gurax_ImplementConstructor(Text)
{
	// Arguments
	ArgPicker args(argument);
	const char* text = args.PickString();
	// Function body
	RefPtr<Text> pText(new Text(text));
	return argument.ReturnValue(processor, new Value_Text(pText.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// xml.Text#Textize()
Gurax_DeclareMethod(Text, Textize)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(Text, Textize)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return new Value_String(valueThis.GetText().Textize());
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// xml.Text#propSkeleton
Gurax_DeclareProperty_R(Text, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Text, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Text
//------------------------------------------------------------------------------
VType_Text VTYPE_Text("Text");

void VType_Text::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Node, Flag::Immutable, Gurax_CreateConstructor(Text));
	// Assignment of method
	Assign(Gurax_CreateMethod(Text, Textize));
	// Assignment of property
	Assign(Gurax_CreateProperty(Text, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Text
//------------------------------------------------------------------------------
VType& Value_Text::vtype = VTYPE_Text;

String Value_Text::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetText().ToString(ss));
}

Gurax_EndModuleScope(xml)
