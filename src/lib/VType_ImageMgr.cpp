//==============================================================================
// VType_ImageMgr.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//-----------------------------------------------------------------------------
// Implementation of class method
//-----------------------------------------------------------------------------
// ImageMgr.Dir()
Gurax_DeclareClassMethod(ImageMgr, Dir)
{
	Declare(VTYPE_List, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns a list of `ImageMgr` instances that represent registered image managers.\n");
}

Gurax_ImplementClassMethod(ImageMgr, Dir)
{
	// Function body
	const ImageMgrList& imageMgrList = Basement::Inst.GetImageMgrList();
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	pValueOwner->reserve(imageMgrList.size());
	for (const ImageMgr* pImageMgr : imageMgrList) {
		pValueOwner->push_back(new Value_ImageMgr(pImageMgr->Reference()));
	}
	return new Value_List(pValueOwner.release());
}

// ImageMgr.Lookup(imgTypeName:String)
Gurax_DeclareClassMethod(ImageMgr, Lookup)
{
	Declare(VTYPE_List, Flag::None);
	DeclareArg("imgTypeName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Looks up an `ImageMgr` instances that matches the specified `imgTypeName`.\n");
}

Gurax_ImplementClassMethod(ImageMgr, Lookup)
{
	// Argument
	ArgPicker args(argument);
	const char* imgTypeName = args.PickString();
	// Function body
	const ImageMgrList& imageMgrList = Basement::Inst.GetImageMgrList();
	const ImageMgr* pImageMgr = imageMgrList.FindByImgTypeName(imgTypeName);
	if (!pImageMgr) {
		Error::Issue(ErrorType::KeyError, "can't find an image manager of the specified image type");
		return Value::nil();
	}
	return new Value_ImageMgr(pImageMgr->Reference());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// module.ImageMgr#IsResponsible(stream:Stream:r)
Gurax_DeclareMethod(ImageMgr, IsResponsible)
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamR);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the data from the stream should be handled by this manager.");
}

Gurax_ImplementMethod(ImageMgr, IsResponsible)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	// Function body
	return new Value_Bool(valueThis.GetImageMgr().IsResponsible(stream));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// ImageMgr#description
Gurax_DeclareProperty_R(ImageMgr, description)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Description for this manager.");
}

Gurax_ImplementPropertyGetter(ImageMgr, description)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetImageMgr().GetDescription());
}

// ImageMgr#imgTypeName
Gurax_DeclareProperty_R(ImageMgr, imgTypeName)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Name of the image type for which this manager is responsible.");
}

Gurax_ImplementPropertyGetter(ImageMgr, imgTypeName)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetImageMgr().GetImgTypeName());
}

//------------------------------------------------------------------------------
// VType_ImageMgr
//------------------------------------------------------------------------------
VType_ImageMgr VTYPE_ImageMgr("ImageMgr");

void VType_ImageMgr::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of class method
	Assign(Gurax_CreateMethod(ImageMgr, Dir));
	Assign(Gurax_CreateMethod(ImageMgr, Lookup));
	// Assignment of method
	Assign(Gurax_CreateMethod(ImageMgr, IsResponsible));
	// Assignment of property
	Assign(Gurax_CreateProperty(ImageMgr, description));
	Assign(Gurax_CreateProperty(ImageMgr, imgTypeName));
}

//------------------------------------------------------------------------------
// Value_ImageMgr
//------------------------------------------------------------------------------
VType& Value_ImageMgr::vtype = VTYPE_ImageMgr;

String Value_ImageMgr::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetImageMgr().ToString(ss));
}

}
