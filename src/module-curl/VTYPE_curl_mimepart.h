//==============================================================================
// VType_curl_mimepart.h
//==============================================================================
#ifndef GURAX_MODULE_CURL_VTYPE_CURL_MIMEPART_H
#define GURAX_MODULE_CURL_VTYPE_CURL_MIMEPART_H
#include <gurax.h>
#include <curl/curl.h>

Gurax_BeginModuleScope(curl)

//------------------------------------------------------------------------------
// VType_curl_mimepart
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_curl_mimepart : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_curl_mimepart VTYPE_curl_mimepart;

//------------------------------------------------------------------------------
// Value_curl_mimepart
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_curl_mimepart : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_curl_mimepart);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_curl_mimepart");
protected:
	curl_mimepart* _part;
public:
	static VType& vtype;
public:
	// Constructor
	Value_curl_mimepart() = delete;
	explicit Value_curl_mimepart(curl_mimepart* part, VType& vtype = VTYPE_curl_mimepart) :
		Value_Object(vtype), _part(part) {}
	// Copy constructor/operator
	Value_curl_mimepart(const Value_curl_mimepart& src) :
		Value_Object(src), _part(src._part) {}
	Value_curl_mimepart& operator=(const Value_curl_mimepart& src) = delete;
	// Move constructor/operator
	Value_curl_mimepart(Value_curl_mimepart&& src) noexcept = delete;
	Value_curl_mimepart& operator=(Value_curl_mimepart&& src) noexcept = delete;
protected:
	// Destructor
	~Value_curl_mimepart() = default;
public:
	curl_mimepart* GetEntityPtr() { return _part; }
	const curl_mimepart* GetEntityPtr() const { return _part; }
public:
	static curl_mimepart* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_curl_mimepart&>(value).GetEntityPtr();
	}
	static const curl_mimepart* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_curl_mimepart&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_curl_mimepart::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_curl_mimepart::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(curl)

#endif
