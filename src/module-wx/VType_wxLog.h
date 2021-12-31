//==============================================================================
// VType_wxLog.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXLOG_H
#define GURAX_MODULE_WX_VTYPE_WXLOG_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxLog
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxLog : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxLog VTYPE_wxLog;

//------------------------------------------------------------------------------
// Value_wxLog
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxLog : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxLog);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxLog");
protected:
	wxLog _entity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxLog() = delete;
	explicit Value_wxLog(const wxLog& entity, VType& vtype = VTYPE_wxLog) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_wxLog(const Value_wxLog& src) = delete;
	Value_wxLog& operator=(const Value_wxLog& src) = delete;
	// Move constructor/operator
	Value_wxLog(Value_wxLog&& src) noexcept = delete;
	Value_wxLog& operator=(Value_wxLog&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxLog() = default;
public:
	wxLog& GetEntity() { return _entity; }
	const wxLog& GetEntity() const { return _entity; }
	wxLog* GetEntityPtr() { return &_entity; }
	const wxLog* GetEntityPtr() const { return &_entity; }
public:
	static wxLog& GetEntity(Value& value) {
		return dynamic_cast<Value_wxLog&>(value).GetEntity();
	}
	static const wxLog& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxLog&>(value).GetEntity();
	}
	static wxLog* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxLog&>(value).GetEntityPtr();
	}
	static const wxLog* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxLog&>(value).GetEntityPtr();
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
