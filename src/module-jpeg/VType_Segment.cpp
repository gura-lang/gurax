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

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// jpeg.Segment#marker
Gurax_DeclareProperty_R(Segment, marker)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(string));
	DeclareAttrOpt(Gurax_Symbol(symbol));
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Segment, marker)
{
	auto& valueThis = GetValueThis(valueTarget);
	if (attr.IsSet(Gurax_Symbol(symbol))) {
		return new Value_Symbol(valueThis.GetSegment().GetMarkerSymbol());
	} else if (attr.IsSet(Gurax_Symbol(symbol))) {
		
	}
	return new Value_Number(valueThis.GetSegment().GetMarker());
}

// jpeg.Segment#parameter
Gurax_DeclareProperty_R(Segment, parameter)
{
	Declare(VTYPE_Pointer, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Segment, parameter)
{
	auto& valueThis = GetValueThis(valueTarget);
	RefPtr<Pointer> pPointer(new Pointer_Binary(valueThis.GetSegment().GetBinaryReferable().Reference()));
	return new Value_Pointer(pPointer.release());
}

//------------------------------------------------------------------------------
// VType_Segment
//------------------------------------------------------------------------------
VType_Segment VTYPE_Segment("Segment");

void VType_Segment::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(Segment, marker));
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
	return new Value_Segment(pSegment.release());
}
	
String VType_Segment::Iterator_Each::ToString(const StringStyle& ss) const
{
	return "Segment.Each";
}

//------------------------------------------------------------------------------
// Value_Segment
//------------------------------------------------------------------------------
VType& Value_Segment::vtype = VTYPE_Segment;

Gurax_EndModuleScope(jpeg)
