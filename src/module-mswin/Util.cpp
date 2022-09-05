//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(mswin)

void SetErrorFromErrCode(DWORD dwErrCode)
{
	LPVOID lpMsgBuf;
	::FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, dwErrCode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR)&lpMsgBuf, 0, nullptr);
	Error::Issue(ErrorType::GuestError, "%s", BSTRToString(reinterpret_cast<OLECHAR *>(lpMsgBuf)).c_str());
	::LocalFree(lpMsgBuf);
}

void SetErrorFromHRESULT(HRESULT hr)
{
	LPWSTR errMsg = nullptr;
	::FormatMessageW(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, hr, LOCALE_SYSTEM_DEFAULT, reinterpret_cast<LPWSTR>(&errMsg), 0, nullptr);
	if (errMsg == nullptr) {
		Error::Issue(ErrorType::GuestError, "COM error [%08x]", hr);
	} else {
		int len = static_cast<int>(::wcslen(errMsg));
		if (len > 0 && errMsg[len - 1] == '\n') len--;
		int bytes = ::WideCharToMultiByte(CP_UTF8, 0, errMsg, len, nullptr, 0, nullptr, nullptr);
		char *pszErrMsg = new char [bytes];
		::WideCharToMultiByte(CP_UTF8, 0, errMsg, len, pszErrMsg, bytes, nullptr, nullptr);
		pszErrMsg[bytes] = '\0';
		Error::Issue(ErrorType::GuestError, "COM error [%08x] %s", hr, pszErrMsg);
		::LocalFree(errMsg);
	}
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

bool ValueToVariant(VARIANT& var, const Value& value)
{
	//::printf("ValueToVariant(%s %s)\n", value.GetTypeName(), value.ToString().c_str());
	::VariantInit(&var);
	if (value.IsType(VTYPE_Number)) {
		Double num = Value_Number::GetNumber<Double>(value);
		if (static_cast<Double>(static_cast<long>(num)) == num) {
			var.vt = VT_I4;
			var.lVal = static_cast<long>(num);
		} else {
			var.vt = VT_R8;
			var.dblVal = num;
		}
	} else if (value.IsType(VTYPE_String)) {
		var.vt = VT_BSTR;
		var.bstrVal = StringToBSTR(Value_String::GetString(value));
	} else if (value.IsType(VTYPE_Bool)) {
		var.vt = VT_BOOL;
		var.boolVal = value.GetBool()? VARIANT_TRUE : VARIANT_FALSE;
	} else if (value.IsList()) {
		const ValueList& valList = Value_List::GetValueOwner(value);
		SAFEARRAYBOUND safeArrayBound;
		safeArrayBound.lLbound = 0;
		safeArrayBound.cElements = static_cast<ULONG>(valList.size());
		SAFEARRAY *pSafeArray = ::SafeArrayCreate(VT_VARIANT, 1, &safeArrayBound);
		//::printf("%p\n", pSafeArray);
		var.vt = VT_VARIANT | VT_ARRAY;
		var.parray = pSafeArray;
		//::SafeArrayLock(pSafeArray);
		long index = 0;
		for (const Value* pValue : valList) {
			VARIANT varElem;
			if (!ValueToVariant(varElem, *pValue)) return false;
			::SafeArrayPutElement(pSafeArray, &index, &varElem);
			index++;
		}
		//::SafeArrayUnlock(pSafeArray);
	} else if (value.IsType(VTYPE_OLE)) {
#if 0
		IDispatch* pDispatch = Value_OLE::GetOLE(value).GetDispatch();
		pDispatch->AddRef();
		var.vt = VT_DISPATCH;
		var.pdispVal = pDispatch;
#endif
	} else if (value.IsType(VTYPE_DateTime)) {
		const DateTime& dateTime = Value_DateTime::GetDateTime(value);
#if 0
		COleDateTime oledt(dateTime.GetYear(), dateTime.GetMonth(), dateTime.GetDay(),
				dateTime.GetHour(), dateTime.GetMin(), dateTime.GetSec());
		var.vt = VT_DATE;
		var.date = oledt.m_dt;
#endif
	} else {
		Error::Issue(ErrorType::TypeError, "cannot convert to ole variant");
		return false;
	}
	return true;
}

Value* VariantToValue(const VARIANT& var)
{
	RefPtr<Value> pValue;
	VARTYPE type = var.vt & VT_TYPEMASK;
	if (var.vt & VT_ARRAY) {
		var.byref;
	} else if (type == VT_UI1) {
		pValue.reset(new Value_Number((var.vt & VT_BYREF)? *var.pbVal : var.bVal));
	} else if (type == VT_I2) {
		pValue.reset(new Value_Number((var.vt & VT_BYREF)? *var.piVal : var.iVal));
	} else if (type == VT_I4) {
		pValue.reset(new Value_Number((var.vt & VT_BYREF)? *var.plVal : var.lVal));
	} else if (type == VT_R4) {
		pValue.reset(new Value_Number((var.vt & VT_BYREF)? *var.pfltVal : var.fltVal));
	} else if (type == VT_R8) {
		pValue.reset(new Value_Number((var.vt & VT_BYREF)? *var.pdblVal :var.dblVal));
	} else if (type == VT_BOOL) {
		bool result = !((static_cast<int>((var.vt & VT_BYREF)? *var.pboolVal : var.boolVal)) == 0);
		pValue.reset(new Value_Bool(result));
	} else if (type == VT_ERROR) {
		Error::Issue(ErrorType::ValueError, "cantnot convert from ole variant ERROR");
		//value = Value(static_cast<Number>((var.vt & VT_BYREF)? *var.pscode : var.code));
		return nullptr;
	} else if (type == VT_CY) {
		Error::Issue(ErrorType::ValueError, "cantnot convert from ole variant CY");
		//value = Value(static_cast<Number>((var.vt & VT_BYREF)? *var.pcyVal : var.cyVal));
		return nullptr;
	} else if (type == VT_DATE) {
		//COleDateTime oledt((var.vt & VT_BYREF)? *var.pdate : var.date);
		//RefPtr<DateTime> pDateTime(new DateTime(oledt.GetYear(), oledt.GetMonth(), oledt.GetDay(),
		//		oledt.GetHour() * 3600 + oledt.GetMinute() * 60 + oledt.GetSecond(),
		//		0, OAL::GetSecsOffsetTZ()));
		//pValue.reset(new Value_DateTime(pDateTime.release()));
		return nullptr;
	} else if (type == VT_BSTR) {
		pValue.reset(new Value_String(BSTRToString(var.bstrVal)));
	} else if (type == VT_UNKNOWN) {
		Error::Issue(ErrorType::ValueError, "cantnot convert from ole variant UNKNOWN");
		//value = Value(static_cast<Number>((var.vt & VT_BYREF)? *var.ppunkVal : var.punkVal));
		return nullptr;
	} else if (type == VT_DISPATCH) {
		IDispatch* pDispatch = (var.vt & VT_BYREF)? *var.ppdispVal : var.pdispVal;
		pDispatch->AddRef(); // prevent deletion by VariantClear()
		//Object_ole *pObj = new Object_ole(env, pDispatch);
		//value = Value(pObj);
		return nullptr;
	} else if (type == VT_VARIANT) {
		Error::Issue(ErrorType::ValueError, "cantnot convert from ole variant VARIANT");
		//value = Value(static_cast<Number>(*var.pvarVal));
		return nullptr;
	}
	return pValue.release();
}

Value* RegDataToValue(DWORD dwType, LPCBYTE lpData, DWORD cbData)
{
	RefPtr<Value> pValueRtn;
	if (dwType == REG_BINARY) {
		pValueRtn.reset(new Value_Binary(Binary(reinterpret_cast<const char *>(lpData), cbData)));
	} else if (dwType == REG_DWORD || dwType == REG_DWORD_LITTLE_ENDIAN) {
		pValueRtn.reset(new Value_Number(*reinterpret_cast<const DWORD *>(lpData)));
	} else if (dwType == REG_DWORD_BIG_ENDIAN) {
		Error::Issue(ErrorType::ValueError, "cantnot convert from registry value REG_DWORD_BIG_ENDIAN");
	} else if (dwType == REG_EXPAND_SZ) {
		Error::Issue(ErrorType::ValueError, "cantnot convert from registry value REG_EXPAND_SZ");
	} else if (dwType == REG_LINK) {
		Error::Issue(ErrorType::ValueError, "cantnot convert from registry value REG_LINK");
	} else if (dwType == REG_MULTI_SZ) {
		RefPtr<ValueOwner> pValueOwner(new ValueOwner());
		size_t bytesSum = 0;
		while (bytesSum + 1 < static_cast<size_t>(cbData)) {
			pValueOwner->push_back(new Value_String(OAL::FromNativeString(reinterpret_cast<const char *>(lpData))));
			size_t bytes = ::strlen(reinterpret_cast<const char *>(lpData)) + 1;
			lpData += bytes;
			bytesSum += bytes;
		}
		pValueRtn.reset(new Value_Tuple(pValueOwner.release()));
	} else if (dwType == REG_NONE) {
		// nothing to do
	} else if (dwType == REG_QWORD || dwType == REG_QWORD_LITTLE_ENDIAN) {
		Error::Issue(ErrorType::ValueError, "cantnot convert from registry value REG_QWORD");
	} else if (dwType == REG_RESOURCE_LIST) {
		Error::Issue(ErrorType::ValueError, "cantnot convert from registry value REG_RESOURCE_LIST");
	} else if (dwType == REG_SZ) {
		pValueRtn.reset(new Value_String(OAL::FromNativeString(reinterpret_cast<const char *>(lpData))));
	}
	return pValueRtn.release();
}

bool ValueToRegData(const Value& value, DWORD* pdwType, LPBYTE* lppData, DWORD* pcbData)
{
	if (value.IsType(VTYPE_Number)) {
		*pdwType = REG_DWORD;
		*pcbData = sizeof(DWORD);
		*lppData = reinterpret_cast<LPBYTE>(::LocalAlloc(LMEM_FIXED, *pcbData));
		*reinterpret_cast<DWORD*>(*lppData) = Value_Number::GetNumber<DWORD>(value);
	} else if (value.IsType(VTYPE_Binary)) {
		const Binary& buff = Value_Binary::GetBinary(value);
		*pdwType = REG_BINARY;
		*pcbData = static_cast<DWORD>(buff.size());
		*lppData = reinterpret_cast<LPBYTE>(::LocalAlloc(LMEM_FIXED, *pcbData));
		::memcpy(*lppData, buff.data(), *pcbData);
	} else if (value.IsList()) {
		size_t bytesSum = 0;
		for (const Value* pValueEach : Value_List::GetValueOwner(value)) {
			if (!pValueEach->IsType(VTYPE_String)) {
				Error::Issue(ErrorType::ValueError, "invalid data type for registry");
				return false;
			}
			String str = OAL::ToNativeString(Value_String::GetString(*pValueEach));
			size_t bytes = str.size() + 1;
			bytesSum += bytes;
		}
		bytesSum++;
		*pdwType = REG_MULTI_SZ;
		*pcbData = static_cast<DWORD>(bytesSum);
		*lppData = reinterpret_cast<LPBYTE>(::LocalAlloc(LMEM_FIXED, *pcbData));
		BYTE *p = *lppData;
		for (const Value* pValueEach : Value_List::GetValueOwner(value)) {
			if (!pValueEach->IsType(VTYPE_String)) {
				Error::Issue(ErrorType::ValueError, "invalid data type for registry");
				return false;
			}
			String str = OAL::ToNativeString(Value_String::GetString(*pValueEach));
			size_t bytes = str.size() + 1;
			::memcpy(p, str.c_str(), bytes);
			p += bytes;
		}
		*p = '\0';
	} else if (value.IsType(VTYPE_String)) {
		String str = OAL::ToNativeString(Value_String::GetString(value));
		*pdwType = REG_SZ;
		*pcbData = static_cast<DWORD>(str.size() + 1);
		*lppData = reinterpret_cast<LPBYTE>(::LocalAlloc(LMEM_FIXED, *pcbData));
		::memcpy(*lppData, str.c_str(), *pcbData);
	}
	return true;
}

Gurax_EndModuleScope(mswin)
