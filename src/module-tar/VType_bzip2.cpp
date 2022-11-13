//==============================================================================
// VType_bzip2.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(tar)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(tar.bzip2, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(tar.bzip2, `en)}

${help.ComposeMethodHelp(tar.bzip2, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of class property
//-----------------------------------------------------------------------------
// tar.bzip2.blockSize100k
Gurax_DeclareClassProperty_RW(bzip2, blockSize100k)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementClassPropertyGetter(bzip2, blockSize100k)
{
	return new Value_Number(Writer::bzip2Info.blockSize100k);
}

Gurax_ImplementClassPropertySetter(bzip2, blockSize100k)
{
	Writer::bzip2Info.blockSize100k = Value_Number::GetNumber<int>(value);
}

// tar.bzip2.verbosity
Gurax_DeclareClassProperty_RW(bzip2, verbosity)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementClassPropertyGetter(bzip2, verbosity)
{
	return new Value_Number(Writer::bzip2Info.verbosity);
}

Gurax_ImplementClassPropertySetter(bzip2, verbosity)
{
	Writer::bzip2Info.verbosity = Value_Number::GetNumber<int>(value);
}

// tar.bzip2.workFactor
Gurax_DeclareClassProperty_RW(bzip2, workFactor)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementClassPropertyGetter(bzip2, workFactor)
{
	return new Value_Number(Writer::bzip2Info.workFactor);
}

Gurax_ImplementClassPropertySetter(bzip2, workFactor)
{
	Writer::bzip2Info.workFactor = Value_Number::GetNumber<int>(value);
}

//------------------------------------------------------------------------------
// VType_bzip2
//------------------------------------------------------------------------------
VType_bzip2 VTYPE_bzip2("bzip2");

void VType_bzip2::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(bzip2, blockSize100k));
	Assign(Gurax_CreateProperty(bzip2, verbosity));
	Assign(Gurax_CreateProperty(bzip2, workFactor));
}

Gurax_EndModuleScope(tar)
