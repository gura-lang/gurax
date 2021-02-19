//==============================================================================
// VType_Palette.cpp
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

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Palette(symbol:Symbol):map {block?}
Gurax_DeclareConstructor(Palette)
{
	Declare(VTYPE_Expr, Flag::Map);
	DeclareArg("symbol", VTYPE_Stream, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an `Palette` instance with entries designated by the argument `symbol` that takes following value:\n"
		"\n"
		"- `` `basic`` .. 16 basic colors.\n"
		"- `` `mono`` .. 2 colors that are Black and white.\n"
		"- `` `websafe`` .. 215 colors that are safe to be used for Web contents.\n"
		"- `` `win256``.. 256 colors defined by Windows.\n");
}

Gurax_ImplementConstructor(Palette)
{
	// Arguments
	ArgPicker args(argument);
	const Symbol* pSymbol = args.PickSymbol();
	// Function body
	RefPtr<Palette> pPalette;
	if (pSymbol->IsIdentical(Gurax_Symbol(basic))) {
		pPalette.reset(Palette::Basic());
	} else if (pSymbol->IsIdentical(Gurax_Symbol(mono))) {
		pPalette.reset(Palette::Mono());
	} else if (pSymbol->IsIdentical(Gurax_Symbol(websafe))) {
		pPalette.reset(Palette::WebSafe());
	} else if (pSymbol->IsIdentical(Gurax_Symbol(win256))) {
		pPalette.reset(Palette::Win256());
	} else {
		Error::Issue(ErrorType::SymbolError, "invalid symbol for Palette");
		return Value::nil();
	}
	return argument.ReturnValue(processor, new Value_Palette(pPalette.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// Palette#Each() {block?}
Gurax_DeclareMethod(Palette, Each)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en), 
		"Creates an iterator that iterates each element in the palette.\n");
}

Gurax_ImplementMethod(Palette, Each)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Palette& palette = valueThis.GetPalette();
	// Function body
	RefPtr<Iterator> pIterator(new VType_Palette::Iterator_Each(palette.Reference()));
	return argument.ReturnIterator(processor, pIterator.release());
}

// Palette#GetNearest(Color:color):map:[index]
Gurax_DeclareMethod(Palette, GetNearest)
{
	Declare(VTYPE_Color, Flag::None);
	DeclareArg("color", VTYPE_Color, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(index));
	AddHelp(
		Gurax_Symbol(en),
		"Returns a `color` instance in the palette that is the nearest with the specified color.\n"
		"\n"
		"If the attribute `:index` is specified, it would return an index\n"
		"of the nearst entry instead of its `color` instance.\n");
}

Gurax_ImplementMethod(Palette, GetNearest)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Palette& palette = valueThis.GetPalette();
	// Arguments
	ArgPicker args(argument);
	const Color& color = Value_Color::GetColor(args.PickValue());
	bool indexFlag = argument.IsSet(Gurax_Symbol(index));
	// Function body
	size_t idx = palette.LookupNearest(color);
	RefPtr<Value> pValue;
	if (indexFlag) {
		pValue.reset(new Value_Number(idx));
	} else {
		pValue.reset(new Value_Color(palette.GetColor(idx)));
	}
	return argument.ReturnValue(processor, pValue.release());
}

// Palette#Shrink():reduce:[align]
Gurax_DeclareMethod(Palette, Shrink)
{
	Declare(VTYPE_Palette, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(align));
	AddHelp(
		Gurax_Symbol(en), 
		"Shrinks the size of the palette to a number powered by two that is\n"
		"enough to contain unique entries. The ordef of existing entries will\n"
		"be kept intact.\n");
}

Gurax_ImplementMethod(Palette, Shrink)
{
#if 0
	Object_palette *pThis = Object_palette::GetObjectThis(arg);
	pThis->GetPalette()->Shrink(pThis->GetPalette()->NextBlankIndex(), arg.IsSet(Gurax_Symbol(align)));
	return arg.GetValueThis();
#endif
	return Value::nil();
}

// Palette#UpdateBy(image_or_palette):reduce:[shrink,align]
Gurax_DeclareMethod(Palette, UpdateBy)
{
	Declare(VTYPE_Palette, Flag::Reduce);
	DeclareArg("image_or_palette", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(shrink));
	DeclareAttrOpt(Gurax_Symbol(align));
	AddHelp(
		Gurax_Symbol(en), 
		"Updates palette entries according to color data in an image or a palette.\n"
		"\n"
		"The order of existing entries will be kept intact. If attribute shrink is\n"
		"specified, the whole size will be shrinked to a number powered by two that\n"
		"is enough to contain unique entries.");
}

Gurax_ImplementMethod(Palette, UpdateBy)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Palette& palette = valueThis.GetPalette();
	// Arguments
	ArgPicker args(argument);
	Value& value = args.PickValue();
	Palette::ShrinkMode shrinkMode =
		argument.IsSet(Gurax_Symbol(shrink))?
			(argument.IsSet(Gurax_Symbol(align))?
				Palette::ShrinkMode::Align : Palette::ShrinkMode::Minimum) :
		Palette::ShrinkMode::None;
	bool rtn = true;
	if (value.IsType(VTYPE_Image)) {
		rtn = palette.UpdateByImage(Value_Image::GetImage(value), shrinkMode);
	} else if (value.IsType(VTYPE_Palette)) {
		rtn = palette.UpdateByPalette(Value_Palette::GetPalette(value), shrinkMode);
	} else {
		Error::Issue(ErrorType::ValueError, "Image or Palette must be specified");
		return Value::nil();
	}
	if (!rtn) {
		Error::Issue(ErrorType::RangeError, "failed to update the palette");
		return Value::nil();
	}
	return valueThis.Reference();
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// Palette#len
Gurax_DeclareProperty_R(Palette, len)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The number of elements in the palette.");
}

Gurax_ImplementPropertyGetter(Palette, len)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetPalette().GetSize());
}

//------------------------------------------------------------------------------
// VType_Palette
//------------------------------------------------------------------------------
VType_Palette VTYPE_Palette("Palette");

void VType_Palette::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Palette));
	// Assignment of method
	Assign(Gurax_CreateMethod(Palette, Each));
	Assign(Gurax_CreateMethod(Palette, GetNearest));
	Assign(Gurax_CreateMethod(Palette, Shrink));
	Assign(Gurax_CreateMethod(Palette, UpdateBy));
	// Assignment of property
	Assign(Gurax_CreateProperty(Palette, len));
}

//------------------------------------------------------------------------------
// VType_Palette::Iterator_Each
//------------------------------------------------------------------------------
Value* VType_Palette::Iterator_Each::DoNextValue()
{
	if (_idx >= _pPalette->GetSize()) return nullptr;
	RefPtr<Value> pValue(new Value_Color(_pPalette->GetColor(_idx)));
	_idx++;
	return pValue.release();
}

String VType_Palette::Iterator_Each::ToString(const StringStyle& ss) const
{
	return "Palette.Each";
}

//------------------------------------------------------------------------------
// Value_Palette
//------------------------------------------------------------------------------
VType& Value_Palette::vtype = VTYPE_Palette;

String Value_Palette::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetPalette().ToString(ss));
}

}
