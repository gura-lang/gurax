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
	AddHelp(
		Gurax_Symbol(en),
		"Changes the current working directory to `pathname`.\n"
		"\n"
		"The block would be evaluated if specified, and the working directory would be changed\n"
		"only during that evaluation period.\n");
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
		RefPtr<Argument> pArgumentSub(Argument::CreateForBlockCall(*pExprOfBlock));
		RefPtr<Value> pValue(processor.EvalExpr(*pExprOfBlock, *pArgumentSub));
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

// fs.ChangeMode(pathname:String, mode):map:void:[follow_link]
Gurax_DeclareFunction(ChangeMode)
{
	Declare(VTYPE_Nil, Flag::Map);
	DeclareArg("pathName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(follow_link));
	AddHelp(
		Gurax_Symbol(en),
		"Changes the access mode of a file specified by `pathname`.\n"
		"\n"
		"There are two formats to specify the mode: one is by a number, and another in a string.\n"
		"\n"
		"When specified in a number, following bits are associated with access permissions:\n"
		"\n"
		"- `b8 b7 b6` .. Read, write and executable permissions for owners\n"
		"- `b5 b4 b3` .. Read, write and executable permissions for groups\n"
		"- `b2 b1 b0` .. Read, write and executable permissions for others\n"
		"\n"
		"When set to one, each permission is validated.\n"
		"\n"
		"When specified in a string, it accepts a permission directive\n"
		"in a format of following regular expression\n"
		"    [ugoa]+([-+=][rwx]+)+\n"
		"It starts with characters that represent target which permissions are modified as described below:\n"
		"\n"
		"- `u` .. owners\n"
		"- `g` .. groups\n"
		"- `o` .. others\n"
		"- `a` .. all users\n"
		"\n"
		"Then, follows an operation:\n"
		"- `-` .. remove\n"
		"- `+` .. append\n"
		"- `=` .. set\n"
		"\n"
		"At last, permission attributes are specified as below:\n"
		"\n"
		"- `r` .. read permission\n"
		"- `w` .. write permission\n"
		"- `x` .. executable permission\n"
		"\n"
		"If the modification target is a link file, each platform would have different result:\n"
		"\n"
		"- Linux .. Modifies permissions of the link file itself.\n"
		"           Specifying `:follow_link` attribute would modify permsisions of the target file\n instead.\n"
		"- MacOS .. Modifies permissions of the target file. Attribute `:follow_link` has no effect.\n"
		"- Windows .. Modifies permissions of the link file. Attribute `:follow_link` has no effect.\n");
}

Gurax_ImplementFunction(ChangeMode)
{
	// Arguments
	ArgPicker args(argument);
	const char* pathName = args.PickString();
	const Value& valueMode = args.PickValue();
	bool followLinkFlag = argument.IsSet(Gurax_Symbol(follow_link));
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
	//DeclareAttrOpt(Gurax_Symbol(follow_link));
	AddHelp(
		Gurax_Symbol(en),
		"Copies a file.\n"
		"\n"
		"An argument `src` needs to specify a path name of a file that is to be copied\n"
		"while `dst` can specify a path name of either a file or a directory.\n"
		"If `dst` is a directory, the file would be copied into that.\n"
		"Otherwise, it would create a copy of `src` that has a name specified by `dst`.\n"
		"\n"
		"If a destination file already exists, an error occurs.\n"
		"Specifying an attribute `:overwrite` would overwrite an existing one.\n");
}

Gurax_ImplementFunction(Copy)
{
	// Arguments
	ArgPicker args(argument);
	const char* pathNameSrc = args.PickString();
	const char* pathNameDst = args.PickString();
	bool failIfExistsFlag = !argument.IsSet(Gurax_Symbol(overwrite));
	bool followLinkFlag = argument.IsSet(Gurax_Symbol(follow_link));
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
	AddHelp(
		Gurax_Symbol(en),
		"Copies a directory.\n"
		"\n"
		"Arguments `src` and `dst` specify source directory and destination directory respectively.\n"
		"In default, sub directories are not copied.`\n"
		"Specifying `:tree` attribute would copy all the sub directories in the source.\n");
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
	AddHelp(
		Gurax_Symbol(en),
		"Creates a directory.\n"
		"\n"
		"If `pathname` consists of multiple sub directories and some of them still doesn't exist,\n"
		"an error occurs. Specifying `:tree` attribute would create such directories.\n");
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

// fs.GetCurDir()
Gurax_DeclareFunction(GetCurDir)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns the current working directory.");
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
	AddHelp(
		Gurax_Symbol(en),
		"Removes a file from the file system.");
}

Gurax_ImplementFunction(Remove)
{
	// Arguments
	ArgPicker args(argument);
	const char* pathName = args.PickString();
	// Function body
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
	AddHelp(
		Gurax_Symbol(en),
		"Removes a directory.\n"
		"\n"
		"If the directory contains sub directories, an error occurs.\n"
		"Specifying `:tree` attribute would delete such a directory.\n");
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
	AddHelp(
		Gurax_Symbol(en),
		"Renames a file or directory.");
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
	return true;
}

Gurax_ModulePrepare()
{
	Frame& frame = GetFrame();
	// Prepare VType
	VTYPE_Stat.Prepare(frame);
	// Assignment of function
	Assign(Gurax_CreateFunction(ChangeDir));
	Assign(Gurax_CreateFunction(ChangeMode));
	Assign(Gurax_CreateFunction(Copy));
	Assign(Gurax_CreateFunction(CopyDir));
	Assign(Gurax_CreateFunction(CreateDir));
	Assign(Gurax_CreateFunction(GetCurDir));
	Assign(Gurax_CreateFunction(Remove));
	Assign(Gurax_CreateFunction(RemoveDir));
	Assign(Gurax_CreateFunction(Rename));
	// Assignment of path manager
	Basement::Inst.AssignPathMgr(new PathMgrEx());
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(fs)
