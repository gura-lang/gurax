//==============================================================================
// VType_CData.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(xml.CData, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(xml.CData, `en)}

${help.ComposeMethodHelp(xml.CData, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// xml.CData() {block?}
Gurax_DeclareConstructor(CData)
{
	Declare(VTYPE_CData, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `xml.CData` instance.
)""");
}

Gurax_ImplementConstructor(CData)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<CData> pCData(new CData());
	return argument.ReturnValue(processor, new Value_CData(pCData.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// xml.CData#Textize()
Gurax_DeclareMethod(CData, Textize)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(CData, Textize)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return new Value_String(valueThis.GetCData().Textize());
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// xml.CData#propSkeleton
Gurax_DeclareProperty_R(CData, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(CData, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_CData
//------------------------------------------------------------------------------
VType_CData VTYPE_CData("CData");

void VType_CData::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Node, Flag::Immutable, Gurax_CreateConstructor(CData));
	// Assignment of method
	Assign(Gurax_CreateMethod(CData, Textize));
	// Assignment of property
	Assign(Gurax_CreateProperty(CData, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_CData
//------------------------------------------------------------------------------
VType& Value_CData::vtype = VTYPE_CData;

String Value_CData::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetCData().ToString(ss));
}

Gurax_EndModuleScope(xml)
