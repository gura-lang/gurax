//==============================================================================
// module-xpm.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(xpm)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// xpm.ReadStrings(iter as Iterator):[rgb,rgba]
Gurax_DeclareFunction(ReadStrings)
{
	Declare(VTYPE_Image, Flag::None);
	DeclareArg("iter", VTYPE_Iterator, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt("rgb");
	DeclareAttrOpt("rgba");
	AddHelp(
		Gurax_Symbol(en),
		"Reads XPM data from Iterator.");
}

Gurax_ImplementFunction(ReadStrings)
{
	// Arguments
	ArgPicker args(argument);
	Iterator& iter = args.PickIterator();
	const Image::Format& format =
		argument.IsSet(Gurax_Symbol(rgb))? Image::Format::RGB : Image::Format::RGBA;
	// Function body
	RefPtr<Image> pImage(XPMData::ReadIterator(format, iter));
	return new Value_Image(pImage.release());
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
	// Assignment of function
	Assign(Gurax_CreateFunction(ReadStrings));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(xpm)
