//==============================================================================
// VType_wxDocMDIChildFrame.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXDOCMDICHILDFRAME_H
#define GURAX_MODULE_WX_VTYPE_WXDOCMDICHILDFRAME_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/docmdi.h>
#include "Util.h"
#include "VType_wxMDIChildFrame.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxDocMDIChildFrame
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxDocMDIChildFrame : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxDocMDIChildFrame VTYPE_wxDocMDIChildFrame;

//------------------------------------------------------------------------------
// Value_wxDocMDIChildFrame
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxDocMDIChildFrame : public Value_wxMDIChildFrame {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxDocMDIChildFrame);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxDocMDIChildFrame");
protected:
	wxWeakRef<wxDocMDIChildFrame> _pEntity;
public:
	class EntityT : public wxDocMDIChildFrame {
	public:
		using wxDocMDIChildFrame::wxDocMDIChildFrame;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxDocMDIChildFrame() = delete;
	explicit Value_wxDocMDIChildFrame(wxDocMDIChildFrame* pEntity, VType& vtype = VTYPE_wxDocMDIChildFrame) :
		Value_wxMDIChildFrame(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxDocMDIChildFrame(const Value_wxDocMDIChildFrame& src) = delete;
	Value_wxDocMDIChildFrame& operator=(const Value_wxDocMDIChildFrame& src) = delete;
	// Move constructor/operator
	Value_wxDocMDIChildFrame(Value_wxDocMDIChildFrame&& src) noexcept = delete;
	Value_wxDocMDIChildFrame& operator=(Value_wxDocMDIChildFrame&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxDocMDIChildFrame() = default;
public:
	wxDocMDIChildFrame& GetEntity() { return *_pEntity; }
	const wxDocMDIChildFrame& GetEntity() const { return *_pEntity; }
	wxDocMDIChildFrame* GetEntityPtr() { return _pEntity.get(); }
	const wxDocMDIChildFrame* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxDocMDIChildFrame& GetEntity(Value& value) {
		return dynamic_cast<Value_wxDocMDIChildFrame&>(value).GetEntity();
	}
	static const wxDocMDIChildFrame& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxDocMDIChildFrame&>(value).GetEntity();
	}
	static wxDocMDIChildFrame* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxDocMDIChildFrame&>(value).GetEntityPtr();
	}
	static const wxDocMDIChildFrame* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxDocMDIChildFrame&>(value).GetEntityPtr();
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
