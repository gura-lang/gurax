//==============================================================================
// VType_Palette.cpp
//==============================================================================
#include "stdafx.h"
#include <gurax/VType_Palette.h>

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
// Implementation of class method
//------------------------------------------------------------------------------
// Palette.Basic()
Gurax_DeclareClassMethod(Palette, Basic)
{
	Declare(VTYPE_Palette, Flag::None);
}

Gurax_ImplementClassMethod(Palette, Basic)
{
	// Function body
	return new Value_Palette(Palette::Basic());
}

// Palette.WebSafe()
Gurax_DeclareClassMethod(Palette, WebSafe)
{
	Declare(VTYPE_Palette, Flag::None);
}

Gurax_ImplementClassMethod(Palette, WebSafe)
{
	// Function body
	return new Value_Palette(Palette::WebSafe());
}

// Palette.Win256()
Gurax_DeclareClassMethod(Palette, Win256)
{
	Declare(VTYPE_Palette, Flag::None);
}

Gurax_ImplementClassMethod(Palette, Win256)
{
	// Function body
	return new Value_Palette(Palette::Win256());
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
#if 0
	Object_palette *pThis = Object_palette::GetObjectThis(arg);
	Iterator *pIterator = new Palette::IteratorEach(Palette::Reference(pThis->GetPalette()));
	return ReturnIterator(env, arg, pIterator);
#endif
	return Value::nil();
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

#if 0
// Palette#UpdateBy(image_or_palette):reduce:[shrink,align]
Gurax_DeclareMethod(palette, updateby)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Reduce, FLAG_None);
	DeclareArg(env, "image_or_palette", VTYPE_any);
	DeclareAttr(Gurax_Symbol(shrink));
	DeclareAttr(Gurax_Symbol(align));
	AddHelp(
		Gurax_Symbol(en), 
		"Updates palette entries according to color data in an image or a palette.\n"
		"\n"
		"The order of existing entries will be kept intact. If attribute shrink is\n"
		"specified, the whole size will be shrinked to a number powered by two that\n"
		"is enough to contain unique entries.");
}

Gurax_ImplementMethod(palette, updateby)
{
	Signal &sig = env.GetSignal();
	Object_palette *pThis = Object_palette::GetObjectThis(arg);
	Palette::ShrinkMode shrinkMode = Palette::ShrinkNone;
	if (arg.IsSet(Gurax_Symbol(shrink))) {
		shrinkMode = arg.IsSet(Gurax_Symbol(align))?
					Palette::ShrinkAlign : Palette::ShrinkMinimum;
	}
	if (arg.Is_image(0)) {
		if (!pThis->GetPalette()->UpdateByImage(sig,
				Object_image::GetObject(arg, 0)->GetImage(), shrinkMode)) {
			return Value::Nil;
		}
	} else if (arg.Is_palette(0)) {
		if (!pThis->GetPalette()->UpdateByPalette(sig,
				Object_palette::GetObject(arg, 0)->GetPalette(), shrinkMode)) {
			return Value::Nil;
		}
	} else {
		sig.SetError(ERR_ValueError, "image or palette must be specified");
		return Value::Nil;
	}
	return arg.GetValueThis();
}
#endif

//------------------------------------------------------------------------------
// VType_Palette
//------------------------------------------------------------------------------
VType_Palette VTYPE_Palette("Palette");

void VType_Palette::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of class method
	Assign(Gurax_CreateClassMethod(Palette, Basic));
	Assign(Gurax_CreateClassMethod(Palette, WebSafe));
	Assign(Gurax_CreateClassMethod(Palette, Win256));
	// Assignment of method
	Assign(Gurax_CreateMethod(Palette, Each));
	Assign(Gurax_CreateMethod(Palette, GetNearest));
	Assign(Gurax_CreateMethod(Palette, Shrink));
}

//------------------------------------------------------------------------------
// Value_Palette
//------------------------------------------------------------------------------
VType& Value_Palette::vtype = VTYPE_Palette;

}
