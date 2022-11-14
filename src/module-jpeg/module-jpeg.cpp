//==============================================================================
// module-jpeg.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(jpeg)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Function

# Class
)**";

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// jpeg.Read(stream:Stream):[rgb,rgba] {block?}
Gurax_DeclareFunction(Read)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamR);
	DeclareAttrOpt(Gurax_Symbol(rgb));
	DeclareAttrOpt(Gurax_Symbol(rgba));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
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
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamR);
	DeclareArg("image", VTYPE_Image, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
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
	// Initialization of static data
	TagInfo::Initialize();
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Assignment of VType
	Assign(VTYPE_Content);
	Assign(VTYPE_Exif);
	Assign(VTYPE_IFD);
	Assign(VTYPE_JFIF);
	Assign(VTYPE_Segment);
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
