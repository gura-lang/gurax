//==============================================================================
// VType_XmlDecl.cpp
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
// xml.XmlDecl(version as String, encoding as String, standalone as Bool) {block?}
Gurax_DeclareConstructor(XmlDecl)
{
	Declare(VTYPE_XmlDecl, Flag::None);
	DeclareArg("version", VTYPE_String, DeclArg::Occur::Once, DeclArg::Flag::None);
	DeclareArg("encoding", VTYPE_String, DeclArg::Occur::Once, DeclArg::Flag::None);
	DeclareArg("standalone", VTYPE_Bool, DeclArg::Occur::Once, DeclArg::Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `xml.XmlDecl` instance.");
}

Gurax_ImplementConstructor(XmlDecl)
{
	// Arguments
	ArgPicker args(argument);
	const char* version = args.PickString();
	const char* encoding = args.PickString();
	bool standalone = args.PickBool();
	// Function body
	RefPtr<XmlDecl> pXmlDecl(new XmlDecl(version, encoding, standalone? 1 : 0));
	return argument.ReturnValue(processor, new Value_XmlDecl(pXmlDecl.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// xml.XmlDecl#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(XmlDecl, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(XmlDecl, MethodSkeleton)
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
// xml.XmlDecl#propSkeleton
Gurax_DeclareProperty_R(XmlDecl, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(XmlDecl, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_XmlDecl
//------------------------------------------------------------------------------
VType_XmlDecl VTYPE_XmlDecl("XmlDecl");

void VType_XmlDecl::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Node, Flag::Immutable, Gurax_CreateConstructor(XmlDecl));
	// Assignment of method
	Assign(Gurax_CreateMethod(XmlDecl, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(XmlDecl, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_XmlDecl
//------------------------------------------------------------------------------
VType& Value_XmlDecl::vtype = VTYPE_XmlDecl;

String Value_XmlDecl::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetXmlDecl().ToString(ss));
}

Gurax_EndModuleScope(xml)
