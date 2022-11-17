//==============================================================================
// Util.h
//==============================================================================
#ifndef GURAX_MODULE_WX_UTIL_H
#define GURAX_MODULE_WX_UTIL_H
#include <gurax.h>
#include <wx/treectrl.h>

#define Gurax_AssignEvent(eventName, eventType) do { \
RefPtr<Value> pValue(new Value_wxEventType(wx##eventName, #eventName, Value_##eventType::eventValueFactory)); \
Util::eventTypeMap[wx##eventName] = pValue.Reference(); \
frame.Assign(#eventName, pValue.release()); \
} while (0)

Gurax_BeginModuleScope(wx)

using EventTypeMap = std::unordered_map<wxEventType, Value*>;

class EventValueFactory;

//------------------------------------------------------------------------------
// EntityCore
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE EntityCore {
private:
	RefPtr<Processor> _pProcessor;
	RefPtr<Value> _pValue;
public:
	void operator=(const EntityCore& core) {
		_pProcessor.reset(core._pProcessor.Reference());
		_pValue.reset(core._pValue.Reference());
	}
	void SetInfo(Processor* pProcessor, const Value& value) {
		_pProcessor.reset(pProcessor);
		_pValue.reset(value.Reference());
	}
	bool PrepareOverrideMethod(const Symbol* pSymbolFunc, Function** ppFunc, RefPtr<Argument>& pArgument) const;
	Processor& GetProcessor() const { return *_pProcessor; }
};

//------------------------------------------------------------------------------
// EventValueFactory
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE EventValueFactory {
public:
	virtual Value* CreateValue(wxEvent& event, Value* pValueUserData) const = 0;
};

template<typename T_Value>
class EventValueFactoryDeriv : public EventValueFactory {
public:
	virtual Value* CreateValue(wxEvent& event, Value* pValueUserData) const override {
		return new T_Value(event, pValueUserData);
	}
};

//-----------------------------------------------------------------------------
// ClientData
//-----------------------------------------------------------------------------
class ClientData : public wxClientData {
private:
	RefPtr<Value> _pValue;
public:
	ClientData(Value* pValue) : _pValue(pValue) {}
	Value& GetValue() { return *_pValue; }
	const Value& GetValue() const { return *_pValue; }
public:
	static wxClientData* Create(const Value& value) { return new ClientData(value.Reference()); }
	static std::vector<wxClientData*> Create(const ValueList& values);
};

//-----------------------------------------------------------------------------
// TreeItemData
//-----------------------------------------------------------------------------
class TreeItemData : public wxTreeItemData {
private:
	RefPtr<Value> _pValue;
public:
	TreeItemData(Value* pValue) : _pValue(pValue) {}
	Value& GetValue() { return *_pValue; }
	const Value& GetValue() const { return *_pValue; }
public:
	static TreeItemData* Create(const Value& value) { return new TreeItemData(value.Reference()); }
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
	static void HandlerFunc(wxEvent& event) {
		wxDynamicCast(event.GetEventUserData(), EventUserData)->Eval(event);
	}
};

//------------------------------------------------------------------------------
// ListCtrlSortItems
//------------------------------------------------------------------------------
class ListCtrlSortItems {
private:
	RefPtr<Value> _pValueCallable;
	RefPtr<Processor> _pProcessor;
	RefPtr<Value> _pValue;
public:
	ListCtrlSortItems(Value* pValueCallable, Processor* pProcessor, Value* pValue) :
		_pValueCallable(pValueCallable), _pProcessor(pProcessor), _pValue(pValue) {}
	static int CompareFunction(wxIntPtr item1, wxIntPtr item2, wxIntPtr sortData);
	Value& GetCallable() { return *_pValueCallable; }
	Processor& GetProcessor() { return *_pProcessor; }
	const Value& GetValue() { return *_pValue; }
	Value* Eval(const Value& valueItem1, const Value& valueItem2);
};

//------------------------------------------------------------------------------
// Utility
//------------------------------------------------------------------------------
namespace Util {

extern EventTypeMap eventTypeMap;

String GetKeyCodeName(int keyCode);
wxArrayString CreateArrayString(const ValueList& values);
wxArrayShort CreateArrayShort(const ValueList& values);
wxArrayInt CreateArrayInt(const ValueList& values);
wxArrayDouble CreateArrayDouble(const ValueList& values);
wxArrayLong CreateArrayLong(const ValueList& values);
wxPointList* CreatePointList(const ValueList& values);
Value* CreateList(const wxArrayString& array);
Value* CreateList(const wxArrayShort& array);
Value* CreateList(const wxArrayInt& array);
Value* CreateList(const wxArrayDouble& array);
Value* CreateList(const wxArrayLong& array);
void BindMultiEvents(Processor& processor, Argument& argument,
		const wxEventType eventTypes[], size_t n, const EventValueFactory& eventValueFactory);
const Value& LookupEventType(wxEventType eventType);
wxImage CreateImage(const Image& imageGura);
void ExitMainLoop();

};

Gurax_EndModuleScope(wx)

#endif
