//==============================================================================
// VType_StatEx.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(fs)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(fs.StatEx, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(fs.StatEx, `en)}

${help.ComposeMethodHelp(fs.StatEx, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// fs.Stat(pathName:String):map {block?}
Gurax_DeclareConstructor(Stat)
{
	Declare(VTYPE_StatEx, Flag::Map);
	DeclareArg("pathName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp("en", u8R"**(
Creates a `fs.Stat` instance from the specified path name.
)**");
}

Gurax_ImplementConstructor(Stat)
{
	// Arguments
	ArgPicker args(argument);
	const char* pathName = args.PickString();
	// Function body
	RefPtr<StatEx> pStatEx(StatEx::Create(pathName));
	if (!pStatEx) return Value::nil();
	return argument.ReturnValue(processor, new Value_StatEx(pStatEx.release()));
}

//------------------------------------------------------------------------------
// VType_StatEx
//------------------------------------------------------------------------------
VType_StatEx VTYPE_StatEx("Stat");

void VType_StatEx::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// VType settings
	Declare(VTYPE_Stat, Flag::Immutable, Gurax_CreateConstructor(Stat));
}

//------------------------------------------------------------------------------
// Value_StatEx
//------------------------------------------------------------------------------
VType& Value_StatEx::vtype = VTYPE_StatEx;

Gurax_EndModuleScope(fs)
