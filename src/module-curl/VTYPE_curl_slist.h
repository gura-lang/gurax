//==============================================================================
// VType_curl_slist.h
//==============================================================================
#ifndef GURAX_MODULE_CURL_VTYPE_CURL_SLIST_H
#define GURAX_MODULE_CURL_VTYPE_CURL_SLIST_H
#include <gurax.h>
#include <curl/curl.h>

Gurax_BeginModuleScope(curl)

//------------------------------------------------------------------------------
// VType_curl_slist
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_curl_slist : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_curl_slist VTYPE_curl_slist;

//------------------------------------------------------------------------------
// Value_curl_slist
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_curl_slist : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_curl_slist);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_curl_slist");
protected:
	curl_slist* _slist;
public:
	static VType& vtype;
public:
	// Constructor
	Value_curl_slist() = delete;
	explicit Value_curl_slist(curl_slist* slist, VType& vtype = VTYPE_curl_slist) :
		Value_Object(vtype), _slist(slist) {}
	// Copy constructor/operator
	Value_curl_slist(const Value_curl_slist& src) :
		Value_Object(src), _slist(src._slist) {}
	Value_curl_slist& operator=(const Value_curl_slist& src) = delete;
	// Move constructor/operator
	Value_curl_slist(Value_curl_slist&& src) noexcept = delete;
	Value_curl_slist& operator=(Value_curl_slist&& src) noexcept = delete;
protected:
	// Destructor
	~Value_curl_slist() = default;
public:
	curl_slist* GetEntityPtr() { return _slist; }
	const curl_slist* GetEntityPtr() const { return _slist; }
public:
	static curl_slist* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_curl_slist&>(value).GetEntityPtr();
	}
	static const curl_slist* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_curl_slist&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_curl_slist::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_curl_slist::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(curl)

#endif
