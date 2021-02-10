//==============================================================================
// VType_ApplicationExtension.h
//==============================================================================
#ifndef GURAX_MODULE_GIF_VTYPE_APPLICATIONEXTENSION_H
#define GURAX_MODULE_GIF_VTYPE_APPLICATIONEXTENSION_H
#include <gurax.h>
#include "Content.h"

Gurax_BeginModuleScope(gif)

//------------------------------------------------------------------------------
// VType_ApplicationExtension
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_ApplicationExtension : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_ApplicationExtension VTYPE_ApplicationExtension;

//------------------------------------------------------------------------------
// Value_ApplicationExtension
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_ApplicationExtension : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_ApplicationExtension);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_ApplicationExtension");
protected:
	Content::ApplicationExtension& _ApplicationExtension;
	RefPtr<Content> _pContent;		// may be nullptr
public:
	static VType& vtype;
public:
	// Constructor
	Value_ApplicationExtension() = delete;
	Value_ApplicationExtension(Content::ApplicationExtension& ApplicationExtension, Content* pContent,
									VType& vtype = VTYPE_ApplicationExtension) :
		Value_Object(vtype), _ApplicationExtension(ApplicationExtension), _pContent(pContent) {}
	// Copy constructor/operator
	Value_ApplicationExtension(const Value_ApplicationExtension& src) :
		Value_Object(src), _ApplicationExtension(src._ApplicationExtension), _pContent(src._pContent->Reference()) {}
	Value_ApplicationExtension& operator=(const Value_ApplicationExtension& src) = delete;
	// Move constructor/operator
	Value_ApplicationExtension(Value_ApplicationExtension&& src) noexcept = delete;
	Value_ApplicationExtension& operator=(Value_ApplicationExtension&& src) noexcept = delete;
protected:
	// Destructor
	~Value_ApplicationExtension() = default;
public:
	Content::ApplicationExtension& GetApplicationExtension() { return _ApplicationExtension; }
	const Content::ApplicationExtension& GetApplicationExtension() const { return _ApplicationExtension; }
public:
	static Content::ApplicationExtension& GetApplicationExtension(Value& value) {
		return dynamic_cast<Value_ApplicationExtension&>(value).GetApplicationExtension();
	}
	static const Content::ApplicationExtension& GetApplicationExtension(const Value& value) {
		return dynamic_cast<const Value_ApplicationExtension&>(value).GetApplicationExtension();
	}
	static Content::ApplicationExtension* GetEntityPtr(Value& value) { return &GetApplicationExtension(value); }
	static const Content::ApplicationExtension* GetEntityPtr(const Value& value) { return &GetApplicationExtension(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr(*this));
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) && GetEntityPtr(*this) == GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr(*this) < GetEntityPtr(value) : GetVType().IsLessThan(value.GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(gif)

#endif
