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
// Implementation of method
//------------------------------------------------------------------------------
// Object#__prop__(symbol:Symbol):map {block?}
Gurax_DeclareMethod(Object, __prop__)
{
	Declare(VTYPE_Bool, Flag::Map);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Returns the value of the specified property.\n");
}

Gurax_ImplementMethod(Object, __prop__)
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

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// Object#__id__
Gurax_DeclareProperty_R(Object, __id__)
{
	Declare(VTYPE_VType, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The object ID.");
}

Gurax_ImplementPropertyGetter(Object, __id__)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(String().Format("#%p", &valueThis));
}

// Object#__vtype__
Gurax_DeclareProperty_R(Object, __vtype__)
{
	Declare(VTYPE_VType, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The value type of this object.");
}

Gurax_ImplementPropertyGetter(Object, __vtype__)
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
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VType::Empty, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Object, __prop__));
	Assign(Gurax_CreateMethod(Object, __str__));
	Assign(Gurax_CreateMethod(Object, Clone));
	Assign(Gurax_CreateMethod(Object, IsInstanceOf));
	// Assignment of property
	Assign(Gurax_CreateProperty(Object, __id__));
	Assign(Gurax_CreateProperty(Object, __vtype__));
}

//------------------------------------------------------------------------------
// Value_Object
//------------------------------------------------------------------------------
VType& Value_Object::vtype = VTYPE_Object;

String Value_Object::ToString(const StringStyle& ss) const
{
	return String().Format("<Object>");
}

//------------------------------------------------------------------------------
// Value_Object::CustomPack
//------------------------------------------------------------------------------
Value_Object::CustomPack::CustomPack(VTypeCustom& vtypeCustom, Processor* pProcessor, Value* pValueThis) :
	_vtypeCustom(vtypeCustom), _pProcessor(pProcessor), _pValueThis(pValueThis), _pValuesProp(new ValueOwner())
{
}

Value_Object::CustomPack::~CustomPack()
{
	const Function& funcDestructor = _vtypeCustom.GetDestructor();
	if (!funcDestructor.IsEmpty()) {
		RefPtr<Argument> pArgument(new Argument(funcDestructor));
		pArgument->SetValueThis(_pValueThis->Reference());
		Value::Delete(funcDestructor.Eval(*_pProcessor, *pArgument));
	}
}

bool Value_Object::CustomPack::InitCustomProp()
{
	const ValueOwner& valuesPropInit = _vtypeCustom.GetValuesPropInit();
	_pValuesProp->reserve(valuesPropInit.size());
	for (const Value* pValue : valuesPropInit) {
		RefPtr<Value> pValueCloned = pValue->Clone();
		if (!pValueCloned) {
			Error::Issue(ErrorType::PropertyError, "failed to initialize property");
			return false;
		}
		_pValuesProp->push_back(pValueCloned.release());
	}
	return true;
}

void Value_Object::CustomPack::SetCustomProp(size_t iProp, Value* pValue)
{
	ValueOwner::iterator ppValue = _pValuesProp->begin() + iProp;
	Value::Delete(*ppValue);
	*ppValue = pValue;
}

Value* Value_Object::CustomPack::GetCustomProp(size_t iProp)
{
	return (*_pValuesProp)[iProp]->Reference();
}

}
