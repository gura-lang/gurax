//==============================================================================
// VType_wxRegion.cpp
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

${help.ComposePropertyHelp(wxRegion)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxRegion)}

${help.ComposeMethodHelp(wxRegion)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.Region(args* as Any) {block?}
Gurax_DeclareConstructorAlias(Region_gurax, "Region")
{
	Declare(VTYPE_wxRegion, Flag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.Region.");
}

Gurax_ImplementConstructorEx(Region_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Gurax::ValueList& args = args_gurax.PickList();
	// Function body
	// wx.Region(x as Coord, y as Coord, width as Coord, height as Coord)
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("x", VTYPE_Number);
			pDeclCallable->DeclareArg("y", VTYPE_Number);
			pDeclCallable->DeclareArg("width", VTYPE_Number);
			pDeclCallable->DeclareArg("height", VTYPE_Number);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		wxCoord x = args.PickNumber<wxCoord>();
		wxCoord y = args.PickNumber<wxCoord>();
		wxCoord width = args.PickNumber<wxCoord>();
		wxCoord height = args.PickNumber<wxCoord>();
		return new Value_wxRegion(wxRegion(x, y, width, height));
	} while (0);
	Error::ClearIssuedFlag();
	// wx.Region(topLeft as const_Point_r, bottomRight as const_Point_r)
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("topLeft", VTYPE_wxPoint);
			pDeclCallable->DeclareArg("bottomRight", VTYPE_wxPoint);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		const wxPoint& topLeft = args.Pick<Value_wxPoint>().GetEntity();
		const wxPoint& bottomRight = args.Pick<Value_wxPoint>().GetEntity();
		return new Value_wxRegion(wxRegion(topLeft, bottomRight));
	} while (0);
	Error::ClearIssuedFlag();
	// wx.Region(points[] as const_Point_r, fillStyle as PolygonFillMode)
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("points", VTYPE_wxPoint, DeclArg::Occur::Once, DeclArg::Flag::ListVar);
			pDeclCallable->DeclareArg("fillStyle", VTYPE_Number);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		const ValueList& values = args.PickList();
		std::unique_ptr<wxPoint> points(new wxPoint[values.size()]);
		size_t i = 0;
		for (const Value* pValue : values) points.get()[i++] = Value_wxPoint::GetEntity(*pValue);
		wxPolygonFillMode fillStyle = args.PickNumber<wxPolygonFillMode>();
		return new Value_wxRegion(wxRegion(values.size(), points.get(), fillStyle));
		} while (0);
	Error::ClearIssuedFlag();
	// wx.Region(rect as const_Rect_r)
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
		return new Value_wxRegion(wxRegion(rect));
	} while (0);
	Error::ClearIssuedFlag();
	// wx.Region(bmp as const_Bitmap_r)
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("bmp", VTYPE_wxBitmap);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		const wxBitmap& bmp = args.Pick<Value_wxBitmap>().GetEntity();
		return new Value_wxRegion(wxRegion(bmp));
	} while (0);
	Error::ClearIssuedFlag();
	// wx.Region(bmp as const_Bitmap_r, transColour as const_Colour_r, tolerance as int = 0)
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("bmp", VTYPE_wxBitmap);
			pDeclCallable->DeclareArg("transColour", VTYPE_wxColour);
			pDeclCallable->DeclareArg("tolerance", VTYPE_Number);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		const wxBitmap& bmp = args.Pick<Value_wxBitmap>().GetEntity();
		const wxColour& transColour = args.Pick<Value_wxColour>().GetEntity();
		int tolerance = args.PickNumber<int>();
		return new Value_wxRegion(wxRegion(bmp, transColour, tolerance));
	} while (0);
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.Region#Clear()
Gurax_DeclareMethodAlias(wxRegion, Clear_gurax, "Clear")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRegion, Clear_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Clear();
	return Gurax::Value::nil();
}

// wx.Region#Contains(args* as Any)
Gurax_DeclareMethodAlias(wxRegion, Contains_gurax, "Contains")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRegion, Contains_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Gurax::ValueList& args = args_gurax.PickList();
	// Function body
	// Contains(x as Coord, y as Coord) as RegionContain
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
		wxCoord x = args.PickNumber<wxCoord>();
		wxCoord y = args.PickNumber<wxCoord>();
		wxRegionContain rtn = pEntity_gurax->Contains(x, y);
		return new Value_Number(rtn);
	} while (0);
	Error::ClearIssuedFlag();
	// Contains(pt as const_Point_r) as RegionContain
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
		wxRegionContain rtn = pEntity_gurax->Contains(pt);
		return new Value_Number(rtn);
	} while (0);
	Error::ClearIssuedFlag();
	// Contains(x as Coord, y as Coord, width as Coord, height as Coord) as RegionContain
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("x", VTYPE_Number);
			pDeclCallable->DeclareArg("y", VTYPE_Number);
			pDeclCallable->DeclareArg("width", VTYPE_Number);
			pDeclCallable->DeclareArg("height", VTYPE_Number);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		wxCoord x = args.PickNumber<wxCoord>();
		wxCoord y = args.PickNumber<wxCoord>();
		wxCoord width = args.PickNumber<wxCoord>();
		wxCoord height = args.PickNumber<wxCoord>();
		wxRegionContain rtn = pEntity_gurax->Contains(x, y, width, height);
		return new Value_Number(rtn);
	} while (0);
	Error::ClearIssuedFlag();
	// Contains(rect as const_Rect_r) as RegionContain
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
		wxRegionContain rtn = pEntity_gurax->Contains(rect);
		return new Value_Number(rtn);
	} while (0);
	return Value::nil();
}

// wx.Region#ConvertToBitmap() {block?}
Gurax_DeclareMethodAlias(wxRegion, ConvertToBitmap_gurax, "ConvertToBitmap")
{
	Declare(VTYPE_wxBitmap, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRegion, ConvertToBitmap_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxBitmap(
		pEntity_gurax->ConvertToBitmap()));
}

// wx.Region#Intersect(args* as Any)
Gurax_DeclareMethodAlias(wxRegion, Intersect_gurax, "Intersect")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRegion, Intersect_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Gurax::ValueList& args = args_gurax.PickList();
	// Function body
	// Intersect(x as Coord, y as Coord, width as Coord, height as Coord) as bool
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("x", VTYPE_Number);
			pDeclCallable->DeclareArg("y", VTYPE_Number);
			pDeclCallable->DeclareArg("width", VTYPE_Number);
			pDeclCallable->DeclareArg("height", VTYPE_Number);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		wxCoord x = args.PickNumber<wxCoord>();
		wxCoord y = args.PickNumber<wxCoord>();
		wxCoord width = args.PickNumber<wxCoord>();
		wxCoord height = args.PickNumber<wxCoord>();
		bool rtn = pEntity_gurax->Intersect(x, y, width, height);
		return new Value_Bool(rtn);
	} while (0);
	Error::ClearIssuedFlag();
	// Intersect(rect as const_Rect_r) as bool
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
		bool rtn = pEntity_gurax->Intersect(rect);
		return new Value_Bool(rtn);
	} while (0);
	Error::ClearIssuedFlag();
	// Intersect(region as const_Region_r) as bool
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("region", VTYPE_wxRegion);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		const wxRegion& region = args.Pick<Value_wxRegion>().GetEntity();
		bool rtn = pEntity_gurax->Intersect(region);
		return new Value_Bool(rtn);
	} while (0);
	return Value::nil();
}

// wx.Region#IsEmpty()
Gurax_DeclareMethodAlias(wxRegion, IsEmpty_gurax, "IsEmpty")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRegion, IsEmpty_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsEmpty();
	return new Gurax::Value_Bool(rtn);
}

// wx.Region#IsEqual(region as wx.Region)
Gurax_DeclareMethodAlias(wxRegion, IsEqual_gurax, "IsEqual")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("region", VTYPE_wxRegion, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRegion, IsEqual_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRegion& value_region = args_gurax.Pick<Value_wxRegion>();
	const wxRegion& region = value_region.GetEntity();
	// Function body
	bool rtn = pEntity_gurax->IsEqual(region);
	return new Gurax::Value_Bool(rtn);
}

// wx.Region#Subtract(args* as Any)
Gurax_DeclareMethodAlias(wxRegion, Subtract_gurax, "Subtract")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRegion, Subtract_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Gurax::ValueList& args = args_gurax.PickList();
	// Function body
	// Subtract(rect as const_Rect_r) as bool
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
		bool rtn = pEntity_gurax->Subtract(rect);
		return new Value_Bool(rtn);
	} while (0);
	Error::ClearIssuedFlag();
	// Subtract(region as const_Region_r) as bool
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("region", VTYPE_wxRegion);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		const wxRegion& region = args.Pick<Value_wxRegion>().GetEntity();
		bool rtn = pEntity_gurax->Subtract(region);
		return new Value_Bool(rtn);
	} while (0);
	return Value::nil();
}

// wx.Region#Union(args* as Any)
Gurax_DeclareMethodAlias(wxRegion, Union_gurax, "Union")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRegion, Union_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Gurax::ValueList& args = args_gurax.PickList();
	// Function body
	// Union(x as Coord, y as Coord, width as Coord, height as Coord) as bool
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("x", VTYPE_Number);
			pDeclCallable->DeclareArg("y", VTYPE_Number);
			pDeclCallable->DeclareArg("width", VTYPE_Number);
			pDeclCallable->DeclareArg("height", VTYPE_Number);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		wxCoord x = args.PickNumber<wxCoord>();
		wxCoord y = args.PickNumber<wxCoord>();
		wxCoord width = args.PickNumber<wxCoord>();
		wxCoord height = args.PickNumber<wxCoord>();
		bool rtn = pEntity_gurax->Union(x, y, width, height);
		return new Value_Bool(rtn);
	} while (0);
	Error::ClearIssuedFlag();
	// Union(rect as const_Rect_r) as bool
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
		bool rtn = pEntity_gurax->Union(rect);
		return new Value_Bool(rtn);
	} while (0);
	Error::ClearIssuedFlag();
	// Union(region as const_Region_r) as bool
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("region", VTYPE_wxRegion);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		const wxRegion& region = args.Pick<Value_wxRegion>().GetEntity();
		bool rtn = pEntity_gurax->Union(region);
		return new Value_Bool(rtn);
	} while (0);
	Error::ClearIssuedFlag();
	// Union(bmp as const_Bitmap_r) as bool
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("bmp", VTYPE_wxBitmap);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		const wxBitmap& bmp = args.Pick<Value_wxBitmap>().GetEntity();
		bool rtn = pEntity_gurax->Union(bmp);
		return new Value_Bool(rtn);
	} while (0);
	Error::ClearIssuedFlag();
	// Union(bmp as const_Bitmap_r, transColour as const_Colour_r, tolerance as int = 0) as bool
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("bmp", VTYPE_wxBitmap);
			pDeclCallable->DeclareArg("transColour", VTYPE_wxColour);
			pDeclCallable->DeclareArg("tolerance", VTYPE_Number);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		const wxBitmap& bmp = args.Pick<Value_wxBitmap>().GetEntity();
		const wxColour& transColour = args.Pick<Value_wxColour>().GetEntity();
		int tolerance = args.PickNumber<int>();
		bool rtn = pEntity_gurax->Union(bmp, transColour, tolerance);
		return new Value_Bool(rtn);
	} while (0);
	return Value::nil();
}

// wx.Region#Xor(args* as Any)
Gurax_DeclareMethodAlias(wxRegion, Xor_gurax, "Xor")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRegion, Xor_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Gurax::ValueList& args = args_gurax.PickList();
	// Function body
	// Xor(x as Coord, y as Coord, width as Coord, height as Coord) as bool
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("x", VTYPE_Number);
			pDeclCallable->DeclareArg("y", VTYPE_Number);
			pDeclCallable->DeclareArg("width", VTYPE_Number);
			pDeclCallable->DeclareArg("height", VTYPE_Number);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		wxCoord x = args.PickNumber<wxCoord>();
		wxCoord y = args.PickNumber<wxCoord>();
		wxCoord width = args.PickNumber<wxCoord>();
		wxCoord height = args.PickNumber<wxCoord>();
		bool rtn = pEntity_gurax->Xor(x, y, width, height);
		return new Value_Bool(rtn);
	} while (0);
	Error::ClearIssuedFlag();
	// Xor(rect as const_Rect_r) as bool
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
		bool rtn = pEntity_gurax->Xor(rect);
		return new Value_Bool(rtn);
	} while (0);
	Error::ClearIssuedFlag();
	// Xor(region as const_Region_r) as bool
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("region", VTYPE_wxRegion);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		const wxRegion& region = args.Pick<Value_wxRegion>().GetEntity();
		bool rtn = pEntity_gurax->Xor(region);
		return new Value_Bool(rtn);
	} while (0);
	return Value::nil();
}

// wx.Region#GetBoxXYWH()
Gurax_DeclareMethodAlias(wxRegion, GetBoxXYWH_gurax, "GetBoxXYWH")
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRegion, GetBoxXYWH_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxCoord x, y, width, height;
	pEntity_gurax->GetBox(x, y, width, height);
	return Value_Tuple::Create(new Value_Number(x), new Value_Number(y), new Value_Number(width), new Value_Number(height));
}

// wx.Region#GetBoxRect() {block?}
Gurax_DeclareMethodAlias(wxRegion, GetBoxRect_gurax, "GetBoxRect")
{
	Declare(VTYPE_wxRect, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRegion, GetBoxRect_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRect(
		pEntity_gurax->GetBox()));
}

// wx.Region#Offset(args* as Any)
Gurax_DeclareMethodAlias(wxRegion, Offset_gurax, "Offset")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRegion, Offset_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Gurax::ValueList& args = args_gurax.PickList();
	// Function body
	// Offset(x as Coord, y as Coord) as bool
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
		wxCoord x = args.PickNumber<wxCoord>();
		wxCoord y = args.PickNumber<wxCoord>();
		bool rtn = pEntity_gurax->Offset(x, y);
		return new Value_Bool(rtn);
	} while (0);
	Error::ClearIssuedFlag();
	// Offset(pt as const_Point_r) as bool
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
		bool rtn = pEntity_gurax->Offset(pt);
		return new Value_Bool(rtn);
	} while (0);
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxRegion
//------------------------------------------------------------------------------
VType_wxRegion VTYPE_wxRegion("Region");

void VType_wxRegion::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxGDIObject, Flag::Mutable, Gurax_CreateConstructor(Region_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxRegion, Clear_gurax));
	Assign(Gurax_CreateMethod(wxRegion, Contains_gurax));
	Assign(Gurax_CreateMethod(wxRegion, ConvertToBitmap_gurax));
	Assign(Gurax_CreateMethod(wxRegion, Intersect_gurax));
	Assign(Gurax_CreateMethod(wxRegion, IsEmpty_gurax));
	Assign(Gurax_CreateMethod(wxRegion, IsEqual_gurax));
	Assign(Gurax_CreateMethod(wxRegion, Subtract_gurax));
	Assign(Gurax_CreateMethod(wxRegion, Union_gurax));
	Assign(Gurax_CreateMethod(wxRegion, Xor_gurax));
	Assign(Gurax_CreateMethod(wxRegion, GetBoxXYWH_gurax));
	Assign(Gurax_CreateMethod(wxRegion, GetBoxRect_gurax));
	Assign(Gurax_CreateMethod(wxRegion, Offset_gurax));
}

//------------------------------------------------------------------------------
// Value_wxRegion
//------------------------------------------------------------------------------
VType& Value_wxRegion::vtype = VTYPE_wxRegion;

String Value_wxRegion::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Region");
}

Gurax_EndModuleScope(wx)
