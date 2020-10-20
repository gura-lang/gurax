//==============================================================================
// VType_FrameThis.h
//==============================================================================
#ifndef GURAX_VTYPE_FRAMETHIS_H
#define GURAX_VTYPE_FRAMETHIS_H
#include "VType_Object.h"
#include "Frame.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_FrameThis
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_FrameThis : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_FrameThis VTYPE_FrameThis;

//------------------------------------------------------------------------------
// Value_FrameThis
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_FrameThis : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_FrameThis);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_FrameThis");
protected:
	RefPtr<Frame> _pFrame;
public:
	static VType& vtype;
public:
	// Constructor
	Value_FrameThis() = delete;
	explicit Value_FrameThis(Frame* pFrame, VType& vtype = VTYPE_FrameThis) :
		Value_Object(vtype), _pFrame(pFrame) {}
	// Copy constructor/operator
	Value_FrameThis(const Value_FrameThis& src) :
		Value_Object(src), _pFrame(src._pFrame->Reference()) {}
	Value_FrameThis& operator=(const Value_FrameThis& src) = delete;
	// Move constructor/operator
	Value_FrameThis(Value_FrameThis&& src) = delete;
	Value_FrameThis& operator=(Value_FrameThis&& src) noexcept = delete;
protected:
	// Destructor
	~Value_FrameThis() = default;
public:
	Frame& GetFrame() { return *_pFrame; }
	const Frame& GetFrame() const { return *_pFrame; }
public:
	static Frame& GetFrame(Value& value) { return dynamic_cast<Value_FrameThis&>(value).GetFrame(); }
	static const Frame& GetFrame(const Value& value) { return dynamic_cast<const Value_FrameThis&>(value).GetFrame(); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetFrame().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetFrame().IsEqualTo(dynamic_cast<const Value_FrameThis&>(value).GetFrame());
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetFrame().IsLessThan(dynamic_cast<const Value_FrameThis&>(value).GetFrame()) :
			GetVType().IsLessThan(value.GetVType());
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
