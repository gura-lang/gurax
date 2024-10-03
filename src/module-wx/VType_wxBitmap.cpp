﻿//==============================================================================
// VType_wxBitmap.cpp
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(wx.Bitmap, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.Bitmap, `en)}

${help.ComposeMethodHelp(wx.Bitmap, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.Bitmap, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.Bitmap, `ja)}

${help.ComposeMethodHelp(wx.Bitmap, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.Bitmap() {block?}
Gurax_DeclareConstructorAlias(Bitmap_gurax, "Bitmap")
{
	Declare(VTYPE_wxBitmap, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(Bitmap_gurax, processor_gurax, argument_gurax)
{
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxBitmap(
		wxBitmap()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.Bitmap#ConvertToImage() {block?}
Gurax_DeclareMethodAlias(wxBitmap, ConvertToImage_gurax, "ConvertToImage")
{
	Declare(VTYPE_wxImage, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxBitmap, ConvertToImage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxImage(pEntity_gurax->ConvertToImage()));
}

// wx.Bitmap#CopyFromIcon(icon as wx.Icon)
Gurax_DeclareMethodAlias(wxBitmap, CopyFromIcon_gurax, "CopyFromIcon")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("icon", VTYPE_wxIcon, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxBitmap, CopyFromIcon_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxIcon& value_icon = args_gurax.Pick<Value_wxIcon>();
	const wxIcon& icon = value_icon.GetEntity();
	// Function body
	bool rtn = pEntity_gurax->CopyFromIcon(icon);
	return new Gurax::Value_Bool(rtn);
}

// wx.Bitmap#Create(width as Number, height as Number, depth? as Number)
Gurax_DeclareMethodAlias(wxBitmap, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("depth", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxBitmap, Create_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int width = args_gurax.PickNumber<int>();
	int height = args_gurax.PickNumber<int>();
	bool depth_validFlag = args_gurax.IsValid();
	int depth = depth_validFlag? args_gurax.PickNumber<int>() : wxBITMAP_SCREEN_DEPTH;
	// Function body
	bool rtn = pEntity_gurax->Create(width, height, depth);
	return new Gurax::Value_Bool(rtn);
}

// wx.Bitmap#GetDepth()
Gurax_DeclareMethodAlias(wxBitmap, GetDepth_gurax, "GetDepth")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxBitmap, GetDepth_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetDepth();
	return new Gurax::Value_Number(rtn);
}

// wx.Bitmap#GetHeight()
Gurax_DeclareMethodAlias(wxBitmap, GetHeight_gurax, "GetHeight")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxBitmap, GetHeight_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetHeight();
	return new Gurax::Value_Number(rtn);
}

// wx.Bitmap#GetMask() {block?}
Gurax_DeclareMethodAlias(wxBitmap, GetMask_gurax, "GetMask")
{
	Declare(VTYPE_wxMask, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxBitmap, GetMask_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxMask(*pEntity_gurax->GetMask()));
}

// wx.Bitmap#GetPalette() {block?}
Gurax_DeclareMethodAlias(wxBitmap, GetPalette_gurax, "GetPalette")
{
	Declare(VTYPE_wxPalette, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxBitmap, GetPalette_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPalette(*pEntity_gurax->GetPalette()));
}

// wx.Bitmap#GetSubBitmap(rect as wx.Rect) {block?}
Gurax_DeclareMethodAlias(wxBitmap, GetSubBitmap_gurax, "GetSubBitmap")
{
	Declare(VTYPE_wxBitmap, Flag::None);
	DeclareArg("rect", VTYPE_wxRect, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxBitmap, GetSubBitmap_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRect& value_rect = args_gurax.Pick<Value_wxRect>();
	const wxRect& rect = value_rect.GetEntity();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxBitmap(pEntity_gurax->GetSubBitmap(rect)));
}

// wx.Bitmap#GetSize() {block?}
Gurax_DeclareMethodAlias(wxBitmap, GetSize_gurax, "GetSize")
{
	Declare(VTYPE_wxSize, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxBitmap, GetSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSize(pEntity_gurax->GetSize()));
}

// wx.Bitmap#ConvertToDisabled(brightness? as Number) {block?}
Gurax_DeclareMethodAlias(wxBitmap, ConvertToDisabled_gurax, "ConvertToDisabled")
{
	Declare(VTYPE_wxBitmap, Flag::None);
	DeclareArg("brightness", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxBitmap, ConvertToDisabled_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool brightness_validFlag = args_gurax.IsValid();
	unsigned char brightness = brightness_validFlag? args_gurax.PickNumber<unsigned char>() : 255;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxBitmap(pEntity_gurax->ConvertToDisabled(brightness)));
}

// wx.Bitmap#GetWidth()
Gurax_DeclareMethodAlias(wxBitmap, GetWidth_gurax, "GetWidth")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxBitmap, GetWidth_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetWidth();
	return new Gurax::Value_Number(rtn);
}

// wx.Bitmap#IsOk()
Gurax_DeclareMethodAlias(wxBitmap, IsOk_gurax, "IsOk")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxBitmap, IsOk_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsOk();
	return new Gurax::Value_Bool(rtn);
}

// wx.Bitmap#LoadFile(name as String, type? as Number)
Gurax_DeclareMethodAlias(wxBitmap, LoadFile_gurax, "LoadFile")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxBitmap, LoadFile_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString name(args_gurax.PickString());
	bool type_validFlag = args_gurax.IsValid();
	wxBitmapType type = type_validFlag? args_gurax.PickNumber<wxBitmapType>() : wxBITMAP_DEFAULT_TYPE;
	// Function body
	bool rtn = pEntity_gurax->LoadFile(name, type);
	return new Gurax::Value_Bool(rtn);
}

// wx.Bitmap#SaveFile(name as String, type as Number, palette? as wx.Palette)
Gurax_DeclareMethodAlias(wxBitmap, SaveFile_gurax, "SaveFile")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("palette", VTYPE_wxPalette, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxBitmap, SaveFile_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString name(args_gurax.PickString());
	wxBitmapType type = args_gurax.PickNumber<wxBitmapType>();
	const wxPalette* palette = args_gurax.IsValid()? args_gurax.Pick<Value_wxPalette>().GetEntityPtr() : nullptr;
	// Function body
	bool rtn = pEntity_gurax->SaveFile(name, type, palette);
	return new Gurax::Value_Bool(rtn);
}

// wx.Bitmap#SetDepth(depth as Number)
Gurax_DeclareMethodAlias(wxBitmap, SetDepth_gurax, "SetDepth")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("depth", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxBitmap, SetDepth_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int depth = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetDepth(depth);
	return Gurax::Value::nil();
}

// wx.Bitmap#SetHeight(height as Number)
Gurax_DeclareMethodAlias(wxBitmap, SetHeight_gurax, "SetHeight")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxBitmap, SetHeight_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int height = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetHeight(height);
	return Gurax::Value::nil();
}

// wx.Bitmap#SetMask(mask as wx.Mask)
Gurax_DeclareMethodAlias(wxBitmap, SetMask_gurax, "SetMask")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mask", VTYPE_wxMask, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxBitmap, SetMask_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxMask& value_mask = args_gurax.Pick<Value_wxMask>();
	wxMask* mask = value_mask.GetEntityPtr();
	// Function body
	pEntity_gurax->SetMask(mask);
	return Gurax::Value::nil();
}

// wx.Bitmap#SetPalette(palette as wx.Palette)
Gurax_DeclareMethodAlias(wxBitmap, SetPalette_gurax, "SetPalette")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("palette", VTYPE_wxPalette, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxBitmap, SetPalette_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxPalette& value_palette = args_gurax.Pick<Value_wxPalette>();
	const wxPalette& palette = value_palette.GetEntity();
	// Function body
	pEntity_gurax->SetPalette(palette);
	return Gurax::Value::nil();
}

// wx.Bitmap#SetWidth(width as Number)
Gurax_DeclareMethodAlias(wxBitmap, SetWidth_gurax, "SetWidth")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxBitmap, SetWidth_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int width = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetWidth(width);
	return Gurax::Value::nil();
}

// wx.Bitmap.AddHandler(handler as wx.GDIImageHandler)
Gurax_DeclareClassMethodAlias(wxBitmap, AddHandler_gurax, "AddHandler")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("handler", VTYPE_wxGDIImageHandler, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementClassMethodEx(wxBitmap, AddHandler_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxGDIImageHandler& value_handler = args_gurax.Pick<Value_wxGDIImageHandler>();
	wxGDIImageHandler* handler = value_handler.GetEntityPtr();
	// Function body
	wxBitmap::AddHandler(handler);
	return Gurax::Value::nil();
}

// wx.Bitmap.CleanUpHandlers()
Gurax_DeclareClassMethodAlias(wxBitmap, CleanUpHandlers_gurax, "CleanUpHandlers")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementClassMethodEx(wxBitmap, CleanUpHandlers_gurax, processor_gurax, argument_gurax)
{
	// Function body
	wxBitmap::CleanUpHandlers();
	return Gurax::Value::nil();
}

// wx.Bitmap.FindHandler(name as String) {block?}
Gurax_DeclareClassMethodAlias(wxBitmap, FindHandler_gurax, "FindHandler")
{
	Declare(VTYPE_wxGDIImageHandler, Flag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementClassMethodEx(wxBitmap, FindHandler_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString name(args_gurax.PickString());
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxGDIImageHandler(wxBitmap::FindHandler(name)));
}

// wx.Bitmap.InitStandardHandlers()
Gurax_DeclareClassMethodAlias(wxBitmap, InitStandardHandlers_gurax, "InitStandardHandlers")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementClassMethodEx(wxBitmap, InitStandardHandlers_gurax, processor_gurax, argument_gurax)
{
	// Function body
	wxBitmap::InitStandardHandlers();
	return Gurax::Value::nil();
}

// wx.Bitmap.InsertHandler(handler as wx.GDIImageHandler)
Gurax_DeclareClassMethodAlias(wxBitmap, InsertHandler_gurax, "InsertHandler")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("handler", VTYPE_wxGDIImageHandler, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementClassMethodEx(wxBitmap, InsertHandler_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxGDIImageHandler& value_handler = args_gurax.Pick<Value_wxGDIImageHandler>();
	wxGDIImageHandler* handler = value_handler.GetEntityPtr();
	// Function body
	wxBitmap::InsertHandler(handler);
	return Gurax::Value::nil();
}

// wx.Bitmap.NewFrom(image as Image) {block?}
Gurax_DeclareClassMethodAlias(wxBitmap, NewFrom_gurax, "NewFrom")
{
	Declare(VTYPE_wxBitmap, Flag::None);
	DeclareArg("image", VTYPE_Image, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementClassMethodEx(wxBitmap, NewFrom_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	RefPtr<Image> image(args_gurax.PickImage().Reference());
	// Function body
	return new Value_wxBitmap(wxBitmap(Util::CreateImage(*image)));
}

// wx.Bitmap.NewFromPNGData(data as Pointer, size? as Number) {block?}
Gurax_DeclareClassMethodAlias(wxBitmap, NewFromPNGData_gurax, "NewFromPNGData")
{
	Declare(VTYPE_wxBitmap, Flag::None);
	DeclareArg("data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementClassMethodEx(wxBitmap, NewFromPNGData_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	RefPtr<Pointer> data(args_gurax.PickPointer().Reference());
	bool size_validFlag = args_gurax.IsValid();
	size_t size = size_validFlag? args_gurax.PickNumber<size_t>() : 0;
	// Function body
	auto rtn = wxBitmap::NewFromPNGData(data->GetPointerC<void>(), size_validFlag? size : data->GetBytesAvailable());
	return new Value_wxBitmap(rtn);
}

// wx.Bitmap.RemoveHandler(name as String)
Gurax_DeclareClassMethodAlias(wxBitmap, RemoveHandler_gurax, "RemoveHandler")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementClassMethodEx(wxBitmap, RemoveHandler_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString name(args_gurax.PickString());
	// Function body
	bool rtn = wxBitmap::RemoveHandler(name);
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxBitmap
//------------------------------------------------------------------------------
VType_wxBitmap VTYPE_wxBitmap("Bitmap");

void VType_wxBitmap::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxGDIObject, Flag::Mutable, Gurax_CreateConstructor(Bitmap_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxBitmap, ConvertToImage_gurax));
	Assign(Gurax_CreateMethod(wxBitmap, CopyFromIcon_gurax));
	Assign(Gurax_CreateMethod(wxBitmap, Create_gurax));
	Assign(Gurax_CreateMethod(wxBitmap, GetDepth_gurax));
	Assign(Gurax_CreateMethod(wxBitmap, GetHeight_gurax));
	Assign(Gurax_CreateMethod(wxBitmap, GetMask_gurax));
	Assign(Gurax_CreateMethod(wxBitmap, GetPalette_gurax));
	Assign(Gurax_CreateMethod(wxBitmap, GetSubBitmap_gurax));
	Assign(Gurax_CreateMethod(wxBitmap, GetSize_gurax));
	Assign(Gurax_CreateMethod(wxBitmap, ConvertToDisabled_gurax));
	Assign(Gurax_CreateMethod(wxBitmap, GetWidth_gurax));
	Assign(Gurax_CreateMethod(wxBitmap, IsOk_gurax));
	Assign(Gurax_CreateMethod(wxBitmap, LoadFile_gurax));
	Assign(Gurax_CreateMethod(wxBitmap, SaveFile_gurax));
	Assign(Gurax_CreateMethod(wxBitmap, SetDepth_gurax));
	Assign(Gurax_CreateMethod(wxBitmap, SetHeight_gurax));
	Assign(Gurax_CreateMethod(wxBitmap, SetMask_gurax));
	Assign(Gurax_CreateMethod(wxBitmap, SetPalette_gurax));
	Assign(Gurax_CreateMethod(wxBitmap, SetWidth_gurax));
	Assign(Gurax_CreateMethod(wxBitmap, AddHandler_gurax));
	Assign(Gurax_CreateMethod(wxBitmap, CleanUpHandlers_gurax));
	Assign(Gurax_CreateMethod(wxBitmap, FindHandler_gurax));
	Assign(Gurax_CreateMethod(wxBitmap, InitStandardHandlers_gurax));
	Assign(Gurax_CreateMethod(wxBitmap, InsertHandler_gurax));
	Assign(Gurax_CreateMethod(wxBitmap, NewFrom_gurax));
	Assign(Gurax_CreateMethod(wxBitmap, NewFromPNGData_gurax));
	Assign(Gurax_CreateMethod(wxBitmap, RemoveHandler_gurax));
}

Value* VType_wxBitmap::DoCastFrom(Processor& processor, const Value& value, DeclArg::Flags flags) const
{
	RefPtr<Value_Image> pValueCasted(value.Cast<Value_Image>(processor, flags));
	if (pValueCasted) {
		return new Value_wxBitmap(wxBitmap(Util::CreateImage(pValueCasted->GetImage())));
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Value_wxBitmap
//------------------------------------------------------------------------------
VType& Value_wxBitmap::vtype = VTYPE_wxBitmap;

String Value_wxBitmap::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Bitmap");
}

Gurax_EndModuleScope(wx)
