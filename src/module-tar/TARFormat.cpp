//==============================================================================
// TARFormat.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(tar)

//-----------------------------------------------------------------------------
// Header
//-----------------------------------------------------------------------------
const char *Header::TMAGIC		= "ustar";	// ustar and a null
const char *Header::TVERSION	= "00";		// 00 and no null

Header::Header(const Header& hdr) :
	_offset(hdr._offset), _name(hdr._name), _linkname(hdr._linkname), _uname(hdr._uname), _gname(hdr._gname),
	_mode(hdr._mode), _uid(hdr._uid), _gid(hdr._gid), _size(hdr._size),
	_pMtime(hdr._pMtime->Reference()), _pAtime(hdr._pAtime->Reference()), _pCtime(hdr._pCtime->Reference()),
	_chksum(hdr._chksum), _typeflag(hdr._typeflag),
	_devmajor(hdr._devmajor), _devminor(hdr._devminor)
{
}

void Header::Initialize()
{
	SetName("");
	SetLinkName("");
	SetUName("");
	SetGName("");
	SetMode(0);
	SetUid(0);
	SetGid(0);
	SetSize(0);
	//SetMTime();
	//SetATime();
	//SetCTime();
	SetChksum(0);
	SetTypeFlag('0');
	SetDevMajor(0);
	SetDevMinor(0);
}

bool Header::SetRawHeader(const star_header& rawHdr)
{
	do {
		_name.clear();
		g_pCodec->Decode(_name, rawHdr.name, sizeof(rawHdr.name));
	} while (0);
	do {
		_linkname.clear();
		g_pCodec->Decode(_linkname, rawHdr.linkname, sizeof(rawHdr.linkname));
	} while (0);
	do {
		_uname.clear();
		g_pCodec->Decode(_uname, rawHdr.uname, sizeof(rawHdr.uname));
	} while (0);
	do {
		_gname.clear();
		g_pCodec->Decode(_gname, rawHdr.gname, sizeof(rawHdr.gname));
	} while (0);
	_mode = OctetToUInt32(rawHdr.mode, sizeof(rawHdr.mode));
	if (Error::IsIssued()) return false;
	_uid = OctetToUInt32(rawHdr.uid, sizeof(rawHdr.uid));
	if (Error::IsIssued()) return false;
	_gid = OctetToUInt32(rawHdr.gid, sizeof(rawHdr.gid));
	if (Error::IsIssued()) return false;
	_size = OctetToUInt32(rawHdr.size, sizeof(rawHdr.size));
	if (Error::IsIssued()) return false;
	do {
		time_t tm = static_cast<time_t>(OctetToUInt64(rawHdr.mtime, sizeof(rawHdr.mtime)));
		if (Error::IsIssued()) return false;
		_pMtime.reset(OAL::CreateDateTime(tm));
	} while (0);
	do {
		time_t tm = static_cast<time_t>(OctetToUInt64(rawHdr.atime, sizeof(rawHdr.atime)));
		if (Error::IsIssued()) return false;
		_pAtime.reset(OAL::CreateDateTime(tm));
	} while (0);
	do {
		time_t tm = static_cast<time_t>(OctetToUInt64(rawHdr.ctime, sizeof(rawHdr.ctime)));
		if (Error::IsIssued()) return false;
		_pCtime.reset(OAL::CreateDateTime(tm));
	} while (0);
	_chksum = OctetToUInt32(rawHdr.chksum, sizeof(rawHdr.chksum));
	if (Error::IsIssued()) return false;
	_typeflag = rawHdr.typeflag;
	_devmajor = OctetToUInt32(rawHdr.devmajor, sizeof(rawHdr.devmajor));
	if (Error::IsIssued()) return false;
	_devminor = OctetToUInt32(rawHdr.devminor, sizeof(rawHdr.devminor));
	if (Error::IsIssued()) return false;
	return true;
}

bool Header::ComposeHeaderBlock(void *memBlock) const
{
	star_header& rawHdr = *reinterpret_cast<star_header *>(memBlock);
	::memset(memBlock, 0x00, BLOCKSIZE);
	do {
		Binary buff;
		if (!g_pCodec->Encode(buff, _name.c_str())) return false;
		if (buff.size() > sizeof(rawHdr.name)) {
			Error::Issue(ErrorType::FormatError, "the length of name is too long");
			return false;
		}
		::memcpy(rawHdr.name, buff.data(), buff.size());
	} while (0);
	::sprintf(rawHdr.mode,			"%06o ", _mode);
	::sprintf(rawHdr.uid,			"%06o ", _uid);
	::sprintf(rawHdr.gid,			"%06o ", _gid);
	::sprintf(rawHdr.size,			"%11o", static_cast<UInt32>(_size));
	rawHdr.size[11] = ' ';
	::sprintf(rawHdr.mtime,			"%11llo", static_cast<UInt64>(GetMTime().ToUnixTime()));
	rawHdr.mtime[11] = ' ';
	::memset(rawHdr.chksum,			' ', 8);
	rawHdr.typeflag = _typeflag;
	do {
		Binary buff;
		if (!g_pCodec->Encode(buff, _linkname.c_str())) return false;
		if (buff.size() > sizeof(rawHdr.linkname)) {
			Error::Issue(ErrorType::FormatError, "the length of link name is too long");
			return false;
		}
		::memcpy(rawHdr.linkname, buff.data(), buff.size());
	} while (0);
	::memcpy(rawHdr.magic,			"ustar ", 6);
	::memcpy(rawHdr.version,		" \x00", 2);
	do {
		Binary buff;
		if (!g_pCodec->Encode(buff, _uname.c_str())) return false;
		if (buff.size() > sizeof(rawHdr.uname)) {
			Error::Issue(ErrorType::FormatError, "the length of user name is too long");
			return false;
		}
		::memcpy(rawHdr.uname, buff.data(), buff.size());
	} while (0);
	do {
		Binary buff;
		if (!g_pCodec->Encode(buff, _gname.c_str())) return false;
		if (buff.size() > sizeof(rawHdr.gname)) {
			Error::Issue(ErrorType::FormatError, "the length of group name is too long");
			return false;
		}
		::memcpy(rawHdr.gname, buff.data(), buff.size());
	} while (0);
	//::sprintf(rawHdr.devmajor,	"%06o ", _devmajor);
	//::sprintf(rawHdr.devminor,	"%06o ", _devminor);
	//::memset(rawHdr.prefix,		0x00, sizeof(rawHdr.prefix));
	//::sprintf(rawHdr.atime,		"%11o", _atime.GetUnixTime());
	//rawHdr.atime[11] = ' ';
	//::sprintf(rawHdr.ctime,		"%11o", _ctime.GetUnixTime());
	//rawHdr.ctime[11] = ' ';
	UInt32 chksum = 0;
	UChar *p = reinterpret_cast<UChar *>(&rawHdr);
	for (int i = 0; i < BLOCKSIZE; i++, p++) chksum += *p;
	::sprintf(rawHdr.chksum,		"%6o ", chksum);
	return true;
}

bool Header::Write(Stream& stream)
{
	return true;
}

UInt64 Header::OctetToUInt64(const char *octet, size_t len)
{
	UInt64 num = 0;
	for (const char *p = octet; len > 0; len--, p++) {
		char ch = *p;
		if (ch == '\0') break;
		if (ch == ' ') {
			continue;
		} else if (!String::IsOctDigit(ch)) {
			Error::Issue(ErrorType::FormatError, "invalid octet format");
			return 0;
		}
		num = (num << 3) | (ch - '0');
	}
	return num;
}

Gurax_EndModuleScope(tar)
