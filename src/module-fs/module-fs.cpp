//==============================================================================
// module-fs.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(fs)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// fs.ChangeDir(dirName:String) {block?}
Gurax_DeclareFunction(ChangeDir)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("dirName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Changes the current working directory to `pathname`.

The block would be evaluated if specified, and the working directory would be changed
only during that evaluation period.
)**");
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementFunction(ChangeDir)
{
	// Arguments
	ArgPicker args(argument);
	const char* dirName = args.PickString();
	const Expr_Block* pExprOfBlock = argument.GetExprOfBlock();
	// Function body
	const char* errMsg = "failed to change current directory";
	if (pExprOfBlock) {
		String dirNameOrg = OAL::GetCurDir();
		if (!OAL::ChangeDir(dirName)) {
			Error::Issue(ErrorType::IOError, errMsg);
			return Value::nil();
		}
		RefPtr<Value> pValue(pExprOfBlock->Eval(processor));
		if (!OAL::ChangeDir(dirNameOrg.c_str())) {
			Error::Issue(ErrorType::IOError, errMsg);
			return Value::nil();
		}
		return pValue.release();
	} else {
		if (!OAL::ChangeDir(dirName)) {
			Error::Issue(ErrorType::IOError, errMsg);
		}
		return Value::nil();
	}
}

// fs.ChangeMode(pathname:String, mode):map:void:[followLink]
Gurax_DeclareFunction(ChangeMode)
{
	Declare(VTYPE_Nil, Flag::Map);
	DeclareArg("pathName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(followLink));
	AddHelp(Gurax_Symbol(en), u8R"**(
Changes the access mode of a file specified by `pathname`.

There are two formats to specify the mode: one is by a number, and another in a string.

When specified in a number, following bits are associated with access permissions:

- `b8 b7 b6` .. Read, write and executable permissions for owners
- `b5 b4 b3` .. Read, write and executable permissions for groups
- `b2 b1 b0` .. Read, write and executable permissions for others

When set to one, each permission is validated.

When specified in a string, it accepts a permission directive
in a format of following regular expression
    [ugoa]+([-+=][rwx]+)+
It starts with characters that represent target which permissions are modified as described below:

- `u` .. owners
- `g` .. groups
- `o` .. others
- `a` .. all users

Then, follows an operation:
- `-` .. remove
- `+` .. append
- `=` .. set

At last, permission attributes are specified as below:

- `r` .. read permission
- `w` .. write permission
- `x` .. executable permission

If the modification target is a link file, each platform would have different result:

- Linux .. Modifies permissions of the link file itself.
           Specifying `:followLink` attribute would modify permsisions of the target file\n instead.
- MacOS .. Modifies permissions of the target file. Attribute `:followLink` has no effect.
- Windows .. Modifies permissions of the link file. Attribute `:followLink` has no effect.
)**");
}

Gurax_ImplementFunction(ChangeMode)
{
	// Arguments
	ArgPicker args(argument);
	const char* pathName = args.PickString();
	const Value& valueMode = args.PickValue();
	bool followLinkFlag = argument.IsSet(Gurax_Symbol(followLink));
	// Function body
	bool rtn = false;
	if (valueMode.IsType(VTYPE_String)) {
		const char* mode = Value_String::GetString(valueMode);
		rtn = OAL::ChangeMode(pathName, mode, followLinkFlag);
	} else if (valueMode.IsType(VTYPE_Number)) {
		Int mode = Value_Number::GetNumberNonNeg<Int>(valueMode);
		if (Error::IsIssued()) return Value::nil();
		rtn = OAL::ChangeMode(pathName, mode, followLinkFlag);
	} else {
		Error::Issue(ErrorType::ValueError, "Number or String value must be specified as mode");
		return Value::nil();
	}
	if (!rtn) {
		Error::Issue(ErrorType::IOError, "failed to change access mode");
	}
	return Value::nil();
}

// fs.Copy(pathNameSrc:String, pathNameDst:String):map:void:[overwrite]
Gurax_DeclareFunction(Copy)
{
	Declare(VTYPE_Nil, Flag::Map);
	DeclareArg("pathNameSrc", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pathNameDst", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(overwrite));
	//DeclareAttrOpt(Gurax_Symbol(followLink));
	AddHelp(Gurax_Symbol(en), u8R"**(
Copies a file.

An argument `src` needs to specify a path name of a file that is to be copied
while `dst` can specify a path name of either a file or a directory.
If `dst` is a directory, the file would be copied into that.
Otherwise, it would create a copy of `src` that has a name specified by `dst`.

If a destination file already exists, an error occurs.
Specifying an attribute `:overwrite` would overwrite an existing one.
)**");
}

Gurax_ImplementFunction(Copy)
{
	// Arguments
	ArgPicker args(argument);
	const char* pathNameSrc = args.PickString();
	const char* pathNameDst = args.PickString();
	bool failIfExistsFlag = !argument.IsSet(Gurax_Symbol(overwrite));
	bool followLinkFlag = argument.IsSet(Gurax_Symbol(followLink));
	// Function body
	if (!OAL::Copy(pathNameSrc, pathNameDst, failIfExistsFlag, followLinkFlag)) {
		Error::Issue(ErrorType::IOError, "failed to copy a file");
	}
	return Value::nil();
}

// fs.CopyDir(dirNameSrc:string, dirNameDst:string):map:void[:tree]
Gurax_DeclareFunction(CopyDir)
{
	Declare(VTYPE_Nil, Flag::Map);
	DeclareArg("dirNameSrc", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dirNameDst", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(tree));
	AddHelp(Gurax_Symbol(en), u8R"**(
Copies a directory.

Arguments `src` and `dst` specify source directory and destination directory respectively.
In default, sub directories are not copied.`
Specifying `:tree` attribute would copy all the sub directories in the source.
)**");
}

Gurax_ImplementFunction(CopyDir)
{
	// Arguments
	ArgPicker args(argument);
	const char* dirNameSrc = args.PickString();
	const char* dirNameDst = args.PickString();
	bool treeFlag = argument.IsSet(Gurax_Symbol(tree));
	// Function body
	if (!(treeFlag? OAL::CopyDirTree(dirNameSrc, dirNameDst) : OAL::CopyDir(dirNameSrc, dirNameDst))) {
		Error::Issue(ErrorType::IOError, "failed to copy a directory");
	}
	return Value::nil();
}

// fs.CreateDir(dirName:string):map:void[:tree]
Gurax_DeclareFunction(CreateDir)
{
	Declare(VTYPE_Nil, Flag::Map);
	DeclareArg("dirName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(tree));
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates a directory.

If `pathname` consists of multiple sub directories and some of them still doesn't exist,
an error occurs. Specifying `:tree` attribute would create such directories.
)**");
}

Gurax_ImplementFunction(CreateDir)
{
	// Arguments
	ArgPicker args(argument);
	const char* dirName = args.PickString();
	bool treeFlag = argument.IsSet(Gurax_Symbol(tree));
	// Function body
	if (!(treeFlag? OAL::CreateDirTree(dirName) : OAL::CreateDir(dirName))) {
		Error::Issue(ErrorType::IOError, "failed to create a directory");
	}
	return Value::nil();
}

// fs.CreateLink(pathNameSrc:String, pathNameDst:String):map:void
Gurax_DeclareFunction(CreateLink)
{
	Declare(VTYPE_Nil, Flag::Map);
	DeclareArg("pathNameSrc", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pathNameDst", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Copies a symbolic link.
)**");
}

Gurax_ImplementFunction(CreateLink)
{
	// Arguments
	ArgPicker args(argument);
	const char* pathNameSrc = args.PickString();
	const char* pathNameDst = args.PickString();
	// Function body
	if (!OAL::CreateLink(pathNameSrc, pathNameDst)) {
		Error::Issue(ErrorType::IOError, "failed to create a link");
	}
	return Value::nil();
}

// fs.Exists(pathName:String):map
Gurax_DeclareFunction(Exists)
{
	Declare(VTYPE_Bool, Flag::Map);
	DeclareArg("pathName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Returns true if the specified file exists in a file system.
)**");
}

Gurax_ImplementFunction(Exists)
{
	// Arguments
	ArgPicker args(argument);
	const char* pathName = args.PickString();
	// Function body
	OAL::FileType fileType = OAL::GetFileType(pathName);
	return new Value_Bool(fileType != OAL::FileType::None);
}

// fs.GetCurDir()
Gurax_DeclareFunction(GetCurDir)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Returns the current working directory.
)**");
}

Gurax_ImplementFunction(GetCurDir)
{
	// Function body
	return new Value_String(OAL::GetCurDir());
}

// fs.Remove(pathName:String):map:void
Gurax_DeclareFunction(Remove)
{
	Declare(VTYPE_Nil, Flag::Map);
	DeclareArg("pathName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Removes a file from the file system.
)**");
}

Gurax_ImplementFunction(Remove)
{
	// Arguments
	ArgPicker args(argument);
	const char* pathName = args.PickString();
	// Function body
	if (OAL::GetFileType(pathName) == OAL::FileType::None) return Value::nil();
	if (!OAL::Remove(pathName)) {
		Error::Issue(ErrorType::IOError, "failed to remove a file");
	}
	return Value::nil();
}

// fs.RemoveDir(dirName:String):map:void[:tree]
Gurax_DeclareFunction(RemoveDir)
{
	Declare(VTYPE_Nil, Flag::Map);
	DeclareArg("dirName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(tree));
	AddHelp(Gurax_Symbol(en), u8R"**(
Removes a directory.

If the directory contains sub directories, an error occurs.
Specifying `:tree` attribute would delete such a directory.
)**");
}

Gurax_ImplementFunction(RemoveDir)
{
	// Arguments
	ArgPicker args(argument);
	const char* dirName = args.PickString();
	bool treeFlag = argument.IsSet(Gurax_Symbol(tree));
	// Function body
	if (!(treeFlag? OAL::RemoveDirTree(dirName) : OAL::RemoveDir(dirName))) {
		Error::Issue(ErrorType::IOError, "failed to remove a directory");
	}
	return Value::nil();
}

// fs.Rename(pathNameSrc:string, pathNameDst:string):map:void
Gurax_DeclareFunction(Rename)
{
	Declare(VTYPE_Nil, Flag::Map);
	DeclareArg("pathNameSrc", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pathNameDst", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Renames a file or directory.
)**");
}

Gurax_ImplementFunction(Rename)
{
	// Arguments
	ArgPicker args(argument);
	const char* pathNameSrc = args.PickString();
	const char* pathNameDst = args.PickString();
	// Function body
	if (!OAL::Rename(pathNameSrc, pathNameDst)) {
		Error::Issue(ErrorType::IOError, "failed to copy a file");
	}
	return Value::nil();
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
	// Assignment of VType
	Assign(VTYPE_StatEx);
	// Assignment of function
	Assign(Gurax_CreateFunction(ChangeDir));
	Assign(Gurax_CreateFunction(ChangeMode));
	Assign(Gurax_CreateFunction(Copy));
	Assign(Gurax_CreateFunction(CopyDir));
	Assign(Gurax_CreateFunction(CreateDir));
	Assign(Gurax_CreateFunction(CreateLink));
	Assign(Gurax_CreateFunction(Exists));
	Assign(Gurax_CreateFunction(GetCurDir));
	Assign(Gurax_CreateFunction(Remove));
	Assign(Gurax_CreateFunction(RemoveDir));
	Assign(Gurax_CreateFunction(Rename));
	// Assignment of path manager
	PathMgr::Assign(new PathMgrEx());
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(fs)
