//==============================================================================
// VType_Directory.cpp
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
// Implementation of constructor
//------------------------------------------------------------------------------
// Directory(pathName:string) {block?}
Gurax_DeclareConstructor(Directory)
{
	Declare(VTYPE_DateTime, Flag::Map);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Stream` instance.");
}

Gurax_ImplementConstructor(Directory)
{
	// Arguments
	ArgPicker args(argument);
	const char* pathName = args.PickString();
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<Directory> pDirectory(Directory::Open(pathName));
	if (!pDirectory) return Value::nil();
	return argument.ReturnValue(processor, new Value_Directory(pDirectory.release()));
}

//------------------------------------------------------------------------------
// VType_Directory
//------------------------------------------------------------------------------
VType_Directory VTYPE_Directory("Directory");

void VType_Directory::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Directory));
}

Value* VType_Directory::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	if (value.IsType(VTYPE_String)) {
		const char* pathName = Value_String::GetString(value);
		RefPtr<Directory> pDirectory(Directory::Open(pathName));
		if (!pDirectory) return nullptr;
		return new Value_Directory(pDirectory.release());
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Value_Directory
//------------------------------------------------------------------------------
VType& Value_Directory::vtype = VTYPE_Directory;

String Value_Directory::ToStringDigest(const StringStyle& ss) const
{
	String str;
	str += "<directory:";
	str += GetDirectory().ToString(ss);
	str += ">";
	return str;
}

String Value_Directory::ToStringDetail(const StringStyle& ss) const
{
	return ToStringDigest(ss);
}

}
