//==============================================================================
// VType_PlainTextExtension.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(gif)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(gif.plainTextExtension, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(gif.plainTextExtension, `en)}

${help.ComposeMethodHelp(gif.plainTextExtension, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// gif.PlainTextExtension#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(PlainTextExtension, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(PlainTextExtension, MethodSkeleton)
{
	// Target
	//auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Double num1 = args.PickNumber<Double>();
	Double num2 = args.PickNumber<Double>();
	// Function body
	return new Value_Number(num1 + num2);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// gif.PlainTextExtension#BlockSize
Gurax_DeclareProperty_R(PlainTextExtension, BlockSize)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(PlainTextExtension, BlockSize)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& plainTextExtension = valueThis.GetPlainTextExtension();
	if (!plainTextExtension.validFlag) return Value::nil();
	return new Value_Number(plainTextExtension.BlockSize);
}

// gif.PlainTextExtension#TextGridLeftPosition
Gurax_DeclareProperty_R(PlainTextExtension, TextGridLeftPosition)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(PlainTextExtension, TextGridLeftPosition)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& plainTextExtension = valueThis.GetPlainTextExtension();
	if (!plainTextExtension.validFlag) return Value::nil();
	return new Value_Number(Gurax_UnpackUInt16(plainTextExtension.TextGridLeftPosition));
}

// gif.PlainTextExtension#TextGridTopPosition
Gurax_DeclareProperty_R(PlainTextExtension, TextGridTopPosition)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(PlainTextExtension, TextGridTopPosition)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& plainTextExtension = valueThis.GetPlainTextExtension();
	if (!plainTextExtension.validFlag) return Value::nil();
	return new Value_Number(Gurax_UnpackUInt16(plainTextExtension.TextGridTopPosition));
}

// gif.PlainTextExtension#TextGridWidth
Gurax_DeclareProperty_R(PlainTextExtension, TextGridWidth)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(PlainTextExtension, TextGridWidth)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& plainTextExtension = valueThis.GetPlainTextExtension();
	if (!plainTextExtension.validFlag) return Value::nil();
	return new Value_Number(Gurax_UnpackUInt16(plainTextExtension.TextGridWidth));
}

// gif.PlainTextExtension#TextGridHeight
Gurax_DeclareProperty_R(PlainTextExtension, TextGridHeight)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(PlainTextExtension, TextGridHeight)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& plainTextExtension = valueThis.GetPlainTextExtension();
	if (!plainTextExtension.validFlag) return Value::nil();
	return new Value_Number(Gurax_UnpackUInt16(plainTextExtension.TextGridHeight));
}

// gif.PlainTextExtension#CharacterCellWidth
Gurax_DeclareProperty_R(PlainTextExtension, CharacterCellWidth)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(PlainTextExtension, CharacterCellWidth)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& plainTextExtension = valueThis.GetPlainTextExtension();
	if (!plainTextExtension.validFlag) return Value::nil();
	return new Value_Number(plainTextExtension.CharacterCellWidth);
}

// gif.PlainTextExtension#CharacterCellHeight
Gurax_DeclareProperty_R(PlainTextExtension, CharacterCellHeight)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(PlainTextExtension, CharacterCellHeight)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& plainTextExtension = valueThis.GetPlainTextExtension();
	if (!plainTextExtension.validFlag) return Value::nil();
	return new Value_Number(plainTextExtension.CharacterCellHeight);
}

// gif.PlainTextExtension#TextForegroundColorIndex
Gurax_DeclareProperty_R(PlainTextExtension, TextForegroundColorIndex)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(PlainTextExtension, TextForegroundColorIndex)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& plainTextExtension = valueThis.GetPlainTextExtension();
	if (!plainTextExtension.validFlag) return Value::nil();
	return new Value_Number(plainTextExtension.TextForegroundColorIndex);
}

// gif.PlainTextExtension#TextBackgroundColorIndex
Gurax_DeclareProperty_R(PlainTextExtension, TextBackgroundColorIndex)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(PlainTextExtension, TextBackgroundColorIndex)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& plainTextExtension = valueThis.GetPlainTextExtension();
	if (!plainTextExtension.validFlag) return Value::nil();
	return new Value_Number(plainTextExtension.TextBackgroundColorIndex);
}

// gif.PlainTextExtension#PlainTextData
Gurax_DeclareProperty_R(PlainTextExtension, PlainTextData)
{
	Declare(VTYPE_Binary, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(PlainTextExtension, PlainTextData)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& plainTextExtension = valueThis.GetPlainTextExtension();
	if (!plainTextExtension.validFlag) return Value::nil();
	return new Value_Binary(plainTextExtension.PlainTextData);
}

//-----------------------------------------------------------------------------
// Implementation of class property
//-----------------------------------------------------------------------------
// gif.PlainTextExtension#default
Gurax_DeclareClassPropertyAlias_R(PlainTextExtension, default_, "default")
{
	Declare(VTYPE_PlainTextExtension, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementClassPropertyGetter(PlainTextExtension, default_)
{
	return new Value_PlainTextExtension(Content::extensionsDefault.plainTextExtension, nullptr);
}

//------------------------------------------------------------------------------
// VType_PlainTextExtension
//------------------------------------------------------------------------------
VType_PlainTextExtension VTYPE_PlainTextExtension("PlainTextExtension");

void VType_PlainTextExtension::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(PlainTextExtension, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(PlainTextExtension, BlockSize));
	// Assignment of class property
	Assign(Gurax_CreateClassProperty(PlainTextExtension, default_));
}

//------------------------------------------------------------------------------
// Value_PlainTextExtension
//------------------------------------------------------------------------------
VType& Value_PlainTextExtension::vtype = VTYPE_PlainTextExtension;

String Value_PlainTextExtension::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "gif.PlainTextExtension");
}

Gurax_EndModuleScope(gif)
