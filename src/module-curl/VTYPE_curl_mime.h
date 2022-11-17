//==============================================================================
// VType_curl_mime.h
//==============================================================================
#ifndef GURAX_MODULE_CURL_VTYPE_CURL_MIME_H
#define GURAX_MODULE_CURL_VTYPE_CURL_MIME_H
#include <gurax.h>
#include <curl/curl.h>

Gurax_BeginModuleScope(curl)

//------------------------------------------------------------------------------
// VType_curl_mime
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_curl_mime : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_curl_mime VTYPE_curl_mime;

//------------------------------------------------------------------------------
// Value_curl_mime
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_curl_mime : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_curl_mime);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_curl_mime");
protected:
	curl_mime* _mime;
public:
	static VType& vtype;
public:
	// Constructor
	Value_curl_mime() = delete;
	explicit Value_curl_mime(curl_mime* mime, VType& vtype = VTYPE_curl_mime) :
		Value_Object(vtype), _mime(mime) {}
	// Copy constructor/operator
	Value_curl_mime(const Value_curl_mime& src) :
		Value_Object(src), _mime(src._mime) {}
	Value_curl_mime& operator=(const Value_curl_mime& src) = delete;
	// Move constructor/operator
	Value_curl_mime(Value_curl_mime&& src) noexcept = delete;
	Value_curl_mime& operator=(Value_curl_mime&& src) noexcept = delete;
protected:
	// Destructor
	~Value_curl_mime() = default;
public:
	curl_mime* GetEntityPtr() { return _mime; }
	const curl_mime* GetEntityPtr() const { return _mime; }
public:
	static curl_mime* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_curl_mime&>(value).GetEntityPtr();
	}
	static const curl_mime* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_curl_mime&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_curl_mime::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_curl_mime::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(curl)

#endif
