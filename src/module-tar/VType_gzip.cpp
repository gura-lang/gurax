//==============================================================================
// VType_gzip.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(tar)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(tar.gzip, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(tar.gzip, `en)}

${help.ComposeMethodHelp(tar.gzip, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of class property
//-----------------------------------------------------------------------------
// tar.gzip.level
Gurax_DeclareClassProperty_RW(gzip, level)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementClassPropertyGetter(gzip, level)
{
	return new Value_Number(Writer::gzipInfo.level);
}

Gurax_ImplementClassPropertySetter(gzip, level)
{
	Writer::gzipInfo.level = Value_Number::GetNumber<int>(value);
}

// tar.gzip.windowBits
Gurax_DeclareClassProperty_RW(gzip, windowBits)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementClassPropertyGetter(gzip, windowBits)
{
	return new Value_Number(Writer::gzipInfo.windowBits);
}

Gurax_ImplementClassPropertySetter(gzip, windowBits)
{
	Writer::gzipInfo.windowBits = Value_Number::GetNumber<int>(value);
}

// tar.gzip.memLevel
Gurax_DeclareClassProperty_RW(gzip, memLevel)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementClassPropertyGetter(gzip, memLevel)
{
	return new Value_Number(Writer::gzipInfo.memLevel);
}

Gurax_ImplementClassPropertySetter(gzip, memLevel)
{
	Writer::gzipInfo.memLevel = Value_Number::GetNumber<int>(value);
}

// tar.gzip.strategy
Gurax_DeclareClassProperty_RW(gzip, strategy)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementClassPropertyGetter(gzip, strategy)
{
	return new Value_Number(Writer::gzipInfo.strategy);
}

Gurax_ImplementClassPropertySetter(gzip, strategy)
{
	Writer::gzipInfo.strategy = Value_Number::GetNumber<int>(value);
}

//------------------------------------------------------------------------------
// VType_gzip
//------------------------------------------------------------------------------
VType_gzip VTYPE_gzip("gzip");

void VType_gzip::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(gzip, level));
	Assign(Gurax_CreateProperty(gzip, windowBits));
	Assign(Gurax_CreateProperty(gzip, memLevel));
	Assign(Gurax_CreateProperty(gzip, strategy));
}

Gurax_EndModuleScope(tar)
