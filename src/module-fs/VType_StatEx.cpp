//==============================================================================
// VType_StatEx.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(fs)

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
// fs.Stat(pathName:String):map {block?}
Gurax_DeclareConstructor(Stat)
{
	Declare(VTYPE_DateTime, Flag::Map);
	DeclareArg("pathName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `fs.Stat` instance from the specified path name.\n");
}

Gurax_ImplementConstructor(Stat)
{
	// Arguments
	ArgPicker args(argument);
	const char* pathName = args.PickString();
	// Function body
	RefPtr<StatEx> pStat(StatEx::Create(pathName));
	if (!pStat) return Value::nil();
	return argument.ReturnValue(processor, new Value_StatEx(pStat.release()));
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
	return new Value_Number(stat.GetSize());
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
// VType_StatEx
//------------------------------------------------------------------------------
VType_StatEx VTYPE_StatEx("StatEx");

void VType_StatEx::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// VType settings
	Declare(VTYPE_Stat, Flag::Immutable, Gurax_CreateConstructor(Stat));
}

//------------------------------------------------------------------------------
// Value_StatEx
//------------------------------------------------------------------------------
VType& Value_StatEx::vtype = VTYPE_StatEx;

Gurax_EndModuleScope(fs)
