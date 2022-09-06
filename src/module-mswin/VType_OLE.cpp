//==============================================================================
// VType_OLE.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(mswin)

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

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// mswin.OLE#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(OLE, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(OLE, MethodSkeleton)
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
// mswin.OLE#propSkeleton
Gurax_DeclareProperty_R(OLE, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(OLE, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_OLE
//------------------------------------------------------------------------------
VType_OLE VTYPE_OLE("OLE");

void VType_OLE::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(OLE, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(OLE, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_OLE
//------------------------------------------------------------------------------
VType& Value_OLE::vtype = VTYPE_OLE;

Value* Value_OLE::DoGetProperty(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag)
{
	DISPID dispid;
	do {
		HRESULT hr = _pOLE->GetDispID(pSymbol->GetName(), dispid);
		if (FAILED(hr)) {
			SetErrorFromHRESULT(hr);
			return Value::nil();
		}
	} while (0);
	VARIANT var;
	do {
		DISPPARAMS dispParams = { nullptr, nullptr, 0, 0 };
		HRESULT hr = _pOLE->GetDispatch()->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT,
						DISPATCH_PROPERTYGET, &dispParams, &var, nullptr, nullptr);
		// notFoundErrorFlag
		if (FAILED(hr)) {
			SetErrorFromHRESULT(hr);
			return Value::nil();
		}
	} while (0);
	RefPtr<Value> pValue(VariantToValue(var));
	::VariantClear(&var);
	return pValue.release();
}

bool Value_OLE::DoSetProperty(const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr)
{
	DISPID dispid;
	do {
		HRESULT hr = _pOLE->GetDispID(pSymbol->GetName(), dispid);
		if (FAILED(hr)) {
			SetErrorFromHRESULT(hr);
			return Value::nil();
		}
	} while (0);
	do {
		VARIANTARG varArgs[1];
		DISPID dispidNamedArgs[1] = { DISPID_PROPERTYPUT };
		if (!ValueToVariant(varArgs[0], *pValue)) return Value::nil();
		DISPPARAMS dispParams;
		dispParams.rgvarg = varArgs;
		dispParams.rgdispidNamedArgs = dispidNamedArgs;
		dispParams.cArgs = 1;
		dispParams.cNamedArgs = 1;
		HRESULT hr = _pOLE->GetDispatch()->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT,
							DISPATCH_PROPERTYPUT, &dispParams, nullptr, nullptr, nullptr);
		::VariantClear(&varArgs[0]);
		if (FAILED(hr)) {
			Error::Issue(ErrorType::GuestError, "can't change OLE property %s", pSymbol->GetName());
			return Value::nil();
		}
	} while (0);
	return true;
}

String Value_OLE::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetOLE().ToString(ss));
}

	Gurax_EndModuleScope(mswin)
