//==============================================================================
// VType_Window.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WINDOW_H
#define GURAX_MODULE_WX_VTYPE_WINDOW_H
#include <gurax.h>
#include <wx/wx.h>

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_Window
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Window : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Window VTYPE_Window;

//------------------------------------------------------------------------------
// Value_Window
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Window : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Window);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Window");
public:
	class EntityT : public wxWindow {
	public:
		using EntitySuper = wxWindow;
		using wxWindow::wxWindow;
	private:
		RefPtr<Processor> _pProcessor;
		RefPtr<Value_Window::WeakPtr> _pwValue;
	public:
	public:
		void SetInfo(Processor* pProcessor, const Value_Window& value) {
			_pProcessor.reset(pProcessor);
			_pwValue.reset(value.GetWeakPtr());
		}
		bool PrepareMethod(const Symbol* pSymbolFunc, Function** ppFunc, RefPtr<Argument>& pArgument) const;
		Value_Window* LockValue() const { return _pwValue->Lock(); }
		Processor& GetProcessor() const { return *_pProcessor; }
	};
protected:
	wxWeakRef<EntityT> _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Window() = delete;
	explicit Value_Window(EntityT* pEntity, VType& vtype = VTYPE_Window) :
		Value_Object(vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_Window(const Value_Window& src) = delete;
	Value_Window& operator=(const Value_Window& src) = delete;
	// Move constructor/operator
	Value_Window(Value_Window&& src) noexcept = delete;
	Value_Window& operator=(Value_Window&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Window() = default;
public:
	EntityT* GetEntity() { return _pEntity.get(); }
	const EntityT* GetEntity() const { return _pEntity.get(); }
public:
	static EntityT* GetEntity(Value& value) {
		return dynamic_cast<Value_Window&>(value).GetEntity();
	}
	static const EntityT* GetEntity(const Value& value) {
		return dynamic_cast<const Value_Window&>(value).GetEntity();
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
