//==============================================================================
// TARFormat.h
// http://www.gnu.org/software/tar/manual/html_node/Standard.html
//==============================================================================
#ifndef GURAX_MODULE_TAR_TARFORMAT_H
#define GURAX_MODULE_TAR_TARFORMAT_H
#include <gurax.h>

Gurax_BeginModuleScope(tar)

extern const int BLOCKSIZE;

extern const char *TMAGIC;
extern const int TMAGLEN;
extern const char *TVERSION;
extern const int TVERSLEN;

// Values used in typeflag field.
extern const char REGTYPE;
extern const char AREGTYPE;
extern const char LNKTYPE;
extern const char SYMTYPE;
extern const char CHRTYPE;
extern const char BLKTYPE;
extern const char DIRTYPE;
extern const char FIFOTYPE;
extern const char CONTTYPE;
extern const char XHDTYPE;
extern const char XGLTYPE;

// Bits used in the mode field, values in octal. 
extern const UInt32 TSUID;
extern const UInt32 TSGID;
extern const UInt32 TSVTX;
										// file permissions
extern const UInt32 TUREAD;
extern const UInt32 TUWRITE;
extern const UInt32 TUEXEC;
extern const UInt32 TGREAD;
extern const UInt32 TGWRITE;
extern const UInt32 TGEXEC;
extern const UInt32 TOREAD;
extern const UInt32 TOWRITE;
extern const UInt32 TOEXEC;

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
private:
	size_t _offset;
	char _name[100 + 1];
	char _linkname[100 + 1];
	char _uname[32 + 1];
	char _gname[32 + 1];
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
	void ComposeHeaderBlock(void* memBlock) const;
	void SetOffset(size_t offset) { _offset = offset; }
	size_t GetOffset() const { return _offset; }
	void SetName(const char* name) {
		::memset(_name, 0x00, sizeof(_name)), ::strcpy(_name, name);
	}
	const char* GetName() const { return _name; }
	void SetLinkName(const char* linkname) {
		::memset(_linkname, 0x00, sizeof(_linkname)), ::strcpy(_linkname, linkname);
	}
	const char* GetLinkName() const { return _linkname; }
	void SetUName(const char* uname) {
		::memset(_uname, 0x00, sizeof(_uname)), ::strcpy(_uname, uname);
	}
	const char* GetUName() const { return _uname; }
	void SetGName(const char* gname) {
		::memset(_gname, 0x00, sizeof(_gname)), ::strcpy(_gname, gname);
	}
	const char* GetGName() const { return _gname; }
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
public:
	static Header* Read(Stream& stream);
	static UInt64 OctetToUInt64(const char* octet, size_t len);
	static UInt32 OctetToUInt32(const char* octet, size_t len) {
		return static_cast<UInt32>(OctetToUInt64(octet, len));
	}
};

Gurax_EndModuleScope(tar)

#endif
