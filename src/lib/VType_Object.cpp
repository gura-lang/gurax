//==============================================================================
// VType_Object.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// Object#Clone()
Gurax_DeclareMethod(Object, Clone)
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(
		Gurax_Symbol(en), 
		"Creates a cloned object.\n");
}

Gurax_ImplementMethod(Object, Clone)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	RefPtr<Value> pValue(valueThis.Clone());
	if (pValue) return pValue.release();
	Error::Issue(ErrorType::ValueError, "failed to create a cloned object");
	return Value::nil();
}

// Object#IsInstanceOf(vtype:VType)
Gurax_DeclareMethod(Object, IsInstanceOf)
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("vtype", VTYPE_VType, ArgOccur::Once, ArgFlag::None);
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
	const VType& vtype = args.Pick<Value_VType>().GetVTypeThis();
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
// Implementation of property
//------------------------------------------------------------------------------
// Object#vtype
Gurax_DeclareProperty_R(Object, vtype)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The number of characters in the string.");
}

Gurax_ImplementPropertyGetter(Object, vtype)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_VType(valueThis.GetVType());
}

//------------------------------------------------------------------------------
// VType_Object
//------------------------------------------------------------------------------
VType_Object VTYPE_Object("Object");

void VType_Object::DoPrepare(Frame& frameOuter)
{
	// Declaration of VType
	Declare(VType::Empty, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Object, Clone));
	Assign(Gurax_CreateMethod(Object, IsInstanceOf));
	Assign(Gurax_CreateMethod(Object, ToString));
	// Assignment of property
	Assign(Gurax_CreateProperty(Object, vtype));
}

//------------------------------------------------------------------------------
// Value_Object
//------------------------------------------------------------------------------
VType& Value_Object::vtype = VTYPE_Object;

}
