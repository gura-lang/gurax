//==============================================================================
// OLE.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(mswin)

//------------------------------------------------------------------------------
// OLE
//------------------------------------------------------------------------------
bool OLE::Create(const char* progID)
{
	HRESULT hr;
	CLSID clsid;
	do {
		OLECHAR* progID_W = StringToBSTR(progID);
		::CLSIDFromProgID(progID_W, &clsid);
		::SysFreeString(progID_W);
	} while (0);
	hr = ::CoCreateInstance(clsid, nullptr, CLSCTX_INPROC_SERVER | CLSCTX_LOCAL_SERVER,
					IID_IDispatch, reinterpret_cast<LPVOID *>(&_pDispatch));
	if (FAILED(hr)) {
		SetErrorFromHRESULT(hr);
		return false;
	}
	return true;
}

bool OLE::Connect(const char* progID)
{
	HRESULT hr;
	CLSID clsid;
	do {
		OLECHAR* progID_W = StringToBSTR(progID);
		::CLSIDFromProgID(progID_W, &clsid);
		::SysFreeString(progID_W);
	} while (0);
	IUnknown* pUnknown = nullptr;
	hr = ::GetActiveObject(clsid, 0, &pUnknown);
	if (FAILED(hr)) {
		SetErrorFromHRESULT(hr);
		return false;
	}
	hr = pUnknown->QueryInterface(IID_IDispatch, reinterpret_cast<LPVOID*>(&_pDispatch));
	if (FAILED(hr)) {
		pUnknown->Release();
		SetErrorFromHRESULT(hr);
		return false;
	}
	pUnknown->Release();
	return true;
}

bool OLE::ImportConstant(Frame& frame)
{
	HRESULT hr;
	//hr = _pDispatch->GetTypeInfoCount(&cnt); // 0 or 1
	ITypeLib* pTypeLib = nullptr;
	do {
		ITypeInfo* pTypeInfo = nullptr;
		do {
			hr = _pDispatch->GetTypeInfo(0, LOCALE_SYSTEM_DEFAULT, &pTypeInfo);
			if (FAILED(hr)) {
				SetErrorFromHRESULT(hr);
				return false;
			}
		} while (0);
		do {
			unsigned int index; // not necessary for the actual use?
			hr = pTypeInfo->GetContainingTypeLib(&pTypeLib, &index);
			if (FAILED(hr)) {
				SetErrorFromHRESULT(hr);
				pTypeInfo->Release();
				return false;
			}
		} while (0);
		pTypeInfo->Release();
	} while (0);
	long cntTypeInfo = pTypeLib->GetTypeInfoCount();
	for (long iTypeInfo = 0; iTypeInfo < cntTypeInfo; iTypeInfo++) {
		ITypeInfo* pTypeInfo = nullptr;
		do {
			hr = pTypeLib->GetTypeInfo(iTypeInfo, &pTypeInfo);
			if (FAILED(hr)) {
				SetErrorFromHRESULT(hr);
				pTypeLib->Release();
				return false;
			}
		} while (0);
		int cVars = 0;
		do {
			TYPEATTR* pTypeAttr = nullptr;
			hr = pTypeInfo->GetTypeAttr(&pTypeAttr);
			if (FAILED(hr)) {
				SetErrorFromHRESULT(hr);
				pTypeInfo->Release();
				pTypeLib->Release();
				return false;
			}
			cVars = pTypeAttr->cVars;
			pTypeInfo->ReleaseTypeAttr(pTypeAttr);
		} while (0);
		for (int iVar = 0; iVar < cVars; iVar++) {
			VARDESC* pVarDesc = nullptr;
			hr = pTypeInfo->GetVarDesc(iVar, &pVarDesc);
			if (FAILED(hr)) continue;
			if (pVarDesc->varkind != VAR_CONST) {
				pTypeInfo->ReleaseVarDesc(pVarDesc);
				continue;
			}
			const Symbol* pSymbol = nullptr;
			do {
				OLECHAR* nameOle;
				unsigned int len;
				hr = pTypeInfo->GetNames(pVarDesc->memid, &nameOle, 1, &len);
				if (FAILED(hr)) break;
				pSymbol = Symbol::Add(BSTRToString(nameOle).c_str());
				::SysFreeString(nameOle);
			} while (0);
			if (pSymbol) {
				RefPtr<Value> pValue(VariantToValue(*pVarDesc->lpvarValue));
				if (!pValue) return false;
				frame.Assign(pSymbol, pValue.release());
			}
			pTypeInfo->ReleaseVarDesc(pVarDesc);
		}
		pTypeInfo->Release();
	}
	pTypeLib->Release();
	return true;
}

HRESULT OLE::GetDispID(const char* name, DISPID& dispid)
{
	OLECHAR* wszName = StringToBSTR(name);
	HRESULT hr = _pDispatch->GetIDsOfNames(IID_NULL, &wszName, 1, LOCALE_USER_DEFAULT, &dispid);
	::SysFreeString(wszName);
	return hr;
}

HRESULT OLE::GetDispIDOfNamedArg(const char* nameMethod, const char* nameArg, DISPID& dispid)
{
	// named argument have to be looked up with a method name. see MSDN KB223165.
	OLECHAR* wszNames[2];
	DISPID dispids[2];
	wszNames[0] = StringToBSTR(nameMethod);
	wszNames[1] = StringToBSTR(nameArg);
	HRESULT hr = _pDispatch->GetIDsOfNames(IID_NULL, wszNames, 2, LOCALE_USER_DEFAULT, dispids);
	::SysFreeString(wszNames[0]);
	::SysFreeString(wszNames[1]);
	dispid = dispids[1];
	return hr;
}

String OLE::ToString(const StringStyle& ss) const
{
	return String().Format("mswin.OLE");
}

Gurax_EndModuleScope(mswin)
