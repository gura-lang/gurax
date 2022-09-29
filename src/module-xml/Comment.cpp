//==============================================================================
// Comment.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// Comment
//------------------------------------------------------------------------------
Comment::Comment(String data) : Node(Type::Comment), _data(data) {}

String Comment::ToString(const StringStyle& ss) const
{
	return String().Format("xml.Comment");
}

Gurax_EndModuleScope(xml)
