//==============================================================================
// Comment.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// Comment
//------------------------------------------------------------------------------
Comment::Comment(String data) : Node(Type::Comment), _data(data) {}

Value* Comment::CreateValue() const
{
	return new Value_Comment(Reference());
}

String Comment::ToString(const StringStyle& ss) const
{
	return String().Format("xml.Comment");
}

Gurax_EndModuleScope(xml)
