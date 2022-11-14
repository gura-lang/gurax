//==============================================================================
// VType_Exif.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(jpeg.jpeg.Exif, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(jpeg.jpeg.Exif, `en)}

${help.ComposeMethodHelp(jpeg.jpeg.Exif, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// jpeg.Exif() {block?}
Gurax_DeclareConstructor(Exif)
{
	Declare(VTYPE_Content, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(
Creates a `jpeg.Exif` instance.
)**");
}

Gurax_ImplementConstructor(Exif)
{
	// Arguments
	ArgPicker args(argument);
	// Function body
	RefPtr<Exif> pExif(new Exif());
	return argument.ReturnValue(processor, new Value_Exif(pExif.release()));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// jpeg.Exif#ifd0
Gurax_DeclareProperty_RW(Exif, ifd0)
{
	Declare(VTYPE_IFD, Flag::None);
	AddHelp("en", u8R"**(
IFD0 field in the Exif. Returns `nil` if not exist.
)**");
}

Gurax_ImplementPropertyGetter(Exif, ifd0)
{
	auto& valueThis = GetValueThis(valueTarget);
	const IFD* pIFD = valueThis.GetExif().GetIFD0();
	if (!pIFD) return Value::nil();
	return new Value_IFD(pIFD->Reference());
}

Gurax_ImplementPropertySetter(Exif, ifd0)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetExif().SetIFD0(Value_IFD::GetIFD(value).Reference());
}

// jpeg.Exif#ifd1
Gurax_DeclareProperty_RW(Exif, ifd1)
{
	Declare(VTYPE_IFD, Flag::None);
	AddHelp("en", u8R"**(
IFD1 field in the Exif. Returns `nil` if not exist.
)**");
}

Gurax_ImplementPropertyGetter(Exif, ifd1)
{
	auto& valueThis = GetValueThis(valueTarget);
	const IFD* pIFD = valueThis.GetExif().GetIFD1();
	if (!pIFD) return Value::nil();
	return new Value_IFD(pIFD->Reference());
}

Gurax_ImplementPropertySetter(Exif, ifd1)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetExif().SetIFD1(Value_IFD::GetIFD(value).Reference());
}

//------------------------------------------------------------------------------
// VType_Exif
//------------------------------------------------------------------------------
VType_Exif VTYPE_Exif("Exif");

void VType_Exif::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Segment, Flag::Immutable, Gurax_CreateConstructor(Exif));
	// Assignment of property
	Assign(Gurax_CreateProperty(Exif, ifd0));
	Assign(Gurax_CreateProperty(Exif, ifd1));
}

//------------------------------------------------------------------------------
// Value_Exif
//------------------------------------------------------------------------------
VType& Value_Exif::vtype = VTYPE_Exif;

String Value_Exif::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetExif().ToString(ss));
}

Gurax_EndModuleScope(jpeg)
