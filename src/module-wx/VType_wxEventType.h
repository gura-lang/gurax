//==============================================================================
// VType_wxEventType.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXEVENTTYPE_H
#define GURAX_MODULE_WX_VTYPE_WXEVENTTYPE_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxEventType
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxEventType : public VType {
public:
	RefPtr<DeclCallable> _pDeclCallable;
public:
	VType_wxEventType(const char* name) : VType(name), _pDeclCallable(new DeclCallable()) {}
	virtual void DoPrepare(Frame& frameOuter) override;
	DeclCallable& GetDeclCallable() { return *_pDeclCallable; }
};

extern GURAX_DLLDECLARE VType_wxEventType VTYPE_wxEventType;

//------------------------------------------------------------------------------
// Value_wxEventType
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxEventType : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxEventType);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxEventType");
protected:
	wxEventType _entity;
	String _name;
	const EventValueFactory& _eventValueFactory;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxEventType() = delete;
	explicit Value_wxEventType(const wxEventType& entity, String name, const EventValueFactory& eventValueFactory, VType& vtype = VTYPE_wxEventType) :
		Value_Object(vtype), _entity(entity), _name(name), _eventValueFactory(eventValueFactory) {}
	// Copy constructor/operator
	Value_wxEventType(const Value_wxEventType& src) = delete;
	Value_wxEventType& operator=(const Value_wxEventType& src) = delete;
	// Move constructor/operator
	Value_wxEventType(Value_wxEventType&& src) noexcept = delete;
	Value_wxEventType& operator=(Value_wxEventType&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxEventType() = default;
public:
	wxEventType& GetEntity() { return _entity; }
	const wxEventType& GetEntity() const { return _entity; }
public:
	static wxEventType& GetEntity(Value& value) {
		return dynamic_cast<Value_wxEventType&>(value).GetEntity();
	}
	static const wxEventType& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxEventType&>(value).GetEntity();
	}
public:
	const char* GetName() const { return _name.c_str(); }
	const EventValueFactory& GetEventValueFactory() const { return _eventValueFactory; }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(&GetEntity(*this));
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) && GetEntity(*this) == GetEntity(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			(&GetEntity(*this) < &GetEntity(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
public:
	virtual const DeclCallable* GetDeclCallable() override;
	virtual Value* DoEval(Processor& processor, Argument& argument) const override;
};

Gurax_EndModuleScope(wx)

#endif
