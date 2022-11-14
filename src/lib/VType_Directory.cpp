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

${help.ComposePropertyHelp(Directory, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(Directory, `en)}

${help.ComposeMethodHelp(Directory, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Directory(pathName:string) {block?}
Gurax_DeclareConstructor(Directory)
{
	Declare(VTYPE_DateTime, Flag::Map);
	DeclareArg("pathName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates a `Stream` instance.
)**");
}

Gurax_ImplementConstructor(Directory)
{
	// Arguments
	ArgPicker args(argument);
	const char* pathName = args.PickString();
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<Directory> pDirectory(PathMgr::OpenDirectory(pathName));
	if (!pDirectory) {
		Error::IssueIfFirst(ErrorType::PathError, "failed to open the path: %s", pathName);
		return Value::nil();
	}
	return argument.ReturnValue(processor, new Value_Directory(pDirectory.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// Directory#Open(pathName:String, mode?:String, codec?:Codec) {block?}
Gurax_DeclareMethod(Directory, Open)
{
	Declare(VTYPE_Directory, Flag::None);
	DeclareArg("pathName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("codec", VTYPE_Codec, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates a `Stream` instance that reads a content stored under the target Directory.
)**");
}

Gurax_ImplementMethod(Directory, Open)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const char* pathName = args.PickString();
	Stream::OpenFlags openFlags = args.IsValid()?
		Stream::ModeToOpenFlags(args.PickString()) : Stream::OpenFlag::None;
	const Codec* pCodec = args.IsValid()? &Value_Codec::GetCodec(args.PickValue()) : nullptr;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	const char* p = pathName;
	RefPtr<Directory> pDirectory(valueThis.GetDirectory().SearchInTree(&p));
	if (!pDirectory || *p != '\0') {
		Error::IssueIfFirst(ErrorType::PathError, "specified path is not found: %s", pathName);
		return Value::nil();
	}
	RefPtr<Stream> pStream(pDirectory->OpenStream(openFlags));
	if (!pStream) return Value::nil();
	if (pCodec) pStream->SetCodec(pCodec->Reference());
	return argument.ReturnValue(processor, new Value_Stream(pStream.release()));
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// Directory#name
Gurax_DeclareProperty_R(Directory, name)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
The name of the directory.
)**");
}

Gurax_ImplementPropertyGetter(Directory, name)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetDirectory().GetName());
}

// Directory#parent
Gurax_DeclareProperty_R(Directory, parent)
{
	Declare(VTYPE_Directory, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
The parent of the directory.
)**");
}

Gurax_ImplementPropertyGetter(Directory, parent)
{
	auto& valueThis = GetValueThis(valueTarget);
	const Directory* pDirectoryParent = valueThis.GetDirectory().GetDirectoryParent();
	if (!pDirectoryParent) return Value::nil();
	return new Value_Directory(pDirectoryParent->Reference());
}

// Directory#type
Gurax_DeclareProperty_R(Directory, type)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
A symbol that represents the directory type:
- `` `item` .. file or data entry
- `` `container` .. directory or folder
- `` `boundary` .. boundary container
- `` `root` .. root container
)**");
}

Gurax_ImplementPropertyGetter(Directory, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Symbol(Directory::TypeToSymbol(valueThis.GetDirectory().GetType()));
}

//------------------------------------------------------------------------------
// VType_Directory
//------------------------------------------------------------------------------
VType_Directory VTYPE_Directory("Directory");

void VType_Directory::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Directory));
	// Assignment of method
	Assign(Gurax_CreateMethod(Directory, Open));
	// Assignment of property
	Assign(Gurax_CreateProperty(Directory, name));
	Assign(Gurax_CreateProperty(Directory, parent));
	Assign(Gurax_CreateProperty(Directory, type));
}

Value* VType_Directory::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	if (value.IsType(VTYPE_String)) {
		const char* pathName = Value_String::GetString(value);
		RefPtr<Directory> pDirectory(PathMgr::OpenDirectory((*pathName == '\0')? "." : pathName));
		if (!pDirectory) return nullptr;
		return new Value_Directory(pDirectory.release());
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Value_Directory
//------------------------------------------------------------------------------
VType& Value_Directory::vtype = VTYPE_Directory;

String Value_Directory::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetDirectory().ToString(ss));;
}

}
