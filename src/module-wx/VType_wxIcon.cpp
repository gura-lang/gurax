﻿//==============================================================================
// VType_wxIcon.cpp
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(wx.Icon, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.Icon, `en)}

${help.ComposeMethodHelp(wx.Icon, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.Icon(args* as Any) {block?}
Gurax_DeclareConstructorAlias(Icon_gurax, "Icon")
{
	Declare(VTYPE_wxIcon, Flag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates an instance of wx.Icon.
)**");
}

Gurax_ImplementConstructorEx(Icon_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Gurax::ValueList& args = args_gurax.PickList();
	// Function body
	// wx.Icon()
	if (args.empty()) {
		return new Value_wxIcon(wxIcon());
	}
	// wx.Icon(bits[] as String)
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("bits", VTYPE_String, DeclArg::Occur::Once, DeclArg::Flag::ListVar);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		const ValueList& values = args.PickList();
		std::unique_ptr<const char*> bits(new (const char*[values.size()]));
		size_t i = 0;
		for (const Value* pValue : values) bits.get()[i++] = Value_String::GetString(*pValue);
		RefPtr<Value> pValueRtn(new Value_wxIcon(wxIcon(bits.get())));
		return pValueRtn.release();
	} while (0);
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.Icon#CopyFromBitmap(bmp as wx.Bitmap)
Gurax_DeclareMethodAlias(wxIcon, CopyFromBitmap_gurax, "CopyFromBitmap")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("bmp", VTYPE_wxBitmap, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxIcon, CopyFromBitmap_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxBitmap& value_bmp = args_gurax.Pick<Value_wxBitmap>();
	const wxBitmap& bmp = value_bmp.GetEntity();
	// Function body
	pEntity_gurax->CopyFromBitmap(bmp);
	return Gurax::Value::nil();
}

// wx.Icon#GetDepth()
Gurax_DeclareMethodAlias(wxIcon, GetDepth_gurax, "GetDepth")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxIcon, GetDepth_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetDepth();
	return new Gurax::Value_Number(rtn);
}

// wx.Icon#GetHeight()
Gurax_DeclareMethodAlias(wxIcon, GetHeight_gurax, "GetHeight")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxIcon, GetHeight_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetHeight();
	return new Gurax::Value_Number(rtn);
}

// wx.Icon#GetWidth()
Gurax_DeclareMethodAlias(wxIcon, GetWidth_gurax, "GetWidth")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxIcon, GetWidth_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetWidth();
	return new Gurax::Value_Number(rtn);
}

// wx.Icon#IsOk()
Gurax_DeclareMethodAlias(wxIcon, IsOk_gurax, "IsOk")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxIcon, IsOk_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsOk();
	return new Gurax::Value_Bool(rtn);
}

// wx.Icon#LoadFile(name as String, type? as Number, desiredWidth? as Number, desiredHeight? as Number)
Gurax_DeclareMethodAlias(wxIcon, LoadFile_gurax, "LoadFile")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("desiredWidth", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("desiredHeight", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxIcon, LoadFile_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* name = args_gurax.PickString();
	bool type_validFlag = args_gurax.IsValid();
	wxBitmapType type = type_validFlag? args_gurax.PickNumber<wxBitmapType>() : wxICON_DEFAULT_TYPE;
	bool desiredWidth_validFlag = args_gurax.IsValid();
	int desiredWidth = desiredWidth_validFlag? args_gurax.PickNumber<int>() : -1;
	bool desiredHeight_validFlag = args_gurax.IsValid();
	int desiredHeight = desiredHeight_validFlag? args_gurax.PickNumber<int>() : -1;
	// Function body
	bool rtn = pEntity_gurax->LoadFile(name, type, desiredWidth, desiredHeight);
	return new Gurax::Value_Bool(rtn);
}

// wx.Icon#SetDepth(depth as Number)
Gurax_DeclareMethodAlias(wxIcon, SetDepth_gurax, "SetDepth")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("depth", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxIcon, SetDepth_gurax, processor_gurax, argument_gurax)
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

// wx.Icon#SetHeight(height as Number)
Gurax_DeclareMethodAlias(wxIcon, SetHeight_gurax, "SetHeight")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxIcon, SetHeight_gurax, processor_gurax, argument_gurax)
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

// wx.Icon#SetWidth(width as Number)
Gurax_DeclareMethodAlias(wxIcon, SetWidth_gurax, "SetWidth")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxIcon, SetWidth_gurax, processor_gurax, argument_gurax)
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

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxIcon
//------------------------------------------------------------------------------
VType_wxIcon VTYPE_wxIcon("Icon");

void VType_wxIcon::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxGDIObject, Flag::Mutable, Gurax_CreateConstructor(Icon_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxIcon, CopyFromBitmap_gurax));
	Assign(Gurax_CreateMethod(wxIcon, GetDepth_gurax));
	Assign(Gurax_CreateMethod(wxIcon, GetHeight_gurax));
	Assign(Gurax_CreateMethod(wxIcon, GetWidth_gurax));
	Assign(Gurax_CreateMethod(wxIcon, IsOk_gurax));
	Assign(Gurax_CreateMethod(wxIcon, LoadFile_gurax));
	Assign(Gurax_CreateMethod(wxIcon, SetDepth_gurax));
	Assign(Gurax_CreateMethod(wxIcon, SetHeight_gurax));
	Assign(Gurax_CreateMethod(wxIcon, SetWidth_gurax));
}

//------------------------------------------------------------------------------
// Value_wxIcon
//------------------------------------------------------------------------------
VType& Value_wxIcon::vtype = VTYPE_wxIcon;

String Value_wxIcon::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Icon");
}

Gurax_EndModuleScope(wx)
