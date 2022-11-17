//==============================================================================
// VType_CURLU.h
//==============================================================================
#ifndef GURAX_MODULE_CURL_VTYPE_CURLU_H
#define GURAX_MODULE_CURL_VTYPE_CURLU_H
#include <gurax.h>
#include <curl/curl.h>

Gurax_BeginModuleScope(curl)

//------------------------------------------------------------------------------
// VType_CURLU
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_CURLU : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_CURLU VTYPE_CURLU;

//------------------------------------------------------------------------------
// Value_CURLU
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_CURLU : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_CURLU);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_CURLU");
protected:
	CURLU* _url;
public:
	static VType& vtype;
public:
	// Constructor
	Value_CURLU() = delete;
	explicit Value_CURLU(CURLU* url, VType& vtype = VTYPE_CURLU) :
		Value_Object(vtype), _url(url) {}
	// Copy constructor/operator
	Value_CURLU(const Value_CURLU& src) :
		Value_Object(src), _url(src._url) {}
	Value_CURLU& operator=(const Value_CURLU& src) = delete;
	// Move constructor/operator
	Value_CURLU(Value_CURLU&& src) noexcept = delete;
	Value_CURLU& operator=(Value_CURLU&& src) noexcept = delete;
protected:
	// Destructor
	~Value_CURLU() = default;
public:
	CURLU* GetEntityPtr() { return _url; }
	const CURLU* GetEntityPtr() const { return _url; }
public:
	static CURLU* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_CURLU&>(value).GetEntityPtr();
	}
	static const CURLU* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_CURLU&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_CURLU::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_CURLU::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(curl)

#endif
