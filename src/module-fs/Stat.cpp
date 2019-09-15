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

Stat* Stat::Generate(const char* pathName)
{
	return nullptr;
}

#else

//------------------------------------------------------------------------------
// Stat (POSIX)
//------------------------------------------------------------------------------
Stat::Stat(const char* pathName, const struct stat& stat) :
	_pathName(pathName), _attr(0), _bytes(stat.st_size),
	_pDateTimeA(OAL::CreateDateTime(stat.st_atime)),
	_pDateTimeM(OAL::CreateDateTime(stat.st_mtime)),
	_pDateTimeC(OAL::CreateDateTime(stat.st_ctime)),
	_uid(stat.st_uid), _gid(stat.st_gid)
{
	if (S_ISDIR(stat.st_mode)) _attr |= Attr::Dir;
	if (S_ISCHR(stat.st_mode)) _attr |= Attr::Chr;
	if (S_ISBLK(stat.st_mode)) _attr |= Attr::Blk;
	if (S_ISREG(stat.st_mode)) _attr |= Attr::Reg;
	if (S_ISFIFO(stat.st_mode)) _attr |= Attr::Fifo;
	if (S_ISLNK(stat.st_mode)) _attr |= Attr::Lnk;
	if (S_ISSOCK(stat.st_mode)) _attr |= Attr::Sock;
	_attr |= (stat.st_mode & 0777);
}

Stat* Stat::Generate(const char* pathName)
{
	struct stat stat;
	String pathNameN = OAL::ToNativeString(PathName(pathName).MakeAbsName().c_str());
	if (::stat(pathNameN.c_str(), &stat) != 0) {
		Error::Issue(ErrorType::IOError, "failed to get file status of %s", pathName);
		return nullptr;
	}
	return new Stat(pathName, stat);
}

#endif

Gurax_EndModuleScope(fs)
