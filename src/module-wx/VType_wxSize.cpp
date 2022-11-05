//==============================================================================
// VType_wxSize.cpp
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

${help.ComposePropertyHelp(wx.Size, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.Size, `en)}

${help.ComposeMethodHelp(wx.Size, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.Size(width? as Number, height? as Number):map {block?}
Gurax_DeclareConstructorAlias(Size_gurax, "Size")
{
	Declare(VTYPE_wxSize, Flag::Map);
	DeclareArg("width", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.Size.");
}

Gurax_ImplementConstructorEx(Size_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool width_validFlag = args_gurax.IsValid();
	int width = width_validFlag? args_gurax.PickNumber<int>() : 0;
	bool height_validFlag = args_gurax.IsValid();
	int height = height_validFlag? args_gurax.PickNumber<int>() : 0;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSize(
		wxSize(width, height)));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.Size#DecTo(size as wx.Size)
Gurax_DeclareMethodAlias(wxSize, DecTo_gurax, "DecTo")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSize, DecTo_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxSize& value_size = args_gurax.Pick<Value_wxSize>();
	const wxSize& size = value_size.GetEntity();
	// Function body
	pEntity_gurax->DecTo(size);
	return Gurax::Value::nil();
}

// wx.Size#DecToIfSpecified(size as wx.Size)
Gurax_DeclareMethodAlias(wxSize, DecToIfSpecified_gurax, "DecToIfSpecified")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSize, DecToIfSpecified_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxSize& value_size = args_gurax.Pick<Value_wxSize>();
	const wxSize& size = value_size.GetEntity();
	// Function body
	pEntity_gurax->DecToIfSpecified(size);
	return Gurax::Value::nil();
}

// wx.Size#GetHeight()
Gurax_DeclareMethodAlias(wxSize, GetHeight_gurax, "GetHeight")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSize, GetHeight_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetHeight();
	return new Gurax::Value_Number(rtn);
}

// wx.Size#GetWidth()
Gurax_DeclareMethodAlias(wxSize, GetWidth_gurax, "GetWidth")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSize, GetWidth_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetWidth();
	return new Gurax::Value_Number(rtn);
}

// wx.Size#IncTo(size as wx.Size)
Gurax_DeclareMethodAlias(wxSize, IncTo_gurax, "IncTo")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSize, IncTo_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxSize& value_size = args_gurax.Pick<Value_wxSize>();
	const wxSize& size = value_size.GetEntity();
	// Function body
	pEntity_gurax->IncTo(size);
	return Gurax::Value::nil();
}

// wx.Size#IsFullySpecified()
Gurax_DeclareMethodAlias(wxSize, IsFullySpecified_gurax, "IsFullySpecified")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSize, IsFullySpecified_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsFullySpecified();
	return new Gurax::Value_Bool(rtn);
}

// wx.Size#Scale(xscale as Number, yscale as Number)
Gurax_DeclareMethodAlias(wxSize, Scale_gurax, "Scale")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("xscale", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("yscale", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSize, Scale_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	float xscale = args_gurax.PickNumber<float>();
	float yscale = args_gurax.PickNumber<float>();
	// Function body
	pEntity_gurax->Scale(xscale, yscale);
	return valueThis_gurax.Reference();
}

// wx.Size#Set(width as Number, height as Number)
Gurax_DeclareMethodAlias(wxSize, Set_gurax, "Set")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSize, Set_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int width = args_gurax.PickNumber<int>();
	int height = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->Set(width, height);
	return Gurax::Value::nil();
}

// wx.Size#SetDefaults(sizeDefault as wx.Size)
Gurax_DeclareMethodAlias(wxSize, SetDefaults_gurax, "SetDefaults")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("sizeDefault", VTYPE_wxSize, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSize, SetDefaults_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxSize& value_sizeDefault = args_gurax.Pick<Value_wxSize>();
	const wxSize& sizeDefault = value_sizeDefault.GetEntity();
	// Function body
	pEntity_gurax->SetDefaults(sizeDefault);
	return Gurax::Value::nil();
}

// wx.Size#SetHeight(height as Number)
Gurax_DeclareMethodAlias(wxSize, SetHeight_gurax, "SetHeight")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSize, SetHeight_gurax, processor_gurax, argument_gurax)
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

// wx.Size#SetWidth(width as Number)
Gurax_DeclareMethodAlias(wxSize, SetWidth_gurax, "SetWidth")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSize, SetWidth_gurax, processor_gurax, argument_gurax)
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

// wx.Size#DecBy(args* as Any)
Gurax_DeclareMethodAlias(wxSize, DecBy_gurax, "DecBy")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSize, DecBy_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Gurax::ValueList& args = args_gurax.PickList();
	// Function body
	// DecBy(pt as const_Point_r) as void
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("pt", VTYPE_wxPoint);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		const wxPoint& pt = args.Pick<Value_wxPoint>().GetEntity();
		pEntity_gurax->DecBy(pt);
		return Value::nil();
	} while (0);
	Error::ClearIssuedFlag();
	// DecBy(size as const_Size_r) as void
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("pt", VTYPE_wxSize);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		const wxSize& size = args.Pick<Value_wxSize>().GetEntity();
		pEntity_gurax->DecBy(size);
		return Value::nil();
	} while (0);
	Error::ClearIssuedFlag();
	// DecBy(dx as int, dy as int) as void
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("dx", VTYPE_Number);
			pDeclCallable->DeclareArg("dy", VTYPE_Number);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		int dx = args.PickNumber<int>();
		int dy = args.PickNumber<int>();
		pEntity_gurax->DecBy(dx, dy);
		return Value::nil();
	} while (0);
	Error::ClearIssuedFlag();
	// DecBy(d as int) as void
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("d", VTYPE_Number);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		int d = args.PickNumber<int>();
		pEntity_gurax->DecBy(d);
		return Value::nil();
	} while (0);
	return Value::nil();
}

// wx.Size#IncBy(args* as Any)
Gurax_DeclareMethodAlias(wxSize, IncBy_gurax, "IncBy")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSize, IncBy_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Gurax::ValueList& args = args_gurax.PickList();
	// Function body
	// IncBy(pt as const_Point_r) as void
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("pt", VTYPE_wxPoint);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		const wxPoint& pt = args.Pick<Value_wxPoint>().GetEntity();
		pEntity_gurax->IncBy(pt);
		return Value::nil();
	} while (0);
	Error::ClearIssuedFlag();
	// IncBy(size as const_Size_r) as void
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("pt", VTYPE_wxSize);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		const wxSize& size = args.Pick<Value_wxSize>().GetEntity();
		pEntity_gurax->IncBy(size);
		return Value::nil();
	} while (0);
	Error::ClearIssuedFlag();
	// IncBy(dx as int, dy as int) as void
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("dx", VTYPE_Number);
			pDeclCallable->DeclareArg("dy", VTYPE_Number);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		int dx = args.PickNumber<int>();
		int dy = args.PickNumber<int>();
		pEntity_gurax->IncBy(dx, dy);
		return Value::nil();
	} while (0);
	Error::ClearIssuedFlag();
	// IncBy(d as int) as void
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("d", VTYPE_Number);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		int d = args.PickNumber<int>();
		pEntity_gurax->IncBy(d);
		return Value::nil();
	} while (0);
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxSize
//------------------------------------------------------------------------------
VType_wxSize VTYPE_wxSize("Size");

void VType_wxSize::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(Size_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxSize, DecTo_gurax));
	Assign(Gurax_CreateMethod(wxSize, DecToIfSpecified_gurax));
	Assign(Gurax_CreateMethod(wxSize, GetHeight_gurax));
	Assign(Gurax_CreateMethod(wxSize, GetWidth_gurax));
	Assign(Gurax_CreateMethod(wxSize, IncTo_gurax));
	Assign(Gurax_CreateMethod(wxSize, IsFullySpecified_gurax));
	Assign(Gurax_CreateMethod(wxSize, Scale_gurax));
	Assign(Gurax_CreateMethod(wxSize, Set_gurax));
	Assign(Gurax_CreateMethod(wxSize, SetDefaults_gurax));
	Assign(Gurax_CreateMethod(wxSize, SetHeight_gurax));
	Assign(Gurax_CreateMethod(wxSize, SetWidth_gurax));
	Assign(Gurax_CreateMethod(wxSize, DecBy_gurax));
	Assign(Gurax_CreateMethod(wxSize, IncBy_gurax));
}

//------------------------------------------------------------------------------
// Value_wxSize
//------------------------------------------------------------------------------
VType& Value_wxSize::vtype = VTYPE_wxSize;

String Value_wxSize::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Size");
}

Gurax_EndModuleScope(wx)
