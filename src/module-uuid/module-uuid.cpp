//==============================================================================
// module-uuid.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(uuid)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// uuid.Generate():[upper]
Gurax_DeclareFunction(Generate)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(upper));
	AddHelp(Gurax_Symbol(en), u8R"**(
Generates a Universal Unique Identifier (UUID). In default, results are output in
lower-case characters. Specifying :upper would generates it in upper-case characters.
)**");
}

Gurax_ImplementFunction(Generate)
{
	// Arguments
	ArgPicker args(argument);
	// Function body
	bool upperFlag = argument.IsSet(Gurax_Symbol(upper));
	char str[64];
#ifdef GURAX_ON_MSWIN
	const char *format = upperFlag?
		"%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X" :
		"%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x";
	GUID guid;
	::CoCreateGuid(&guid);
	::sprintf(str, format,
		guid.Data1, guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1],
		guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
#else
	const char *format = upperFlag?
		"%02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X" :
		"%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x";
	uuid_t guid;
	::uuid_generate(guid);
	::sprintf(str, format,
		guid[0], guid[1], guid[2], guid[3], guid[4], guid[5], guid[6], guid[7],
		guid[8], guid[9], guid[10], guid[11], guid[12], guid[13], guid[14], guid[15]);
#endif
	return new Value_String(str);
}

//------------------------------------------------------------------------------
// Entries
//------------------------------------------------------------------------------
Gurax_ModuleValidate()
{
	return Version::CheckCoreVersion(GURAX_VERSION, nullptr);
}

Gurax_ModulePrepare()
{
	// Assignment of function
	Assign(Gurax_CreateFunction(Generate));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(uuid)
