//==============================================================================
// VType_Content.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_CONTENT_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_CONTENT_H
#include <gurax.h>
#include "Content.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_Content
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Content : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Content VTYPE_Content;

//------------------------------------------------------------------------------
// Value_Content
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Content : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Content);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Content");
protected:
	RefPtr<Content> _pContent;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Content() = delete;
	explicit Value_Content(Content* pContent, VType& vtype = VTYPE_Content) :
		Value_Object(vtype), _pContent(pContent) {}
	// Copy constructor/operator
	Value_Content(const Value_Content& src) :
		Value_Object(src), _pContent(src._pContent->Reference()) {}
	Value_Content& operator=(const Value_Content& src) = delete;
	// Move constructor/operator
	Value_Content(Value_Content&& src) noexcept = delete;
	Value_Content& operator=(Value_Content&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Content() = default;
public:
	Content& GetContent() { return *_pContent; }
	const Content& GetContent() const { return *_pContent; }
public:
	static Content& GetContent(Value& value) {
		return dynamic_cast<Value_Content&>(value).GetContent();
	}
	static const Content& GetContent(const Value& value) {
		return dynamic_cast<const Value_Content&>(value).GetContent();
	}
	static Content* GetEntityPtr(Value& value) { return &GetContent(value); }
	static const Content* GetEntityPtr(const Value& value) { return &GetContent(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetContent().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetContent().IsEqualTo(Value_Content::GetContent(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetContent().IsLessThan(Value_Content::GetContent(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
