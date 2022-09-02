//==============================================================================
// VType_RegKey.cpp
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

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
#if 0
// mswin.RegKey() {block?}
Gurax_DeclareConstructor(RegKey)
{
	Declare(VTYPE_RegKey, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `mswin.RegKey` instance.");
}

Gurax_ImplementConstructor(RegKey)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<RegKey> pRegKey(new RegKey());
	return argument.ReturnValue(processor, new Value_RegKey(pRegKey.release()));
}
#endif

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
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
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
		//SetError(sig, dwErrCode);
		return Value::nil();
	}
	return new Value_RegKey(new RegKey(hKeyResult));
}

// mswin.RegKey#OpenKey(subKey as String, options? as Number, samDesired? as Number)
Gurax_DeclareMethod(RegKey, OpenKey)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("subKey", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("samDesired", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(RegKey, OpenKey)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const char* subKey = args.PickString();
	REGSAM samDesired = args.IsValid()? args.PickNumber<REGSAM>() : KEY_ALL_ACCESS;
	// Function body
	HKEY hKey = valueThis.GetRegKey().GetHKEY();
	HKEY hKeyResult;
	DWORD dwErrCode = ::RegOpenKeyEx(hKey, OAL::ToNativeString(subKey).c_str(), 0, samDesired, &hKeyResult);
	if (dwErrCode != ERROR_SUCCESS) {
		//SetError(sig, dwErrCode);
		return Value::nil();
	}
	return new Value_RegKey(new RegKey(hKeyResult));
}

// mswin.RegKey#DeleteKey(subKey as String)
Gurax_DeclareMethod(RegKey, DeleteKey)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("subKey", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(RegKey, DeleteKey)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const char* subKey = args.PickString();
	// Function body
	HKEY hKey = valueThis.GetRegKey().GetHKEY();
	DWORD dwErrCode = ::RegDeleteKey(hKey, OAL::ToNativeString(subKey).c_str());
	if (dwErrCode != ERROR_SUCCESS) {
		//SetError(sig, dwErrCode);
		return Value::nil();
	}
	return Value::nil();
}

// mswin.RegKey#EnumKey(samDesired? as Number)
Gurax_DeclareMethod(RegKey, EnumKey)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("samDesired", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(RegKey, EnumKey)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	REGSAM samDesired = args.IsValid()? args.PickNumber<REGSAM>() : KEY_ALL_ACCESS;
	// Function body
	
	return Value::nil();
}

// mswin.RegKey#SetValue(num1 as Number, num2 as Number)
Gurax_DeclareMethod(RegKey, SetValue)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(RegKey, SetValue)
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

// mswin.RegKey#DeleteValue(num1 as Number, num2 as Number)
Gurax_DeclareMethod(RegKey, DeleteValue)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(RegKey, DeleteValue)
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

// mswin.RegKey#QueryValue(num1 as Number, num2 as Number)
Gurax_DeclareMethod(RegKey, QueryValue)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(RegKey, QueryValue)
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

// mswin.RegKey#EnumValue(num1 as Number, num2 as Number)
Gurax_DeclareMethod(RegKey, EnumValue)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(RegKey, EnumValue)
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
// mswin.RegKey#propSkeleton
Gurax_DeclareProperty_R(RegKey, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(RegKey, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_RegKey
//------------------------------------------------------------------------------
VType_RegKey VTYPE_RegKey("RegKey");

void VType_RegKey::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	//Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(RegKey));
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(RegKey, CreateKey));
	Assign(Gurax_CreateMethod(RegKey, OpenKey));
	Assign(Gurax_CreateMethod(RegKey, DeleteKey));
	Assign(Gurax_CreateMethod(RegKey, EnumKey));
	Assign(Gurax_CreateMethod(RegKey, SetValue));
	Assign(Gurax_CreateMethod(RegKey, DeleteValue));
	Assign(Gurax_CreateMethod(RegKey, QueryValue));
	Assign(Gurax_CreateMethod(RegKey, EnumValue));
	// Assignment of property
	Assign(Gurax_CreateProperty(RegKey, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_RegKey
//------------------------------------------------------------------------------
VType& Value_RegKey::vtype = VTYPE_RegKey;

String Value_RegKey::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetRegKey().ToString(ss));
}

Gurax_EndModuleScope(mswin)
