//==============================================================================
// VType_IFD.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(jpeg)

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
// jpeg.IFD() {block?}
Gurax_DeclareConstructor(IFD)
{
	Declare(VTYPE_IFD, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `jpeg.IFD` instance.");
}

Gurax_ImplementConstructor(IFD)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	//RefPtr<IFD> pIFD(new IFD());
	//return argument.ReturnValue(processor, new Value_IFD(pIFD.release()));
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// jpeg.IFD#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(IFD, MethodSkeleton)
{
	Declare(VTYPE_List, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(IFD, MethodSkeleton)
{
	// Target
	//auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Double num1 = args.PickNumber<Double>();
	Double num2 = args.PickNumber<Double>();
	// Function body
	return new Value_Number(num1 + num2);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// jpeg.IFD#tags
Gurax_DeclareProperty_R(IFD, tags)
{
	Declare(VTYPE_Iterator, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(IFD, tags)
{
	auto& valueThis = GetValueThis(valueTarget);
	const IFD& ifd = valueThis.GetIFD();
	RefPtr<Iterator> pIterator(new VType_Tag::Iterator_Each(ifd.GetTagOwner().Reference()));
	return new Value_Iterator(pIterator.release());
}

//------------------------------------------------------------------------------
// VType_IFD
//------------------------------------------------------------------------------
VType_IFD VTYPE_IFD("IFD");

void VType_IFD::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(IFD));
	// Assignment of method
	Assign(Gurax_CreateMethod(IFD, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(IFD, tags));
}

//------------------------------------------------------------------------------
// Value_IFD
//------------------------------------------------------------------------------
VType& Value_IFD::vtype = VTYPE_IFD;

Value* Value_IFD::DoPropGet(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag)
{
	Tag* pTag = GetIFD().GetTagMap().Lookup(pSymbol);
	if (pTag) return pTag->GetValue().Reference();
	return Value_Object::DoPropGet(pSymbol, attr, notFoundErrorFlag);
}

bool Value_IFD::DoPropSet(const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr)
{
	Tag* pTag = GetIFD().GetTagMap().Lookup(pSymbol);
	if (pTag) {
		if (!pTag->CheckAcceptableValue(*pValue)) return false;
		pTag->SetValue(pValue.release());
		return true;
	}
	return Value_Object::DoPropSet(pSymbol, pValue.release(), attr);
}

Gurax_EndModuleScope(jpeg)
