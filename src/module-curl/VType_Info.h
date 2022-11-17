//==============================================================================
// VType_Info.h
//==============================================================================
#ifndef GURAX_MODULE_CURL_VTYPE_INFO_H
#define GURAX_MODULE_CURL_VTYPE_INFO_H
#include <gurax.h>
#include "Info.h"

Gurax_BeginModuleScope(curl)

//------------------------------------------------------------------------------
// VType_Info
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Info : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Info VTYPE_Info;

//------------------------------------------------------------------------------
// Value_Info
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Info : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Info);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Info");
protected:
	RefPtr<Info> _pInfo;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Info() = delete;
	explicit Value_Info(Info* pInfo, VType& vtype = VTYPE_Info) :
		Value_Object(vtype), _pInfo(pInfo) {}
	// Copy constructor/operator
	Value_Info(const Value_Info& src) :
		Value_Object(src), _pInfo(src._pInfo->Reference()) {}
	Value_Info& operator=(const Value_Info& src) = delete;
	// Move constructor/operator
	Value_Info(Value_Info&& src) noexcept = delete;
	Value_Info& operator=(Value_Info&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Info() = default;
public:
	Info& GetInfo() { return *_pInfo; }
	const Info& GetInfo() const { return *_pInfo; }
public:
	static Info& GetInfo(Value& value) {
		return dynamic_cast<Value_Info&>(value).GetInfo();
	}
	static const Info& GetInfo(const Value& value) {
		return dynamic_cast<const Value_Info&>(value).GetInfo();
	}
	static Info* GetEntityPtr(Value& value) { return &GetInfo(value); }
	static const Info* GetEntityPtr(const Value& value) { return &GetInfo(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetInfo().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetInfo().IsEqualTo(Value_Info::GetInfo(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetInfo().IsLessThan(Value_Info::GetInfo(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
public:
	virtual Value* DoGetProperty(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag);
};

Gurax_EndModuleScope(curl)

#endif
