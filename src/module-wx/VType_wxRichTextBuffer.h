//==============================================================================
// VType_wxRichTextBuffer.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXRICHTEXTBUFFER_H
#define GURAX_MODULE_WX_VTYPE_WXRICHTEXTBUFFER_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/richtext/richtextbuffer.h>
#include "Util.h"
#include "VType_wxRichTextParagraphLayoutBox.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxRichTextBuffer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxRichTextBuffer : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxRichTextBuffer VTYPE_wxRichTextBuffer;

//------------------------------------------------------------------------------
// Value_wxRichTextBuffer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxRichTextBuffer : public Value_wxRichTextParagraphLayoutBox {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxRichTextBuffer);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxRichTextBuffer");
protected:
	wxRichTextBuffer* _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxRichTextBuffer() = delete;
	explicit Value_wxRichTextBuffer(wxRichTextBuffer* pEntity, VType& vtype = VTYPE_wxRichTextBuffer) :
		Value_wxRichTextParagraphLayoutBox(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxRichTextBuffer(const Value_wxRichTextBuffer& src) = delete;
	Value_wxRichTextBuffer& operator=(const Value_wxRichTextBuffer& src) = delete;
	// Move constructor/operator
	Value_wxRichTextBuffer(Value_wxRichTextBuffer&& src) noexcept = delete;
	Value_wxRichTextBuffer& operator=(Value_wxRichTextBuffer&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxRichTextBuffer() = default;
public:
	wxRichTextBuffer& GetEntity() { return *_pEntity; }
	const wxRichTextBuffer& GetEntity() const { return *_pEntity; }
	wxRichTextBuffer* GetEntityPtr() { return _pEntity; }
	const wxRichTextBuffer* GetEntityPtr() const { return _pEntity; }
public:
	static wxRichTextBuffer& GetEntity(Value& value) {
		return dynamic_cast<Value_wxRichTextBuffer&>(value).GetEntity();
	}
	static const wxRichTextBuffer& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxRichTextBuffer&>(value).GetEntity();
	}
	static wxRichTextBuffer* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxRichTextBuffer&>(value).GetEntityPtr();
	}
	static const wxRichTextBuffer* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxRichTextBuffer&>(value).GetEntityPtr();
	}
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
			(GetEntityPtr(*this) < GetEntityPtr(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(wx)

#endif