//==============================================================================
// VType_AppConsole.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_AppConsole_H
#define GURAX_MODULE_WX_VTYPE_AppConsole_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_AppConsole
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_AppConsole : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_AppConsole VTYPE_AppConsole;

//------------------------------------------------------------------------------
// Value_AppConsole
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_AppConsole : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_AppConsole);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_AppConsole");
public:
	class EntityT : public wxAppConsole {
	public:
		using EntitySuper = wxAppConsole;
		using wxAppConsole::wxAppConsole;
	public:
		EntityCore core;
	};
protected:
	wxWeakRef<EntityT> _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_AppConsole() = delete;
	explicit Value_AppConsole(EntityT* pEntity, VType& vtype = VTYPE_AppConsole) :
		Value_Object(vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_AppConsole(const Value_AppConsole& src) = delete;
	Value_AppConsole& operator=(const Value_AppConsole& src) = delete;
	// Move constructor/operator
	Value_AppConsole(Value_AppConsole&& src) noexcept = delete;
	Value_AppConsole& operator=(Value_AppConsole&& src) noexcept = delete;
protected:
	// Destructor
	~Value_AppConsole() = default;
public:
	EntityT* GetEntity() { return _pEntity.get(); }
	const EntityT* GetEntity() const { return _pEntity.get(); }
public:
	static EntityT* GetEntity(Value& value) {
		return dynamic_cast<Value_AppConsole&>(value).GetEntity();
	}
	static const EntityT* GetEntity(const Value& value) {
		return dynamic_cast<const Value_AppConsole&>(value).GetEntity();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntity(*this));
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) && GetEntity(*this) == GetEntity(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			(GetEntity(*this) < GetEntity(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(wx)

#endif
