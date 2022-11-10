﻿//==============================================================================
// VType_wxScrolledCanvas.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXSCROLLEDCANVAS_H
#define GURAX_MODULE_WX_VTYPE_WXSCROLLEDCANVAS_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxWindow.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxScrolledCanvas
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxScrolledCanvas : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxScrolledCanvas VTYPE_wxScrolledCanvas;

//------------------------------------------------------------------------------
// Value_wxScrolledCanvas
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxScrolledCanvas : public Value_wxWindow {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxScrolledCanvas);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxScrolledCanvas");
protected:
	wxWeakRef<wxScrolledCanvas> _pEntity;
public:
	class EntityT : public wxScrolledCanvas {
	public:
		using wxScrolledCanvas::wxScrolledCanvas;
	public:
		EntityCore core_gurax;
		virtual void OnDraw(wxDC& dc) override;
		virtual void AdjustScrollbars() override;
		void public_OnDraw(wxDC& dc) { wxScrolledCanvas::OnDraw(dc); }
		void public_AdjustScrollbars() { wxScrolledCanvas::AdjustScrollbars(); }
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxScrolledCanvas() = delete;
	explicit Value_wxScrolledCanvas(wxScrolledCanvas* pEntity, VType& vtype = VTYPE_wxScrolledCanvas) :
		Value_wxWindow(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxScrolledCanvas(const Value_wxScrolledCanvas& src) = delete;
	Value_wxScrolledCanvas& operator=(const Value_wxScrolledCanvas& src) = delete;
	// Move constructor/operator
	Value_wxScrolledCanvas(Value_wxScrolledCanvas&& src) noexcept = delete;
	Value_wxScrolledCanvas& operator=(Value_wxScrolledCanvas&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxScrolledCanvas() = default;
public:
	wxScrolledCanvas& GetEntity() { return *_pEntity; }
	const wxScrolledCanvas& GetEntity() const { return *_pEntity; }
	wxScrolledCanvas* GetEntityPtr() { return _pEntity.get(); }
	const wxScrolledCanvas* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxScrolledCanvas& GetEntity(Value& value) {
		return dynamic_cast<Value_wxScrolledCanvas&>(value).GetEntity();
	}
	static const wxScrolledCanvas& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxScrolledCanvas&>(value).GetEntity();
	}
	static wxScrolledCanvas* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxScrolledCanvas&>(value).GetEntityPtr();
	}
	static const wxScrolledCanvas* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxScrolledCanvas&>(value).GetEntityPtr();
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
