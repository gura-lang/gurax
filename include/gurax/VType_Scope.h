//==============================================================================
// VType_Scope.h
//==============================================================================
#ifndef GURAX_VTYPE_SCOPE_H
#define GURAX_VTYPE_SCOPE_H
#include "VType_Object.h"
#include "Frame.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Scope
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Scope : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Scope VTYPE_Scope;

//------------------------------------------------------------------------------
// Value_Scope
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Scope : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Scope);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Scope");
protected:
	RefPtr<Frame> _pFrame;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Scope() = delete;
	explicit Value_Scope(Frame* pFrame, VType& vtype = VTYPE_Scope) :
		Value_Object(vtype), _pFrame(pFrame) {}
	// Copy constructor/operator
	Value_Scope(const Value_Scope& src) :
		Value_Object(src), _pFrame(src._pFrame->Reference()) {}
	Value_Scope& operator=(const Value_Scope& src) = delete;
	// Move constructor/operator
	Value_Scope(Value_Scope&& src) = delete;
	Value_Scope& operator=(Value_Scope&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Scope() = default;
public:
	Frame& GetFrame() { return *_pFrame; }
	const Frame& GetFrame() const { return *_pFrame; }
public:
	static Frame& GetFrame(Value& value) { return dynamic_cast<Value_Scope&>(value).GetFrame(); }
	static const Frame& GetFrame(const Value& value) { return dynamic_cast<const Value_Scope&>(value).GetFrame(); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetFrame().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetFrame().IsEqualTo(dynamic_cast<const Value_Scope&>(value).GetFrame());
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetFrame().IsLessThan(dynamic_cast<const Value_Scope&>(value).GetFrame()) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
public:
	// Virtual functions for runtime process
	virtual void GatherMemberSymbol(SymbolList& symbolList) const override {
		GetFrame().GatherSymbol(symbolList);
	}
	virtual bool CanEvalAsMethod(const Function& function) const override;
	virtual Value* DoGetProperty(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag) override;
	virtual bool DoSetProperty(const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr) override;
};

}

#endif
