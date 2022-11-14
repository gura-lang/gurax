//==============================================================================
// VType_PathMgr.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(PathMgr, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(PathMgr, `en)}

${help.ComposeMethodHelp(PathMgr, `en)}
)**";

//------------------------------------------------------------------------------
// VType_PathMgr
//------------------------------------------------------------------------------
VType_PathMgr VTYPE_PathMgr("PathMgr");

void VType_PathMgr::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_PathMgr
//------------------------------------------------------------------------------
VType& Value_PathMgr::vtype = VTYPE_PathMgr;

String Value_PathMgr::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetPathMgr().ToString(ss));
}


}
