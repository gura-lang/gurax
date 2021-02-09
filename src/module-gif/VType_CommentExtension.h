//==============================================================================
// VType_CommentExtension.h
//==============================================================================
#ifndef GURAX_MODULE_GIF_VTYPE_COMMENTEXTENSION_H
#define GURAX_MODULE_GIF_VTYPE_COMMENTEXTENSION_H
#include <gurax.h>
#include "Content.h"

Gurax_BeginModuleScope(gif)

//------------------------------------------------------------------------------
// VType_CommentExtension
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_CommentExtension : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_CommentExtension VTYPE_CommentExtension;

//------------------------------------------------------------------------------
// Value_CommentExtension
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_CommentExtension : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_CommentExtension);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_CommentExtension");
protected:
	RefPtr<Content> _pContent;
public:
	static VType& vtype;
public:
	// Constructor
	Value_CommentExtension() = delete;
	explicit Value_CommentExtension(Content* pContent, VType& vtype = VTYPE_CommentExtension) :
		Value_Object(vtype), _pContent(pContent) {}
	// Copy constructor/operator
	Value_CommentExtension(const Value_CommentExtension& src) :
		Value_Object(src), _pContent(src._pContent->Reference()) {}
	Value_CommentExtension& operator=(const Value_CommentExtension& src) = delete;
	// Move constructor/operator
	Value_CommentExtension(Value_CommentExtension&& src) noexcept = delete;
	Value_CommentExtension& operator=(Value_CommentExtension&& src) noexcept = delete;
protected:
	// Destructor
	~Value_CommentExtension() = default;
public:
	Content& GetContent() { return *_pContent; }
	const Content& GetContent() const { return *_pContent; }
public:
	static Content& GetContent(Value& value) {
		return dynamic_cast<Value_CommentExtension&>(value).GetContent();
	}
	static const Content& GetContent(const Value& value) {
		return dynamic_cast<const Value_CommentExtension&>(value).GetContent();
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
			GetContent().IsEqualTo(Value_CommentExtension::GetContent(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetContent().IsLessThan(Value_CommentExtension::GetContent(value)) :
			GetVType().IsLessThan(value.GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(gif)

#endif
