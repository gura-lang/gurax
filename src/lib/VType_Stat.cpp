//==============================================================================
// VType_Stat.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

The `Stat` class provides information such as file name, size and creation time of a file.
`This is a base class from which `fs.Stat` and `zip.Stat` inherit.\n"

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Stat(pathName:String):map {block?}
Gurax_DeclareConstructor(Stat)
{
	Declare(VTYPE_Stat, Flag::Map);
	DeclareArg("pathName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Stat` instance from the specified path name.\n");
}

Gurax_ImplementConstructor(Stat)
{
	// Arguments
	ArgPicker args(argument);
	const char* pathName = args.PickString();
	// Function body
	RefPtr<Directory> pDirectory(PathMgr::OpenDirectory(pathName));
	if (!pDirectory) return Value::nil();
	RefPtr<Value_Stat> pValue(pDirectory->CreateStatValue());
	if (!pValue) return Value::nil();
	return argument.ReturnValue(processor, pValue.release());
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// Stat#pathName
Gurax_DeclareProperty_R(Stat, pathName)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The path name of the item.");
}

Gurax_ImplementPropertyGetter(Stat, pathName)
{
	Stat& stat = GetValueThis(valueTarget).GetStat();
	return new Value_String(stat.GetPathName());
}

// Stat#dirName
Gurax_DeclareProperty_R(Stat, dirName)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The directory name of the item.");
}

Gurax_ImplementPropertyGetter(Stat, dirName)
{
	Stat& stat = GetValueThis(valueTarget).GetStat();
	return new Value_String(PathName(stat.GetPathName()).ExtractDirName());
}

// Stat#fileName
Gurax_DeclareProperty_R(Stat, fileName)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The file name of the item.");
}

Gurax_ImplementPropertyGetter(Stat, fileName)
{
	Stat& stat = GetValueThis(valueTarget).GetStat();
	return new Value_String(PathName(stat.GetPathName()).ExtractFileName());
}

// Stat#headName
Gurax_DeclareProperty_R(Stat, headName)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The head name of the item.");
}

Gurax_ImplementPropertyGetter(Stat, headName)
{
	Stat& stat = GetValueThis(valueTarget).GetStat();
	return new Value_String(PathName(stat.GetPathName()).ExtractHeadName());
}

// Stat#bottomName
Gurax_DeclareProperty_R(Stat, bottomName)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The bottom name of the item.");
}

Gurax_ImplementPropertyGetter(Stat, bottomName)
{
	Stat& stat = GetValueThis(valueTarget).GetStat();
	return new Value_String(PathName(stat.GetPathName()).ExtractBottomName());
}

// Stat#size
Gurax_DeclareProperty_R(Stat, size)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The file size in bytes.");
}

Gurax_ImplementPropertyGetter(Stat, size)
{
	Stat& stat = GetValueThis(valueTarget).GetStat();
	return new Value_Number(stat.GetBytes());
}

// Stat#atime
Gurax_DeclareProperty_R(Stat, atime)
{
	Declare(VTYPE_DateTime, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"A `DateTime` instance that represents when the file has been accessed at last.");
}

Gurax_ImplementPropertyGetter(Stat, atime)
{
	Stat& stat = GetValueThis(valueTarget).GetStat();
	return new Value_DateTime(stat.GetDateTimeA().Reference());
}

// Stat#mtime
Gurax_DeclareProperty_R(Stat, mtime)
{
	Declare(VTYPE_DateTime, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"A `DateTime` instance that represents when the file has been modified at last.");
}

Gurax_ImplementPropertyGetter(Stat, mtime)
{
	Stat& stat = GetValueThis(valueTarget).GetStat();
	return new Value_DateTime(stat.GetDateTimeM().Reference());
}

// Stat#ctime
Gurax_DeclareProperty_R(Stat, ctime)
{
	Declare(VTYPE_DateTime, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"A `DateTime` instance that represents when the file has been created.");
}

Gurax_ImplementPropertyGetter(Stat, ctime)
{
	Stat& stat = GetValueThis(valueTarget).GetStat();
	return new Value_DateTime(stat.GetDateTimeC().Reference());
}

// Stat#isblk
Gurax_DeclareProperty_R(Stat, isblk)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the item is a block device.");
}

Gurax_ImplementPropertyGetter(Stat, isblk)
{
	Stat& stat = GetValueThis(valueTarget).GetStat();
	return new Value_Bool(stat.IsBlk());
}

// Stat#ischr
Gurax_DeclareProperty_R(Stat, ischr)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the item is a character device.");
}

Gurax_ImplementPropertyGetter(Stat, ischr)
{
	Stat& stat = GetValueThis(valueTarget).GetStat();
	return new Value_Bool(stat.IsChr());
}

// Stat#isdir
Gurax_DeclareProperty_R(Stat, isdir)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the item is a directory.");
}

Gurax_ImplementPropertyGetter(Stat, isdir)
{
	Stat& stat = GetValueThis(valueTarget).GetStat();
	return new Value_Bool(stat.IsDir());
}

// Stat#isfifo
Gurax_DeclareProperty_R(Stat, isfifo)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the item is a FIFO.");
}

Gurax_ImplementPropertyGetter(Stat, isfifo)
{
	Stat& stat = GetValueThis(valueTarget).GetStat();
	return new Value_Bool(stat.IsFifo());
}

// Stat#islnk
Gurax_DeclareProperty_R(Stat, islnk)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the item is a link.");
}

Gurax_ImplementPropertyGetter(Stat, islnk)
{
	Stat& stat = GetValueThis(valueTarget).GetStat();
	return new Value_Bool(stat.IsLnk());
}

// Stat#isreg
Gurax_DeclareProperty_R(Stat, isreg)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the file is a regular file.");
}

Gurax_ImplementPropertyGetter(Stat, isreg)
{
	Stat& stat = GetValueThis(valueTarget).GetStat();
	return new Value_Bool(stat.IsReg());
}

// Stat#issock
Gurax_DeclareProperty_R(Stat, issock)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the item is a socket.");
}

Gurax_ImplementPropertyGetter(Stat, issock)
{
	Stat& stat = GetValueThis(valueTarget).GetStat();
	return new Value_Bool(stat.IsBlk());
}

// Stat#gid
Gurax_DeclareProperty_R(Stat, gid)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The group ID that the item belongs to.");
}

Gurax_ImplementPropertyGetter(Stat, gid)
{
	Stat& stat = GetValueThis(valueTarget).GetStat();
	return new Value_Number(stat.GetGid());
}

// Stat#uid
Gurax_DeclareProperty_R(Stat, uid)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The user ID that the item belongs to.");
}

Gurax_ImplementPropertyGetter(Stat, uid)
{
	Stat& stat = GetValueThis(valueTarget).GetStat();
	return new Value_Number(stat.GetUid());
}

//------------------------------------------------------------------------------
// VType_Stat
//------------------------------------------------------------------------------
VType_Stat VTYPE_Stat("Stat");

void VType_Stat::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Stat));
	// Assignment of property
	Assign(Gurax_CreateProperty(Stat, pathName));
	Assign(Gurax_CreateProperty(Stat, dirName));
	Assign(Gurax_CreateProperty(Stat, fileName));
	Assign(Gurax_CreateProperty(Stat, headName));
	Assign(Gurax_CreateProperty(Stat, bottomName));
	Assign(Gurax_CreateProperty(Stat, size));
	Assign(Gurax_CreateProperty(Stat, atime));
	Assign(Gurax_CreateProperty(Stat, mtime));
	Assign(Gurax_CreateProperty(Stat, ctime));
	Assign(Gurax_CreateProperty(Stat, isblk));
	Assign(Gurax_CreateProperty(Stat, ischr));
	Assign(Gurax_CreateProperty(Stat, isdir));
	Assign(Gurax_CreateProperty(Stat, isfifo));
	Assign(Gurax_CreateProperty(Stat, islnk));
	Assign(Gurax_CreateProperty(Stat, isreg));
	Assign(Gurax_CreateProperty(Stat, issock));
	Assign(Gurax_CreateProperty(Stat, gid));
	Assign(Gurax_CreateProperty(Stat, uid));
}

//------------------------------------------------------------------------------
// Value_Stat
//------------------------------------------------------------------------------
VType& Value_Stat::vtype = VTYPE_Stat;

String Value_Stat::ToStringFormatter(const StringStyle& ss) const
{
	String str;
	_ToStringFormatter(str, ss);
	str.Format(":%s>", GetStat().ToString(ss).c_str());
	return str;
}

String Value_Stat::ToStringDetail(const StringStyle& ss) const
{
	return ToStringFormatter(ss);
}

}
