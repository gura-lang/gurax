//==============================================================================
// VType_Stream.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// Stream#Println(objs*):void
Gurax_DeclareMethod(Stream, Println)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("values", VTYPE_Any, DeclArg::Occur::ZeroOrMore, DeclArg::Flag::None, nullptr);
}

Gurax_ImplementMethod(Stream, Println)
{
	auto& valueThis = GetValueThis(argument);
	Stream& stream = valueThis.GetStream();
	// Arguments
	ArgPicker args(argument);
	const ValueList& values = args.PickList();
	// Function body
	stream.Println(values);
	return Value::nil();
}

//------------------------------------------------------------------------------
// VType_Stream
//------------------------------------------------------------------------------
VType_Stream VTYPE_Stream("Stream");

void VType_Stream::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	frameOuter.Assign(*this);
	// Assignment of method
	Assign(Gurax_CreateMethod(Stream, Println));
}

//------------------------------------------------------------------------------
// Value_Stream
//------------------------------------------------------------------------------

}
