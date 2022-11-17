//==============================================================================
// VType_LogicalScreenDescriptor.h
//==============================================================================
#ifndef GURAX_MODULE_GIF_VTYPE_LOGICALSCREENDESCRIPTOR_H
#define GURAX_MODULE_GIF_VTYPE_LOGICALSCREENDESCRIPTOR_H
#include <gurax.h>
#include "Content.h"

Gurax_BeginModuleScope(gif)

//------------------------------------------------------------------------------
// VType_LogicalScreenDescriptor
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_LogicalScreenDescriptor : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_LogicalScreenDescriptor VTYPE_LogicalScreenDescriptor;

//------------------------------------------------------------------------------
// Value_LogicalScreenDescriptor
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_LogicalScreenDescriptor : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_LogicalScreenDescriptor);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_LogicalScreenDescriptor");
protected:
	RefPtr<Content> _pContent;
public:
	static VType& vtype;
public:
	// Constructor
	Value_LogicalScreenDescriptor() = delete;
	explicit Value_LogicalScreenDescriptor(Content* pContent, VType& vtype = VTYPE_LogicalScreenDescriptor) :
		Value_Object(vtype), _pContent(pContent) {}
	// Copy constructor/operator
	Value_LogicalScreenDescriptor(const Value_LogicalScreenDescriptor& src) :
		Value_Object(src), _pContent(src._pContent->Reference()) {}
	Value_LogicalScreenDescriptor& operator=(const Value_LogicalScreenDescriptor& src) = delete;
	// Move constructor/operator
	Value_LogicalScreenDescriptor(Value_LogicalScreenDescriptor&& src) noexcept = delete;
	Value_LogicalScreenDescriptor& operator=(Value_LogicalScreenDescriptor&& src) noexcept = delete;
protected:
	// Destructor
	~Value_LogicalScreenDescriptor() = default;
public:
	Content& GetContent() { return *_pContent; }
	const Content& GetContent() const { return *_pContent; }
public:
	static Content& GetContent(Value& value) {
		return dynamic_cast<Value_LogicalScreenDescriptor&>(value).GetContent();
	}
	static const Content& GetContent(const Value& value) {
		return dynamic_cast<const Value_LogicalScreenDescriptor&>(value).GetContent();
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
			GetContent().IsEqualTo(Value_LogicalScreenDescriptor::GetContent(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetContent().IsLessThan(Value_LogicalScreenDescriptor::GetContent(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(gif)

#endif
