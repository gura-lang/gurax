//==============================================================================
// VType_wxGraphicsObject.cpp
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

${help.ComposePropertyHelp(wx.GraphicsObject, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.GraphicsObject, `en)}

${help.ComposeMethodHelp(wx.GraphicsObject, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.GraphicsObject#GetRenderer() {block?}
Gurax_DeclareMethodAlias(wxGraphicsObject, GetRenderer_gurax, "GetRenderer")
{
	Declare(VTYPE_wxGraphicsRenderer, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxGraphicsObject, GetRenderer_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxGraphicsRenderer(
		pEntity_gurax->GetRenderer()));
}

// wx.GraphicsObject#IsNull()
Gurax_DeclareMethodAlias(wxGraphicsObject, IsNull_gurax, "IsNull")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxGraphicsObject, IsNull_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsNull();
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxGraphicsObject
//------------------------------------------------------------------------------
VType_wxGraphicsObject VTYPE_wxGraphicsObject("GraphicsObject");

void VType_wxGraphicsObject::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxObject, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxGraphicsObject, GetRenderer_gurax));
	Assign(Gurax_CreateMethod(wxGraphicsObject, IsNull_gurax));
}

//------------------------------------------------------------------------------
// Value_wxGraphicsObject
//------------------------------------------------------------------------------
VType& Value_wxGraphicsObject::vtype = VTYPE_wxGraphicsObject;

String Value_wxGraphicsObject::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GraphicsObject");
}

Gurax_EndModuleScope(wx)
