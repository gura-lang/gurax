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
	using Attrs = UInt32;
	struct Attr {
		static const Attrs Dir	= (1 << 22);
		static const Attrs Chr	= (1 << 21);
		static const Attrs Blk	= (1 << 20);
		static const Attrs Reg	= (1 << 19);
		static const Attrs Fifo	= (1 << 18);
		static const Attrs Lnk	= (1 << 17);
		static const Attrs Sock	= (1 << 16);
	};
private:
	String _pathName;
	UInt32 _attr;
	UInt32 _bytes;
	RefPtr<DateTime> _pDateTimeA;
	RefPtr<DateTime> _pDateTimeM;
	RefPtr<DateTime> _pDateTimeC;
	long _uid;
	long _gid;
public:
	Stat() : _attr(0), _bytes(0), _uid(0), _gid(0) {}
	Stat(String pathName, UInt32 attr, UInt32 bytes,
		 DateTime* pDateTimeA, DateTime* pDateTimeM, DateTime* pDateTimeC,
		 long uid, long gid) :
		_pathName(pathName), _attr(attr), _bytes(bytes),
		_pDateTimeA(pDateTimeA), _pDateTimeM(pDateTimeM), _pDateTimeC(pDateTimeC),
		_uid(uid), _gid(gid) {}
	Stat(const Stat& stat) :
		_pathName(stat._pathName), _attr(stat._attr), _bytes(stat._bytes),
		_pDateTimeA(stat._pDateTimeA->Reference()), _pDateTimeM(stat._pDateTimeM->Reference()),
		_pDateTimeC(stat._pDateTimeC->Reference()),
		_uid(stat._uid), _gid(stat._gid) {}
#if defined(GURA_ON_MSWIN)
	Stat(const char* pathName, const BY_HANDLE_FILE_INFORMATION& attrData);
	Stat(const char* pathName, const WIN32_FILE_ATTRIBUTE_DATA& attrData);
	Stat(const char* pathName, const WIN32_FIND_DATA& findData);
#else
	Stat(const char* pathName, const struct stat& stat);
#endif
protected:
	~Stat() = default;
public:
	static Stat* Generate(const char* pathName);
	const char* GetPathName() const { return _pathName.c_str(); }
	ULong GetSize() const { return _bytes; }
	const DateTime& GetDateTimeA() const { return *_pDateTimeA; }
	const DateTime& GetDateTimeM() const { return *_pDateTimeM; }
	const DateTime& GetDateTimeC() const { return *_pDateTimeC; }
	long GetUid() const { return _uid; }
	long GetGid() const { return _gid; }
	long GetMode() const { return _attr & 0777; }
	bool IsDir() const { return (_attr & Attr::Dir) != 0; }
	bool IsChr() const { return (_attr & Attr::Chr) != 0; }
	bool IsBlk() const { return (_attr & Attr::Blk) != 0; }
	bool IsReg() const { return (_attr & Attr::Reg) != 0; }
	bool IsFifo() const { return (_attr & Attr::Fifo) != 0; }
	bool IsLnk() const { return (_attr & Attr::Lnk) != 0; }
	bool IsSock() const { return (_attr & Attr::Sock) != 0; }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Stat& stat) const { return this == &stat; }
	bool IsEqualTo(const Stat& stat) const { return IsIdentical(stat); }
	bool IsLessThan(const Stat& stat) const { return this < &stat; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(fs)

#endif
