//==============================================================================
// VType_Object.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// Object#IsInstanceOf(vtype:VType)
Gurax_DeclareMethod(Object, IsInstanceOf)
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("vtype", VTYPE_VType, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr);
	AddHelp(
		Gurax_Symbol(en), 
		"Returns `true` if the object is an instance of the specified `vtype`.\n");
}

Gurax_ImplementMethod(Object, IsInstanceOf)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const VType& vtype = Value_VType::GetVTypeThis(args.PickValue());
	// Function body
	return new Value_Bool(valueThis.IsInstanceOf(vtype));
}

// Object#ToString()
Gurax_DeclareMethod(Object, ToString)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en), 
		"Converts the object to a string.\n");
}

Gurax_ImplementMethod(Object, ToString)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	if (valueThis.IsInstanceOf(VTYPE_String)) return valueThis.Reference();
	return new Value_String(valueThis.ToString());
}

//------------------------------------------------------------------------------
// VType_Object
//------------------------------------------------------------------------------
VType_Object VTYPE_Object("Object");

void VType_Object::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VType::Empty, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Object, IsInstanceOf));
	Assign(Gurax_CreateMethod(Object, ToString));
}

//------------------------------------------------------------------------------
// Value_Object
//------------------------------------------------------------------------------

}
