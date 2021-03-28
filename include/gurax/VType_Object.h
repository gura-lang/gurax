//==============================================================================
// VType_Object.h
//==============================================================================
#ifndef GURAX_VTYPE_OBJECT_H
#define GURAX_VTYPE_OBJECT_H
#include "Value.h"

namespace Gurax {

class VTypeCustom;

//------------------------------------------------------------------------------
// VType_Object
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Object : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Object VTYPE_Object;

//------------------------------------------------------------------------------
// Value_Object
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Object : public Value {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Object);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Object");
public:
	class CustomPack {
	private:
		VTypeCustom& _vtypeCustom;
		RefPtr<Processor> _pProcessor;
		Value* _pValueThis;
		RefPtr<ValueOwner> _pValuesProp;
	public:
		CustomPack(VTypeCustom& vtypeCustom, Processor* pProcessor, Value* pValueThis);
		virtual ~CustomPack();
		bool InitCustomProp();
		void SetCustomProp(size_t iProp, Value* pValue);
		Value* GetCustomProp(size_t iProp);
	};
public:
	static VType& vtype;
protected:
	std::unique_ptr<CustomPack> _pCustomPack;
public:
	// Constructor
	Value_Object() : Value_Object(VTYPE_Object) {}
	explicit Value_Object(VType& vtype) : Value(vtype) {}
	// Copy constructor/operator
	Value_Object(const Value_Object& src) : Value(src) {}
	Value_Object& operator=(const Value_Object& src) = delete;
	// Move constructor/operator
	Value_Object(Value_Object&& src) = delete;
	Value_Object& operator=(Value_Object&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Value_Object() = default;
public:
	bool InitCustomProp(VTypeCustom& vtypeCustom, Processor* pProcessor) {
		_pCustomPack.reset(new CustomPack(vtypeCustom, pProcessor, this));
		return _pCustomPack->InitCustomProp();
	}
	void SetCustomProp(size_t iProp, Value* pValue) {
		if (_pCustomPack) _pCustomPack->SetCustomProp(iProp, pValue);
	}
	Value* GetCustomProp(size_t iProp) {
		if (_pCustomPack) return _pCustomPack->GetCustomProp(iProp);
		return Value::nil();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return nullptr; }
	virtual size_t DoCalcHash() const override { return 0; }
	virtual bool IsEqualTo(const Value& value) const override { return IsSameType(value); }
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)? false : GetVType().IsLessThan(value.GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif
