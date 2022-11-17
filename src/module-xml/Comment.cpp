//==============================================================================
// Comment.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// Comment
//------------------------------------------------------------------------------
Comment::Comment(String data) : Node(Type::Comment), _data(data) {}

bool Comment::Compose(Stream& stream) const
{
	stream.Print("<--");
	stream.Print(String::EscapeHTML(GetData(), false).c_str());
	stream.Print("-->");
	return !Error::IsIssued();
}

String Comment::Textize() const
{
	String str;
	str += "<--";
	str += _data;
	str += "-->";
	return str;
}

Value* Comment::CreateValue() const
{
	return new Value_Comment(Reference());
}

String Comment::ToString(const StringStyle& ss) const
{
	return String().Format("xml.Comment:%s", String::Enquote(GetData(), '\'').c_str());
}

Gurax_EndModuleScope(xml)
