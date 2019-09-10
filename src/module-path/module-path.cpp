//==============================================================================
// module-path.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(path)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// path.AbsName(name:string):map:[uri]
Gurax_DeclareFunction(AbsName)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("name", VTYPE_String);
	DeclareAttrOpt(Gurax_Symbol(uri));
	AddHelp(
		Gurax_Symbol(en),
		"Returns an absolute path name of the given name.");
}

Gurax_ImplementFunction(AbsName)
{
#if 0
	char chSeparator = arg.IsSet(Gurax_Symbol(uri))? '/' : OAL::FileSeparator;
	return Value(OAL::MakeAbsPathName(chSeparator, arg.GetString(0)));
#endif
	// Arguments
	ArgPicker args(argument);
	// Function body
	return Value::nil();
}

// path.BaseName(pathname:string):map
Gurax_DeclareFunction(BaseName)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("pathname", VTYPE_String);
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
#if 0
	const char *pathName = arg.GetString(0);
	const char *p = PathMgr::SeekExtName(pathName);
	size_t lenLeft = p - pathName;
	return Value(pathName, lenLeft);
#endif
	return Value::nil();
}

// path.Bottom(pathname:string):map
Gurax_DeclareFunction(Bottom)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("pathname", VTYPE_String);
	AddHelp(
		Gurax_Symbol(en), 
		"Returns the last part of a path name (cf. `path.FileName()`)."
		"This is complementary to `path.CutBottom()`.\n"
		"\n"
		"Example:\n"
		"```\n"
		"path.Bottom('/foo/bar/file.txt')  # Returns 'file.txt'\n"
		"path.Bottom('/foo/bar/dir/')      # Returns 'dir'\n"
		"```\n");
}

Gurax_ImplementFunction(Bottom)
{
#if 0
	String bottom;
	PathMgr::SplitBottom(arg.GetString(0), nullptr, &bottom);
	return Value(bottom);
#endif
	return Value::nil();
}

// path.CutBottom(pathname:string):map
Gurax_DeclareFunction(CutBottom)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("pathname", VTYPE_String);
	AddHelp(
		Gurax_Symbol(en), 
		"Returns a path name after eliminating its bottom part (cf. `path.dirname()`)."
		"This is complementary to `path.Bottom()`.\n"
		"\n"
		"Example:\n"
		"```\n"
		"path.CutBottom('/foo/bar/file.txt')  # Returns '/foo/bar/'\n"
		"path.CutBottom('/foo/bar/dir/')      # Returns '/foo/bar/'\n"
		"```\n");
}

Gurax_ImplementFunction(CutBottom)
{
#if 0
	String top;
	PathMgr::SplitBottom(arg.GetString(0), &top, nullptr);
	return Value(top);
#endif
	return Value::nil();
}

// path.Dir(directory?:directory, pattern*:string):map:flat:[stat,file,dir,case,icase] {block?}
Gurax_DeclareFunction(Dir)
{
	Declare(VTYPE_Any, Flag::Map | Flag::Flat);
	DeclareArg("directory", VTYPE_Directory, ArgOccur::ZeroOrOnce);
	DeclareArg("pattern", VTYPE_String, ArgOccur::ZeroOrMore);
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

// path.DirName(pathname:string):map
Gurax_DeclareFunction(DirName)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("pathname", VTYPE_String);
	AddHelp(
		Gurax_Symbol(en), 
		"Splits a pathname by a directory separator and returns a directory name part (cf. `path.CutBottom()`)."
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
#if 0
	String dirName;
	PathMgr::SplitFileName(arg.GetString(0), &dirName, nullptr);
	return Value(dirName);
#endif
	return Value::nil();
}

// path.Exists(pathname:string):map
Gurax_DeclareFunction(Exists)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("pathname", VTYPE_String);
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

// path.ExtName(pathname:string):map
Gurax_DeclareFunction(ExtName)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("pathname", VTYPE_String);
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
#if 0
	const char *pathName = arg.GetString(0);
	const char *p = PathMgr::SeekExtName(pathName);
	return Value((*p == '.')? p + 1 : p);
#endif
	return Value::nil();
}

// path.FileName(pathname:string):map
Gurax_DeclareFunction(FileName)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("pathname", VTYPE_String);
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
#if 0
	String fileName;
	PathMgr::SplitFileName(arg.GetString(0), nullptr, &fileName);
	return Value(fileName);
#endif
	return Value::nil();
}

// path.Glob(pattern:string):map:flat:[stat,file,dir,case,icase] {block?}
Gurax_DeclareFunction(Glob)
{
	Declare(VTYPE_Any, Flag::Map | Flag::Flat);
	DeclareArg("pattern", VTYPE_String);
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

// path.Join(paths+:string):map:[uri]
Gurax_DeclareFunction(Join)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("paths", VTYPE_String, ArgOccur::OnceOrMore);
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
	return Value::nil();
}

// path.Match(pattern:string, name:string):map:[case,icase]
Gurax_DeclareFunction(Match)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("pattern", VTYPE_String);
	DeclareArg("name", VTYPE_String);
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
	DeclareArg("name", VTYPE_String);
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

// path.Split(pathname:string):map:[bottom]
Gurax_DeclareFunction(Split)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("pathname", VTYPE_String);
	DeclareAttrOpt(Gurax_Symbol(bottom));
	AddHelp(
		Gurax_Symbol(en), 
		"Splits a pathname by a directory separator and returns a list containing\n"
		"a directory name as the first element and a base name as the second one.\n"
		"\n"
		"Calling this function has the same result as calling `path.DirName()` and `path.FileName()`.\n"
		"\n"
		"Calling this function with `:bottom` attribute has the same result as calling\n"
		"`path.CutBottom()` and `path.Bottom()`.\n"
		"\n"
		"Example:\n"
		"```\n"
		"path.Split('/foo/bar/file.txt')         # Returns ['/foo/bar/', 'file.txt']\n"
		"path.Split('/foo/bar/dir/')             # Returns ['/foo/bar/dir/', '']\n"
		"\n"
		"path.Split('/foo/bar/file.txt'):bottom  # Returns ['/foo/bar/', 'file.txt']\n"
		"path.Split('/foo/bar/dir/'):bottom      # Returns ['/foo/bar/', 'dir']\n"
		"```\n");
}

Gurax_ImplementFunction(Split)
{
#if 0
	String first, second;
	if (arg.IsSet(Gurax_Symbol(bottom))) {
		PathMgr::SplitBottom(arg.GetString(0), &first, &second);
	} else {
		PathMgr::SplitFileName(arg.GetString(0), &first, &second);
	}
	Value result;
	Object_list *pObjList = result.InitAsList(env);
	pObjList->Add(Value(first));
	pObjList->Add(Value(second));
	return result;
#endif
	return Value::nil();
}

// path.SplitExt(pathname:string):map
Gurax_DeclareFunction(SplitExt)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("pathname", VTYPE_String);
	AddHelp(
		Gurax_Symbol(en), 
		"Splits a pathname by a dot character indicating a beginning of an extension\n"
		"and returns a list containing a path name without an extention\n"
		"and an extention part.");
}

Gurax_ImplementFunction(SplitExt)
{
#if 0
	const char *pathName = arg.GetString(0);
	const char *p = PathMgr::SeekExtName(pathName);
	Value result;
	Object_list *pObjList = result.InitAsList(env);
	size_t lenLeft = p - pathName;
	pObjList->Add(Value(pathName, lenLeft));
	pObjList->Add(Value((*p == '.')? p + 1 : p));
	return result;
#endif
	return Value::nil();
}

// path.Stat(directory:directory):map
Gurax_DeclareFunction(Stat)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("directory", VTYPE_Directory);
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
	DeclareArg("directory", VTYPE_Directory, ArgOccur::ZeroOrOnce);
	DeclareArg("maxdepth", VTYPE_Number, ArgOccur::ZeroOrOnce);
	DeclareArg("pattern", VTYPE_String, ArgOccur::ZeroOrMore);
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
	Assign(Gurax_CreateFunction(Bottom));
	Assign(Gurax_CreateFunction(CutBottom));
	Assign(Gurax_CreateFunction(Dir));
	Assign(Gurax_CreateFunction(DirName));
	Assign(Gurax_CreateFunction(Exists));
	Assign(Gurax_CreateFunction(ExtName));
	Assign(Gurax_CreateFunction(FileName));
	Assign(Gurax_CreateFunction(Glob));
	Assign(Gurax_CreateFunction(Join));
	Assign(Gurax_CreateFunction(Match));
	Assign(Gurax_CreateFunction(Regulate));
	Assign(Gurax_CreateFunction(Split));
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
