//==============================================================================
// VType_Frame.h
//==============================================================================
#ifndef GURAX_VTYPE_FRAME_H
#define GURAX_VTYPE_FRAME_H
#include "VType_Object.h"
#include "Frame.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Frame
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Frame : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Frame VTYPE_Frame;

//------------------------------------------------------------------------------
// Value_Frame
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Frame : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Frame);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Frame");
protected:
	RefPtr<Frame> _pFrame;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Frame() = delete;
	explicit Value_Frame(Frame* pFrame, VType& vtype = VTYPE_Frame) :
		Value_Object(vtype), _pFrame(pFrame) {}
	// Copy constructor/operator
	Value_Frame(const Value_Frame& src) :
		Value_Object(src), _pFrame(src._pFrame->Reference()) {}
	Value_Frame& operator=(const Value_Frame& src) = delete;
	// Move constructor/operator
	Value_Frame(Value_Frame&& src) = delete;
	Value_Frame& operator=(Value_Frame&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Frame() = default;
public:
	Frame& GetFrame() { return *_pFrame; }
	const Frame& GetFrame() const { return *_pFrame; }
public:
	static Frame& GetFrame(Value& value) { return dynamic_cast<Value_Frame&>(value).GetFrame(); }
	static const Frame& GetFrame(const Value& value) { return dynamic_cast<const Value_Frame&>(value).GetFrame(); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetFrame().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetFrame().IsEqualTo(dynamic_cast<const Value_Frame&>(value).GetFrame());
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetFrame().IsLessThan(dynamic_cast<const Value_Frame&>(value).GetFrame()) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif
