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
	Content::PlainTextExtension& _plainTextExtension;
	RefPtr<Content> _pContent;
public:
	static VType& vtype;
public:
	// Constructor
	Value_PlainTextExtension() = delete;
	Value_PlainTextExtension(Content::PlainTextExtension& plainTextExtension, Content* pContent,
									VType& vtype = VTYPE_PlainTextExtension) :
		Value_Object(vtype), _plainTextExtension(plainTextExtension), _pContent(pContent) {}
	// Copy constructor/operator
	Value_PlainTextExtension(const Value_PlainTextExtension& src) :
		Value_Object(src), _plainTextExtension(src._plainTextExtension), _pContent(src._pContent->Reference()) {}
	Value_PlainTextExtension& operator=(const Value_PlainTextExtension& src) = delete;
	// Move constructor/operator
	Value_PlainTextExtension(Value_PlainTextExtension&& src) noexcept = delete;
	Value_PlainTextExtension& operator=(Value_PlainTextExtension&& src) noexcept = delete;
protected:
	// Destructor
	~Value_PlainTextExtension() = default;
public:
	Content::PlainTextExtension& GetPlainTextExtension() { return _plainTextExtension; }
	const Content::PlainTextExtension& GetPlainTextExtension() const { return _plainTextExtension; }
public:
	static Content::PlainTextExtension& GetPlainTextExtension(Value& value) {
		return dynamic_cast<Value_PlainTextExtension&>(value).GetPlainTextExtension();
	}
	static const Content::PlainTextExtension& GetPlainTextExtension(const Value& value) {
		return dynamic_cast<const Value_PlainTextExtension&>(value).GetPlainTextExtension();
	}
	static Content::PlainTextExtension* GetEntityPtr(Value& value) { return &GetPlainTextExtension(value); }
	static const Content::PlainTextExtension* GetEntityPtr(const Value& value) { return &GetPlainTextExtension(value); }
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
