﻿//==============================================================================
// VType_wxTimer.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXTIMER_H
#define GURAX_MODULE_WX_VTYPE_WXTIMER_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxEvtHandler.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxTimer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxTimer : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxTimer VTYPE_wxTimer;

//------------------------------------------------------------------------------
// Value_wxTimer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxTimer : public Value_wxEvtHandler {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxTimer);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxTimer");
protected:
	wxWeakRef<wxTimer> _pEntity;
public:
	class EntityT : public wxTimer {
	public:
		using wxTimer::wxTimer;
	public:
		EntityCore core_gurax;
		virtual void Notify() override;
		virtual bool Start(int milliseconds, bool oneShot) override;
		virtual void Stop() override;
		void public_Notify() { wxTimer::Notify(); }
		bool public_Start(int milliseconds, bool oneShot) { return wxTimer::Start(milliseconds, oneShot); }
		void public_Stop() { wxTimer::Stop(); }
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxTimer() = delete;
	explicit Value_wxTimer(wxTimer* pEntity, VType& vtype = VTYPE_wxTimer) :
		Value_wxEvtHandler(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxTimer(const Value_wxTimer& src) = delete;
	Value_wxTimer& operator=(const Value_wxTimer& src) = delete;
	// Move constructor/operator
	Value_wxTimer(Value_wxTimer&& src) noexcept = delete;
	Value_wxTimer& operator=(Value_wxTimer&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxTimer() = default;
public:
	wxTimer& GetEntity() { return *_pEntity; }
	const wxTimer& GetEntity() const { return *_pEntity; }
	wxTimer* GetEntityPtr() { return _pEntity.get(); }
	const wxTimer* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxTimer& GetEntity(Value& value) {
		return dynamic_cast<Value_wxTimer&>(value).GetEntity();
	}
	static const wxTimer& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxTimer&>(value).GetEntity();
	}
	static wxTimer* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxTimer&>(value).GetEntityPtr();
	}
	static const wxTimer* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxTimer&>(value).GetEntityPtr();
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
