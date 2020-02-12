//==============================================================================
// VType_Image.cpp
//==============================================================================
#include "stdafx.h"
#include <gurax/VType_Image.h>

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

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// Image#Fill(color:Color)
Gurax_DeclareMethod(Image, Fill)
{
	Declare(VTYPE_Nil, Flag::Reduce);
	DeclareArg("color", VTYPE_Color, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethod(Image, Fill)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Image& image = valueThis.GetImage();
	// Argument
	ArgPicker args(argument);
	const Color& color = Value_Color::GetColor(args.PickValue());
	// Function body
	image.Fill(color);
	return valueThis.Reference();
}

// Image#FillRect(x:Number, y:Number, width:Number, height:Number, color:Color)
Gurax_DeclareMethod(Image, FillRect)
{
	Declare(VTYPE_Nil, Flag::Reduce);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("color", VTYPE_Color, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethod(Image, FillRect)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Image& image = valueThis.GetImage();
	// Argument
	ArgPicker args(argument);
	int x = args.PickNumber<int>();
	int y = args.PickNumber<int>();
	int width = args.PickNumber<int>();
	int height = args.PickNumber<int>();
	const Color& color = Value_Color::GetColor(args.PickValue());
	// Function body
	Image::Rect rect;
	if (image.AdjustCoord(&rect, x, y, width, height)) {
		image.FillRect(rect.x, rect.y, rect.width, rect.height, color);
	}
	return valueThis.Reference();
}

//------------------------------------------------------------------------------
// VType_Image
//------------------------------------------------------------------------------
VType_Image VTYPE_Image("Image");

void VType_Image::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Image, Fill));
	Assign(Gurax_CreateMethod(Image, FillRect));
}

//------------------------------------------------------------------------------
// Value_Image
//------------------------------------------------------------------------------
VType& Value_Image::vtype = VTYPE_Image;

}
