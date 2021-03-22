//==============================================================================
// VType_wxApp.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXAPP_H
#define GURAX_MODULE_WX_VTYPE_WXAPP_H
#include <gurax.h>
#include <wx/wx.h>

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxApp
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxApp : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxApp VTYPE_wxApp;

//------------------------------------------------------------------------------
// Value_wxApp
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxApp : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxApp);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxApp");
protected:
	wxWeakRef<wxApp> _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxApp() = delete;
	explicit Value_wxApp(wxApp* pEntity, VType& vtype = VTYPE_wxApp) :
		Value_Object(vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxApp(const Value_wxApp& src) = delete;
	Value_wxApp& operator=(const Value_wxApp& src) = delete;
	// Move constructor/operator
	Value_wxApp(Value_wxApp&& src) noexcept = delete;
	Value_wxApp& operator=(Value_wxApp&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxApp() = default;
public:
	wxApp& GetEntity() { return *_pEntity; }
	const wxApp& GetEntity() const { return *_pEntity; }
public:
	static wxApp& GetEntity(Value& value) {
		return dynamic_cast<Value_wxApp&>(value).GetEntity();
	}
	static const wxApp& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxApp&>(value).GetEntity();
	}
	static wxApp* GetEntityPtr(Value& value) { return &GetEntity(value); }
	static const wxApp* GetEntityPtr(const Value& value) { return &GetEntity(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr(*this));
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr(*this) == GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			(GetEntityPtr(*this) < GetEntityPtr(value)) :
			GetVType().IsLessThan(value.GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(wx)

#endif
