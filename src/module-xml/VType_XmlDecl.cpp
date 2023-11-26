//==============================================================================
// VType_XmlDecl.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(xml.XmlDecl, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(xml.XmlDecl, `en)}

${help.ComposeMethodHelp(xml.XmlDecl, `en)}
)""";

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
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `xml.XmlDecl` instance.
)""");
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
#if 0
// xml.XmlDecl#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(XmlDecl, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
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
#endif

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// xml.XmlDecl#version
Gurax_DeclareProperty_R(XmlDecl, version)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(XmlDecl, version)
{
	auto& valueThis = GetValueThis(valueTarget);
	const char* str = valueThis.GetXmlDecl().GetVersion();
	if (str) return new Value_String(str);
	return Value::nil();
}

// xml.XmlDecl#encoding
Gurax_DeclareProperty_R(XmlDecl, encoding)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(XmlDecl, encoding)
{
	auto& valueThis = GetValueThis(valueTarget);
	const char* str = valueThis.GetXmlDecl().GetEncoding();
	if (str) return new Value_String(str);
	return Value::nil();
}

// xml.XmlDecl#standalone
Gurax_DeclareProperty_R(XmlDecl, standalone)
{
	Declare(VTYPE_Bool, Flag::Nil);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(XmlDecl, standalone)
{
	auto& valueThis = GetValueThis(valueTarget);
	const XmlDecl& xmlDecl = valueThis.GetXmlDecl();
	if (xmlDecl.HasStandalone()) return new Value_Bool(static_cast<bool>(xmlDecl.GetStandalone()));
	return Value::nil();
}

//------------------------------------------------------------------------------
// VType_XmlDecl
//------------------------------------------------------------------------------
VType_XmlDecl VTYPE_XmlDecl("XmlDecl");

void VType_XmlDecl::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Node, Flag::Immutable, Gurax_CreateConstructor(XmlDecl));
	// Assignment of method
	//Assign(Gurax_CreateMethod(XmlDecl, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(XmlDecl, version));
	Assign(Gurax_CreateProperty(XmlDecl, encoding));
	Assign(Gurax_CreateProperty(XmlDecl, standalone));
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
