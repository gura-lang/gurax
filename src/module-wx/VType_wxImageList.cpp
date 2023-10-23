﻿//==============================================================================
// VType_wxImageList.cpp
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

${help.ComposePropertyHelp(wx.ImageList, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.ImageList, `en)}

${help.ComposeMethodHelp(wx.ImageList, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.ImageList, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.ImageList, `ja)}

${help.ComposeMethodHelp(wx.ImageList, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.ImageList(width as Number, height as Number, mask? as Bool, initialCount? as Number) {block?}
Gurax_DeclareConstructorAlias(ImageList_gurax, "ImageList")
{
	Declare(VTYPE_wxImageList, Flag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mask", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("initialCount", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(ImageList_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int width = args_gurax.PickNumber<int>();
	int height = args_gurax.PickNumber<int>();
	bool mask = args_gurax.IsValid()? args_gurax.PickBool() : true;
	bool initialCount_validFlag = args_gurax.IsValid();
	int initialCount = initialCount_validFlag? args_gurax.PickNumber<int>() : 1;
	// Function body
	auto pEntity_gurax = new wxImageList(width, height, mask, initialCount);
	RefPtr<Value_wxImageList> pValue_gurax(new Value_wxImageList(pEntity_gurax));
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.ImageList#Add(args* as Any)
Gurax_DeclareMethodAlias(wxImageList, Add_gurax, "Add")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxImageList, Add_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Gurax::ValueList& args = args_gurax.PickList();
	// Function body
	// Add(bitmap as const_Bitmap_r, mask as const_Bitmap_r = wxNullBitmap) as int
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("bitmap", VTYPE_wxBitmap);
			pDeclCallable->DeclareArg("mask", VTYPE_wxBitmap, DeclArg::Occur::ZeroOrOnce);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		const wxBitmap& bitmap = args.Pick<Value_wxBitmap>().GetEntity();
		const wxBitmap& mask = args.IsValid()? args.Pick<Value_wxBitmap>().GetEntity() : wxNullBitmap;
		int rtn = pEntity_gurax->Add(bitmap, mask);
		return new Value_Number(rtn);
	} while (0);
	Error::ClearIssuedFlag();
	// Add(bitmap as const_Bitmap_r, maskColour as const_Colour_r) as int
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("bitmap", VTYPE_wxBitmap);
			pDeclCallable->DeclareArg("maskColour", VTYPE_wxColour);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		const wxBitmap& bitmap = args.Pick<Value_wxBitmap>().GetEntity();
		const wxColour& maskColour = args.Pick<Value_wxColour>().GetEntity();
		int rtn = pEntity_gurax->Add(bitmap, maskColour);
		return new Value_Number(rtn);
	} while (0);
	Error::ClearIssuedFlag();
	// Add(icon as const_Icon_r) as int
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("icon", VTYPE_wxIcon);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		const wxIcon& icon = args.Pick<Value_wxIcon>().GetEntity();
		int rtn = pEntity_gurax->Add(icon);
		return new Value_Number(rtn);
	} while (0);
	return Value::nil();
}

// wx.ImageList#Create(width as Number, height as Number, mask? as Bool, initialCount? as Number)
Gurax_DeclareMethodAlias(wxImageList, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mask", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("initialCount", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxImageList, Create_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int width = args_gurax.PickNumber<int>();
	int height = args_gurax.PickNumber<int>();
	bool mask = args_gurax.IsValid()? args_gurax.PickBool() : true;
	bool initialCount_validFlag = args_gurax.IsValid();
	int initialCount = initialCount_validFlag? args_gurax.PickNumber<int>() : 1;
	// Function body
	bool rtn = pEntity_gurax->Create(width, height, mask, initialCount);
	return new Gurax::Value_Bool(rtn);
}

// wx.ImageList#Draw(index as Number, dc as wx.DC, x as Number, y as Number, flags? as Number, solidBackground? as Bool)
Gurax_DeclareMethodAlias(wxImageList, Draw_gurax, "Draw")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dc", VTYPE_wxDC, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("solidBackground", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxImageList, Draw_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int index = args_gurax.PickNumber<int>();
	Value_wxDC& value_dc = args_gurax.Pick<Value_wxDC>();
	wxDC& dc = value_dc.GetEntity();
	int x = args_gurax.PickNumber<int>();
	int y = args_gurax.PickNumber<int>();
	bool flags_validFlag = args_gurax.IsValid();
	int flags = flags_validFlag? args_gurax.PickNumber<int>() : wxIMAGELIST_DRAW_NORMAL;
	bool solidBackground = args_gurax.IsValid()? args_gurax.PickBool() : false;
	// Function body
	bool rtn = pEntity_gurax->Draw(index, dc, x, y, flags, solidBackground);
	return new Gurax::Value_Bool(rtn);
}

// wx.ImageList#GetBitmap(index as Number) {block?}
Gurax_DeclareMethodAlias(wxImageList, GetBitmap_gurax, "GetBitmap")
{
	Declare(VTYPE_wxBitmap, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxImageList, GetBitmap_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int index = args_gurax.PickNumber<int>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxBitmap(pEntity_gurax->GetBitmap(index)));
}

// wx.ImageList#GetIcon(index as Number) {block?}
Gurax_DeclareMethodAlias(wxImageList, GetIcon_gurax, "GetIcon")
{
	Declare(VTYPE_wxIcon, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxImageList, GetIcon_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int index = args_gurax.PickNumber<int>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxIcon(pEntity_gurax->GetIcon(index)));
}

// wx.ImageList#GetImageCount()
Gurax_DeclareMethodAlias(wxImageList, GetImageCount_gurax, "GetImageCount")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxImageList, GetImageCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetImageCount();
	return new Gurax::Value_Number(rtn);
}

// wx.ImageList#GetSize(index as Number, &width:nilRef as Number, &height:nilRef as Number)
Gurax_DeclareMethodAlias(wxImageList, GetSize_gurax, "GetSize")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementMethodEx(wxImageList, GetSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int index = args_gurax.PickNumber<int>();
	RefPtr<Referencer> width(args_gurax.PickReferencer().Reference());
	RefPtr<Referencer> height(args_gurax.PickReferencer().Reference());
	// Function body
	int width_, height_;
	bool rtn = pEntity_gurax->GetSize(index, width_, height_);
	width->SetValue(new Value_Number(width_));
	height->SetValue(new Value_Number(height_));
	return new Value_Number(rtn);
}

// wx.ImageList#Remove(index as Number)
Gurax_DeclareMethodAlias(wxImageList, Remove_gurax, "Remove")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxImageList, Remove_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int index = args_gurax.PickNumber<int>();
	// Function body
	bool rtn = pEntity_gurax->Remove(index);
	return new Gurax::Value_Bool(rtn);
}

// wx.ImageList#RemoveAll()
Gurax_DeclareMethodAlias(wxImageList, RemoveAll_gurax, "RemoveAll")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxImageList, RemoveAll_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->RemoveAll();
	return new Gurax::Value_Bool(rtn);
}

// wx.ImageList#Replace(args* as Any)
Gurax_DeclareMethodAlias(wxImageList, Replace_gurax, "Replace")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxImageList, Replace_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Gurax::ValueList& args = args_gurax.PickList();
	// Function body
	// Replace(index as int, bitmap as const_Bitmap_r, mask as const_Bitmap_r = wxNullBitmap) as bool
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("index", VTYPE_Number);
			pDeclCallable->DeclareArg("bitmap", VTYPE_wxBitmap);
			pDeclCallable->DeclareArg("mask", VTYPE_wxBitmap, DeclArg::Occur::ZeroOrOnce);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		int index = args.PickNumber<int>();
		const wxBitmap& bitmap = args.Pick<Value_wxBitmap>().GetEntity();
		const wxBitmap& mask = args.IsValid()? args.Pick<Value_wxBitmap>().GetEntity() : wxNullBitmap;
		bool rtn = pEntity_gurax->Replace(index, bitmap, mask);
		return new Value_Bool(rtn);
	} while (0);
	Error::ClearIssuedFlag();
	// Replace(index as int, icon as const_Icon_r) as bool
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("index", VTYPE_Number);
			pDeclCallable->DeclareArg("icon", VTYPE_wxIcon);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		int index = args.PickNumber<int>();
		const wxIcon& icon = args.Pick<Value_wxIcon>().GetEntity();
		bool rtn = pEntity_gurax->Replace(index, icon);
		return new Value_Bool(rtn);
	} while (0);
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxImageList
//------------------------------------------------------------------------------
VType_wxImageList VTYPE_wxImageList("ImageList");

void VType_wxImageList::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(ImageList_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxImageList, Add_gurax));
	Assign(Gurax_CreateMethod(wxImageList, Create_gurax));
	Assign(Gurax_CreateMethod(wxImageList, Draw_gurax));
	Assign(Gurax_CreateMethod(wxImageList, GetBitmap_gurax));
	Assign(Gurax_CreateMethod(wxImageList, GetIcon_gurax));
	Assign(Gurax_CreateMethod(wxImageList, GetImageCount_gurax));
	Assign(Gurax_CreateMethod(wxImageList, GetSize_gurax));
	Assign(Gurax_CreateMethod(wxImageList, Remove_gurax));
	Assign(Gurax_CreateMethod(wxImageList, RemoveAll_gurax));
	Assign(Gurax_CreateMethod(wxImageList, Replace_gurax));
}

//------------------------------------------------------------------------------
// Value_wxImageList
//------------------------------------------------------------------------------
VType& Value_wxImageList::vtype = VTYPE_wxImageList;

String Value_wxImageList::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.ImageList");
}

Gurax_EndModuleScope(wx)
