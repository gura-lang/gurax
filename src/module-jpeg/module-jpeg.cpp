//==============================================================================
// module-jpeg.cpp
//==============================================================================
#include "stdafx.h"
#include <gurax/VType_Image.h>

Gurax_BeginModule(jpeg)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// jpeg.Read(stream:Stream):[rgb,rgba] {block?}
Gurax_DeclareFunction(Read)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(rgb));
	DeclareAttrOpt(Gurax_Symbol(rgba));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(Read)
{
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	const Image::Format& format =
		argument.IsSet(Gurax_Symbol(rgb))? Image::Format::RGB : Image::Format::RGBA;
	// Function body
	RefPtr<Image> pImage(new Image(format));
	if (!ImageMgrEx::ReadStream(stream, *pImage, false)) return Value::nil();
	return argument.ReturnValue(processor, new Value_Image(pImage.release()));
}

// jpeg.Write(stream:Stream, image:Image):void
Gurax_DeclareFunction(Write)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::None);
	DeclareArg("image", VTYPE_Image, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(Write)
{
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	Image& image = args.PickImage();
	// Function body
	if (!ImageMgrEx::WriteStream(stream, image, false)) return Value::nil();
	return Value::nil();
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
	Assign(VTYPE_Exif);
	Assign(VTYPE_IFD);
	Assign(VTYPE_Tag);
	// Assignment of function
	Assign(Gurax_CreateFunction(Read));
	Assign(Gurax_CreateFunction(Write));
	// Assignment of ImageMgr
	ImageMgr::Assign(new ImageMgrEx());
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(jpeg)
