//==============================================================================
// module-fs.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(fs)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// fs.ChangeDir(pathName:String) {block?}
Gurax_DeclareFunction(ChangeDir)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("pathName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
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
#if 0
	Signal &sig = env.GetSignal();
	if (arg.IsBlockSpecified()) {
		String pathNameOrg = OAL::GetCurDir();
		if (!OAL::ChangeCurDir(arg.GetString(0))) {
			sig.SetError(ERR_IOError, "failed to change current directory");
			return Value::Nil;
		}
		const Expr_Block *pExprBlock = arg.GetBlockCooked(env);
		if (sig.IsSignalled()) return Value::Nil;
		Value rtn = pExprBlock->Exec(env);
		OAL::ChangeCurDir(pathNameOrg.c_str());
		return rtn;
	} else if (!OAL::ChangeCurDir(arg.GetString(0))) {
		sig.SetError(ERR_IOError, "failed to change current directory");
		return Value::Nil;
	}
	return Value::Nil;
#endif
	return Value::nil();
}

// fs.ChangeMode(mode, pathname:string):map:void:[follow_link]
Gurax_DeclareFunction(ChangeMode)
{
	Declare(VTYPE_Nil, Flag::Map);
	DeclareArg("mode", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pathname", VTYPE_String, ArgOccur::Once, ArgFlag::None);
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
#if 0
	Signal &sig = env.GetSignal();
	bool rtn = false;
	bool followLinkFlag = arg.IsSet(Gurax_Symbol(follow_link));
	if (arg.Is_string(0)) {
		rtn = OAL::ChangeMode(arg.GetString(0), arg.GetString(1), followLinkFlag);
	} else if (arg.Is_number(0)) {
		rtn = OAL::ChangeMode(arg.GetInt(0), arg.GetString(1), followLinkFlag);
	} else {
		sig.SetError(ERR_ValueError, "number or string must be specified as mode");
		return Value::Nil;
	}
	if (!rtn) {
		sig.SetError(ERR_IOError, "failed to change access mode");
	}
#endif
	return Value::nil();
}

// fs.Copy(src:string, dst:string):map:void:[overwrite]
Gurax_DeclareFunction(Copy)
{
	Declare(VTYPE_Nil, Flag::Map);
	DeclareArg("src", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dst", VTYPE_String, ArgOccur::Once, ArgFlag::None);
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
#if 0
	Signal &sig = env.GetSignal();
	bool failIfExistsFlag = !arg.IsSet(Gurax_Symbol(overwrite));
	bool followLinkFlag = arg.IsSet(Gurax_Symbol(follow_link));
	if (!OAL::Copy(arg.GetString(0), arg.GetString(1), failIfExistsFlag, followLinkFlag)) {
		sig.SetError(ERR_IOError, "failed to copy a file %s", arg.GetString(0));
	}
#endif
	return Value::nil();
}

// fs.CopyDir(src:string, dst:string):map:void[:tree]
Gurax_DeclareFunction(CopyDir)
{
	Declare(VTYPE_Nil, Flag::Map);
	DeclareArg("src", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dst", VTYPE_String, ArgOccur::Once, ArgFlag::None);
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
#if 0
	Signal &sig = env.GetSignal();
	const char *dirNameSrc = arg.GetString(0);
	const char *dirNameDst = arg.GetString(1);
	bool rtn = arg.IsSet(Gurax_Symbol(tree))?
				OAL::CopyDirTree(dirNameSrc, dirNameDst) :
				OAL::CopyDir(dirNameSrc, dirNameDst);
	if (!rtn) {
		sig.SetError(ERR_IOError, "failed to copies a directory '%s' to '%s'",
													dirNameSrc, dirNameDst);
	}
#endif
	return Value::nil();
}

// fs.CreateDir(pathname:string):map:void[:tree]
Gurax_DeclareFunction(CreateDir)
{
	Declare(VTYPE_Nil, Flag::Map);
	DeclareArg("pathname", VTYPE_String, ArgOccur::Once, ArgFlag::None);
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
#if 0
	Signal &sig = env.GetSignal();
	const char *pathName = arg.GetString(0);
	bool rtn = arg.IsSet(Gurax_Symbol(tree))?
				OAL::CreateDirTree(pathName) :
				OAL::CreateDir(pathName);
	if (!rtn) {
		sig.SetError(ERR_IOError, "failed to create a directory %s", pathName);
	}
	return Value::Nil;
#endif
	return Value::nil();
}

// fs.GetCurDir()
Gurax_DeclareFunction(GetCurDir)
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns the current working directory.");
}

Gurax_ImplementFunction(GetCurDir)
{
#if 0
	String pathName = OAL::GetCurDir();
	return Value(pathName);
#endif
	return Value::nil();
}

// fs.Remove(pathname:string):map:void
Gurax_DeclareFunction(Remove)
{
	Declare(VTYPE_Nil, Flag::Map);
	DeclareArg("pathname", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Removes a file from the file system.");
}

Gurax_ImplementFunction(Remove)
{
#if 0
	Signal &sig = env.GetSignal();
	if (!OAL::Remove(arg.GetString(0))) {
		sig.SetError(ERR_IOError, "failed to remove a file");
	}
	return Value::Nil;
#endif
	return Value::nil();
}

// fs.Rename(src:string, dst:string):map:void
Gurax_DeclareFunction(Rename)
{
	Declare(VTYPE_Nil, Flag::Map);
	DeclareArg("src", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dst", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Renames a file or directory.");
}

Gurax_ImplementFunction(Rename)
{
#if 0
	Signal &sig = env.GetSignal();
	if (!OAL::Rename(arg.GetString(0), arg.GetString(1))) {
		sig.SetError(ERR_IOError, "failed to rename a file or directory");
	}
	return Value::Nil;
#endif
	return Value::nil();
}

// fs.RemoveDir(pathname:string):map:void[:tree]
Gurax_DeclareFunction(RemoveDir)
{
	Declare(VTYPE_Nil, Flag::Map);
	DeclareArg("pathname", VTYPE_String, ArgOccur::Once, ArgFlag::None);
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
#if 0
	Signal &sig = env.GetSignal();
	const char *pathName = arg.GetString(0);
	bool rtn = arg.IsSet(Gurax_Symbol(tree))?
		OAL::RemoveDirTree(pathName) : OAL::RemoveDir(pathName);
	if (!rtn) {
		sig.SetError(ERR_IOError, "failed to remove a directory %s", pathName);
	}
	return Value::Nil;
#endif
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
	Assign(Gurax_CreateFunction(Rename));
	Assign(Gurax_CreateFunction(RemoveDir));
	// Assignment of path manager
	Basement::Inst.AssignPathMgr(new PathMgrEx());
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(fs)
