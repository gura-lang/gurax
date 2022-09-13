//==============================================================================
// VType_Object.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Object() {block?}
Gurax_DeclareConstructor(Object)
{
	Declare(VTYPE_Color, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an `Object` instance.\n");
}

Gurax_ImplementConstructor(Object)
{
	// Function body
	return argument.ReturnValue(processor, new Value_Object());
}

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// Object##__prop__(symbol:Symbol):map {block?}
Gurax_DeclareHybridMethod(Object, __prop__)
{
	Declare(VTYPE_Bool, Flag::Map);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Returns the value of the specified property.\n");
}

Gurax_ImplementHybridMethod(Object, __prop__)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const Symbol* pSymbol = args.PickSymbol();
	// Function body
	RefPtr<Value> pValue(valueThis.DoGetProperty(pSymbol, argument.GetAttr(), false));
	if (!pValue) return Value::nil();
	return argument.ReturnValue(processor, pValue.release());
}

// Object#__str__()
Gurax_DeclareClassMethod(Object, __str__)
{
	Declare(VTYPE_String, Flag::None);
	StringStyle::DeclareAttrOpt(*this);
	AddHelp(
		Gurax_Symbol(en), 
		"Converts the object to a string.\n");
}

Gurax_ImplementClassMethod(Object, __str__)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Argument
	StringStyle::Flags flags = StringStyle::ToFlags(argument);
	// Function body
	return new Value_String(valueThis.ToString(StringStyle(flags)));
}

// Object#__clone__()
Gurax_DeclareMethod(Object, __clone__)
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(
		Gurax_Symbol(en), 
		"Creates a cloned object.\n");
}

Gurax_ImplementMethod(Object, __clone__)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	RefPtr<Value> pValue(valueThis.Clone());
	if (pValue) return pValue.release();
	Error::Issue(ErrorType::ValueError, "failed to create a cloned object");
	return Value::nil();
}

// Object#__instanceOf__(vtype:VType)
Gurax_DeclareMethod(Object, __instanceOf__)
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("vtype", VTYPE_VType, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en), 
		"Returns `true` if the object is an instance of the specified `vtype`.\n");
}

Gurax_ImplementMethod(Object, __instanceOf__)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const VType& vtype = args.Pick<Value_VType>().GetVTypeThis();
	// Function body
	return new Value_Bool(valueThis.IsInstanceOf(vtype));
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// Object##__id__
Gurax_DeclareHybridProperty_R(Object, __id__)
{
	Declare(VTYPE_VType, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The object ID.");
}

Gurax_ImplementHybridPropertyGetter(Object, __id__)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(String().Format("#%p", &valueThis));
}

// Object##__vtype__
Gurax_DeclareHybridProperty_R(Object, __vtype__)
{
	Declare(VTYPE_VType, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The value type of this object.");
}

Gurax_ImplementHybridPropertyGetter(Object, __vtype__)
{
	auto& valueThis = GetValueThis(valueTarget);
	VType& vtype = valueThis.IsType(VTYPE_VType)?
				Value_VType::GetVTypeThis(valueThis) : valueThis.GetVTypeCustom();
	return new Value_VType(vtype);
}

// Object##__vtypeInh__
Gurax_DeclareHybridProperty_R(Object, __vtypeInh__)
{
	Declare(VTYPE_VType, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The value type of this object's parent class.");
}

Gurax_ImplementHybridPropertyGetter(Object, __vtypeInh__)
{
	auto& valueThis = GetValueThis(valueTarget);
	VType& vtype = valueThis.IsType(VTYPE_VType)?
				Value_VType::GetVTypeThis(valueThis) : valueThis.GetVTypeCustom();
	VType& vtypeInh = vtype.GetVTypeInh();
	if (vtypeInh.IsInvalid()) return Value::nil();
	return new Value_VType(vtypeInh);
}

//------------------------------------------------------------------------------
// VType_Object
//------------------------------------------------------------------------------
VType_Object VTYPE_Object("Object");

void VType_Object::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VType::Invalid, Flag::Immutable, Gurax_CreateConstructor(Object));
	// Assignment of method
	Assign(Gurax_CreateMethod(Object, __prop__));
	Assign(Gurax_CreateMethod(Object, __str__));
	Assign(Gurax_CreateMethod(Object, __clone__));
	Assign(Gurax_CreateMethod(Object, __instanceOf__));
	// Assignment of property
	Assign(Gurax_CreateProperty(Object, __id__));
	Assign(Gurax_CreateProperty(Object, __vtype__));
	Assign(Gurax_CreateProperty(Object, __vtypeInh__));
}

//------------------------------------------------------------------------------
// Value_Object
//------------------------------------------------------------------------------
VType& Value_Object::vtype = VTYPE_Object;

String Value_Object::ToString(const StringStyle& ss) const
{
	return String().Format("<%s>", GetVTypeCustom().MakeFullName().c_str());
}

}
