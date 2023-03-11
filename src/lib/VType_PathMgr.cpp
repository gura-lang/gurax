//==============================================================================
// VType_PathMgr.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(PathMgr, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(PathMgr, `en)}

${help.ComposeMethodHelp(PathMgr, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of class method
//-----------------------------------------------------------------------------
// PathMgr.Dir()
Gurax_DeclareClassMethod(PathMgr, Dir)
{
	Declare(VTYPE_List, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Returns a list of `PathMgr` instances that represent registered path managers.
)""");
}

Gurax_ImplementClassMethod(PathMgr, Dir)
{
	// Function body
	const PathMgrOwner& pathMgrOwner = Basement::Inst.GetPathMgrOwner();
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	pValueOwner->reserve(pathMgrOwner.size());
	for (const PathMgr* pPathMgr : pathMgrOwner) {
		pValueOwner->push_back(new Value_PathMgr(pPathMgr->Reference()));
	}
	return new Value_List(pValueOwner.release());
}

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
	// Assignment of class method
	Assign(Gurax_CreateMethod(PathMgr, Dir));
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
