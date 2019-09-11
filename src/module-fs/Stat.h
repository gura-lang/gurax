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
	
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Stat& stat) const { return this == &stat; }
	bool IsEqualTo(const Stat& stat) const { return IsIdentical(stat); }
	bool IsLessThan(const Stat& stat) const { return this < &stat; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(fs)

#endif
