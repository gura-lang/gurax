//==============================================================================
// TARFormat.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(tar)

const int BLOCKSIZE			= 512;

const char *TMAGIC			= "ustar";	// ustar and a null
const int TMAGLEN			= 6;
const char *TVERSION		= "00";		// 00 and no null
const int TVERSLEN			= 2;

// Values used in typeflag field.
const char REGTYPE			= '0';		// regular file
const char AREGTYPE			= '\0';		// regular file
const char LNKTYPE			= '1';		// link
const char SYMTYPE			= '2';		// reserved
const char CHRTYPE			= '3';		// character special
const char BLKTYPE			= '4';		// block special
const char DIRTYPE			= '5';		// directory
const char FIFOTYPE			= '6';		// FIFO special
const char CONTTYPE			= '7';		// reserved
const char XHDTYPE			= 'x';		// Extended header referring to the next file in the archive
const char XGLTYPE			= 'g';		// Global extended header

// Bits used in the mode field, values in octal. 
const UInt32 TSUID			= 04000;	// set UID on execution
const UInt32 TSGID			= 02000;	// set GID on execution
const UInt32 TSVTX			= 01000;	// reserved
										// file permissions
const UInt32 TUREAD			= 00400;	// read by owner
const UInt32 TUWRITE		= 00200;	// write by owner
const UInt32 TUEXEC			= 00100;	// execute/search by owner
const UInt32 TGREAD			= 00040;	// read by group
const UInt32 TGWRITE		= 00020;	// write by group
const UInt32 TGEXEC			= 00010;	// execute/search by group
const UInt32 TOREAD			= 00004;	// read by other
const UInt32 TOWRITE		= 00002;	// write by other
const UInt32 TOEXEC			= 00001;	// execute/search by other

//-----------------------------------------------------------------------------
// Header
//-----------------------------------------------------------------------------
Header::Header(const Header& hdr) :
	_offset(hdr._offset), _mode(hdr._mode), _uid(hdr._uid), _gid(hdr._gid), _size(hdr._size),
	_pMtime(hdr._pMtime->Reference()), _pAtime(hdr._pAtime->Reference()), _pCtime(hdr._pCtime->Reference()),
	_chksum(hdr._chksum), _typeflag(hdr._typeflag),
	_devmajor(hdr._devmajor), _devminor(hdr._devminor)
{
	::memcpy(_name, hdr._name, sizeof(_name));
	::memcpy(_linkname, hdr._linkname, sizeof(_linkname));
	::memcpy(_uname, hdr._uname, sizeof(_uname));
	::memcpy(_gname, hdr._gname, sizeof(_gname));
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
	_name[sizeof(_name) - 1] = '\0';
	_linkname[sizeof(_linkname) - 1] = '\0';
	_uname[sizeof(_uname) - 1] = '\0';
	_gname[sizeof(_gname) - 1] = '\0';
	::memcpy(_name, rawHdr.name, sizeof(rawHdr.name));
	::memcpy(_linkname, rawHdr.linkname, sizeof(rawHdr.linkname));
	::memcpy(_uname, rawHdr.uname, sizeof(rawHdr.uname));
	::memcpy(_gname, rawHdr.gname, sizeof(rawHdr.gname));
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

void Header::ComposeHeaderBlock(void *memBlock) const
{
	star_header& rawHdr = *reinterpret_cast<star_header *>(memBlock);
	::memset(memBlock, 0x00, BLOCKSIZE);
	::memcpy(rawHdr.name,			_name, sizeof(rawHdr.name));
	::sprintf(rawHdr.mode,			"%06o ", _mode);
	::sprintf(rawHdr.uid,			"%06o ", _uid);
	::sprintf(rawHdr.gid,			"%06o ", _gid);
	::sprintf(rawHdr.size,			"%11o", static_cast<UInt32>(_size));
	rawHdr.size[11] = ' ';
	::sprintf(rawHdr.mtime,			"%11llo", static_cast<UInt64>(GetMTime().ToUnixTime()));
	rawHdr.mtime[11] = ' ';
	::memset(rawHdr.chksum,			' ', 8);
	rawHdr.typeflag = _typeflag;
	::memcpy(rawHdr.linkname,		_linkname, sizeof(rawHdr.linkname));
	::memcpy(rawHdr.magic,			"ustar ", 6);
	::memcpy(rawHdr.version,		" \x00", 2);
	::memcpy(rawHdr.uname,			_uname, sizeof(rawHdr.uname));
	::memcpy(rawHdr.gname,			_gname, sizeof(rawHdr.gname));
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
}

bool Header::Write(Stream& stream)
{
	return true;
}

Header* Header::Read(Stream& stream)
{
	char buffBlock[BLOCKSIZE];
	int nTerminator = 0;
	for (;;) {
		size_t bytesRead = stream.Read(buffBlock, BLOCKSIZE);
		if (Error::IsIssued()) return nullptr;
		if (bytesRead < BLOCKSIZE) {
			Error::Issue(ErrorType::FormatError, "failed to read a block");
			return nullptr;
		}
		bool zeroBlockFlag = true;
		UInt32* p = reinterpret_cast<UInt32 *>(buffBlock);
		for (int i = 0; i < BLOCKSIZE / sizeof(UInt32); i++, p++) {
			if (*p != 0x00000000) {
				zeroBlockFlag = false;
				break;
			}
		}
		if (!zeroBlockFlag) break;
		nTerminator++;
		if (nTerminator == 2) return nullptr;
	}
	star_header& hdrRaw = *reinterpret_cast<star_header *>(buffBlock);
	std::unique_ptr<Header> pHdr(new Header());
	pHdr->SetOffset(stream.GetOffset());
	if (!pHdr->SetRawHeader(hdrRaw)) return nullptr;
	return pHdr.release();
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
