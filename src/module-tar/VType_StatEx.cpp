//==============================================================================
// VType_Stat.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(tar)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(tar.StatEx, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(tar.StatEx, `en)}

${help.ComposeMethodHelp(tar.StatEx, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// tar.StatEx#chksum
Gurax_DeclareProperty_R(StatEx, chksum)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(StatEx, chksum)
{
	const Header& hdr = GetValueThis(valueTarget).GetStatEx().GetHeader();
	return new Value_Number(hdr.GetChksum());
}

// tar.StatEx#devmajor
Gurax_DeclareProperty_R(StatEx, devmajor)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(StatEx, devmajor)
{
	const Header& hdr = GetValueThis(valueTarget).GetStatEx().GetHeader();
	return new Value_Number(hdr.GetDevMajor());
}

// tar.StatEx#devminor
Gurax_DeclareProperty_R(StatEx, devminor)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(StatEx, devminor)
{
	const Header& hdr = GetValueThis(valueTarget).GetStatEx().GetHeader();
	return new Value_Number(hdr.GetDevMinor());
}

// tar.StatEx#mode
Gurax_DeclareProperty_R(StatEx, mode)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(StatEx, mode)
{
	const Header& hdr = GetValueThis(valueTarget).GetStatEx().GetHeader();
	return new Value_Number(hdr.GetMode());
}

// tar.StatEx#gname
Gurax_DeclareProperty_R(StatEx, gname)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(StatEx, gname)
{
	const Header& hdr = GetValueThis(valueTarget).GetStatEx().GetHeader();
	return new Value_String(hdr.GetGName());
}

// tar.StatEx#uname
Gurax_DeclareProperty_R(StatEx, uname)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(StatEx, uname)
{
	const Header& hdr = GetValueThis(valueTarget).GetStatEx().GetHeader();
	return new Value_String(hdr.GetUName());
}

// tar.StatEx#linkName
Gurax_DeclareProperty_R(StatEx, linkName)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(StatEx, linkName)
{
	const Header& hdr = GetValueThis(valueTarget).GetStatEx().GetHeader();
	return new Value_String(hdr.GetLinkName());
}

// tar.StatEx#name@tar
Gurax_DeclarePropertyAlias_R(StatEx, name_at_tar, "name@tar")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(StatEx, name_at_tar)
{
	const Header& hdr = GetValueThis(valueTarget).GetStatEx().GetHeader();
	return new Value_String(hdr.GetName());
}

//------------------------------------------------------------------------------
// VType_StatEx
//------------------------------------------------------------------------------
VType_StatEx VTYPE_StatEx("Stat");

void VType_StatEx::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Stat, Flag::Immutable);
	// Assignment of method
	// Assignment of property
	Assign(Gurax_CreateProperty(StatEx, chksum));
	Assign(Gurax_CreateProperty(StatEx, devmajor));
	Assign(Gurax_CreateProperty(StatEx, devminor));
	Assign(Gurax_CreateProperty(StatEx, mode));
	Assign(Gurax_CreateProperty(StatEx, gname));
	Assign(Gurax_CreateProperty(StatEx, uname));
	Assign(Gurax_CreateProperty(StatEx, linkName));
	Assign(Gurax_CreateProperty(StatEx, name_at_tar));
}

//------------------------------------------------------------------------------
// Value_StatEx
//------------------------------------------------------------------------------
VType& Value_StatEx::vtype = VTYPE_StatEx;

Gurax_EndModuleScope(tar)
