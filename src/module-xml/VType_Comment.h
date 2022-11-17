//==============================================================================
// VType_Comment.h
//==============================================================================
#ifndef GURAX_MODULE_XML_VTYPE_COMMENT_H
#define GURAX_MODULE_XML_VTYPE_COMMENT_H
#include <gurax.h>
#include "Comment.h"
#include "VType_Node.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// VType_Comment
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Comment : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Comment VTYPE_Comment;

//------------------------------------------------------------------------------
// Value_Comment
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Comment : public Value_Node {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Comment);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Comment");
public:
	static VType& vtype;
public:
	// Constructor
	Value_Comment() = delete;
	explicit Value_Comment(Comment* pComment, VType& vtype = VTYPE_Comment) : Value_Node(pComment, vtype) {}
	// Copy constructor/operator
	Value_Comment(const Value_Comment& src) : Value_Node(src) {}
	Value_Comment& operator=(const Value_Comment& src) = delete;
	// Move constructor/operator
	Value_Comment(Value_Comment&& src) noexcept = delete;
	Value_Comment& operator=(Value_Comment&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Comment() = default;
public:
	Comment& GetComment() { return dynamic_cast<Comment&>(GetNode()); }
	const Comment& GetComment() const { return dynamic_cast<const Comment&>(GetNode()); }
public:
	static Comment& GetComment(Value& value) {
		return dynamic_cast<Value_Comment&>(value).GetComment();
	}
	static const Comment& GetComment(const Value& value) {
		return dynamic_cast<const Value_Comment&>(value).GetComment();
	}
	static Comment* GetEntityPtr(Value& value) { return &GetComment(value); }
	static const Comment* GetEntityPtr(const Value& value) { return &GetComment(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetComment().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetComment().IsEqualTo(Value_Comment::GetComment(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetComment().IsLessThan(Value_Comment::GetComment(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(xml)

#endif
