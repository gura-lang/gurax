//==============================================================================
// DirRecord.h
//==============================================================================
#ifndef GURAX_DIRRECORD_H
#define GURAX_DIRRECORD_H

namespace Gurax {

//------------------------------------------------------------------------------
// DirRecord
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE DirRecord : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(DirRecord);
public:
	// Constructor
	DirRecord() {}
	// Copy constructor/operator
	DirRecord(const DirRecord& src) = delete;
	DirRecord& operator=(const DirRecord& src) = delete;
	// Move constructor/operator
	DirRecord(DirRecord&& src) = delete;
	DirRecord& operator=(DirRecord&& src) noexcept = delete;
protected:
	~DirRecord() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const DirRecord& pathMgr) const { return this == &pathMgr; }
	bool IsEqualTo(const DirRecord& pathMgr) const { return IsIdentical(pathMgr); }
	bool IsLessThan(const DirRecord& pathMgr) const { return this < &pathMgr; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// DirRecordList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE DirRecordList : public std::vector<DirRecord*> {
public:
	using std::vector<DirRecord*>::vector;
};

//------------------------------------------------------------------------------
// DirRecordOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE DirRecordOwner : public DirRecordList {
public:
	~DirRecordOwner() { Clear(); }
	void Clear();
};

}

#endif
