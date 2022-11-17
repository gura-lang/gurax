//==============================================================================
// VType_Pattern.h
//==============================================================================
#ifndef GURAX_MODULE_RE_VTYPE_PATTERN_H
#define GURAX_MODULE_RE_VTYPE_PATTERN_H
#include <gurax.h>
#include "Pattern.h"

Gurax_BeginModuleScope(re)

//------------------------------------------------------------------------------
// VType_Pattern
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Pattern : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
	virtual Value* DoCastFrom(const Value& value, DeclArg::Flags flags) const override;
};

extern GURAX_DLLDECLARE VType_Pattern VTYPE_Pattern;

//------------------------------------------------------------------------------
// Value_Pattern
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Pattern : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Pattern);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Pattern");
protected:
	RefPtr<Pattern> _pPattern;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Pattern() = delete;
	Value_Pattern(Pattern* pPattern, VType& vtype = VTYPE_Pattern) :
		Value_Object(vtype), _pPattern(pPattern) {}
	// Copy constructor/operator
	Value_Pattern(const Value_Pattern& src) :
		Value_Object(src), _pPattern(src._pPattern->Reference()) {}
	Value_Pattern& operator=(const Value_Pattern& src) = delete;
	// Move constructor/operator
	Value_Pattern(Value_Pattern&& src) = delete;
	Value_Pattern& operator=(Value_Pattern&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Pattern() = default;
public:
	Pattern& GetPattern() { return *_pPattern; }
	const Pattern& GetPattern() const { return *_pPattern; }
public:
	static Pattern& GetPattern(Value& value) {
		return dynamic_cast<Value_Pattern&>(value).GetPattern();
	}
	static const Pattern& GetPattern(const Value& value) {
		return dynamic_cast<const Value_Pattern&>(value).GetPattern();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetPattern().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetPattern().IsEqualTo(Value_Pattern::GetPattern(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetPattern().IsLessThan(Value_Pattern::GetPattern(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(re)

#endif
