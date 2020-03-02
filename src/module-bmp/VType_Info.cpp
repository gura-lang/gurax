//==============================================================================
// VType_Info.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(bmp)

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
// bmp.Info(stream:Stream) {block?}
Gurax_DeclareConstructor(Info)
{
	Declare(VTYPE_Info, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `bmp.Info` instance.");
}

Gurax_ImplementConstructor(Info)
{
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	// Function body
	RefPtr<Info> pInfo(new Info());
	if (!pInfo->Read(stream)) return Value::nil();
	return argument.ReturnValue(processor, new Value_Info(pInfo.release()));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// bmp.Info#bfh
Gurax_DeclareProperty_R(Info, bfh)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The structure data of BitmapFileHeader.");
}

Gurax_ImplementPropertyGetter(Info, bfh)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_BitmapFileHeader(valueThis.GetInfo().Reference());
}

// bmp.Info#bih
Gurax_DeclareProperty_R(Info, bih)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The structure data of BitmapInfoHeader.");
}

Gurax_ImplementPropertyGetter(Info, bih)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_BitmapInfoHeader(valueThis.GetInfo().Reference());
}

//------------------------------------------------------------------------------
// VType_Info
//------------------------------------------------------------------------------
VType_Info VTYPE_Info("Info");

void VType_Info::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Info));
	// Assignment of property
	Assign(Gurax_CreateProperty(Info, bfh));
	Assign(Gurax_CreateProperty(Info, bih));
}

//------------------------------------------------------------------------------
// Value_Info
//------------------------------------------------------------------------------
VType& Value_Info::vtype = VTYPE_Info;

Gurax_EndModuleScope(bmp)
