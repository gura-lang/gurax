//==============================================================================
// VType_wxBitmapHandler.cpp
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

${help.ComposePropertyHelp(wx.BitmapHandler, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.BitmapHandler, `en)}

${help.ComposeMethodHelp(wx.BitmapHandler, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.BitmapHandler() {block?}
Gurax_DeclareConstructorAlias(BitmapHandler_gurax, "BitmapHandler")
{
	Declare(VTYPE_wxBitmapHandler, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.BitmapHandler.");
}

Gurax_ImplementConstructorEx(BitmapHandler_gurax, processor_gurax, argument_gurax)
{
	// Function body
	auto pEntity_gurax = new wxBitmapHandler();
	RefPtr<Value_wxBitmapHandler> pValue_gurax(new Value_wxBitmapHandler(pEntity_gurax));
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.BitmapHandler#Create(bitmap as wx.Bitmap, data as Pointer, type as Number, width as Number, height as Number, depth? as Number)
Gurax_DeclareMethodAlias(wxBitmapHandler, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("bitmap", VTYPE_wxBitmap, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("depth", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBitmapHandler, Create_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxBitmap& value_bitmap = args_gurax.Pick<Value_wxBitmap>();
	wxBitmap* bitmap = value_bitmap.GetEntityPtr();
	const void* data = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetPointerC<void>();
	wxBitmapType type = args_gurax.PickNumber<wxBitmapType>();
	int width = args_gurax.PickNumber<int>();
	int height = args_gurax.PickNumber<int>();
	bool depth_validFlag = args_gurax.IsValid();
	int depth = depth_validFlag? args_gurax.PickNumber<int>() : 1;
	// Function body
	bool rtn = pEntity_gurax->Create(bitmap, data, type, width, height, depth);
	return new Gurax::Value_Bool(rtn);
}

// wx.BitmapHandler#GetExtension()
Gurax_DeclareMethodAlias(wxBitmapHandler, GetExtension_gurax, "GetExtension")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBitmapHandler, GetExtension_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetExtension();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.BitmapHandler#GetName()
Gurax_DeclareMethodAlias(wxBitmapHandler, GetName_gurax, "GetName")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBitmapHandler, GetName_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetName();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.BitmapHandler#GetType()
Gurax_DeclareMethodAlias(wxBitmapHandler, GetType_gurax, "GetType")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBitmapHandler, GetType_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxBitmapType rtn = pEntity_gurax->GetType();
	return new Gurax::Value_Number(rtn);
}

// wx.BitmapHandler#LoadFile(bitmap as wx.Bitmap, name as String, type as Number, desiredWidth as Number, desiredHeight as Number)
Gurax_DeclareMethodAlias(wxBitmapHandler, LoadFile_gurax, "LoadFile")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("bitmap", VTYPE_wxBitmap, ArgOccur::Once, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("desiredWidth", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("desiredHeight", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBitmapHandler, LoadFile_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxBitmap& value_bitmap = args_gurax.Pick<Value_wxBitmap>();
	wxBitmap* bitmap = value_bitmap.GetEntityPtr();
	const char* name = args_gurax.PickString();
	wxBitmapType type = args_gurax.PickNumber<wxBitmapType>();
	int desiredWidth = args_gurax.PickNumber<int>();
	int desiredHeight = args_gurax.PickNumber<int>();
	// Function body
	bool rtn = pEntity_gurax->LoadFile(bitmap, name, type, desiredWidth, desiredHeight);
	return new Gurax::Value_Bool(rtn);
}

// wx.BitmapHandler#SaveFile(bitmap as wx.Bitmap, name as String, type as Number, palette? as wx.Palette)
Gurax_DeclareMethodAlias(wxBitmapHandler, SaveFile_gurax, "SaveFile")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("bitmap", VTYPE_wxBitmap, ArgOccur::Once, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("palette", VTYPE_wxPalette, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBitmapHandler, SaveFile_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxBitmap& value_bitmap = args_gurax.Pick<Value_wxBitmap>();
	const wxBitmap* bitmap = value_bitmap.GetEntityPtr();
	const char* name = args_gurax.PickString();
	wxBitmapType type = args_gurax.PickNumber<wxBitmapType>();
	const wxPalette* palette = args_gurax.IsValid()? args_gurax.Pick<Value_wxPalette>().GetEntityPtr() : nullptr;
	// Function body
	bool rtn = pEntity_gurax->SaveFile(bitmap, name, type, palette);
	return new Gurax::Value_Bool(rtn);
}

// wx.BitmapHandler#SetExtension(extension as String)
Gurax_DeclareMethodAlias(wxBitmapHandler, SetExtension_gurax, "SetExtension")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("extension", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBitmapHandler, SetExtension_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* extension = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetExtension(extension);
	return Gurax::Value::nil();
}

// wx.BitmapHandler#SetName(name as String)
Gurax_DeclareMethodAlias(wxBitmapHandler, SetName_gurax, "SetName")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBitmapHandler, SetName_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* name = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetName(name);
	return Gurax::Value::nil();
}

// wx.BitmapHandler#SetType(type as Number)
Gurax_DeclareMethodAlias(wxBitmapHandler, SetType_gurax, "SetType")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("type", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBitmapHandler, SetType_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxBitmapType type = args_gurax.PickNumber<wxBitmapType>();
	// Function body
	pEntity_gurax->SetType(type);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxBitmapHandler
//------------------------------------------------------------------------------
VType_wxBitmapHandler VTYPE_wxBitmapHandler("BitmapHandler");

void VType_wxBitmapHandler::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(BitmapHandler_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxBitmapHandler, Create_gurax));
	Assign(Gurax_CreateMethod(wxBitmapHandler, GetExtension_gurax));
	Assign(Gurax_CreateMethod(wxBitmapHandler, GetName_gurax));
	Assign(Gurax_CreateMethod(wxBitmapHandler, GetType_gurax));
	Assign(Gurax_CreateMethod(wxBitmapHandler, LoadFile_gurax));
	Assign(Gurax_CreateMethod(wxBitmapHandler, SaveFile_gurax));
	Assign(Gurax_CreateMethod(wxBitmapHandler, SetExtension_gurax));
	Assign(Gurax_CreateMethod(wxBitmapHandler, SetName_gurax));
	Assign(Gurax_CreateMethod(wxBitmapHandler, SetType_gurax));
}

//------------------------------------------------------------------------------
// Value_wxBitmapHandler
//------------------------------------------------------------------------------
VType& Value_wxBitmapHandler::vtype = VTYPE_wxBitmapHandler;

String Value_wxBitmapHandler::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.BitmapHandler");
}

Gurax_EndModuleScope(wx)
