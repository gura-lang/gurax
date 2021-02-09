//==============================================================================
// VType_PlainTextExtension.h
//==============================================================================
#ifndef GURAX_MODULE_GIF_VTYPE_PLAINTEXTEXTENSION_H
#define GURAX_MODULE_GIF_VTYPE_PLAINTEXTEXTENSION_H
#include <gurax.h>
#include "Content.h"

Gurax_BeginModuleScope(gif)

//------------------------------------------------------------------------------
// VType_PlainTextExtension
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_PlainTextExtension : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_PlainTextExtension VTYPE_PlainTextExtension;

//------------------------------------------------------------------------------
// Value_PlainTextExtension
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_PlainTextExtension : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_PlainTextExtension);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_PlainTextExtension");
protected:
	RefPtr<Content> _pContent;
public:
	static VType& vtype;
public:
	// Constructor
	Value_PlainTextExtension() = delete;
	explicit Value_PlainTextExtension(Content* pContent, VType& vtype = VTYPE_PlainTextExtension) :
		Value_Object(vtype), _pContent(pContent) {}
	// Copy constructor/operator
	Value_PlainTextExtension(const Value_PlainTextExtension& src) :
		Value_Object(src), _pContent(src._pContent->Reference()) {}
	Value_PlainTextExtension& operator=(const Value_PlainTextExtension& src) = delete;
	// Move constructor/operator
	Value_PlainTextExtension(Value_PlainTextExtension&& src) noexcept = delete;
	Value_PlainTextExtension& operator=(Value_PlainTextExtension&& src) noexcept = delete;
protected:
	// Destructor
	~Value_PlainTextExtension() = default;
public:
	Content& GetContent() { return *_pContent; }
	const Content& GetContent() const { return *_pContent; }
public:
	static Content& GetContent(Value& value) {
		return dynamic_cast<Value_PlainTextExtension&>(value).GetContent();
	}
	static const Content& GetContent(const Value& value) {
		return dynamic_cast<const Value_PlainTextExtension&>(value).GetContent();
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
			GetContent().IsEqualTo(Value_PlainTextExtension::GetContent(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetContent().IsLessThan(Value_PlainTextExtension::GetContent(value)) :
			GetVType().IsLessThan(value.GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(gif)

#endif
