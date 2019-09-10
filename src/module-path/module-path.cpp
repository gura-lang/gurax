//==============================================================================
// module-path.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(path)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// path.AbsName(pathName:string):map:[uri]
Gurax_DeclareFunction(AbsName)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("pathName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(uri));
	AddHelp(
		Gurax_Symbol(en),
		"Returns an absolute path name of the given name.");
}

Gurax_ImplementFunction(AbsName)
{
	// Arguments
	ArgPicker args(argument);
	PathName pathName(args.PickString());
	// Function body
	if (argument.IsSet(Gurax_Symbol(uri))) pathName.SetSepUNIX();
	return new Value_String(pathName.MakeAbsName());
}

// path.BaseName(pathName:string):map
Gurax_DeclareFunction(BaseName)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("pathName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en), 
		"Removes a suffix part of a path name.\n"
		"This is complementary to `path.ExtName()`.\n"
		"\n"
		"Example:\n"
		"```\n"
		"path.BaseName('/foo/bar/file.txt')  # Returns '/foo/bar/file'\n"
		"```\n");
}

Gurax_ImplementFunction(BaseName)
{
	// Arguments
	ArgPicker args(argument);
	PathName pathName(args.PickString());
	// Function body
	return new Value_String(pathName.ExtractBaseName());
}

// path.BottomName(pathName:string):map
Gurax_DeclareFunction(BottomName)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("pathName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en), 
		"Returns the last part of a path name (cf. `path.FileName()`)."
		"This is complementary to `path.HeadName()`.\n"
		"\n"
		"Example:\n"
		"```\n"
		"path.BottomName('/foo/bar/file.txt')  # Returns 'file.txt'\n"
		"path.BottomName('/foo/bar/dir/')      # Returns 'dir'\n"
		"```\n");
}

Gurax_ImplementFunction(BottomName)
{
	// Arguments
	ArgPicker args(argument);
	PathName pathName(args.PickString());
	// Function body
	return new Value_String(pathName.ExtractBottomName());
}

// path.Dir(directory?:directory, pattern*:string):map:flat:[stat,file,dir,case,icase] {block?}
Gurax_DeclareFunction(Dir)
{
	Declare(VTYPE_Any, Flag::Map | Flag::Flat);
	DeclareArg("directory", VTYPE_Directory, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pattern", VTYPE_String, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	DeclareAttrOpt(Gurax_Symbol(stat));
	DeclareAttrOpt(Gurax_Symbol(file));
	DeclareAttrOpt(Gurax_Symbol(dir));
	DeclareAttrOpt(Gurax_Symbol(case_));
	DeclareAttrOpt(Gurax_Symbol(icase));
	AddHelp(
		Gurax_Symbol(en), 
		"Creates an iterator that lists item names in the specified directory.\n"
		"If pathname is omitted, the current directory shall be listed.\n"
		"\n"
		"Though the default sensitiveness of character cases during pattern matching depends on the target directory,\n"
		"it can be changed by attributes `:case` for case-sensitive and `:icase` for case-insensitive.\n");
}

Gurax_ImplementFunction(Dir)
{
#if 0
	bool addSepFlag = true;
	bool statFlag = arg.IsSet(Gurax_Symbol(stat));
	bool fileFlag = arg.IsSet(Gurax_Symbol(file)) || !arg.IsSet(Gurax_Symbol(dir));
	bool dirFlag = arg.IsSet(Gurax_Symbol(dir)) || !arg.IsSet(Gurax_Symbol(file));
	int depthMax = 0;
	StringList patterns;
	arg.GetList(1).ToStringList(patterns);
	AutoPtr<Directory> pDirectory;
	if (arg.Is_directory(0)) {
		pDirectory.reset(Directory::Reference(Object_directory::GetObject(arg, 0)->GetDirectory()));
	} else {
		pDirectory.reset(Directory::Open(env, "", PathMgr::NF_Signal));
		if (pDirectory.IsNull()) return Value::Nil;
	}
	bool ignoreCaseFlag = pDirectory->DoesIgnoreCase();
	if (arg.IsSet(Gurax_Symbol(case_))) ignoreCaseFlag = false;
	if (arg.IsSet(Gurax_Symbol(icase))) ignoreCaseFlag = true;
	Directory::Iterator_Walk *pIterator = new Directory::Iterator_Walk(
					addSepFlag, statFlag, ignoreCaseFlag, fileFlag, dirFlag,
					pDirectory.release(), depthMax, patterns);
	return ReturnIterator(env, arg, pIterator);
#endif
	return Value::nil();
}

// path.DirName(pathName:string):map
Gurax_DeclareFunction(DirName)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("pathName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en), 
		"Splits a pathname by a directory separator and returns a directory name part (cf. `path.HeadName()`)."
		"This is complementary to `path.FileName()`.\n"
		"\n"
		"Example:\n"
		"```\n"
		"path.DirName('/foo/bar/file.txt')  # Returns '/foo/bar/'\n"
		"path.DirName('/foo/bar/dir/')      # Returns '/foo/bar/dir/'\n"
		"```\n");
}

Gurax_ImplementFunction(DirName)
{
	// Arguments
	ArgPicker args(argument);
	PathName pathName(args.PickString());
	// Function body
	return new Value_String(pathName.ExtractDirName());
}

// path.Exists(pathName:string):map
Gurax_DeclareFunction(Exists)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("pathName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns true if the specified file exists in a file system.");
}

Gurax_ImplementFunction(Exists)
{
#if 0
	Signal &sig = env.GetSignal();
	bool existFlag = PathMgr::DoesExist(env, arg.GetString(0));
	if (sig.IsSignalled()) return Value::Nil;
	return Value(existFlag);
#endif
	return Value::nil();
}

// path.ExtName(pathName:string):map
Gurax_DeclareFunction(ExtName)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("pathName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en), 
		"Extracts a suffix part of a path name. It returns an empty string when the given pathname has no suffix.\n"
		"This is complementary to `path.BaseName()`.\n"
		"\n"
		"Example:\n"
		"```\n"
		"path.ExtName('/foo/bar/file.txt')  # Returns 'txt'\n"
		"path.ExtName('/foo/bar/file')      # Returns ''\n"
		"```\n");
}

Gurax_ImplementFunction(ExtName)
{
	// Arguments
	ArgPicker args(argument);
	PathName pathName(args.PickString());
	// Function body
	return new Value_String(pathName.ExtractExtName());
}

// path.FileName(pathName:string):map
Gurax_DeclareFunction(FileName)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("pathName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en), 
		"Splits a pathname by a directory separator and returns a file name part (cf. `path.Bottom()`).\n"
		"This is complementary to `path.DirName()`.\n"
		"\n"
		"Example:\n"
		"```\n"
		"path.FileName('/foo/bar/file.txt')  # Returns 'file.txt'\n"
		"path.FileName('/foo/bar/dir/')      # Returns ''\n"
		"```\n");
}

Gurax_ImplementFunction(FileName)
{
	// Arguments
	ArgPicker args(argument);
	PathName pathName(args.PickString());
	// Function body
	return new Value_String(pathName.ExtractFileName());
}

// path.Glob(pattern:string):map:flat:[stat,file,dir,case,icase] {block?}
Gurax_DeclareFunction(Glob)
{
	Declare(VTYPE_Any, Flag::Map | Flag::Flat);
	DeclareArg("pattern", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	DeclareAttrOpt(Gurax_Symbol(stat));
	DeclareAttrOpt(Gurax_Symbol(file));
	DeclareAttrOpt(Gurax_Symbol(dir));
	DeclareAttrOpt(Gurax_Symbol(case_));
	DeclareAttrOpt(Gurax_Symbol(icase));
	AddHelp(
		Gurax_Symbol(en), 
		"Creates an iterator for item names that match with a pattern supporting\n"
		"UNIX shell-style wild cards. In default, case of characters is distinguished.\n"
		"\n"
		"Though the default sensitiveness of character cases during pattern matching depends on the current platform,\n"
		"it can be changed by attributes `:case` for case-sensitive and `:icase` for case-insensitive.\n");
}

Gurax_ImplementFunction(Glob)
{
#if 0
	bool addSepFlag = true;
	bool statFlag = arg.IsSet(Gurax_Symbol(stat));
	bool ignoreCaseFlag = OAL::IgnoreCaseInPathNameFlag;
	bool fileFlag = arg.IsSet(Gurax_Symbol(file)) || !arg.IsSet(Gurax_Symbol(dir));
	bool dirFlag = arg.IsSet(Gurax_Symbol(dir)) || !arg.IsSet(Gurax_Symbol(file));
	if (arg.IsSet(Gurax_Symbol(case_))) ignoreCaseFlag = false;
	if (arg.IsSet(Gurax_Symbol(icase))) ignoreCaseFlag = true;
	AutoPtr<Directory::Iterator_Glob> pIterator(new Directory::Iterator_Glob(
					addSepFlag, statFlag, ignoreCaseFlag, fileFlag, dirFlag));
	if (!pIterator->Init(env, arg.GetString(0))) {
		return Value::Nil;
	}
	return ReturnIterator(env, arg, pIterator.release());
#endif
	return Value::nil();
}

// path.HeadName(pathName:string):map
Gurax_DeclareFunction(HeadName)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("pathName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en), 
		"Returns a path name after eliminating its bottom part (cf. `path.DirName()`)."
		"This is complementary to `path.BottomName()`.\n"
		"\n"
		"Example:\n"
		"```\n"
		"path.HeadName('/foo/bar/file.txt')  # Returns '/foo/bar/'\n"
		"path.HeadName('/foo/bar/dir/')      # Returns '/foo/bar/'\n"
		"```\n");
}

Gurax_ImplementFunction(HeadName)
{
	// Arguments
	ArgPicker args(argument);
	PathName pathName(args.PickString());
	// Function body
	return new Value_String(pathName.ExtractHeadName());
}

// path.Join(paths+:string):map:[uri]
Gurax_DeclareFunction(Join)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("paths", VTYPE_String, ArgOccur::OnceOrMore, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(uri));
	AddHelp(
		Gurax_Symbol(en),
		"Returns a path name that joins given strings with directory separators.");
}

Gurax_ImplementFunction(Join)
{
#if 0
	String str;
	const ValueList &valList = arg.GetList(0);
	char chSeparator = arg.IsSet(Gurax_Symbol(uri))? '/' : OAL::FileSeparator;
	foreach_const (ValueList, pValue, valList) {
		str = OAL::JoinPathName(chSeparator, str.c_str(), pValue->GetString());
	}
	return Value(str);
#endif
	// Arguments
	ArgPicker args(argument);
	const ValueList& valList = args.PickList();
	// Function body
	String str;
	char sep = argument.IsSet(Gurax_Symbol(uri))? PathName::SepUNIX : PathName::SepPlatform;
	for (const Value* pValue : valList) {
		str = PathName(str).SetSep(sep).JoinAfter(Value_String::GetString(*pValue));
	}
	return new Value_String(str);
}

// path.Match(pattern:string, name:string):map:[case,icase]
Gurax_DeclareFunction(Match)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("pattern", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(case_));
	DeclareAttrOpt(Gurax_Symbol(icase));
	AddHelp(
		Gurax_Symbol(en), 
		"Returns true if a name matches with a pattern that supports UNIX shell-style wild cards.\n"
		"\n"
		"Though the default sensitiveness of character cases depends on the current platform,\n"
		"it can be changed by attributes `:case` for case-sensitive and `:icase` for case-insensitive.\n");
}

Gurax_ImplementFunction(Match)
{
#if 0
	const char *pattern = arg.GetString(0);
	const char *name = arg.GetString(1);
	bool ignoreCaseFlag = OAL::IgnoreCaseInPathNameFlag;
	if (arg.IsSet(Gurax_Symbol(case_))) ignoreCaseFlag = false;
	if (arg.IsSet(Gurax_Symbol(icase))) ignoreCaseFlag = true;
	return Value(PathMgr::DoesMatchName(pattern, name, ignoreCaseFlag));
#endif
	return Value::nil();
}

// path.Regulate(name:string):map:[uri]
Gurax_DeclareFunction(Regulate)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(uri));
	AddHelp(
		Gurax_Symbol(en),
		"Removes redundant relative directories.");
}

Gurax_ImplementFunction(Regulate)
{
#if 0
	char chSeparator = arg.IsSet(Gurax_Symbol(uri))? '/' : OAL::FileSeparator;
	bool cutLastSepFlag = false;
	return Value(OAL::RegulatePathName(chSeparator, arg.GetString(0), cutLastSepFlag));
#endif
	return Value::nil();
}

// path.Split(pathName:string):map
Gurax_DeclareFunction(Split)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("pathName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en), 
		"Splits a pathname by a directory separator and returns a list containing\n"
		"a directory name as the first element and a base name as the second one.\n"
		"\n"
		"Calling this function has the same result as calling `path.DirName()` and `path.FileName()`.\n"
		"\n"
		"\n"
		"Example:\n"
		"```\n"
		"path.Split('/foo/bar/file.txt')         # Returns ['/foo/bar/', 'file.txt']\n"
		"path.Split('/foo/bar/dir/')             # Returns ['/foo/bar/dir/', '']\n"
		"```\n");
}

Gurax_ImplementFunction(Split)
{
	// Arguments
	ArgPicker args(argument);
	PathName pathName(args.PickString());
	// Function body
	String dirName, fileName;
	pathName.SplitFileName(&dirName, &fileName);
	return Value_List::Create(new Value_String(dirName), new Value_String(fileName));
}

// path.SplitBottom(pathName:string):map
Gurax_DeclareFunction(SplitBottom)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("pathName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en), 
		"Splits a pathname by a directory separator and returns a list containing\n"
		"a directory name as the first element and a base name as the second one.\n"
		"\n"
		"Calling this function has the same result as calling `path.HeadName()` and `path.BottomName()`.\n"
		"\n"
		"Example:\n"
		"```\n"
		"path.SplitBottom('/foo/bar/file.txt'):bottom  # Returns ['/foo/bar/', 'file.txt']\n"
		"path.SplitBottom('/foo/bar/dir/'):bottom      # Returns ['/foo/bar/', 'dir']\n"
		"```\n");
}

Gurax_ImplementFunction(SplitBottom)
{
	// Arguments
	ArgPicker args(argument);
	PathName pathName(args.PickString());
	// Function body
	String headName, bottomName;
	pathName.SplitBottomName(&headName, &bottomName);
	return Value_List::Create(new Value_String(headName), new Value_String(bottomName));
}

// path.SplitExt(pathName:string):map
Gurax_DeclareFunction(SplitExt)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("pathName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en), 
		"Splits a pathname by a dot character indicating a beginning of an extension\n"
		"and returns a list containing a path name without an extention\n"
		"and an extention part."
		"\n"
		"Calling this function has the same result as calling `path.BaseName()` and `path.ExtName()`.\n"
		"\n"
		"Example:\n"
		"```\n"
		"path.SplitExt('/foo/bar/file.txt'):bottom  # Returns ['/foo/bar/file', 'txt']\n"
		"path.SplitExt('/foo/bar/file'):bottom      # Returns ['/foo/bar/file', '']\n"
		"```\n");
}

Gurax_ImplementFunction(SplitExt)
{
	// Arguments
	ArgPicker args(argument);
	PathName pathName(args.PickString());
	// Function body
	String baseName, extName;
	pathName.SplitExtName(&baseName, &extName);
	return Value_List::Create(new Value_String(baseName), new Value_String(extName));
}

// path.Stat(directory:directory):map
Gurax_DeclareFunction(Stat)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("directory", VTYPE_Directory, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en), 
		"Returns a stat object associated with the specified item.");
}

Gurax_ImplementFunction(Stat)
{
#if 0
	Signal &sig = env.GetSignal();
	Directory *pDirectory = Object_directory::GetObject(arg, 0)->GetDirectory();
	AutoPtr<Object> pObj(pDirectory->GetStatObj(sig));
	if (sig.IsSignalled()) return Value::Nil;
	return Value(pObj.release());
#endif
	return Value::nil();
}

// path.Walk(directory?:directory, maxdepth?:number, pattern*:string):map:flat:[stat,file,dir,case,icase] {block?}
Gurax_DeclareFunction(Walk)
{
	Declare(VTYPE_Any, Flag::Map | Flag::Flat);
	DeclareArg("directory", VTYPE_Directory, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("maxdepth", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pattern", VTYPE_String, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	DeclareAttrOpt(Gurax_Symbol(stat));
	DeclareAttrOpt(Gurax_Symbol(file));
	DeclareAttrOpt(Gurax_Symbol(dir));
	DeclareAttrOpt(Gurax_Symbol(case_));
	DeclareAttrOpt(Gurax_Symbol(icase));
	AddHelp(
		Gurax_Symbol(en), 
		"Creates an iterator that recursively lists item names under the specified directory.\n"
		"If `directory` is omitted, search starts at the current directory.\n"
		"\n"
		"Though the default sensitiveness of character cases during pattern matching depends on the target directory,\n"
		"it can be changed by attributes `:case` for case-sensitive and `:icase` for case-insensitive.\n");
}

Gurax_ImplementFunction(Walk)
{
#if 0
	bool addSepFlag = true;
	bool statFlag = arg.IsSet(Gurax_Symbol(stat));
	bool fileFlag = arg.IsSet(Gurax_Symbol(file)) || !arg.IsSet(Gurax_Symbol(dir));
	bool dirFlag = arg.IsSet(Gurax_Symbol(dir)) || !arg.IsSet(Gurax_Symbol(file));
	int depthMax = arg.Is_number(1)? arg.GetInt(1) : -1;
	StringList patterns;
	arg.GetList(2).ToStringList(patterns);
	AutoPtr<Directory> pDirectory;
	if (arg.Is_directory(0)) {
		pDirectory.reset(Directory::Reference(Object_directory::GetObject(arg, 0)->GetDirectory()));
	} else {
		pDirectory.reset(Directory::Open(env, "", PathMgr::NF_Signal));
		if (pDirectory.IsNull()) return Value::Nil;
	}
	bool ignoreCaseFlag = pDirectory->DoesIgnoreCase();
	if (arg.IsSet(Gurax_Symbol(case_))) ignoreCaseFlag = false;
	if (arg.IsSet(Gurax_Symbol(icase))) ignoreCaseFlag = true;
	Directory::Iterator_Walk *pIterator = new Directory::Iterator_Walk(
					addSepFlag, statFlag, ignoreCaseFlag, fileFlag, dirFlag,
					pDirectory.release(), depthMax, patterns);
	return ReturnIterator(env, arg, pIterator);
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
	// Assignment of function
	Assign(Gurax_CreateFunction(AbsName));
	Assign(Gurax_CreateFunction(BaseName));
	Assign(Gurax_CreateFunction(BottomName));
	Assign(Gurax_CreateFunction(Dir));
	Assign(Gurax_CreateFunction(DirName));
	Assign(Gurax_CreateFunction(Exists));
	Assign(Gurax_CreateFunction(ExtName));
	Assign(Gurax_CreateFunction(FileName));
	Assign(Gurax_CreateFunction(Glob));
	Assign(Gurax_CreateFunction(HeadName));
	Assign(Gurax_CreateFunction(Join));
	Assign(Gurax_CreateFunction(Match));
	Assign(Gurax_CreateFunction(Regulate));
	Assign(Gurax_CreateFunction(Split));
	Assign(Gurax_CreateFunction(SplitBottom));
	Assign(Gurax_CreateFunction(SplitExt));
	Assign(Gurax_CreateFunction(Stat));
	Assign(Gurax_CreateFunction(Walk));
	//Assign(Gurax_CreateFunction(Exit));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(path)
