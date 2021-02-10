//==============================================================================
// module-gif.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(gif)

//-----------------------------------------------------------------------------
// Implementation of module property
//-----------------------------------------------------------------------------
// gif.ApplicationExtension
Gurax_DeclareModuleProperty_R(ApplicationExtension)
{
	Declare(VTYPE_ApplicationExtension, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementModulePropertyGetter(ApplicationExtension)
{
	return new Value_ApplicationExtension(Content::extensionsCommon.applicationExtension, nullptr);
}

// gif.CommentExtension
Gurax_DeclareModuleProperty_R(CommentExtension)
{
	Declare(VTYPE_CommentExtension, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementModulePropertyGetter(CommentExtension)
{
	return new Value_CommentExtension(Content::extensionsCommon.commentExtension, nullptr);
}

// gif.PlainTextExtension
Gurax_DeclareModuleProperty_R(PlainTextExtension)
{
	Declare(VTYPE_PlainTextExtension, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementModulePropertyGetter(PlainTextExtension)
{
	return new Value_PlainTextExtension(Content::extensionsCommon.plainTextExtension, nullptr);
}

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
	Assign(VTYPE_ApplicationExtension);
	Assign(VTYPE_CommentExtension);
	Assign(VTYPE_Content);
	Assign(VTYPE_GraphicControlExtension);
	Assign(VTYPE_ImageDescriptor);
	Assign(VTYPE_ImageProp);
	Assign(VTYPE_LogicalScreenDescriptor);
	Assign(VTYPE_PlainTextExtension);
	// Assignment of property
	Assign(Gurax_CreateModuleProperty(ApplicationExtension));
	Assign(Gurax_CreateModuleProperty(CommentExtension));
	Assign(Gurax_CreateModuleProperty(PlainTextExtension));
	// Assignment of ImageMgr
	ImageMgr::Assign(new ImageMgrEx());
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(gif)
