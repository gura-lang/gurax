//==============================================================================
// module-path.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(path)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// path.AbsName(pathName as String):map:[uri]
Gurax_DeclareFunction(AbsName)
{
	Declare(VTYPE_String, Flag::Map);
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

// path.BaseName(pathName as String):map
Gurax_DeclareFunction(BaseName)
{
	Declare(VTYPE_String, Flag::Map);
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

// path.BottomName(pathName as String):map
Gurax_DeclareFunction(BottomName)
{
	Declare(VTYPE_String, Flag::Map);
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

// path.Dir(directory? as Directory, pattern* as String):map:flat:[addSep,elimSep,stat,file,dir,case,icase] {block?}
Gurax_DeclareFunction(Dir)
{
	Declare(VTYPE_Any, Flag::Map | Flag::Flat);
	DeclareArg("directory", VTYPE_Directory, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pattern", VTYPE_String, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	Directory::WalkFlag::DeclareAttrOpt(*this);
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
	// Arguments
	ArgPicker args(argument);
	RefPtr<Directory> pDirectory(
		args.IsValid()? Value_Directory::GetDirectory(args.PickValue()).Reference() :
		PathMgr::OpenDirectory("."));
	int depthMax = 0;
	StringList patterns = args.PickStringList();
	if (Error::IsIssued()) return Value::nil();
	Directory::WalkFlags walkFlags = Directory::WalkFlag::CheckArgument(argument, true, pDirectory->GetCaseFlag());
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_DirectoryWalk(pDirectory.release(), depthMax, patterns, walkFlags));
	return argument.ReturnIterator(processor, pIterator.release());
}

// path.DirName(pathName as String):map
Gurax_DeclareFunction(DirName)
{
	Declare(VTYPE_String, Flag::Map);
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

// path.Exists(pathName as String):map
Gurax_DeclareFunction(Exists)
{
	Declare(VTYPE_Bool, Flag::Map);
	DeclareArg("pathName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns true if the specified path exists.");
}

Gurax_ImplementFunction(Exists)
{
	// Arguments
	ArgPicker args(argument);
	const char* pathName = args.PickString();
	// Function body
	PathMgr::Existence existence = PathMgr::CheckExistence(pathName);
	return new Value_Bool(existence != PathMgr::Existence::None);
}

// path.ExtName(pathName as String):map
Gurax_DeclareFunction(ExtName)
{
	Declare(VTYPE_String, Flag::Map);
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

// path.FileName(pathName as String):map
Gurax_DeclareFunction(FileName)
{
	Declare(VTYPE_String, Flag::Map);
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

// path.Glob(pattern as string):map:flat:[addSep,elimSep,stat,file,dir,case,icase] {block?}
Gurax_DeclareFunction(Glob)
{
	Declare(VTYPE_Any, Flag::Map | Flag::Flat);
	DeclareArg("pattern", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	Directory::WalkFlag::DeclareAttrOpt(*this);
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
	// Arguments
	ArgPicker args(argument);
	const char* pattern = args.PickString();
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<Iterator_DirectoryGlob> pIterator(new Iterator_DirectoryGlob());
	if (!pIterator->Initialize(pattern)) return Value::nil();
	pIterator->SetWalkFlags(Directory::WalkFlag::CheckArgument(argument, true, pIterator->GetDirectoryCur().GetCaseFlag()));
	return argument.ReturnIterator(processor, pIterator.release());
}

// path.HeadName(pathName as String):map
Gurax_DeclareFunction(HeadName)
{
	Declare(VTYPE_String, Flag::Map);
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

// path.Join(paths+ as String):map:[uri]
Gurax_DeclareFunction(Join)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("paths", VTYPE_String, ArgOccur::OnceOrMore, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(uri));
	AddHelp(
		Gurax_Symbol(en),
		"Returns a path name that joins given strings with directory separators.");
}

Gurax_ImplementFunction(Join)
{
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

// path.Match(pathName1 as String, pathName2 as String):map:[case,icase]
Gurax_DeclareFunction(Match)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("pathName1", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pathName2", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(case_));
	DeclareAttrOpt(Gurax_Symbol(icase));
	AddHelp(
		Gurax_Symbol(en), 
		"Returns true if the both path names are determined as equal each other.\n"
		"\n"
		"Though the default sensitiveness of character cases depends on the current platform,\n"
		"it can be changed by attributes `:case` for case-sensitive and `:icase` for case-insensitive.\n");
}

Gurax_ImplementFunction(Match)
{
	// Arguments
	ArgPicker args(argument);
	PathName pathName1(args.PickString());
	const char* pathName2 = args.PickString();
	// Function body
	if (argument.IsSet(Gurax_Symbol(case_))) pathName1.SetCaseFlag(true);
	if (argument.IsSet(Gurax_Symbol(icase))) pathName1.SetCaseFlag(false);
	return new Value_Bool(pathName1.DoesMatch(pathName2));
}

// path.MatchPattern(pattern as String, pathName as String):map:[case,icase]
Gurax_DeclareFunction(MatchPattern)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("pattern", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pathName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(case_));
	DeclareAttrOpt(Gurax_Symbol(icase));
	AddHelp(
		Gurax_Symbol(en), 
		"Returns true if a name matches with a pattern that supports UNIX shell-style wild cards.\n"
		"\n"
		"Though the default sensitiveness of character cases depends on the current platform,\n"
		"it can be changed by attributes `:case` for case-sensitive and `:icase` for case-insensitive.\n");
}

Gurax_ImplementFunction(MatchPattern)
{
	// Arguments
	ArgPicker args(argument);
	const char* pattern = args.PickString();
	PathName pathName(args.PickString());
	// Function body
	if (argument.IsSet(Gurax_Symbol(case_))) pathName.SetCaseFlag(true);
	if (argument.IsSet(Gurax_Symbol(icase))) pathName.SetCaseFlag(false);
	return new Value_Bool(pathName.DoesMatchPattern(pattern));
}

// path.Regulate(pathName as String):map:[uri]
Gurax_DeclareFunction(Regulate)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("pathName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(uri));
	AddHelp(
		Gurax_Symbol(en),
		"Removes redundant relative directories.");
}

Gurax_ImplementFunction(Regulate)
{
	// Arguments
	ArgPicker args(argument);
	PathName pathName(args.PickString());
	// Function body
	if (argument.IsSet(Gurax_Symbol(uri))) pathName.SetSepUNIX();
	return new Value_String(pathName.Regulate());
}

// path.Split(pathName as String):map
Gurax_DeclareFunction(Split)
{
	Declare(VTYPE_List, Flag::Map);
	DeclareArg("pathName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en), 
		"Splits a pathname by a directory separator and returns a tuple containing\n"
		"a directory name as the first element and a base name as the second one.\n"
		"\n"
		"Calling this function has the same result as calling `path.DirName()` and `path.FileName()`.\n"
		"\n"
		"\n"
		"Example:\n"
		"```\n"
		"path.Split('/foo/bar/file.txt')         # Returns ('/foo/bar/', 'file.txt')\n"
		"path.Split('/foo/bar/dir/')             # Returns ('/foo/bar/dir/', '')\n"
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
	return Value_Tuple::Create(new Value_String(dirName), new Value_String(fileName));
}

// path.SplitBottom(pathName as String):map
Gurax_DeclareFunction(SplitBottom)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("pathName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en), 
		"Splits a pathname by a directory separator and returns a tuple containing\n"
		"a directory name as the first element and a base name as the second one.\n"
		"\n"
		"Calling this function has the same result as calling `path.HeadName()` and `path.BottomName()`.\n"
		"\n"
		"Example:\n"
		"```\n"
		"path.SplitBottom('/foo/bar/file.txt'):bottom  # Returns ('/foo/bar/', 'file.txt')\n"
		"path.SplitBottom('/foo/bar/dir/'):bottom      # Returns ('/foo/bar/', 'dir')\n"
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
	return Value_Tuple::Create(new Value_String(headName), new Value_String(bottomName));
}

// path.SplitExt(pathName as String):map
Gurax_DeclareFunction(SplitExt)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("pathName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en), 
		"Splits a pathname by a dot character indicating a beginning of an extension\n"
		"and returns a tuple containing a path name without an extention\n"
		"and an extention part."
		"\n"
		"Calling this function has the same result as calling `path.BaseName()` and `path.ExtName()`.\n"
		"\n"
		"Example:\n"
		"```\n"
		"path.SplitExt('/foo/bar/file.txt'):bottom  # Returns ('/foo/bar/file', 'txt')\n"
		"path.SplitExt('/foo/bar/file'):bottom      # Returns ('/foo/bar/file', '')\n"
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
	return Value_Tuple::Create(new Value_String(baseName), new Value_String(extName));
}

// path.Stat(directory as Directory):map {block?}
Gurax_DeclareFunction(Stat)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("directory", VTYPE_Directory, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en), 
		"Returns a stat object associated with the specified item.");
}

Gurax_ImplementFunction(Stat)
{
	// Arguments
	ArgPicker args(argument);
	Directory& directory = Value_Directory::GetDirectory(args.PickValue());
	// Function body
	RefPtr<Value_Stat> pValue(directory.CreateStatValue());
	if (!pValue) return Value::nil();
	return argument.ReturnValue(processor, pValue.release());
}

// path.Walk(directory? as Directory, depthMax? as Number, pattern* as String):map:flat:[addSep,elimSep,stat,file,dir,case,icase] {block?}
Gurax_DeclareFunction(Walk)
{
	Declare(VTYPE_Any, Flag::Map | Flag::Flat);
	DeclareArg("directory", VTYPE_Directory, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("depthMax", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pattern", VTYPE_String, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	Directory::WalkFlag::DeclareAttrOpt(*this);
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
	// Arguments
	ArgPicker args(argument);
	RefPtr<Directory> pDirectory(
		args.IsValid()? Value_Directory::GetDirectory(args.PickValue()).Reference() :
		PathMgr::OpenDirectory("."));
	int depthMax = args.IsValid()? args.PickNumberNonNeg<int>() : -1;
	StringList patterns = args.PickStringList();
	if (Error::IsIssued()) return Value::nil();
	Directory::WalkFlags walkFlags = Directory::WalkFlag::CheckArgument(argument, true, pDirectory->GetCaseFlag());
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_DirectoryWalk(pDirectory.release(), depthMax, patterns, walkFlags));
	return argument.ReturnIterator(processor, pIterator.release());
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
	Assign(Gurax_CreateFunction(MatchPattern));
	Assign(Gurax_CreateFunction(Regulate));
	Assign(Gurax_CreateFunction(Split));
	Assign(Gurax_CreateFunction(SplitBottom));
	Assign(Gurax_CreateFunction(SplitExt));
	Assign(Gurax_CreateFunction(Stat));
	Assign(Gurax_CreateFunction(Walk));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(path)
