//==============================================================================
// Stat.h
//==============================================================================
#ifndef GURAX_MODULE_ZIP_STAT_H
#define GURAX_MODULE_ZIP_STAT_H
#include <gurax.h>
#include "ZIPFormat.h"

Gurax_BeginModuleScope(zip)

//------------------------------------------------------------------------------
// Stat
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Stat : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Stat);
private:
	CentralFileHeader _centralFileHeader;
public:
	// Constructor
	Stat() {}
	// Copy constructor/operator
	Stat(const Stat& src) = delete;
	Stat& operator=(const Stat& src) = delete;
	// Move constructor/operator
	Stat(Stat&& src) = delete;
	Stat& operator=(Stat&& src) noexcept = delete;
protected:
	~Stat() = default;
public:
	CentralFileHeader& GetCentralFileHeader() { return _centralFileHeader; }
	const CentralFileHeader& GetCentralFileHeader() const { return _centralFileHeader; }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Stat& other) const { return this == &other; }
	bool IsEqualTo(const Stat& other) const { return IsIdentical(other); }
	bool IsLessThan(const Stat& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// StatList
//------------------------------------------------------------------------------
class StatList : public std::vector<Stat*> {
};

//------------------------------------------------------------------------------
// StatOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE StatOwner : public StatList {
public:
	~StatOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(zip)

#endif
