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
	Content::CommentExtension& _CommentExtension;
	RefPtr<Content> _pContent;		// may be nullptr
public:
	static VType& vtype;
public:
	// Constructor
	Value_CommentExtension() = delete;
	Value_CommentExtension(Content::CommentExtension& CommentExtension, Content* pContent,
									VType& vtype = VTYPE_CommentExtension) :
		Value_Object(vtype), _CommentExtension(CommentExtension), _pContent(pContent) {}
	// Copy constructor/operator
	Value_CommentExtension(const Value_CommentExtension& src) :
		Value_Object(src), _CommentExtension(src._CommentExtension), _pContent(src._pContent->Reference()) {}
	Value_CommentExtension& operator=(const Value_CommentExtension& src) = delete;
	// Move constructor/operator
	Value_CommentExtension(Value_CommentExtension&& src) noexcept = delete;
	Value_CommentExtension& operator=(Value_CommentExtension&& src) noexcept = delete;
protected:
	// Destructor
	~Value_CommentExtension() = default;
public:
	Content::CommentExtension& GetCommentExtension() { return _CommentExtension; }
	const Content::CommentExtension& GetCommentExtension() const { return _CommentExtension; }
public:
	static Content::CommentExtension& GetCommentExtension(Value& value) {
		return dynamic_cast<Value_CommentExtension&>(value).GetCommentExtension();
	}
	static const Content::CommentExtension& GetCommentExtension(const Value& value) {
		return dynamic_cast<const Value_CommentExtension&>(value).GetCommentExtension();
	}
	static Content::CommentExtension* GetEntityPtr(Value& value) { return &GetCommentExtension(value); }
	static const Content::CommentExtension* GetEntityPtr(const Value& value) { return &GetCommentExtension(value); }
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
			GetEntityPtr(*this) < GetEntityPtr(value) : GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(gif)

#endif
