//==============================================================================
// Util.h
//==============================================================================
#ifndef GURAX_MODULE_WX_UTIL_H
#define GURAX_MODULE_WX_UTIL_H
#include <gurax.h>

Gurax_BeginModuleScope(wx)

class EventValueFactory;

//------------------------------------------------------------------------------
// EntityCore
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE EntityCore {
private:
	RefPtr<Processor> _pProcessor;
	RefPtr<Value::WeakPtr> _pwValue;
public:
	void operator=(const EntityCore& core) {
		_pProcessor.reset(core._pProcessor.Reference());
		_pwValue.reset(core._pwValue.Reference());
	}
	void SetInfo(Processor* pProcessor, const Value& value) {
		_pProcessor.reset(pProcessor);
		_pwValue.reset(value.GetWeakPtr());
	}
	bool PrepareMethod(const Symbol* pSymbolFunc, Function** ppFunc, RefPtr<Argument>& pArgument) const;
	Processor& GetProcessor() const { return *_pProcessor; }
	Value* LockValue() const { return _pwValue->Lock(); }
};

//------------------------------------------------------------------------------
// EventValueFactory
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE EventValueFactory {
public:
	virtual Value* CreateValue(const wxEvent& event, Value* pValueUserData) const = 0;
};

template<typename T_Value>
class EventValueFactoryDeriv : public EventValueFactory {
public:
	virtual Value* CreateValue(const wxEvent& event, Value* pValueUserData) const override {
		return new T_Value(event, pValueUserData);
	}
};

//-----------------------------------------------------------------------------
// EventUserData
//-----------------------------------------------------------------------------
class EventUserData : public wxObject {
private:
	RefPtr<Processor> _pProcessor;
	RefPtr<Value> _pValueFunct;
	RefPtr<Value> _pValueUserData;
	const EventValueFactory& _eventValueFactory;
public:
	EventUserData(Processor* pProcessor, Value* pValueFunct, Value* pValueUserData, const EventValueFactory& eventValueFactory) :
			_pProcessor(pProcessor), _pValueFunct(pValueFunct), _pValueUserData(pValueUserData), _eventValueFactory(eventValueFactory) {}
public:
	void Eval(wxEvent& event);
	const Value& GetValueUserData() const { return *_pValueUserData; }
	static void HandlerFunc(wxEvent& event) {
		wxDynamicCast(event.GetEventUserData(), EventUserData)->Eval(event);
	}
	static const Value& GetValueUserData(wxEvent& event) {
		return wxDynamicCast(event.GetEventUserData(), EventUserData)->GetValueUserData();
	}
};

//------------------------------------------------------------------------------
// Utility
//------------------------------------------------------------------------------
namespace Util {
void BindMultiEvents(Processor& processor, Argument& argument,
		const wxEventType eventTypes[], size_t n, const EventValueFactory& eventValueFactory);

void ExitMainLoop();
};

Gurax_EndModuleScope(wx)

#endif
