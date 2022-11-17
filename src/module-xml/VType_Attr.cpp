//==============================================================================
// VType_Attr.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(xml.Attr, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(xml.Attr, `en)}

${help.ComposeMethodHelp(xml.Attr, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// xml.Attr(name as String, value as String) {block?}
Gurax_DeclareConstructor(Attr)
{
	Declare(VTYPE_Attr, Flag::None);
	DeclareArg("name", VTYPE_String, DeclArg::Occur::Once, DeclArg::Flag::None);
	DeclareArg("value", VTYPE_String, DeclArg::Occur::Once, DeclArg::Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates a `xml.Attr` instance.
)**");
}

Gurax_ImplementConstructor(Attr)
{
	// Arguments
	ArgPicker args(argument);
	const char* name = args.PickString();
	const char* value = args.PickString();
	// Function body
	RefPtr<Attr> pAttr(new Attr(name, value));
	return argument.ReturnValue(processor, new Value_Attr(pAttr.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// xml.Attr#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Attr, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(Attr, MethodSkeleton)
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
// xml.Attr#propSkeleton
Gurax_DeclareProperty_R(Attr, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Attr, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Attr
//------------------------------------------------------------------------------
VType_Attr VTYPE_Attr("Attr");

void VType_Attr::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Attr));
	// Assignment of method
	Assign(Gurax_CreateMethod(Attr, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Attr, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Attr
//------------------------------------------------------------------------------
VType& Value_Attr::vtype = VTYPE_Attr;

String Value_Attr::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetAttr().ToString(ss));
}

Gurax_EndModuleScope(xml)
