//==============================================================================
// VType_wxRect.cpp
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

${help.ComposePropertyHelp(wx.Rect, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.Rect, `en)}

${help.ComposeMethodHelp(wx.Rect, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.Rect(x? as Number, y? as Number, width? as Number, height? as Number):map {block?}
Gurax_DeclareConstructorAlias(Rect_gurax, "Rect")
{
	Declare(VTYPE_wxRect, Flag::Map);
	DeclareArg("x", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.Rect.");
}

Gurax_ImplementConstructorEx(Rect_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool x_validFlag = args_gurax.IsValid();
	int x = x_validFlag? args_gurax.PickNumber<int>() : 0;
	bool y_validFlag = args_gurax.IsValid();
	int y = y_validFlag? args_gurax.PickNumber<int>() : 0;
	bool width_validFlag = args_gurax.IsValid();
	int width = width_validFlag? args_gurax.PickNumber<int>() : 0;
	bool height_validFlag = args_gurax.IsValid();
	int height = height_validFlag? args_gurax.PickNumber<int>() : 0;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRect(
		wxRect(x, y, width, height)));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.Rect#Contains(args* as Any)
Gurax_DeclareMethodAlias(wxRect, Contains_gurax, "Contains")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRect, Contains_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Gurax::ValueList& args = args_gurax.PickList();
	// Function body
	// Contains(x as int, y as int) as bool
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("x", VTYPE_Number);
			pDeclCallable->DeclareArg("y", VTYPE_Number);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		int x = args.PickNumber<int>();
		int y = args.PickNumber<int>();
		bool rtn = pEntity_gurax->Contains(x, y);
		return new Value_Bool(rtn);
	} while (0);
	Error::ClearIssuedFlag();
	// Contains(pt as const_Point_r) as bool
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
		bool rtn = pEntity_gurax->Contains(pt);
		return new Value_Bool(rtn);
	} while (0);
	Error::ClearIssuedFlag();
	// Contains(rect as const_Rect_r) as bool
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("rect", VTYPE_wxRect);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		const wxRect& rect = args.Pick<Value_wxRect>().GetEntity();
		bool rtn = pEntity_gurax->Contains(rect);
		return new Value_Bool(rtn);
	} while (0);
	return Value::nil();
}

// wx.Rect#GetBottom()
Gurax_DeclareMethodAlias(wxRect, GetBottom_gurax, "GetBottom")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRect, GetBottom_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetBottom();
	return new Gurax::Value_Number(rtn);
}

// wx.Rect#GetBottomLeft() {block?}
Gurax_DeclareMethodAlias(wxRect, GetBottomLeft_gurax, "GetBottomLeft")
{
	Declare(VTYPE_wxPoint, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRect, GetBottomLeft_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPoint(
		pEntity_gurax->GetBottomLeft()));
}

// wx.Rect#GetBottomRight() {block?}
Gurax_DeclareMethodAlias(wxRect, GetBottomRight_gurax, "GetBottomRight")
{
	Declare(VTYPE_wxPoint, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRect, GetBottomRight_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPoint(
		pEntity_gurax->GetBottomRight()));
}

// wx.Rect#GetHeight()
Gurax_DeclareMethodAlias(wxRect, GetHeight_gurax, "GetHeight")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRect, GetHeight_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetHeight();
	return new Gurax::Value_Number(rtn);
}

// wx.Rect#GetLeft()
Gurax_DeclareMethodAlias(wxRect, GetLeft_gurax, "GetLeft")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRect, GetLeft_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetLeft();
	return new Gurax::Value_Number(rtn);
}

// wx.Rect#GetPosition() {block?}
Gurax_DeclareMethodAlias(wxRect, GetPosition_gurax, "GetPosition")
{
	Declare(VTYPE_wxPoint, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRect, GetPosition_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPoint(
		pEntity_gurax->GetPosition()));
}

// wx.Rect#GetRight()
Gurax_DeclareMethodAlias(wxRect, GetRight_gurax, "GetRight")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRect, GetRight_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetRight();
	return new Gurax::Value_Number(rtn);
}

// wx.Rect#GetSize() {block?}
Gurax_DeclareMethodAlias(wxRect, GetSize_gurax, "GetSize")
{
	Declare(VTYPE_wxSize, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRect, GetSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSize(
		pEntity_gurax->GetSize()));
}

// wx.Rect#GetTop()
Gurax_DeclareMethodAlias(wxRect, GetTop_gurax, "GetTop")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRect, GetTop_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetTop();
	return new Gurax::Value_Number(rtn);
}

// wx.Rect#GetTopLeft() {block?}
Gurax_DeclareMethodAlias(wxRect, GetTopLeft_gurax, "GetTopLeft")
{
	Declare(VTYPE_wxPoint, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRect, GetTopLeft_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPoint(
		pEntity_gurax->GetTopLeft()));
}

// wx.Rect#GetTopRight() {block?}
Gurax_DeclareMethodAlias(wxRect, GetTopRight_gurax, "GetTopRight")
{
	Declare(VTYPE_wxPoint, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRect, GetTopRight_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPoint(
		pEntity_gurax->GetTopRight()));
}

// wx.Rect#GetWidth()
Gurax_DeclareMethodAlias(wxRect, GetWidth_gurax, "GetWidth")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRect, GetWidth_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetWidth();
	return new Gurax::Value_Number(rtn);
}

// wx.Rect#GetX()
Gurax_DeclareMethodAlias(wxRect, GetX_gurax, "GetX")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRect, GetX_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetX();
	return new Gurax::Value_Number(rtn);
}

// wx.Rect#GetY()
Gurax_DeclareMethodAlias(wxRect, GetY_gurax, "GetY")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRect, GetY_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetY();
	return new Gurax::Value_Number(rtn);
}

// wx.Rect#Intersect(rect as wx.Rect) {block?}
Gurax_DeclareMethodAlias(wxRect, Intersect_gurax, "Intersect")
{
	Declare(VTYPE_wxRect, Flag::None);
	DeclareArg("rect", VTYPE_wxRect, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRect, Intersect_gurax, processor_gurax, argument_gurax)
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
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRect(
		pEntity_gurax->Intersect(rect)));
}

// wx.Rect#IsEmpty()
Gurax_DeclareMethodAlias(wxRect, IsEmpty_gurax, "IsEmpty")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRect, IsEmpty_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsEmpty();
	return new Gurax::Value_Bool(rtn);
}

// wx.Rect#SetHeight(height as Number)
Gurax_DeclareMethodAlias(wxRect, SetHeight_gurax, "SetHeight")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRect, SetHeight_gurax, processor_gurax, argument_gurax)
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

// wx.Rect#SetPosition(pos as wx.Point)
Gurax_DeclareMethodAlias(wxRect, SetPosition_gurax, "SetPosition")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRect, SetPosition_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxPoint& value_pos = args_gurax.Pick<Value_wxPoint>();
	const wxPoint& pos = value_pos.GetEntity();
	// Function body
	pEntity_gurax->SetPosition(pos);
	return Gurax::Value::nil();
}

// wx.Rect#SetSize(s as wx.Size)
Gurax_DeclareMethodAlias(wxRect, SetSize_gurax, "SetSize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("s", VTYPE_wxSize, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRect, SetSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxSize& value_s = args_gurax.Pick<Value_wxSize>();
	const wxSize& s = value_s.GetEntity();
	// Function body
	pEntity_gurax->SetSize(s);
	return Gurax::Value::nil();
}

// wx.Rect#SetWidth(width as Number)
Gurax_DeclareMethodAlias(wxRect, SetWidth_gurax, "SetWidth")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRect, SetWidth_gurax, processor_gurax, argument_gurax)
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

// wx.Rect#SetX(x as Number)
Gurax_DeclareMethodAlias(wxRect, SetX_gurax, "SetX")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRect, SetX_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int x = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetX(x);
	return Gurax::Value::nil();
}

// wx.Rect#SetY(y as Number)
Gurax_DeclareMethodAlias(wxRect, SetY_gurax, "SetY")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRect, SetY_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int y = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetY(y);
	return Gurax::Value::nil();
}

// wx.Rect#SetLeft(left as Number)
Gurax_DeclareMethodAlias(wxRect, SetLeft_gurax, "SetLeft")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("left", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRect, SetLeft_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int left = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetLeft(left);
	return Gurax::Value::nil();
}

// wx.Rect#SetRight(right as Number)
Gurax_DeclareMethodAlias(wxRect, SetRight_gurax, "SetRight")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("right", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRect, SetRight_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int right = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetRight(right);
	return Gurax::Value::nil();
}

// wx.Rect#SetTop(top as Number)
Gurax_DeclareMethodAlias(wxRect, SetTop_gurax, "SetTop")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("top", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRect, SetTop_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int top = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetTop(top);
	return Gurax::Value::nil();
}

// wx.Rect#SetBottom(bottom as Number)
Gurax_DeclareMethodAlias(wxRect, SetBottom_gurax, "SetBottom")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("bottom", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRect, SetBottom_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int bottom = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetBottom(bottom);
	return Gurax::Value::nil();
}

// wx.Rect#SetTopLeft(p as wx.Point)
Gurax_DeclareMethodAlias(wxRect, SetTopLeft_gurax, "SetTopLeft")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("p", VTYPE_wxPoint, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRect, SetTopLeft_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxPoint& value_p = args_gurax.Pick<Value_wxPoint>();
	const wxPoint& p = value_p.GetEntity();
	// Function body
	pEntity_gurax->SetTopLeft(p);
	return Gurax::Value::nil();
}

// wx.Rect#SetBottomRight(p as wx.Point)
Gurax_DeclareMethodAlias(wxRect, SetBottomRight_gurax, "SetBottomRight")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("p", VTYPE_wxPoint, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRect, SetBottomRight_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxPoint& value_p = args_gurax.Pick<Value_wxPoint>();
	const wxPoint& p = value_p.GetEntity();
	// Function body
	pEntity_gurax->SetBottomRight(p);
	return Gurax::Value::nil();
}

// wx.Rect#SetTopRight(p as wx.Point)
Gurax_DeclareMethodAlias(wxRect, SetTopRight_gurax, "SetTopRight")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("p", VTYPE_wxPoint, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRect, SetTopRight_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxPoint& value_p = args_gurax.Pick<Value_wxPoint>();
	const wxPoint& p = value_p.GetEntity();
	// Function body
	pEntity_gurax->SetTopRight(p);
	return Gurax::Value::nil();
}

// wx.Rect#SetBottomLeft(p as wx.Point)
Gurax_DeclareMethodAlias(wxRect, SetBottomLeft_gurax, "SetBottomLeft")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("p", VTYPE_wxPoint, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRect, SetBottomLeft_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxPoint& value_p = args_gurax.Pick<Value_wxPoint>();
	const wxPoint& p = value_p.GetEntity();
	// Function body
	pEntity_gurax->SetBottomLeft(p);
	return Gurax::Value::nil();
}

// wx.Rect#CentreIn(r as wx.Rect, dir? as Number) {block?}
Gurax_DeclareMethodAlias(wxRect, CentreIn_gurax, "CentreIn")
{
	Declare(VTYPE_wxRect, Flag::None);
	DeclareArg("r", VTYPE_wxRect, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dir", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRect, CentreIn_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRect& value_r = args_gurax.Pick<Value_wxRect>();
	const wxRect& r = value_r.GetEntity();
	bool dir_validFlag = args_gurax.IsValid();
	int dir = dir_validFlag? args_gurax.PickNumber<int>() : wxBOTH;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRect(
		pEntity_gurax->CentreIn(r, dir)));
}

// wx.Rect#CenterIn(r as wx.Rect, dir? as Number) {block?}
Gurax_DeclareMethodAlias(wxRect, CenterIn_gurax, "CenterIn")
{
	Declare(VTYPE_wxRect, Flag::None);
	DeclareArg("r", VTYPE_wxRect, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dir", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRect, CenterIn_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRect& value_r = args_gurax.Pick<Value_wxRect>();
	const wxRect& r = value_r.GetEntity();
	bool dir_validFlag = args_gurax.IsValid();
	int dir = dir_validFlag? args_gurax.PickNumber<int>() : wxBOTH;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRect(
		pEntity_gurax->CenterIn(r, dir)));
}

// wx.Rect#Deflate(args* as Any)
Gurax_DeclareMethodAlias(wxRect, Deflate_gurax, "Deflate")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRect, Deflate_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Gurax::ValueList& args = args_gurax.PickList();
	// Function body
	// Deflate(dx as Coord, dy as Coord):returnThis
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
		wxCoord dx = args.PickNumber<wxCoord>();
		wxCoord dy = args.PickNumber<wxCoord>();
		pEntity_gurax->Deflate(dx, dy);
		return valueThis_gurax.Reference();
	} while (0);
	Error::ClearIssuedFlag();
	// Deflate(diff as const_Size_r):returnThis
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("diff", VTYPE_wxSize);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		const wxSize& diff = args.Pick<Value_wxSize>().GetEntity();
		pEntity_gurax->Deflate(diff);
		return valueThis_gurax.Reference();
	} while (0);
	Error::ClearIssuedFlag();
	// Deflate(diff as Coord):returnThis
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("diff", VTYPE_Number);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		wxCoord diff = args.PickNumber<wxCoord>();
		pEntity_gurax->Deflate(diff);
		return valueThis_gurax.Reference();
	} while (0);
	return Value::nil();
}

// wx.Rect#Inflate(args* as Any)
Gurax_DeclareMethodAlias(wxRect, Inflate_gurax, "Inflate")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRect, Inflate_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Gurax::ValueList& args = args_gurax.PickList();
	// Function body
	// Inflate(dx as Coord, dy as Coord):returnThis
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
		wxCoord dx = args.PickNumber<wxCoord>();
		wxCoord dy = args.PickNumber<wxCoord>();
		pEntity_gurax->Inflate(dx, dy);
		return valueThis_gurax.Reference();
	} while (0);
	Error::ClearIssuedFlag();
	// Inflate(diff as const_Size_r):returnThis
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("diff", VTYPE_wxSize);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		const wxSize& diff = args.Pick<Value_wxSize>().GetEntity();
		pEntity_gurax->Inflate(diff);
		return valueThis_gurax.Reference();
	} while (0);
	Error::ClearIssuedFlag();
	// Inflate(diff as Coord):returnThis
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("diff", VTYPE_Number);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		wxCoord diff = args.PickNumber<wxCoord>();
		pEntity_gurax->Inflate(diff);
		return valueThis_gurax.Reference();
	} while (0);
	return Value::nil();
}

// wx.Rect#Offset(args* as Any)
Gurax_DeclareMethodAlias(wxRect, Offset_gurax, "Offset")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRect, Offset_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Gurax::ValueList& args = args_gurax.PickList();
	// Function body
	// Offset(dx as Coord, dy as Coord) as void
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
		wxCoord dx = args.PickNumber<wxCoord>();
		wxCoord dy = args.PickNumber<wxCoord>();
		pEntity_gurax->Offset(dx, dy);
		return Value::nil();
	} while (0);
	Error::ClearIssuedFlag();
	// Offset(pt as const_Point_r) as void
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
		pEntity_gurax->Offset(pt);
		return Value::nil();
	} while (0);
	return Value::nil();
}

// wx.Rect#Union(rect as wx.Rect)
Gurax_DeclareMethodAlias(wxRect, Union_gurax, "Union")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("rect", VTYPE_wxRect, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRect, Union_gurax, processor_gurax, argument_gurax)
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
	pEntity_gurax->Union(rect);
	return valueThis_gurax.Reference();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
Gurax_DeclareProperty_RW(wxRect, width)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(wxRect, width)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	return new Value_Number(valueThis_gurax.GetEntity().width);
}

Gurax_ImplementPropertySetter(wxRect, width)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	auto& value_gurax = value;
	int width = Value_Number::GetNumber<int>(value_gurax);
	valueThis_gurax.GetEntity().width = width;
}

Gurax_DeclareProperty_RW(wxRect, height)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(wxRect, height)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	return new Value_Number(valueThis_gurax.GetEntity().height);
}

Gurax_ImplementPropertySetter(wxRect, height)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	auto& value_gurax = value;
	int height = Value_Number::GetNumber<int>(value_gurax);
	valueThis_gurax.GetEntity().height = height;
}

Gurax_DeclareProperty_RW(wxRect, x)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(wxRect, x)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	return new Value_Number(valueThis_gurax.GetEntity().x);
}

Gurax_ImplementPropertySetter(wxRect, x)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	auto& value_gurax = value;
	int x = Value_Number::GetNumber<int>(value_gurax);
	valueThis_gurax.GetEntity().x = x;
}

Gurax_DeclareProperty_RW(wxRect, y)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(wxRect, y)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	return new Value_Number(valueThis_gurax.GetEntity().y);
}

Gurax_ImplementPropertySetter(wxRect, y)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	auto& value_gurax = value;
	int y = Value_Number::GetNumber<int>(value_gurax);
	valueThis_gurax.GetEntity().y = y;
}

//------------------------------------------------------------------------------
// VType_wxRect
//------------------------------------------------------------------------------
VType_wxRect VTYPE_wxRect("Rect");

void VType_wxRect::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(Rect_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxRect, Contains_gurax));
	Assign(Gurax_CreateMethod(wxRect, GetBottom_gurax));
	Assign(Gurax_CreateMethod(wxRect, GetBottomLeft_gurax));
	Assign(Gurax_CreateMethod(wxRect, GetBottomRight_gurax));
	Assign(Gurax_CreateMethod(wxRect, GetHeight_gurax));
	Assign(Gurax_CreateMethod(wxRect, GetLeft_gurax));
	Assign(Gurax_CreateMethod(wxRect, GetPosition_gurax));
	Assign(Gurax_CreateMethod(wxRect, GetRight_gurax));
	Assign(Gurax_CreateMethod(wxRect, GetSize_gurax));
	Assign(Gurax_CreateMethod(wxRect, GetTop_gurax));
	Assign(Gurax_CreateMethod(wxRect, GetTopLeft_gurax));
	Assign(Gurax_CreateMethod(wxRect, GetTopRight_gurax));
	Assign(Gurax_CreateMethod(wxRect, GetWidth_gurax));
	Assign(Gurax_CreateMethod(wxRect, GetX_gurax));
	Assign(Gurax_CreateMethod(wxRect, GetY_gurax));
	Assign(Gurax_CreateMethod(wxRect, Intersect_gurax));
	Assign(Gurax_CreateMethod(wxRect, IsEmpty_gurax));
	Assign(Gurax_CreateMethod(wxRect, SetHeight_gurax));
	Assign(Gurax_CreateMethod(wxRect, SetPosition_gurax));
	Assign(Gurax_CreateMethod(wxRect, SetSize_gurax));
	Assign(Gurax_CreateMethod(wxRect, SetWidth_gurax));
	Assign(Gurax_CreateMethod(wxRect, SetX_gurax));
	Assign(Gurax_CreateMethod(wxRect, SetY_gurax));
	Assign(Gurax_CreateMethod(wxRect, SetLeft_gurax));
	Assign(Gurax_CreateMethod(wxRect, SetRight_gurax));
	Assign(Gurax_CreateMethod(wxRect, SetTop_gurax));
	Assign(Gurax_CreateMethod(wxRect, SetBottom_gurax));
	Assign(Gurax_CreateMethod(wxRect, SetTopLeft_gurax));
	Assign(Gurax_CreateMethod(wxRect, SetBottomRight_gurax));
	Assign(Gurax_CreateMethod(wxRect, SetTopRight_gurax));
	Assign(Gurax_CreateMethod(wxRect, SetBottomLeft_gurax));
	Assign(Gurax_CreateMethod(wxRect, CentreIn_gurax));
	Assign(Gurax_CreateMethod(wxRect, CenterIn_gurax));
	Assign(Gurax_CreateMethod(wxRect, Deflate_gurax));
	Assign(Gurax_CreateMethod(wxRect, Inflate_gurax));
	Assign(Gurax_CreateMethod(wxRect, Offset_gurax));
	Assign(Gurax_CreateMethod(wxRect, Union_gurax));
	// Assignment of property
	Assign(Gurax_CreateProperty(wxRect, width));
	Assign(Gurax_CreateProperty(wxRect, height));
	Assign(Gurax_CreateProperty(wxRect, x));
	Assign(Gurax_CreateProperty(wxRect, y));
}

//------------------------------------------------------------------------------
// Value_wxRect
//------------------------------------------------------------------------------
VType& Value_wxRect::vtype = VTYPE_wxRect;

String Value_wxRect::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Rect");
}

Gurax_EndModuleScope(wx)
