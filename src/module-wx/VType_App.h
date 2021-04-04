//==============================================================================
// VType_App.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_APP_H
#define GURAX_MODULE_WX_VTYPE_APP_H
#include <gurax.h>
#include <wx/wx.h>

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_App
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_App : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_App VTYPE_App;

//------------------------------------------------------------------------------
// Value_App
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_App : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_App);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_App");
public:
	class EntityT : public wxApp {
	public:
		using wxApp::wxApp;
	private:
		RefPtr<Value_App::WeakPtr> _pwValue;
	public:
		virtual bool OnInit();
	public:
		void SetValue(const Value_App& value) { _pwValue.reset(value.GetWeakPtr()); }
		Value_App* LockValue() const { return _pwValue->Lock(); }
	};
protected:
	wxWeakRef<EntityT> _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_App() = delete;
	explicit Value_App(EntityT* pEntity, VType& vtype = VTYPE_App) :
		Value_Object(vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_App(const Value_App& src) = delete;
	Value_App& operator=(const Value_App& src) = delete;
	// Move constructor/operator
	Value_App(Value_App&& src) noexcept = delete;
	Value_App& operator=(Value_App&& src) noexcept = delete;
protected:
	// Destructor
	~Value_App() = default;
public:
	EntityT* GetEntity() { return _pEntity.get(); }
	const EntityT* GetEntity() const { return _pEntity.get(); }
public:
	static EntityT* GetEntity(Value& value) {
		return dynamic_cast<Value_App&>(value).GetEntity();
	}
	static const EntityT* GetEntity(const Value& value) {
		return dynamic_cast<const Value_App&>(value).GetEntity();
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
