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

String Text::Textize() const
{
	return String::EscapeHTML(GetText(), false);
}

bool Text::Compose(Stream& stream) const
{
	stream.Print(Textize());
	return !Error::IsIssued();
}

Value* Text::CreateValue() const
{
	return new Value_Text(Reference());
}

String Text::ToString(const StringStyle& ss) const
{
	return String().Format("xml.Text:%s", String::Enquote(GetText(), '\'').c_str());
}

Gurax_EndModuleScope(xml)
