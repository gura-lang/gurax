//==============================================================================
// VType_CURL.h
//==============================================================================
#ifndef GURAX_MODULE_CURL_VTYPE_CURL_H
#define GURAX_MODULE_CURL_VTYPE_CURL_H
#include <gurax.h>
#include <curl/curl.h>

Gurax_BeginModuleScope(curl)

//------------------------------------------------------------------------------
// VType_CURL
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_CURL : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_CURL VTYPE_CURL;

//------------------------------------------------------------------------------
// Value_CURL
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_CURL : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_CURL);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_CURL");
protected:
	CURL* _pCURL;
public:
	static VType& vtype;
public:
	// Constructor
	Value_CURL() = delete;
	explicit Value_CURL(CURL* pCURL, VType& vtype = VTYPE_CURL) :
		Value_Object(vtype), _pCURL(pCURL) {}
	// Copy constructor/operator
	Value_CURL(const Value_CURL& src) :
		Value_Object(src), _pCURL(src._pCURL) {}
	Value_CURL& operator=(const Value_CURL& src) = delete;
	// Move constructor/operator
	Value_CURL(Value_CURL&& src) noexcept = delete;
	Value_CURL& operator=(Value_CURL&& src) noexcept = delete;
protected:
	// Destructor
	~Value_CURL() = default;
public:
	CURL* GetEntityPtr() { return _pCURL; }
	const CURL* GetEntityPtr() const { return _pCURL; }
public:
	static CURL* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_CURL&>(value).GetEntityPtr();
	}
	static const CURL* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_CURL&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_CURL::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_CURL::GetEntityPtr(value) :
			GetVType().IsLessThan(value.GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(curl)

#endif
