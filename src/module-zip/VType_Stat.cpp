//==============================================================================
// VType_Stat.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(zip)

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

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// zip.Stat#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(Stat, MethodSkeleton)
{
	Declare(VTYPE_List, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Stat, MethodSkeleton)
{
	// Target
	//auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Double num1 = args.PickNumber<Double>();
	Double num2 = args.PickNumber<Double>();
	// Function body
	return new Value_Number(num1 + num2);
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
#if 0
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
#endif

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
	CentralFileHeader& hdr = GetValueThis(valueTarget).GetCentralFileHeader();
	return new Value_String(PathName(hdr.GetFileName()).ExtractFileName());
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
	CentralFileHeader& hdr = GetValueThis(valueTarget).GetCentralFileHeader();
	return new Value_Number(hdr.GetUncompressedSize());
}

// Stat#sizeCompressed
Gurax_DeclareProperty_R(Stat, sizeCompressed)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The compressed size in bytes.");
}

Gurax_ImplementPropertyGetter(Stat, sizeCompressed)
{
	CentralFileHeader& hdr = GetValueThis(valueTarget).GetCentralFileHeader();
	return new Value_Number(hdr.GetCompressedSize());
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
	CentralFileHeader& hdr = GetValueThis(valueTarget).GetCentralFileHeader();
	return new Value_DateTime(hdr.MakeLastModDateTime());
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
	CentralFileHeader& hdr = GetValueThis(valueTarget).GetCentralFileHeader();
	return new Value_DateTime(hdr.MakeLastModDateTime());
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
	CentralFileHeader& hdr = GetValueThis(valueTarget).GetCentralFileHeader();
	return new Value_DateTime(hdr.MakeLastModDateTime());
}

#if 0
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
#endif

//------------------------------------------------------------------------------
// VType_Stat
//------------------------------------------------------------------------------
VType_Stat VTYPE_Stat("Stat");

void VType_Stat::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Stat, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Stat, fileName));
	Assign(Gurax_CreateProperty(Stat, size));
	Assign(Gurax_CreateProperty(Stat, sizeCompressed));
	Assign(Gurax_CreateProperty(Stat, atime));
	Assign(Gurax_CreateProperty(Stat, mtime));
	Assign(Gurax_CreateProperty(Stat, ctime));
}

//------------------------------------------------------------------------------
// Value_Stat
//------------------------------------------------------------------------------
VType& Value_Stat::vtype = VTYPE_Stat;

Gurax_EndModuleScope(zip)
