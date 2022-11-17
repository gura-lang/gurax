//==============================================================================
// module-gif.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(gif)

//------------------------------------------------------------------------------
// Entries
//------------------------------------------------------------------------------
Gurax_ModuleValidate()
{
	return Version::CheckCoreVersion(GURAX_VERSION, nullptr);
}

Gurax_ModulePrepare()
{
	// Assignment of VType
	Assign(VTYPE_CommentExtension);
	Assign(VTYPE_Content);
	Assign(VTYPE_GraphicControlExtension);
	Assign(VTYPE_ImageDescriptor);
	Assign(VTYPE_GraphicBlock);
	Assign(VTYPE_LogicalScreenDescriptor);
	Assign(VTYPE_PlainTextExtension);
	// Assignment of ImageMgr
	ImageMgr::Assign(new ImageMgrEx());
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(gif)
