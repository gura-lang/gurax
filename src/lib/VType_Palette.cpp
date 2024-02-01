//==============================================================================
// VType_Palette.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(Palette, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(Palette, `en)}

${help.ComposeMethodHelp(Palette, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Palette(symbol as Symbol):map {block?}
Gurax_DeclareConstructor(Palette)
{
	Declare(VTYPE_Expr, Flag::Map);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates an `Palette` instance with entries designated by the argument `symbol` that takes following values:

- `` `basic`` .. 16 basic colors.
- `` `mono`` .. 2 colors that are Black and white.
- `` `websafe`` .. 215 colors that are safe to be used for Web contents.
- `` `win256``.. 256 colors defined by Windows.
)""");
}

Gurax_ImplementConstructor(Palette)
{
	// Arguments
	ArgPicker args(argument);
	const Symbol* pSymbol = args.PickSymbol();
	// Function body
	RefPtr<Palette> pPalette(Palette::CreateFromSymbol(pSymbol));
	if (!pPalette) return Value::nil();
	return argument.ReturnValue(processor, new Value_Palette(pPalette.release()));
}

//------------------------------------------------------------------------------
// Implementation of class method
//------------------------------------------------------------------------------
// Palette.Create(n as Number, color? as Color) {block?}
Gurax_DeclareClassMethod(Palette, Create)
{
	Declare(VTYPE_Image, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("color", VTYPE_Color, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates an `Palette` instance filled with the specified color.
If the argument `color` is omitted, it will be filled with black.
)""");
}

Gurax_ImplementClassMethod(Palette, Create)
{
	// Arguments
	ArgPicker args(argument);
	size_t n = args.PickNumberPos<size_t>();
	if (Error::IsIssued()) return Value::nil();
	const Color& color = args.IsValid()? args.PickColor() : Color::black;
	// Function body
	RefPtr<Palette> pPalette(new Palette(n));
	pPalette->Fill(color);
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
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates an iterator that iterates each element in the palette.
)""");
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

// Palette#Fill(color as Color):reduce
Gurax_DeclareMethod(Palette, Fill)
{
	Declare(VTYPE_Palette, Flag::Reduce);
	DeclareArg("color", VTYPE_Color, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Fills the palette with the specified color.
)""");
}

Gurax_ImplementMethod(Palette, Fill)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Palette& palette = valueThis.GetPalette();
	// Arguments
	ArgPicker args(argument);
	const Color& color = args.PickColor();
	// Function body
	palette.Fill(color);
	return valueThis.Reference();
}

// Palette#GetNearest(color as Color):map:[index]
Gurax_DeclareMethod(Palette, GetNearest)
{
	Declare(VTYPE_Color, Flag::None);
	DeclareArg("color", VTYPE_Color, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(index));
	AddHelp(Gurax_Symbol(en), u8R"""(
Returns a `color` instance in the palette that is the nearest with the specified color.

If the attribute `:index` is specified, it would return an index
of the nearst entry instead of its `color` instance.
)""");
}

Gurax_ImplementMethod(Palette, GetNearest)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Palette& palette = valueThis.GetPalette();
	// Arguments
	ArgPicker args(argument);
	const Color& color = args.PickColor();
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
	AddHelp(Gurax_Symbol(en), u8R"""(
Shrinks the size of the palette to a number powered by two that is
enough to contain unique entries. The ordef of existing entries will
be kept intact.
)""");
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

// Palette#UpdateBy(image_or_palette as Any):reduce:[shrink,align]
Gurax_DeclareMethod(Palette, UpdateBy)
{
	Declare(VTYPE_Palette, Flag::Reduce);
	DeclareArg("image_or_palette", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(shrink));
	DeclareAttrOpt(Gurax_Symbol(align));
	AddHelp(Gurax_Symbol(en), u8R"""(
Updates palette entries according to color data in an image or a palette.

The order of existing entries will be kept intact. If attribute shrink is
specified, the whole size will be shrinked to a number powered by two that
is enough to contain unique entries.
)""");
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
	AddHelp(Gurax_Symbol(en), u8R"""(
The number of elements in the palette.
)""");
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
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Palette));
	// Assignment of class method
	Assign(Gurax_CreateClassMethod(Palette, Create));
	// Assignment of method
	Assign(Gurax_CreateMethod(Palette, Each));
	Assign(Gurax_CreateMethod(Palette, Fill));
	Assign(Gurax_CreateMethod(Palette, GetNearest));
	Assign(Gurax_CreateMethod(Palette, Shrink));
	Assign(Gurax_CreateMethod(Palette, UpdateBy));
	// Assignment of property
	Assign(Gurax_CreateProperty(Palette, len));
}

Value* VType_Palette::DoCastFrom(Processor& processor, const Value& value, DeclArg::Flags flags) const
{
	if (value.IsType(VTYPE_Expr)) {
		const Symbol* pSymbol = Value_Expr::GetExpr(value).GetPureSymbol();
		if (!pSymbol) return nullptr;
		RefPtr<Palette> pPalette(Palette::CreateFromSymbol(pSymbol));
		if (!pPalette) return Value::nil();
		return new Value_Palette(pPalette.release());
	}
	return nullptr;
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

bool Value_Palette::DoEmptyIndexGet(Value** ppValue) const
{
	Error::Issue(ErrorType::IndexError, "empty-indexing access is not supported");
	return Value::undefined();
}

bool Value_Palette::DoEmptyIndexSet(RefPtr<Value> pValue)
{
	Error::Issue(ErrorType::IndexError, "empty-indexing access is not supported");
	return false;
}

bool Value_Palette::DoSingleIndexGet(const Value& valueIndex, Value** ppValue) const
{
	const Palette& palette = GetPalette();
	size_t idx = 0;
	if (!Index::GetIndexNumber(valueIndex, palette.GetSize(), &idx)) return false;
	*ppValue = new Value_Color(palette.GetColor(idx));
	return true;
}

bool Value_Palette::DoSingleIndexSet(Processor& processor, const Value& valueIndex, RefPtr<Value> pValue)
{
	RefPtr<Value_Color> pValueCasted(pValue->Cast<Value_Color>(processor));
	if (!pValueCasted) return false;
	const Color& color = pValueCasted->GetColor();
	Palette& palette = GetPalette();
	size_t idx = 0;
	if (!Index::GetIndexNumber(valueIndex, palette.GetSize(), &idx)) return false;
	palette.SetColor(idx, color);
	return true;
}

bool Value_Palette::DoSerialize(Stream& stream) const
{
	return GetPalette().Serialize(stream);
}

Value* VType_Palette::DoDeserialize(Stream& stream) const
{
	RefPtr<Palette> pPalette(Palette::Deserialize(stream));
	return pPalette? new Value_Palette(pPalette.release()) : nullptr;
}

}
