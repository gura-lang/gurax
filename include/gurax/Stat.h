//==============================================================================
// Stat.h
//==============================================================================
#ifndef GURAX_STAT_H
#define GURAX_STAT_H
#include "Referable.h"
#include "ListBase.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Stat
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Stat : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Stat);
public:
	using Flags = UInt32;
	struct GURAX_DLLDECLARE Flag {
		static const Flags Dir	= (1 << 0);
		static const Flags Chr	= (1 << 1);
		static const Flags Blk	= (1 << 2);
		static const Flags Reg	= (1 << 3);
		static const Flags Fifo	= (1 << 4);
		static const Flags Lnk	= (1 << 5);
		static const Flags Sock	= (1 << 6);
	};
protected:
	RefPtr<DateTime> _pDateTimeC;
	RefPtr<DateTime> _pDateTimeM;
	RefPtr<DateTime> _pDateTimeA;
	String _name;
	UInt32 _flags;
	UInt16 _mode;
	size_t _bytes;
	long _uid;
	long _gid;
public:
	// Constructor
	Stat(DateTime* pDateTimeC, DateTime* pDateTimeM, DateTime* pDateTimeA,
		 String name, UInt32 flags, UInt16 mode, size_t bytes, long uid, long gid) :
		_pDateTimeC(pDateTimeC), _pDateTimeM(pDateTimeM), _pDateTimeA(pDateTimeA),
		_name(name), _flags(flags), _mode(mode), _bytes(bytes), _uid(uid), _gid(gid) {}
	Stat(DateTime* pDateTime,
		 String name, UInt32 flags, UInt32 mode, size_t bytes, long uid, long gid) :
		_pDateTimeC(pDateTime), _pDateTimeM(pDateTime->Reference()), _pDateTimeA(pDateTime->Reference()),
		_name(name), _flags(flags), _mode(mode), _bytes(bytes), _uid(uid), _gid(gid) {}
	// Copy constructor/operator
	Stat(const Stat& src) = delete;
	Stat& operator=(const Stat& src) = delete;
	// Move constructor/operator
	Stat(Stat&& src) = delete;
	Stat& operator=(Stat&& src) noexcept = delete;
protected:
	virtual ~Stat() = default;
public:
	const DateTime& GetDateTimeC() const { return *_pDateTimeC; }
	const DateTime& GetDateTimeM() const { return *_pDateTimeM; }
	const DateTime& GetDateTimeA() const { return *_pDateTimeA; }
	const char* GetName() const { return _name.c_str(); }
	size_t GetBytes() const { return _bytes; }
	bool IsDir() const { return (_flags & Flag::Dir) != 0; }
	bool IsChr() const { return (_flags & Flag::Chr) != 0; }
	bool IsBlk() const { return (_flags & Flag::Blk) != 0; }
	bool IsReg() const { return (_flags & Flag::Reg) != 0; }
	bool IsFifo() const { return (_flags & Flag::Fifo) != 0; }
	bool IsLnk() const { return (_flags & Flag::Lnk) != 0; }
	bool IsSock() const { return (_flags & Flag::Sock) != 0; }
	UInt16 GetMode() const { return _mode; }
	long GetUid() const { return _uid; }
	long GetGid() const { return _gid; }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Stat& other) const { return this == &other; }
	bool IsEqualTo(const Stat& other) const { return IsIdentical(other); }
	bool IsLessThan(const Stat& other) const { return this < &other; }
	virtual String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// StatDummy
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE StatDummy : public Stat {
public:
	// Referable declaration
	Gurax_DeclareReferable(StatDummy);
public:
	StatDummy(String name);
};

//------------------------------------------------------------------------------
// StatList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE StatList : public ListBase<Stat*> {
public:
	Stat* FindByName(const char* fileName) const;
};

//------------------------------------------------------------------------------
// StatOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE StatOwner : public StatList {
public:
	~StatOwner() { Clear(); }
	void Clear();
};

}

#endif
