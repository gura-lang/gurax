//==============================================================================
// VType_wxMemoryBuffer.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXMEMORYBUFFER_H
#define GURAX_MODULE_WX_VTYPE_WXMEMORYBUFFER_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxMemoryBuffer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxMemoryBuffer : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxMemoryBuffer VTYPE_wxMemoryBuffer;

//------------------------------------------------------------------------------
// Value_wxMemoryBuffer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxMemoryBuffer : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxMemoryBuffer);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxMemoryBuffer");
protected:
	wxMemoryBuffer _entity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxMemoryBuffer() = delete;
	explicit Value_wxMemoryBuffer(const wxMemoryBuffer& entity, VType& vtype = VTYPE_wxMemoryBuffer) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_wxMemoryBuffer(const Value_wxMemoryBuffer& src) = delete;
	Value_wxMemoryBuffer& operator=(const Value_wxMemoryBuffer& src) = delete;
	// Move constructor/operator
	Value_wxMemoryBuffer(Value_wxMemoryBuffer&& src) noexcept = delete;
	Value_wxMemoryBuffer& operator=(Value_wxMemoryBuffer&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxMemoryBuffer() = default;
public:
	wxMemoryBuffer& GetEntity() { return _entity; }
	const wxMemoryBuffer& GetEntity() const { return _entity; }
	wxMemoryBuffer* GetEntityPtr() { return &_entity; }
	const wxMemoryBuffer* GetEntityPtr() const { return &_entity; }
public:
	static wxMemoryBuffer& GetEntity(Value& value) {
		return dynamic_cast<Value_wxMemoryBuffer&>(value).GetEntity();
	}
	static const wxMemoryBuffer& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxMemoryBuffer&>(value).GetEntity();
	}
	static wxMemoryBuffer* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxMemoryBuffer&>(value).GetEntityPtr();
	}
	static const wxMemoryBuffer* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxMemoryBuffer&>(value).GetEntityPtr();
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
