//==============================================================================
// Stat.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(fs)

//------------------------------------------------------------------------------
// Stat (common)
//------------------------------------------------------------------------------
String Stat::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("%s:%dbytes", GetPathName(), GetSize());
	return str;
}

Stat::Stat(const char* pathName, const struct stat& sb) :
	_pDateTimeC(OAL::CreateDateTime(sb.st_ctime)),
	_pDateTimeM(OAL::CreateDateTime(sb.st_mtime)),
	_pDateTimeA(OAL::CreateDateTime(sb.st_atime)),
	_pathName(pathName), _flags(0), _mode(0),
	_bytes(sb.st_size), _uid(sb.st_uid), _gid(sb.st_gid)
{
	if (S_ISDIR(sb.st_mode)) _flags |= Flag::Dir;
	if (S_ISCHR(sb.st_mode)) _flags |= Flag::Chr;
	if (S_ISBLK(sb.st_mode)) _flags |= Flag::Blk;
	if (S_ISREG(sb.st_mode)) _flags |= Flag::Reg;
	if (S_ISFIFO(sb.st_mode)) _flags |= Flag::Fifo;
	if (S_ISLNK(sb.st_mode)) _flags |= Flag::Lnk;
	if (S_ISSOCK(sb.st_mode)) _flags |= Flag::Sock;
	_mode = (sb.st_mode & 0777);
}

Stat* Stat::Create(const char* pathName)
{
	struct stat sb;
	String pathNameN = OAL::ToNativeString(PathName(pathName).MakeAbsName().c_str());
	if (::stat(pathNameN.c_str(), &sb) < 0) return nullptr;
	return new Stat(pathName, sb);
}

#if defined(GURAX_ON_MSWIN)

//------------------------------------------------------------------------------
// Stat (MSWIN)
//------------------------------------------------------------------------------
Stat::Stat(const char* pathName, const BY_HANDLE_FILE_INFORMATION& attrData)
{
}

Stat::Stat(const char* pathName, const WIN32_FILE_ATTRIBUTE_DATA& attrData)
{
}

Stat::Stat(const char* pathName, const WIN32_FIND_DATA& findData)
{
}

#endif

Gurax_EndModuleScope(fs)
