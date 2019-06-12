//==============================================================================
// VType_PropHandler.h
//==============================================================================
#ifndef GURAX_VTYPE_PROPHANDLER_H
#define GURAX_VTYPE_PROPHANDLER_H
#include "VType_Object.h"
#include "PropHandler.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_PropHandler
//------------------------------------------------------------------------------
class VType_PropHandler : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern VType_PropHandler VTYPE_PropHandler;

//------------------------------------------------------------------------------
// Value_PropHandler
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_PropHandler : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_PropHandler);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_PropHandler");
protected:
	RefPtr<PropHandler> _pPropHandler;
public:
	// Constructor
	Value_PropHandler() = delete;
	Value_PropHandler(PropHandler* pPropHandler, VType& vtype = VTYPE_PropHandler) :
		Value_Object(vtype), _pPropHandler(pPropHandler) {}
	// Copy constructor/operator
	Value_PropHandler(const Value_PropHandler& src) :
		Value_Object(src), _pPropHandler(src._pPropHandler->Reference()) {}
	Value_PropHandler& operator=(const Value_PropHandler& src) = delete;
	// Move constructor/operator
	Value_PropHandler(Value_PropHandler&& src) = delete;
	Value_PropHandler& operator=(Value_PropHandler&& src) noexcept = delete;
protected:
	// Destructor
	~Value_PropHandler() = default;
public:
	PropHandler& GetPropHandler() { return *_pPropHandler; }
	const PropHandler& GetPropHandler() const { return *_pPropHandler; }
public:
	static PropHandler& GetPropHandler(Value& value) {
		return dynamic_cast<Value_PropHandler&>(value).GetPropHandler();
	}
	static const PropHandler& GetPropHandler(const Value& value) {
		return dynamic_cast<const Value_PropHandler&>(value).GetPropHandler();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetPropHandler().CalcHash();
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetPropHandler().IsEqualTo(Value_PropHandler::GetPropHandler(*pValue));
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetPropHandler().IsLessThan(Value_PropHandler::GetPropHandler(*pValue)) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDetail(const StringStyle& ss) const override {
		return GetPropHandler().ToString(ss);
	}
};

}

#endif
