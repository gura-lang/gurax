//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(mswin)

void SetError(DWORD dwErrCode)
{
	LPVOID lpMsgBuf;
	::FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, dwErrCode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR)&lpMsgBuf, 0, nullptr);
	Error::Issue(ErrorType::GuestError, "%s", BSTRToString(reinterpret_cast<OLECHAR *>(lpMsgBuf)).c_str());
	::LocalFree(lpMsgBuf);
}

OLECHAR* StringToBSTR(const char* psz)
{
	// cnt includes null-terminater
	int cnt = ::MultiByteToWideChar(CP_UTF8, 0, psz, -1, nullptr, 0);
	OLECHAR *bstr = ::SysAllocStringByteLen(nullptr, (cnt + 1) * sizeof(OLECHAR));
	::MultiByteToWideChar(CP_UTF8, 0, psz, -1, bstr, cnt);
	bstr[cnt] = 0;
	return bstr;
}

String BSTRToString(const OLECHAR* bstr)
{
	// cnt includes null-terminater
	int cnt = ::WideCharToMultiByte(CP_UTF8, 0, bstr, -1, nullptr, 0, nullptr, nullptr);
	char* psz = new char[cnt + 1];
	::WideCharToMultiByte(CP_UTF8, 0, bstr, -1, psz, cnt, nullptr, nullptr);
	psz[cnt] = '\0';
	return String(psz);
}

#if 0
bool ValueToVariant(VARIANT& var, const Value& value)
{
	//::printf("ValueToVariant(%s %s)\n", value.GetTypeName(), value.ToString().c_str());
	::VariantInit(&var);
	if (value.Is_number()) {
		Number num = value.GetNumber();
		if (static_cast<Number>(static_cast<long>(num)) == num) {
			var.vt = VT_I4;
			var.lVal = static_cast<long>(value.GetNumber());
		} else {
			var.vt = VT_R8;
			var.dblVal = value.GetNumber();
		}
	} else if (value.Is_string()) {
		var.vt = VT_BSTR;
		var.bstrVal = StringToBSTR(value.GetString());
	} else if (value.Is_boolean()) {
		var.vt = VT_BOOL;
		var.boolVal = value.GetBoolean()? VARIANT_TRUE : VARIANT_FALSE;
	} else if (value.Is_list()) {
		const ValueList& valList = value.GetList();
		SAFEARRAYBOUND safeArrayBound;
		safeArrayBound.lLbound = 0;
		safeArrayBound.cElements = static_cast<ULONG>(valList.size());
		SAFEARRAY *pSafeArray = ::SafeArrayCreate(VT_VARIANT, 1, &safeArrayBound);
		//::printf("%p\n", pSafeArray);
		var.vt = VT_VARIANT | VT_ARRAY;
		var.parray = pSafeArray;
		//::SafeArrayLock(pSafeArray);
		for (const Value* pValue : valList) {
			VARIANT varElem;
			if (!ValueToVariant(sig, varElem, *pValue)) return false;
			long index = static_cast<long>(pValue - valList.begin());
			::SafeArrayPutElement(pSafeArray, &index, &varElem);
		}
		//::SafeArrayUnlock(pSafeArray);
	} else if (value.IsType(VTYPE_ole)) {
		IDispatch *pDispatch = Object_ole::GetObject(value)->GetDispatch();
		pDispatch->AddRef();
		var.vt = VT_DISPATCH;
		var.pdispVal = pDispatch;
	} else if (value.Is_datetime()) {
		const DateTime &dateTime = Object_datetime::GetObject(value)->GetDateTime();
		COleDateTime oledt(dateTime.GetYear(), dateTime.GetMonth(), dateTime.GetDay(),
				dateTime.GetHour(), dateTime.GetMin(), dateTime.GetSec());
		var.vt = VT_DATE;
		var.date = oledt.m_dt;
	} else {
		sig.SetError(ERR_ValueError, "cannot convert to ole variant");
		return false;
	}
	return true;
}

bool VariantToValue(Value& value, const VARIANT& var)
{
	VARTYPE type = var.vt & VT_TYPEMASK;
	if (var.vt & VT_ARRAY) {
		var.byref;
	} else if (type == VT_UI1) {
		value = Value(static_cast<Number>((var.vt & VT_BYREF)? *var.pbVal : var.bVal));
	} else if (type == VT_I2) {
		value = Value(static_cast<Number>((var.vt & VT_BYREF)? *var.piVal : var.iVal));
	} else if (type == VT_I4) {
		value = Value(static_cast<Number>((var.vt & VT_BYREF)? *var.plVal : var.lVal));
	} else if (type == VT_R4) {
		value = Value(static_cast<Number>((var.vt & VT_BYREF)? *var.pfltVal : var.fltVal));
	} else if (type == VT_R8) {
		value = Value(static_cast<Number>((var.vt & VT_BYREF)? *var.pdblVal :var.dblVal));
	} else if (type == VT_BOOL) {
		bool result = !((static_cast<Number>((var.vt & VT_BYREF)?
											*var.pboolVal : var.boolVal)) == 0);
		value = Value(result);
	} else if (type == VT_ERROR) {
		sig.SetError(ERR_ValueError, "cantnot convert from ole variant ERROR");
		//value = Value(static_cast<Number>((var.vt & VT_BYREF)? *var.pscode : var.code));
	} else if (type == VT_CY) {
		sig.SetError(ERR_ValueError, "cantnot convert from ole variant CY");
		//value = Value(static_cast<Number>((var.vt & VT_BYREF)? *var.pcyVal : var.cyVal));
	} else if (type == VT_DATE) {
		COleDateTime oledt((var.vt & VT_BYREF)? *var.pdate : var.date);
		DateTime dateTime(oledt.GetYear(), oledt.GetMonth(), oledt.GetDay(),
				oledt.GetHour() * 3600 + oledt.GetMinute() * 60 + oledt.GetSecond(),
				0, OAL::GetSecsOffsetTZ());
		value = Value(new Object_datetime(env, dateTime));
	} else if (type == VT_BSTR) {
		value = Value(BSTRToString(var.bstrVal));
	} else if (type == VT_UNKNOWN) {
		sig.SetError(ERR_ValueError, "cantnot convert from ole variant UNKNOWN");
		//value = Value(static_cast<Number>((var.vt & VT_BYREF)? *var.ppunkVal : var.punkVal));
	} else if (type == VT_DISPATCH) {
		IDispatch *pDispatch = (var.vt & VT_BYREF)? *var.ppdispVal : var.pdispVal;
		pDispatch->AddRef(); // prevent deletion by VariantClear()
		Object_ole *pObj = new Object_ole(env, pDispatch);
		value = Value(pObj);
	} else if (type == VT_VARIANT) {
		sig.SetError(ERR_ValueError, "cantnot convert from ole variant VARIANT");
		//value = Value(static_cast<Number>(*var.pvarVal));
	}
	return true;
}

Value RegDataToValue(DWORD dwType, LPCBYTE lpData, DWORD cbData)
{
	Value result;
	if (dwType == REG_BINARY) {
		result = Value(new Object_binary(env, reinterpret_cast<const char *>(lpData), cbData, true));
	} else if (dwType == REG_DWORD || dwType == REG_DWORD_LITTLE_ENDIAN) {
		result = Value(*reinterpret_cast<const DWORD *>(lpData));
	} else if (dwType == REG_DWORD_BIG_ENDIAN) {
		sig.SetError(ERR_ValueError, "cantnot convert from registry value REG_DWORD_BIG_ENDIAN");
	} else if (dwType == REG_EXPAND_SZ) {
		sig.SetError(ERR_ValueError, "cantnot convert from registry value REG_EXPAND_SZ");
	} else if (dwType == REG_LINK) {
		sig.SetError(ERR_ValueError, "cantnot convert from registry value REG_LINK");
	} else if (dwType == REG_MULTI_SZ) {
		Object_list *pObjList = result.InitAsList(env);
		size_t bytesSum = 0;
		while (bytesSum + 1 < static_cast<size_t>(cbData)) {
			Value value(OAL::FromNativeString(reinterpret_cast<const char *>(lpData)));
			pObjList->Add(value);
			size_t bytes = ::strlen(reinterpret_cast<const char *>(lpData)) + 1;
			lpData += bytes;
			bytesSum += bytes;
		}
	} else if (dwType == REG_NONE) {
		// nothing to do
	} else if (dwType == REG_QWORD || dwType == REG_QWORD_LITTLE_ENDIAN) {
		sig.SetError(ERR_ValueError, "cantnot convert from registry value REG_QWORD");
	} else if (dwType == REG_RESOURCE_LIST) {
		sig.SetError(ERR_ValueError, "cantnot convert from registry value REG_RESOURCE_LIST");
	} else if (dwType == REG_SZ) {
		result = Value(OAL::FromNativeString(reinterpret_cast<const char *>(lpData)));
	}
	return result;
}

bool ValueToRegData(const Value &value, DWORD* pdwType, LPBYTE* lppData, DWORD* pcbData)
{
	if (value.Is_number()) {
		*pdwType = REG_DWORD;
		*pcbData = sizeof(DWORD);
		*lppData = reinterpret_cast<LPBYTE>(::LocalAlloc(LMEM_FIXED, *pcbData));
		*reinterpret_cast<DWORD *>(*lppData) = value.GetULong();
		return true;
	} else if (value.Is_binary()) {
		const Binary &buff = value.GetBinary();
		*pdwType = REG_BINARY;
		*pcbData = static_cast<DWORD>(buff.size());
		*lppData = reinterpret_cast<LPBYTE>(::LocalAlloc(LMEM_FIXED, *pcbData));
		::memcpy(*lppData, buff.data(), *pcbData);
		return true;
	} else if (value.Is_list()) {
		size_t bytesSum = 0;
		foreach_const (ValueList, pValue, value.GetList()) {
			if (!pValue->Is_string()) goto error_done;
			String str = OAL::ToNativeString(pValue->GetString());
			size_t bytes = str.size() + 1;
			bytesSum += bytes;
		}
		bytesSum++;
		*pdwType = REG_MULTI_SZ;
		*pcbData = static_cast<DWORD>(bytesSum);
		*lppData = reinterpret_cast<LPBYTE>(::LocalAlloc(LMEM_FIXED, *pcbData));
		BYTE *p = *lppData;
		for (const Value* pValue : value.GetList()) {
			if (!pValue->Is_string()) goto error_done;
			String str = OAL::ToNativeString(pValue->GetString());
			size_t bytes = str.size() + 1;
			::memcpy(p, str.c_str(), bytes);
			p += bytes;
		}
		*p = '\0';
		return true;
	} else if (value.Is_string()) {
		String str = OAL::ToNativeString(value.GetString());
		*pdwType = REG_SZ;
		*pcbData = static_cast<DWORD>(str.size() + 1);
		*lppData = reinterpret_cast<LPBYTE>(::LocalAlloc(LMEM_FIXED, *pcbData));
		::memcpy(*lppData, str.c_str(), *pcbData);
		return true;
	}
error_done:
	sig.SetError(ERR_ValueError, "invalid data type for registry");
	return false;
}
#endif

Gurax_EndModuleScope(mswin)
