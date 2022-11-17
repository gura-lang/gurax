//==============================================================================
// TARFormat.h
// http://www.gnu.org/software/tar/manual/html_node/Standard.html
//==============================================================================
#ifndef GURAX_MODULE_TAR_TARFORMAT_H
#define GURAX_MODULE_TAR_TARFORMAT_H
#include <gurax.h>

Gurax_BeginModuleScope(tar)


//-----------------------------------------------------------------------------
// posix_header
//-----------------------------------------------------------------------------
struct posix_header
{						// byte offset
	char name[100];		//   0
	char mode[8];		// 100
	char uid[8];		// 108
	char gid[8];		// 116
	char size[12];		// 124
	char mtime[12];		// 136
	char chksum[8];		// 148
	char typeflag;		// 156
	char linkname[100];	// 157
	char magic[6];		// 257
	char version[2];	// 263
	char uname[32];		// 265
	char gname[32];		// 297
	char devmajor[8];	// 329
	char devminor[8];	// 337
	char prefix[155];	// 345
						// 500
};

//-----------------------------------------------------------------------------
// star_header
//-----------------------------------------------------------------------------
struct star_header
{						// byte offset
	char name[100];		//   0
	char mode[8];		// 100
	char uid[8];		// 108
	char gid[8];		// 116
	char size[12];		// 124
	char mtime[12];		// 136
	char chksum[8];		// 148
	char typeflag;		// 156
	char linkname[100];	// 157
	char magic[6];		// 257
	char version[2];	// 263
	char uname[32];		// 265
	char gname[32];		// 297
	char devmajor[8];	// 329
	char devminor[8];	// 337
	char prefix[131];	// 345
	char atime[12];		// 476
	char ctime[12];		// 488
						// 500
};

//-----------------------------------------------------------------------------
// Header
//-----------------------------------------------------------------------------
class Header {
public:
	// General information
	static const int BLOCKSIZE		= 512;
	static const char *TMAGIC;					// ustar and a null
	static const int TMAGLEN		= 6;
	static const char *TVERSION;				// 00 and no null
	static const int TVERSLEN		= 2;
	// Values used in typeflag field.
	static const char REGTYPE		= '0';		// regular file
	static const char AREGTYPE		= '\0';		// regular file
	static const char LNKTYPE		= '1';		// link
	static const char SYMTYPE		= '2';		// reserved
	static const char CHRTYPE		= '3';		// character special
	static const char BLKTYPE		= '4';		// block special
	static const char DIRTYPE		= '5';		// directory
	static const char FIFOTYPE		= '6';		// FIFO special
	static const char CONTTYPE		= '7';		// reserved
	static const char XHDTYPE		= 'x';		// Extended header referring to the next file in the archive
	static const char XGLTYPE		= 'g';		// Global extended header
	// Bits used in the mode field, values in octal. 
	static const UInt32 TSUID		= 04000;	// set UID on execution
	static const UInt32 TSGID		= 02000;	// set GID on execution
	static const UInt32 TSVTX		= 01000;	// reserved
												// file permissions
	static const UInt32 TUREAD		= 00400;	// read by owner
	static const UInt32 TUWRITE		= 00200;	// write by owner
	static const UInt32 TUEXEC		= 00100;	// execute/search by owner
	static const UInt32 TGREAD		= 00040;	// read by group
	static const UInt32 TGWRITE		= 00020;	// write by group
	static const UInt32 TGEXEC		= 00010;	// execute/search by group
	static const UInt32 TOREAD		= 00004;	// read by other
	static const UInt32 TOWRITE		= 00002;	// write by other
	static const UInt32 TOEXEC		= 00001;	// execute/search by other
private:
	size_t _offset;
	String _name;
	String _linkname;
	String _uname;
	String _gname;
	UInt32 _mode;
	UInt32 _uid;
	UInt32 _gid;
	size_t _size;
	RefPtr<DateTime> _pMtime;
	RefPtr<DateTime> _pAtime;
	RefPtr<DateTime> _pCtime;
	UInt32 _chksum;
	char _typeflag;
	UInt32 _devmajor;
	UInt32 _devminor;
public:
	Header() {}
	Header(const Header& hdr);
	void Initialize();
	bool SetRawHeader(const star_header& rawHdr);
	bool ComposeHeaderBlock(void* memBlock) const;
	void SetOffset(size_t offset) { _offset = offset; }
	size_t GetOffset() const { return _offset; }
	void SetName(const char* name) { _name = name; }
	const char* GetName() const { return _name.c_str(); }
	const char* GetFileName() const { return _name.c_str(); }
	void SetLinkName(const char* linkname) { _linkname = linkname; }
	const char* GetLinkName() const { return _linkname.c_str(); }
	void SetUName(const char* uname) { _uname = uname; }
	const char* GetUName() const { return _uname.c_str(); }
	void SetGName(const char* gname) { _gname = gname; }
	const char* GetGName() const { return _gname.c_str(); }
	void SetMode(UInt32 mode) { _mode = mode; }
	UInt32 GetMode() const { return _mode; }
	void SetUid(UInt32 uid) { _uid = uid; }
	UInt32 GetUid() const { return _uid; }
	void SetGid(UInt32 gid) { _gid = gid; }
	UInt32 GetGid() const { return _gid; }
	void SetSize(size_t size) { _size = size; }
	size_t GetSize() const { return _size; }
	void SetMTime(DateTime* pMtime) { _pMtime.reset(pMtime); }
	const DateTime& GetMTime() const { return *_pMtime; }
	void SetATime(DateTime* pAtime) { _pAtime.reset(pAtime); }
	const DateTime& GetATime() const { return *_pAtime; }
	void SetCTime(DateTime* pCtime) { _pCtime.reset(pCtime); }
	const DateTime& GetCTime() const { return *_pCtime; }
	void SetChksum(UInt32 chksum) { _chksum = chksum; }
	UInt32 GetChksum() const { return _chksum; }
	void SetTypeFlag(char typeflag) { _typeflag = typeflag; }
	char GetTypeFlag() const { return _typeflag; }
	bool IsFolder() const { return GetTypeFlag() == DIRTYPE; }
	void SetDevMajor(UInt32 devmajor) { _devmajor = devmajor; }
	UInt32 GetDevMajor() const { return _devmajor; }
	void SetDevMinor(UInt32 devminor) { _devminor = devminor; }
	UInt32 GetDevMinor() const { return _devminor; }
	UInt32 CalcBlocks() const { return (_size + BLOCKSIZE - 1) / BLOCKSIZE; }
	bool Write(Stream& stream);
public:
	static Header* Read(Stream& stream);
	static UInt64 OctetToUInt64(const char* octet, size_t len);
	static UInt32 OctetToUInt32(const char* octet, size_t len) {
		return static_cast<UInt32>(OctetToUInt64(octet, len));
	}
};

Gurax_EndModuleScope(tar)

#endif
