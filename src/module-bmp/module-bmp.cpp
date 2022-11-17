//==============================================================================
// module-bmp.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(bmp)

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
	Assign(VTYPE_Content);
	Assign(VTYPE_BitmapFileHeader);
	Assign(VTYPE_BitmapInfoHeader);
	// Assignment of ImageMgr
	ImageMgr::Assign(new ImageMgrEx());
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(bmp)
