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
	void SetInfo(Processor* pProcessor, const Value& value) {
		_pProcessor.reset(pProcessor);
		_pwValue.reset(value.GetWeakPtr());
	}
	bool PrepareMethod(const Symbol* pSymbolFunc, Function** ppFunc, RefPtr<Argument>& pArgument) const;
	Processor& GetProcessor() const { return *_pProcessor; }
	Value* LockValue() const { return _pwValue->Lock(); }
};

//------------------------------------------------------------------------------
// Utility
//------------------------------------------------------------------------------
void BindMultiEvents(Processor& processor, Argument& argument,
		const wxEventType eventTypes[], size_t n, const EventValueFactory& eventValueFactory);

Gurax_EndModuleScope(wx)

#endif
