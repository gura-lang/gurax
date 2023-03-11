//==============================================================================
// VType_RegKey.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(mswin)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(mswin.RegKey, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(mswin.RegKey, `en)}

${help.ComposeMethodHelp(mswin.RegKey, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// mswin.RegKey#CreateKey(subKey as String, options? as Number, samDesired? as Number)
Gurax_DeclareMethod(RegKey, CreateKey)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("subKey", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("options", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("samDesired", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(RegKey, CreateKey)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const char* subKey = args.PickString();
	DWORD dwOptions = args.IsValid()? args.PickNumber<DWORD>() : REG_OPTION_NON_VOLATILE;
	REGSAM samDesired = args.IsValid()? args.PickNumber<REGSAM>() : KEY_ALL_ACCESS;
	// Function body
	HKEY hKey = valueThis.GetRegKey().GetHKEY();
	HKEY hKeyResult;
	DWORD dwDisposition;
	DWORD dwErrCode = ::RegCreateKeyEx(hKey, OAL::ToNativeString(subKey).c_str(),
			0, nullptr, dwOptions, samDesired, nullptr, &hKeyResult, &dwDisposition);
	if (dwErrCode != ERROR_SUCCESS) {
		SetErrorFromErrCode(dwErrCode);
		return Value::nil();
	}
	return new Value_RegKey(new RegKey(hKeyResult, subKey));
}

// mswin.RegKey#OpenKey(subKey as String, options? as Number, samDesired? as Number)
Gurax_DeclareMethod(RegKey, OpenKey)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("subKey", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("samDesired", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(RegKey, OpenKey)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const char* lpSubKey = args.PickString();
	REGSAM samDesired = args.IsValid()? args.PickNumber<REGSAM>() : KEY_ALL_ACCESS;
	// Function body
	HKEY hKey = valueThis.GetRegKey().GetHKEY();
	HKEY hKeyResult;
	DWORD dwErrCode = ::RegOpenKeyEx(hKey, OAL::ToNativeString(lpSubKey).c_str(), 0, samDesired, &hKeyResult);
	if (dwErrCode != ERROR_SUCCESS) {
		SetErrorFromErrCode(dwErrCode);
		return Value::nil();
	}
	return new Value_RegKey(new RegKey(hKeyResult, lpSubKey));
}

// mswin.RegKey#DeleteKey(subKey as String)
Gurax_DeclareMethod(RegKey, DeleteKey)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("subKey", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(RegKey, DeleteKey)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const char* lpSubKey = args.PickString();
	// Function body
	HKEY hKey = valueThis.GetRegKey().GetHKEY();
	DWORD dwErrCode = ::RegDeleteKey(hKey, OAL::ToNativeString(lpSubKey).c_str());
	if (dwErrCode != ERROR_SUCCESS) {
		SetErrorFromErrCode(dwErrCode);
		return Value::nil();
	}
	return Value::nil();
}

// mswin.RegKey#EnumKey(samDesired? as Number) {block?}
Gurax_DeclareMethod(RegKey, EnumKey)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("samDesired", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(RegKey, EnumKey)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	REGSAM samDesired = args.IsValid()? args.PickNumber<REGSAM>() : KEY_ALL_ACCESS;
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_RegEnumKey(valueThis.GetRegKey().Reference(), samDesired));
	return argument.ReturnIterator(processor, pIterator.release());
}

// mswin.RegKey#SetKeyValue(subKey as String, valueName as String, data:noMap)
Gurax_DeclareMethod(RegKey, SetKeyValue)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("subKey", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("valueName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Any, ArgOccur::Once, ArgFlag::NoMap);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(RegKey, SetKeyValue)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const char* lpSubKey = args.PickString();
	const char* lpValueName = args.PickString();
	const Value& valueData = args.PickValue();
	// Function body
	HKEY hKey = valueThis.GetRegKey().GetHKEY();
	DWORD dwType = 0;
	BYTE *lpData = nullptr;
	DWORD cbData = 0;
	if (!ValueToRegData(valueData, &dwType, &lpData, &cbData)) return Value::nil();
	DWORD dwErrCode = ::RegSetKeyValue(hKey, OAL::ToNativeString(lpSubKey).c_str(),
			OAL::ToNativeString(lpValueName).c_str(), dwType, lpData, cbData);
	::LocalFree(lpData);
	if (dwErrCode != ERROR_SUCCESS) SetErrorFromErrCode(dwErrCode);
	return Value::nil();
}

// mswin.RegKey#SetValue(valueName as String, data:noMap)
Gurax_DeclareMethod(RegKey, SetValue)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("valueName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Any, ArgOccur::Once, ArgFlag::NoMap);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(RegKey, SetValue)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const char* lpValueName = args.PickString();
	const Value& valueData = args.PickValue();
	// Function body
	HKEY hKey = valueThis.GetRegKey().GetHKEY();
	DWORD dwType = 0;
	BYTE *lpData = nullptr;
	DWORD cbData = 0;
	if (!ValueToRegData(valueData, &dwType, &lpData, &cbData)) return Value::nil();
	DWORD dwErrCode = ::RegSetValueEx(hKey,
			OAL::ToNativeString(lpValueName).c_str(), 0, dwType, lpData, cbData);
	::LocalFree(lpData);
	if (dwErrCode != ERROR_SUCCESS) SetErrorFromErrCode(dwErrCode);
	return Value::nil();
}

// mswin.RegKey#DeleteValue(subKey as String)
Gurax_DeclareMethod(RegKey, DeleteValue)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("subKey", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(RegKey, DeleteValue)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const char* lpSubKey = args.PickString();
	// Function body
	HKEY hKey = valueThis.GetRegKey().GetHKEY();
	DWORD dwErrCode = ::RegDeleteKey(hKey, OAL::ToNativeString(lpSubKey).c_str());
	if (dwErrCode != ERROR_SUCCESS) SetErrorFromErrCode(dwErrCode);
	return Value::nil();
}

// mswin.RegKey#QueryValue(valueName? as String)
Gurax_DeclareMethod(RegKey, QueryValue)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("valueName", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(RegKey, QueryValue)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const char* lpValueName = args.IsValid()? args.PickString() : nullptr;
	// Function body
	HKEY hKey = valueThis.GetRegKey().GetHKEY();
	DWORD dwType;
	DWORD cbData;
	DWORD dwErrCode = ::RegQueryValueEx(hKey,
		(lpValueName == nullptr)? nullptr : OAL::ToNativeString(lpValueName).c_str(),
		nullptr, &dwType, nullptr, &cbData);
	if (dwErrCode != ERROR_SUCCESS) {
		SetErrorFromErrCode(dwErrCode);
		return Value::nil();
	}
	LPBYTE lpData = reinterpret_cast<LPBYTE>(::LocalAlloc(LMEM_FIXED, cbData));
	dwErrCode = ::RegQueryValueEx(hKey,
		(lpValueName == nullptr)? nullptr : OAL::ToNativeString(lpValueName).c_str(),
		nullptr, &dwType, lpData, &cbData);
	if (dwErrCode != ERROR_SUCCESS) {
		::LocalFree(lpData);
		SetErrorFromErrCode(dwErrCode);
		return Value::nil();
	}
	RefPtr<Value> pValueRtn(RegDataToValue(dwType, lpData, cbData));
	::LocalFree(lpData);
	return pValueRtn.release();
}

// mswin.RegKey#EnumValue() {block?}
Gurax_DeclareMethod(RegKey, EnumValue)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(RegKey, EnumValue)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_RegEnumValue(valueThis.GetRegKey().Reference()));
	return argument.ReturnIterator(processor, pIterator.release());
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// mswin.RegKey#name
Gurax_DeclareProperty_R(RegKey, name)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(RegKey, name)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetRegKey().GetName());
}

//------------------------------------------------------------------------------
// VType_RegKey
//------------------------------------------------------------------------------
VType_RegKey VTYPE_RegKey("RegKey");

void VType_RegKey::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(RegKey, CreateKey));
	Assign(Gurax_CreateMethod(RegKey, OpenKey));
	Assign(Gurax_CreateMethod(RegKey, DeleteKey));
	Assign(Gurax_CreateMethod(RegKey, EnumKey));
	Assign(Gurax_CreateMethod(RegKey, SetKeyValue));
	Assign(Gurax_CreateMethod(RegKey, SetValue));
	Assign(Gurax_CreateMethod(RegKey, DeleteValue));
	Assign(Gurax_CreateMethod(RegKey, QueryValue));
	Assign(Gurax_CreateMethod(RegKey, EnumValue));
	// Assignment of property
	Assign(Gurax_CreateProperty(RegKey, name));
}

//------------------------------------------------------------------------------
// Value_RegKey
//------------------------------------------------------------------------------
VType& Value_RegKey::vtype = VTYPE_RegKey;

String Value_RegKey::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetRegKey().ToString(ss));
}

//------------------------------------------------------------------------------
// Iterator_RegEnumKey
//------------------------------------------------------------------------------
Value* Iterator_RegEnumKey::DoNextValue()
{
	char name[256];
	FILETIME ftLastWriteTime;
	HKEY hKey = _pRegKey->GetHKEY();
	DWORD pcName = Gurax_ArraySizeOf(name);
	DWORD dwErrCode = ::RegEnumKeyEx(hKey, _dwIndex, name, &pcName, nullptr, nullptr, nullptr, &ftLastWriteTime);
	if (dwErrCode != ERROR_SUCCESS) {
		if (dwErrCode != ERROR_NO_MORE_ITEMS) SetErrorFromErrCode(dwErrCode);
		return nullptr;
	}
	RefPtr<Value> pValueRtn;
	if (_samDesired == 0) {
		pValueRtn.reset(new Value_String(OAL::FromNativeString(name)));
	} else {
		HKEY hKeyRtn;
		DWORD dwErrCode = ::RegOpenKeyEx(hKey, name, 0, _samDesired, &hKeyRtn);
		if (dwErrCode != ERROR_SUCCESS) {
			SetErrorFromErrCode(dwErrCode);
			return false;
		}
		pValueRtn.reset(new Value_RegKey(new RegKey(hKeyRtn, name)));
	}
	_dwIndex++;
	return pValueRtn.release();
}

String Iterator_RegEnumKey::ToString(const StringStyle& ss) const
{
	return String().Format("mswin.RegEnumKey");
}

//-----------------------------------------------------------------------------
// Iterator_RegEnumValue
//-----------------------------------------------------------------------------
Value* Iterator_RegEnumValue::DoNextValue()
{
	char valueName[256];
	DWORD cValueName = Gurax_ArraySizeOf(valueName);
	HKEY hKey = _pRegKey->GetHKEY();
	DWORD dwType;
	DWORD cbData;
	DWORD dwErrCode = ::RegEnumValue(hKey, _dwIndex, valueName, &cValueName, nullptr, &dwType, nullptr, &cbData);
	if (dwErrCode != ERROR_SUCCESS) {
		if (dwErrCode != ERROR_NO_MORE_ITEMS) SetErrorFromErrCode(dwErrCode);
		return nullptr;
	}
	cValueName = Gurax_ArraySizeOf(valueName);
	LPBYTE lpData = reinterpret_cast<LPBYTE>(::LocalAlloc(LMEM_FIXED, cbData));
	dwErrCode = ::RegEnumValue(hKey, _dwIndex, valueName, &cValueName, nullptr, &dwType, lpData, &cbData);
	if (dwErrCode != ERROR_SUCCESS) {
		::LocalFree(lpData);
		if (dwErrCode != ERROR_NO_MORE_ITEMS) SetErrorFromErrCode(dwErrCode);
		return nullptr;
	}
	RefPtr<Value> pValueRtn(Value_Tuple::Create(
		new Value_String(OAL::FromNativeString(valueName)), RegDataToValue(dwType, lpData, cbData)));
	::LocalFree(lpData);
	if (Error::IsIssued()) return nullptr;
	_dwIndex++;
	return pValueRtn.release();
}

String Iterator_RegEnumValue::ToString(const StringStyle& ss) const
{
	return String().Format("mswin.RegEnumValue");
}

Gurax_EndModuleScope(mswin)
