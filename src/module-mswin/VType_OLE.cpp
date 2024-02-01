//==============================================================================
// VType_OLE.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(mswin)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(mswin.OLE, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(mswin.OLE, `en)}

${help.ComposeMethodHelp(mswin.OLE, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// mswin.OLE#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(OLE, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
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
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
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
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
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

const DeclCallable* Value_OLE::GetDeclCallableWithError()
{
	return nullptr;
}

const DeclCallable* Value_OLE::GetDeclCallable()
{
	HRESULT hr;
	UINT ctinfo;
	if (FAILED(hr = GetOLE().GetDispatch()->GetTypeInfoCount(&ctinfo))) {
		SetErrorFromHRESULT(hr);
		return nullptr;
	}
	if (ctinfo == 0) return nullptr;
	ITypeInfo* pTInfo;
	if (FAILED(hr = GetOLE().GetDispatch()->GetTypeInfo(0, LOCALE_USER_DEFAULT, &pTInfo))) {
		SetErrorFromHRESULT(hr);
		return nullptr;
	}
	FUNCDESC* pFuncDesc;
	if (FAILED(hr = pTInfo->GetFuncDesc(0, &pFuncDesc))) {
		SetErrorFromHRESULT(hr);
		return nullptr;
	}
	pFuncDesc->lprgelemdescParam->paramdesc.pparamdescex;
	return nullptr;
}

//void Value_OLE::DoCall(Processor& processor, Argument& argument)
//{
//}

Value* Value_OLE::DoEval(Processor& processor, Argument& argument) const
{
#if 0
	size_t cArgs = argument.CountArgSlot();
	VARIANTARG *varArgs = nullptr;
	if (cArgs > 0) {
		varArgs = new VARIANTARG[cArgs];
		size_t iArg = 0;
		for (ArgSlot* pArgSlot = argument.GetArgSlotFirst(); pArgSlot; pArgSlot = pArgSlot->GetNext(), iArg++) {
			if (!ValueToVariant(varArgs[iArg], pArgSlot->GetValue())) return Value::nil();
		}
	}
	DISPPARAMS dispParams;
	dispParams.rgvarg = varArgs;
	dispParams.cArgs = static_cast<UINT>(cArgs);
	dispParams.rgdispidNamedArgs = dispidNamedArgs;
	dispParams.cNamedArgs = static_cast<UINT>(argNames.size());
	VARIANT varResult;
	hr = _pObj->GetDispatch()->Invoke(_dispid, IID_NULL, LOCALE_USER_DEFAULT,
					DISPATCH_METHOD | DISPATCH_PROPERTYGET,
					&dispParams, &varResult, nullptr, nullptr);
	if (varArgs != nullptr) {
		for (size_t iArg = 0; iArg < cArgs; iArg++) {
			::VariantClear(&varArgs[iArg]);
		}
	}
	delete[] varArgs;
	delete[] dispidNamedArgs;
	if (FAILED(hr)) {
		::VariantClear(&varResult);
		Object_ole::SetError(sig, hr);
		return Value::Nil;
	}
	VariantToValue(env, sig, result, varResult);
	::VariantClear(&varResult);
	return result;
#endif
	return Value::nil();
}

Value* Value_OLE::DoGetProperty(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag)
{
	HRESULT hr;
	DISPID dispid;
	if (FAILED(hr = _pOLE->GetDispID(pSymbol->GetName(), dispid))) {
		SetErrorFromHRESULT(hr);
		return Value::nil();
	}
	VARIANT var;
	DISPPARAMS dispParams = { nullptr, nullptr, 0, 0 };
	if (FAILED(hr = _pOLE->GetDispatch()->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT,
					DISPATCH_PROPERTYGET, &dispParams, &var, nullptr, nullptr))) {
		// notFoundErrorFlag
		SetErrorFromHRESULT(hr);
		return Value::nil();
	}
	RefPtr<Value> pValue(VariantToValue(var));
	::VariantClear(&var);
	return pValue.release();
}

bool Value_OLE::DoSetProperty(Processor& processor, const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr)
{
	HRESULT hr;
	DISPID dispid;
	if (FAILED(hr = _pOLE->GetDispID(pSymbol->GetName(), dispid))) {
		SetErrorFromHRESULT(hr);
		return Value::nil();
	}
	VARIANTARG varArgs[1];
	DISPID dispidNamedArgs[1] = { DISPID_PROPERTYPUT };
	if (!ValueToVariant(varArgs[0], *pValue)) return Value::nil();
	DISPPARAMS dispParams;
	dispParams.rgvarg = varArgs;
	dispParams.rgdispidNamedArgs = dispidNamedArgs;
	dispParams.cArgs = 1;
	dispParams.cNamedArgs = 1;
	if (FAILED(hr = _pOLE->GetDispatch()->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT,
						DISPATCH_PROPERTYPUT, &dispParams, nullptr, nullptr, nullptr))) {
		Error::Issue(ErrorType::GuestError, "can't change OLE property %s", pSymbol->GetName());
		return Value::nil();
	}
	::VariantClear(&varArgs[0]);
	return true;
}

String Value_OLE::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetOLE().ToString(ss));
}

	Gurax_EndModuleScope(mswin)
