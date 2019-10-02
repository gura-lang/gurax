//==============================================================================
// VType_Match.h
//==============================================================================
#ifndef GURAX_MODULE_RE_VTYPE_MATCH_H
#define GURAX_MODULE_RE_VTYPE_MATCH_H
#include <gurax.h>
#include "Match.h"

Gurax_BeginModuleScope(re)

//------------------------------------------------------------------------------
// VType_Match
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Match : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern VType_Match VTYPE_Match;

//------------------------------------------------------------------------------
// Value_Match
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Match : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Match);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Match");
protected:
	RefPtr<Match> _pMatch;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Match() = delete;
	Value_Match(Match* pMatch, VType& vtype = VTYPE_Match) :
		Value_Object(vtype), _pMatch(pMatch) {}
	// Copy constructor/operator
	Value_Match(const Value_Match& src) :
		Value_Object(src), _pMatch(src._pMatch->Reference()) {}
	Value_Match& operator=(const Value_Match& src) = delete;
	// Move constructor/operator
	Value_Match(Value_Match&& src) = delete;
	Value_Match& operator=(Value_Match&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Match() = default;
public:
	Match& GetMatch() { return *_pMatch; }
	const Match& GetMatch() const { return *_pMatch; }
public:
	static Match& GetMatch(Value& value) {
		return dynamic_cast<Value_Match&>(value).GetMatch();
	}
	static const Match& GetMatch(const Value& value) {
		return dynamic_cast<const Value_Match&>(value).GetMatch();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetMatch().CalcHash();
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetMatch().IsEqualTo(Value_Match::GetMatch(*pValue));
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetMatch().IsLessThan(Value_Match::GetMatch(*pValue)) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDetail(const StringStyle& ss) const override {
		return GetMatch().ToString(ss);
	}
};

Gurax_EndModuleScope(re)

#endif
