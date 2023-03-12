//==============================================================================
// VType_Connect.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_CONNECT_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_CONNECT_H
#include <gurax.h>
#include "Data.h"
#include "Connect.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_Connect
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Connect : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Connect VTYPE_Connect;

//------------------------------------------------------------------------------
// Value_Connect
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Connect : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Connect);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Connect");
protected:
	RefPtr<Connect> _pConnect;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Connect() = delete;
	explicit Value_Connect(Connect* pConnect, VType& vtype = VTYPE_Connect) :
		Value_Object(vtype), _pConnect(pConnect) {}
	// Copy constructor/operator
	Value_Connect(const Value_Connect& src) :
		Value_Object(src), _pConnect(src._pConnect->Reference()) {}
	Value_Connect& operator=(const Value_Connect& src) = delete;
	// Move constructor/operator
	Value_Connect(Value_Connect&& src) noexcept = delete;
	Value_Connect& operator=(Value_Connect&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Connect() = default;
public:
	Connect& GetConnect() { return *_pConnect; }
	const Connect& GetConnect() const { return *_pConnect; }
public:
	static Connect& GetConnect(Value& value) {
		return dynamic_cast<Value_Connect&>(value).GetConnect();
	}
	static const Connect& GetConnect(const Value& value) {
		return dynamic_cast<const Value_Connect&>(value).GetConnect();
	}
	static Connect* GetEntityPtr(Value& value) { return &GetConnect(value); }
	static const Connect* GetEntityPtr(const Value& value) { return &GetConnect(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetConnect().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetConnect().IsEqualTo(Value_Connect::GetConnect(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetConnect().IsLessThan(Value_Connect::GetConnect(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
