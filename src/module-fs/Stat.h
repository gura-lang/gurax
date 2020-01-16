//==============================================================================
// Stat.h
//==============================================================================
#ifndef GURAX_MODULE_FS_STAT_H
#define GURAX_MODULE_FS_STAT_H
#include <gurax.h>

Gurax_BeginModuleScope(fs)

//------------------------------------------------------------------------------
// Stat
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Stat : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Stat);
public:
	using Flags = UInt32;
	struct Flag {
		static const Flags Dir	= (1 << 0);
		static const Flags Chr	= (1 << 1);
		static const Flags Blk	= (1 << 2);
		static const Flags Reg	= (1 << 3);
		static const Flags Fifo	= (1 << 4);
		static const Flags Lnk	= (1 << 5);
		static const Flags Sock	= (1 << 6);
	};
private:
	RefPtr<DateTime> _pDateTimeC;
	RefPtr<DateTime> _pDateTimeM;
	RefPtr<DateTime> _pDateTimeA;
	String _pathName;
	UInt32 _flags;
	UInt32 _mode;
	size_t _bytes;
	long _uid;
	long _gid;
public:
	Stat() : _flags(0), _mode(0), _bytes(0), _uid(0), _gid(0) {}
	Stat(DateTime* pDateTimeC, DateTime* pDateTimeM, DateTime* pDateTimeA,
		 String pathName, UInt32 flags, UInt32 mode, size_t bytes, long uid, long gid) :
		_pDateTimeC(pDateTimeC), _pDateTimeM(pDateTimeM), _pDateTimeA(pDateTimeA),
		_pathName(pathName), _flags(flags), _mode(mode),
		_bytes(bytes), _uid(uid), _gid(gid) {}
	Stat(const Stat& stat) :
		_pDateTimeC(stat._pDateTimeC->Reference()), _pDateTimeM(stat._pDateTimeM->Reference()),
		_pDateTimeA(stat._pDateTimeA->Reference()),
		_pathName(stat._pathName), _flags(stat._flags), _mode(stat._mode),
		_bytes(stat._bytes), _uid(stat._uid), _gid(stat._gid) {}
	Stat(const char* pathName, const struct stat& sb);
#if defined(GURA_ON_MSWIN)
	Stat(const char* pathName, const BY_HANDLE_FILE_INFORMATION& attrData);
	Stat(const char* pathName, const WIN32_FILE_ATTRIBUTE_DATA& attrData);
	Stat(const char* pathName, const WIN32_FIND_DATA& findData);
#endif
protected:
	~Stat() = default;
public:
	static Stat* Create(const char* pathName);
	const DateTime& GetDateTimeA() const { return *_pDateTimeA; }
	const DateTime& GetDateTimeM() const { return *_pDateTimeM; }
	const DateTime& GetDateTimeC() const { return *_pDateTimeC; }
	const char* GetPathName() const { return _pathName.c_str(); }
	size_t GetSize() const { return _bytes; }
	bool IsDir() const { return (_flags & Flag::Dir) != 0; }
	bool IsChr() const { return (_flags & Flag::Chr) != 0; }
	bool IsBlk() const { return (_flags & Flag::Blk) != 0; }
	bool IsReg() const { return (_flags & Flag::Reg) != 0; }
	bool IsFifo() const { return (_flags & Flag::Fifo) != 0; }
	bool IsLnk() const { return (_flags & Flag::Lnk) != 0; }
	bool IsSock() const { return (_flags & Flag::Sock) != 0; }
	UInt32 GetMode() const { return _mode; }
	long GetUid() const { return _uid; }
	long GetGid() const { return _gid; }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Stat& stat) const { return this == &stat; }
	bool IsEqualTo(const Stat& stat) const { return IsIdentical(stat); }
	bool IsLessThan(const Stat& stat) const { return this < &stat; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(fs)

#endif
