//==============================================================================
// VType_Segment.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(jpeg.Segment, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(jpeg.Segment, `en)}

${help.ComposeMethodHelp(jpeg.Segment, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// jpeg.Segment#IsExif()
Gurax_DeclareMethod(Segment, IsExif)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Returns `true` if the segment is an Exif.
)**");
}

Gurax_ImplementMethod(Segment, IsExif)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return new Value_Bool(valueThis.GetSegment().IsExif());
}

// jpeg.Segment#IsJFIF()
Gurax_DeclareMethod(Segment, IsJFIF)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Returns `true` if the segment is an JFIF.
)**");
}

Gurax_ImplementMethod(Segment, IsJFIF)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return new Value_Bool(valueThis.GetSegment().IsJFIF());
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// jpeg.Segment#marker
Gurax_DeclareProperty_R(Segment, marker)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Segment, marker)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetSegment().GetMarker());
}

// jpeg.Segment#markerName
Gurax_DeclareProperty_R(Segment, markerName)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Segment, markerName)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetSegment().GetMarkerSymbol()->GetName());
}

// jpeg.Segment#markerSymbol
Gurax_DeclareProperty_R(Segment, markerSymbol)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Segment, markerSymbol)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Symbol(valueThis.GetSegment().GetMarkerSymbol());
}

// jpeg.Segment#parameter
Gurax_DeclareProperty_R(Segment, parameter)
{
	Declare(VTYPE_Pointer, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Segment, parameter)
{
	auto& valueThis = GetValueThis(valueTarget);
	const BinaryReferable* pBuff = valueThis.GetSegment().GetBinaryReferable();
	if (!pBuff) return Value::nil();
	RefPtr<Pointer> pPointer(new Pointer_Binary(pBuff->Reference()));
	return new Value_Pointer(pPointer.release());
}

//------------------------------------------------------------------------------
// VType_Segment
//------------------------------------------------------------------------------
VType_Segment VTYPE_Segment("Segment");

void VType_Segment::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Segment, IsExif));
	Assign(Gurax_CreateMethod(Segment, IsJFIF));
	// Assignment of property
	Assign(Gurax_CreateProperty(Segment, marker));
	Assign(Gurax_CreateProperty(Segment, markerName));
	Assign(Gurax_CreateProperty(Segment, markerSymbol));
	Assign(Gurax_CreateProperty(Segment, parameter));
}

//-----------------------------------------------------------------------------
// VType_Segment::Iterator_Each
//-----------------------------------------------------------------------------
Value* VType_Segment::Iterator_Each::DoNextValue()
{
	if (_idx >= GetSegmentOwner().size()) return nullptr;
	RefPtr<Segment> pSegment(GetSegmentOwner()[_idx]->Reference());
	_idx++;
	return pSegment->CreateValue();
}
	
String VType_Segment::Iterator_Each::ToString(const StringStyle& ss) const
{
	return "Segment.Each";
}

//------------------------------------------------------------------------------
// Value_Segment
//------------------------------------------------------------------------------
VType& Value_Segment::vtype = VTYPE_Segment;

String Value_Segment::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetSegment().ToString(ss));
}

Gurax_EndModuleScope(jpeg)
