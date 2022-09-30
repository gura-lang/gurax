//==============================================================================
// Text.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// Text
//------------------------------------------------------------------------------
Text Text::Empty("");

Text::Text(String text) : Node(Type::Text), _text(text) {}

Value* Text::CreateValue() const
{
	return new Value_Text(Reference());
}

String Text::ToString(const StringStyle& ss) const
{
	return String().Format("xml.Text");
}

Gurax_EndModuleScope(xml)
