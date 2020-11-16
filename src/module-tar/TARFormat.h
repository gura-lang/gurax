//==============================================================================
// TARFormat.h
// http://www.gnu.org/software/tar/manual/html_node/Standard.html
//==============================================================================
#include <gurax.h>

extern const int BLOCKSIZE;

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
// Header declaration
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
	DateTime _mtime;
	DateTime _atime;
	DateTime _ctime;
	UInt32 _chksum;
	char _typeflag;
	UInt32 _devmajor;
	UInt32 _devminor;
public:
	Header();
	Header(const Header &hdr);
	void Initialize();
	bool SetRawHeader(Signal &sig, const star_header &rawHdr);
	void ComposeHeaderBlock(void *memBlock) const;
	void SetOffset(size_t offset) { _offset = offset; }
	size_t GetOffset() const { return _offset; }
	void SetName(const char *name) {
		::memset(_name, 0x00, sizeof(_name)), ::strcpy(_name, name);
	}
	const char *GetName() const { return _name; }
	void SetLinkName(const char *linkname) {
		::memset(_linkname, 0x00, sizeof(_linkname)), ::strcpy(_linkname, linkname);
	}
	const char *GetLinkName() const { return _linkname; }
	void SetUName(const char *uname) {
		::memset(_uname, 0x00, sizeof(_uname)), ::strcpy(_uname, uname);
	}
	const char *GetUName() const { return _uname; }
	void SetGName(const char *gname) {
		::memset(_gname, 0x00, sizeof(_gname)), ::strcpy(_gname, gname);
	}
	const char *GetGName() const { return _gname; }
	void SetMode(UInt32 mode) { _mode = mode; }
	UInt32 GetMode() const { return _mode; }
	void SetUid(UInt32 uid) { _uid = uid; }
	UInt32 GetUid() const { return _uid; }
	void SetGid(UInt32 gid) { _gid = gid; }
	UInt32 GetGid() const { return _gid; }
	void SetSize(size_t size) { _size = size; }
	size_t GetSize() const { return _size; }
	void SetMTime(const DateTime &mtime) { _mtime = mtime; }
	DateTime GetMTime() const { return _mtime; }
	void SetATime(const DateTime &atime) { _atime = atime; }
	DateTime GetATime() const { return _atime; }
	void SetCTime(const DateTime &ctime) { _ctime = ctime; }
	DateTime GetCTime() const { return _ctime; }
	void SetChksum(UInt32 chksum) { _chksum = chksum; }
	UInt32 GetChksum() const { return _chksum; }
	void SetTypeFlag(char typeflag) { _typeflag = typeflag; }
	char GetTypeFlag() const { return _typeflag; }
	void SetDevMajor(UInt32 devmajor) { _devmajor = devmajor; }
	UInt32 GetDevMajor() const { return _devmajor; }
	void SetDevMinor(UInt32 devminor) { _devminor = devminor; }
	UInt32 GetDevMinor() const { return _devminor; }
	UInt32 CalcBlocks() const {
		return (_size + BLOCKSIZE - 1) / BLOCKSIZE;
	}
};
