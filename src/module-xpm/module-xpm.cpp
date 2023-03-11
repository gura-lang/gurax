//==============================================================================
// module-xpm.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(xpm)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// xpm.ParseIterator(iter as Iterator, image? as Image):[rgb,rgba]
Gurax_DeclareFunction(ParseIterator)
{
	Declare(VTYPE_Image, Flag::None);
	DeclareArg("iter", VTYPE_Iterator, ArgOccur::Once, ArgFlag::None);
	DeclareArg("image", VTYPE_Image, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareAttrOpt("rgb");
	DeclareAttrOpt("rgba");
	AddHelp(Gurax_Symbol(en), u8R"""(
Reads XPM data from Iterator.
)""");
}

Gurax_ImplementFunction(ParseIterator)
{
	// Arguments
	ArgPicker args(argument);
	Iterator& iter = args.PickIterator();
	const Image::Format& format =
		argument.IsSet(Gurax_Symbol(rgb))? Image::Format::RGB : Image::Format::RGBA;
	RefPtr<Image> pImage(args.IsValid()? args.Pick<Value_Image>().GetImage().Reference() : new Image(format));
	// Function body
	if (!XPMData::ReadIterator(*pImage, iter)) return Value::nil();
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
	Assign(Gurax_CreateFunction(ParseIterator));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(xpm)
