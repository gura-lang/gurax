//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// EntityCore
//------------------------------------------------------------------------------
bool EntityCore::PrepareOverrideMethod(const Symbol* pSymbolFunc, Function** ppFunc, RefPtr<Argument>& pArgument) const
{
	Function* pFunc = &_pValue->LookupMethod(pSymbolFunc);
	*ppFunc = pFunc;
	if (pFunc->IsEmpty() || !pFunc->IsCustom()) return false;
	pArgument.reset(new Argument(GetProcessor(), *pFunc));
	pArgument->SetValueThis(_pValue.Reference());
	return true;
}

//------------------------------------------------------------------------------
// EventValueFactory
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// ClientData
//-----------------------------------------------------------------------------
std::vector<wxClientData*> ClientData::Create(const ValueList& values)
{
	std::vector<wxClientData*> rtn;
	rtn.reserve(values.size());
	for (const Value* pValue : values) rtn.push_back(new ClientData(pValue->Reference()));
	return rtn;
}

//-----------------------------------------------------------------------------
// ClientObject
//-----------------------------------------------------------------------------
std::vector<wxObject*> ClientObject::Create(const ValueList& values)
{
	std::vector<wxObject*> rtn;
	rtn.reserve(values.size());
	for (const Value* pValue : values) rtn.push_back(new ClientObject(pValue->Reference()));
	return rtn;
}

//-----------------------------------------------------------------------------
// EventUserData
//-----------------------------------------------------------------------------
void EventUserData::Eval(wxEvent& event)
{
	const DeclCallable* pDeclCallable = _pValueFunct->GetDeclCallableWithError();
	if (!pDeclCallable) return;
	RefPtr<Argument> pArg(new Argument(*_pProcessor, pDeclCallable->Reference()));
	ArgFeeder args(*pArg, _pProcessor->GetFrameCur());
	if (!args.FeedValue(_eventValueFactory.CreateValue(event, _pValueUserData.Reference()))) return;
	Value::Delete(_pValueFunct->Eval(*_pProcessor, *pArg));
	if (Error::IsIssued()) Util::ExitMainLoop();
}

//------------------------------------------------------------------------------
// ListCtrlSortItems
//------------------------------------------------------------------------------
Value* ListCtrlSortItems::Eval(const Value& valueItem1, const Value& valueItem2)
{
	const DeclCallable* pDeclCallable = GetCallable().GetDeclCallableWithError();
	if (!pDeclCallable) return Value::nil();
	RefPtr<Argument> pArg(new Argument(GetProcessor(), pDeclCallable->Reference(), DeclCallable::Flag::CutExtraArgs));
	ArgFeeder args(*pArg, GetProcessor().GetFrameCur());
	if (!args.FeedValues(valueItem1.Reference(), valueItem2.Reference(), GetValue().Reference())) return Value::nil();
	return GetCallable().Eval(GetProcessor(), *pArg);
}

int ListCtrlSortItems::CompareFunction(wxIntPtr item1, wxIntPtr item2, wxIntPtr sortData)
{
	ListCtrlSortItems& listCtrlSortItems = *reinterpret_cast<ListCtrlSortItems*>(sortData);
	const Value& valueItem1 = item1? *reinterpret_cast<const Value*>(item1) : Value::C_nil();
	const Value& valueItem2 = item2? *reinterpret_cast<const Value*>(item2) : Value::C_nil();
	RefPtr<Value> pValueRtn(listCtrlSortItems.Eval(valueItem1, valueItem2));
	if (Error::IsIssued()) return 0;
	if (!pValueRtn->IsType(VTYPE_Number)) {
		if (!Error::IsIssued()) Error::Issue(ErrorType::TypeError, "Return value must be of Number type");
		return 0;
	}
	return Value_Number::GetNumber<int>(*pValueRtn);
}

//------------------------------------------------------------------------------
// Utility
//------------------------------------------------------------------------------
namespace Util {

EventTypeMap eventTypeMap;

String GetKeyCodeName(int keyCode)
{
	struct Assoc {
		int keyCode;
		const char* name;
	};
	static const Assoc assocTbl[] = {
		{ WXK_NONE,				"NONE"				},
		{ WXK_CONTROL_A,		"CONTROL_A"			},
		{ WXK_CONTROL_B,		"CONTROL_B"			},
		{ WXK_CONTROL_C,		"CONTROL_C"			},
		{ WXK_CONTROL_D,		"CONTROL_D"			},
		{ WXK_CONTROL_E,		"CONTROL_E"			},
		{ WXK_CONTROL_F,		"CONTROL_F"			},
		{ WXK_CONTROL_G,		"CONTROL_G"			},
		{ WXK_CONTROL_H,		"CONTROL_H"			},
		{ WXK_CONTROL_I,		"CONTROL_I"			},
		{ WXK_CONTROL_J,		"CONTROL_J"			},
		{ WXK_CONTROL_K,		"CONTROL_K"			},
		{ WXK_CONTROL_L,		"CONTROL_L"			},
		{ WXK_CONTROL_M,		"CONTROL_M"			},
		{ WXK_CONTROL_N,		"CONTROL_N"			},
		{ WXK_CONTROL_O,		"CONTROL_O"			},
		{ WXK_CONTROL_P,		"CONTROL_P"			},
		{ WXK_CONTROL_Q,		"CONTROL_Q"			},
		{ WXK_CONTROL_R,		"CONTROL_R"			},
		{ WXK_CONTROL_S,		"CONTROL_S"			},
		{ WXK_CONTROL_T,		"CONTROL_T"			},
		{ WXK_CONTROL_U,		"CONTROL_U"			},
		{ WXK_CONTROL_V,		"CONTROL_V"			},
		{ WXK_CONTROL_W,		"CONTROL_W"			},
		{ WXK_CONTROL_X,		"CONTROL_X"			},
		{ WXK_CONTROL_Y,		"CONTROL_Y"			},
		{ WXK_CONTROL_Z,		"CONTROL_Z"			},
		{ WXK_BACK,				"BACK"				},
		{ WXK_TAB,				"TAB"				},
		{ WXK_RETURN,			"RETURN"			},
		{ WXK_ESCAPE,			"ESCAPE"			},
		{ WXK_SPACE,			"SPACE"				},
		{ WXK_DELETE,			"DELETE"			},
		{ WXK_START,			"START"				},
		{ WXK_LBUTTON,			"LBUTTON"			},
		{ WXK_RBUTTON,			"RBUTTON"			},
		{ WXK_CANCEL,			"CANCEL"			},
		{ WXK_MBUTTON,			"MBUTTON"			},
		{ WXK_CLEAR,			"CLEAR"				},
		{ WXK_SHIFT,			"SHIFT"				},
		{ WXK_ALT,				"ALT"				},
		{ WXK_CONTROL,			"CONTROL"			},
		{ WXK_RAW_CONTROL,		"RAW_CONTROL"		},
		{ WXK_MENU,				"MENU"				},
		{ WXK_PAUSE,			"PAUSE"				},
		{ WXK_CAPITAL,			"CAPITAL"			},
		{ WXK_END,				"END"				},
		{ WXK_HOME,				"HOME"				},
		{ WXK_LEFT,				"LEFT"				},
		{ WXK_UP,				"UP"				},
		{ WXK_RIGHT,			"RIGHT"				},
		{ WXK_DOWN,				"DOWN"				},
		{ WXK_SELECT,			"SELECT"			},
		{ WXK_PRINT,			"PRINT"				},
		{ WXK_EXECUTE,			"EXECUTE"			},
		{ WXK_SNAPSHOT,			"SNAPSHOT"			},
		{ WXK_INSERT,			"INSERT"			},
		{ WXK_HELP,				"HELP"				},
		{ WXK_NUMPAD0,			"NUMPAD0"			},
		{ WXK_NUMPAD1,			"NUMPAD1"			},
		{ WXK_NUMPAD2,			"NUMPAD2"			},
		{ WXK_NUMPAD3,			"NUMPAD3"			},
		{ WXK_NUMPAD4,			"NUMPAD4"			},
		{ WXK_NUMPAD5,			"NUMPAD5"			},
		{ WXK_NUMPAD6,			"NUMPAD6"			},
		{ WXK_NUMPAD7,			"NUMPAD7"			},
		{ WXK_NUMPAD8,			"NUMPAD8"			},
		{ WXK_NUMPAD9,			"NUMPAD9"			},
		{ WXK_MULTIPLY,			"MULTIPLY"			},
		{ WXK_ADD,				"ADD"				},
		{ WXK_SEPARATOR,		"SEPARATOR"			},
		{ WXK_SUBTRACT,			"SUBTRACT"			},
		{ WXK_DECIMAL,			"DECIMAL"			},
		{ WXK_DIVIDE,			"DIVIDE"			},
		{ WXK_F1,				"F1"				},
		{ WXK_F2,				"F2"				},
		{ WXK_F3,				"F3"				},
		{ WXK_F4,				"F4"				},
		{ WXK_F5,				"F5"				},
		{ WXK_F6,				"F6"				},
		{ WXK_F7,				"F7"				},
		{ WXK_F8,				"F8"				},
		{ WXK_F9,				"F9"				},
		{ WXK_F10,				"F10"				},
		{ WXK_F11,				"F11"				},
		{ WXK_F12,				"F12"				},
		{ WXK_F13,				"F13"				},
		{ WXK_F14,				"F14"				},
		{ WXK_F15,				"F15"				},
		{ WXK_F16,				"F16"				},
		{ WXK_F17,				"F17"				},
		{ WXK_F18,				"F18"				},
		{ WXK_F19,				"F19"				},
		{ WXK_F20,				"F20"				},
		{ WXK_F21,				"F21"				},
		{ WXK_F22,				"F22"				},
		{ WXK_F23,				"F23"				},
		{ WXK_F24,				"F24"				},
		{ WXK_NUMLOCK,			"NUMLOCK"			},
		{ WXK_SCROLL,			"SCROLL"			},
		{ WXK_PAGEUP,			"PAGEUP"			},
		{ WXK_PAGEDOWN,			"PAGEDOWN"			},
		{ WXK_NUMPAD_SPACE,		"NUMPAD_SPACE"		},
		{ WXK_NUMPAD_TAB,		"NUMPAD_TAB"		},
		{ WXK_NUMPAD_ENTER,		"NUMPAD_ENTER"		},
		{ WXK_NUMPAD_F1,		"NUMPAD_F1"			},
		{ WXK_NUMPAD_F2,		"NUMPAD_F2"			},
		{ WXK_NUMPAD_F3,		"NUMPAD_F3"			},
		{ WXK_NUMPAD_F4,		"NUMPAD_F4"			},
		{ WXK_NUMPAD_HOME,		"NUMPAD_HOME"		},
		{ WXK_NUMPAD_LEFT,		"NUMPAD_LEFT"		},
		{ WXK_NUMPAD_UP,		"NUMPAD_UP"			},
		{ WXK_NUMPAD_RIGHT,		"NUMPAD_RIGHT"		},
		{ WXK_NUMPAD_DOWN,		"NUMPAD_DOWN"		},
		{ WXK_NUMPAD_PAGEUP,	"NUMPAD_PAGEUP"		},
		{ WXK_NUMPAD_PAGEDOWN,	"NUMPAD_PAGEDOWN"	},
		{ WXK_NUMPAD_END,		"NUMPAD_END"		},
		{ WXK_NUMPAD_BEGIN,		"NUMPAD_BEGIN"		},
		{ WXK_NUMPAD_INSERT,	"NUMPAD_INSERT"		},
		{ WXK_NUMPAD_DELETE,	"NUMPAD_DELETE"		},
		{ WXK_NUMPAD_EQUAL,		"NUMPAD_EQUAL"		},
		{ WXK_NUMPAD_MULTIPLY,	"NUMPAD_MULTIPLY"	},
		{ WXK_NUMPAD_ADD,		"NUMPAD_ADD"		},
		{ WXK_NUMPAD_SEPARATOR,	"NUMPAD_SEPARATOR"	},
		{ WXK_NUMPAD_SUBTRACT,	"NUMPAD_SUBTRACT"	},
		{ WXK_NUMPAD_DECIMAL,	"NUMPAD_DECIMAL"	},
		{ WXK_NUMPAD_DIVIDE,	"NUMPAD_DIVIDE"		},
		{ WXK_WINDOWS_LEFT,		"WINDOWS_LEFT"		},
		{ WXK_WINDOWS_RIGHT,	"WINDOWS_RIGHT"		},
		{ WXK_WINDOWS_MENU,		"WINDOWS_MENU"		},
		{ WXK_COMMAND,			"COMMAND"			},
		{ WXK_SPECIAL1,			"SPECIAL1"			},
		{ WXK_SPECIAL2,			"SPECIAL2"			},
		{ WXK_SPECIAL3,			"SPECIAL3"			},
		{ WXK_SPECIAL4,			"SPECIAL4"			},
		{ WXK_SPECIAL5,			"SPECIAL5"			},
		{ WXK_SPECIAL6,			"SPECIAL6"			},
		{ WXK_SPECIAL7,			"SPECIAL7"			},
		{ WXK_SPECIAL8,			"SPECIAL8"			},
		{ WXK_SPECIAL9,			"SPECIAL9"			},
		{ WXK_SPECIAL10,		"SPECIAL10"			},
		{ WXK_SPECIAL11,		"SPECIAL11"			},
		{ WXK_SPECIAL12,		"SPECIAL12"			},
		{ WXK_SPECIAL13,		"SPECIAL13"			},
		{ WXK_SPECIAL14,		"SPECIAL14"			},
		{ WXK_SPECIAL15,		"SPECIAL15"			},
		{ WXK_SPECIAL16,		"SPECIAL16"			},
		{ WXK_SPECIAL17,		"SPECIAL17"			},
		{ WXK_SPECIAL18,		"SPECIAL18"			},
		{ WXK_SPECIAL19,		"SPECIAL19"			},
		{ WXK_SPECIAL20,		"SPECIAL20"			},
	};
	using Map = std::unordered_map<int, String>;
	static Map* pMap = nullptr;
	if (!pMap) {
		pMap = new Map();
		for (int i = 0; i < Gurax_ArraySizeOf(assocTbl); i++) {
			(*pMap)[assocTbl[i].keyCode] = assocTbl[i].name;
		}
	}
	auto iter = pMap->find(keyCode);
	if (iter != pMap->end()) return iter->second;
	if (String::IsPrint(keyCode)) return String().Format("%c", keyCode);
	return String().Format("#%d", keyCode);
}

wxArrayString CreateArrayString(const ValueList& values)
{
	wxArrayString rtn;
	rtn.reserve(values.size());
	for (const Value* pValue : values) rtn.push_back(Value_String::GetString(*pValue));
	return rtn;
}

wxArrayShort CreateArrayShort(const ValueList& values)
{
	wxArrayShort rtn;
	rtn.reserve(values.size());
	for (const Value* pValue : values) rtn.push_back(Value_Number::GetNumber<Short>(*pValue));
	return rtn;
}

wxArrayInt CreateArrayInt(const ValueList& values)
{
	wxArrayInt rtn;
	rtn.reserve(values.size());
	for (const Value* pValue : values) rtn.push_back(Value_Number::GetNumber<Int>(*pValue));
	return rtn;
}

wxArrayDouble CreateArrayDouble(const ValueList& values)
{
	wxArrayDouble rtn;
	rtn.reserve(values.size());
	for (const Value* pValue : values) rtn.push_back(Value_Number::GetNumber<Double>(*pValue));
	return rtn;
}

wxArrayLong CreateArrayLong(const ValueList& values)
{
	wxArrayLong rtn;
	rtn.reserve(values.size());
	for (const Value* pValue : values) rtn.push_back(Value_Number::GetNumber<Long>(*pValue));
	return rtn;
}

wxPointList* CreatePointList(const ValueList& values)
{
	std::unique_ptr<wxPointList> rtn(new wxPointList());
	for (const Value* pValue : values) rtn->push_back(new wxPoint(Value_wxPoint::GetEntity(*pValue)));
	return rtn.release();
}

Value* CreateList(const wxArrayString& array)
{
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	pValueOwner->reserve(array.size());
	for (const wxString& str : array) pValueOwner->push_back(new Value_String(str.utf8_str().data()));
	return new Value_List(VTYPE_String, pValueOwner.release());
}

Value* CreateList(const wxArrayShort& array)
{
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	pValueOwner->reserve(array.size());
	for (Short num : array) pValueOwner->push_back(new Value_Number(num));
	return new Value_List(VTYPE_String, pValueOwner.release());
}

Value* CreateList(const wxArrayInt& array)
{
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	pValueOwner->reserve(array.size());
	for (Int num : array) pValueOwner->push_back(new Value_Number(num));
	return new Value_List(VTYPE_String, pValueOwner.release());
}

Value* CreateList(const wxArrayDouble& array)
{
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	pValueOwner->reserve(array.size());
	for (Double num : array) pValueOwner->push_back(new Value_Number(num));
	return new Value_List(VTYPE_String, pValueOwner.release());
}

Value* CreateList(const wxArrayLong& array)
{
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	pValueOwner->reserve(array.size());
	for (Long num : array) pValueOwner->push_back(new Value_Number(num));
	return new Value_List(VTYPE_String, pValueOwner.release());
}

void BindMultiEvents(Processor& processor, Argument& argument,
		const wxEventType eventTypes[], size_t n, const EventValueFactory& eventValueFactory)
{
	// Arguments
	ArgPicker args(argument);
	wxEvtHandler* pEvtHandler = args.Pick<Value_wxEvtHandler>().GetEntityPtr();
	Value& valueFunct = args.PickValue();
	int id = args.IsValid()? args.PickNumber<int>() : wxID_ANY;
	// Function body
	for (size_t i = 0; i < n; i++) {
		wxEventType eventType = eventTypes[i];
		pEvtHandler->Bind(eventType, &EventUserData::HandlerFunc, id, -1,
			new EventUserData(processor.Reference(), valueFunct.Reference(), Value::nil(), eventValueFactory));
	}
}

const Value& LookupEventType(wxEventType eventType)
{
	auto iter = eventTypeMap.find(eventType);
	if (iter == eventTypeMap.end()) return Value::C_nil();
	return *iter->second;
}

wxImage CreateImage(const Image& imageGura)
{
	wxImage image(imageGura.GetWidth(), imageGura.GetHeight(), false);
	size_t nPixels = imageGura.GetWidth() * imageGura.GetHeight();
	size_t bytesPerPixel = imageGura.GetBytesPerPixel();
	const UInt8* pBuffSrc = imageGura.GetPointerC();
	UInt8* pBuffDst = image.GetData();
	if (imageGura.IsFormat(Image::Format::RGBA)) {
		image.SetAlpha();
		UInt8* pBuffDstAlpha = image.GetAlpha();
		for (size_t i = 0; i < nPixels; i++) {
			*(pBuffDst + 0) = *(pBuffSrc + Image::offsetR);
			*(pBuffDst + 1) = *(pBuffSrc + Image::offsetG);
			*(pBuffDst + 2) = *(pBuffSrc + Image::offsetB);
			*pBuffDstAlpha = *(pBuffSrc + Image::offsetA);
			pBuffSrc += bytesPerPixel;
			pBuffDst += 3;
			pBuffDstAlpha++;
		}
	} else {
		for (size_t i = 0; i < nPixels; i++) {
			*(pBuffDst + 0) = *(pBuffSrc + Image::offsetR);
			*(pBuffDst + 1) = *(pBuffSrc + Image::offsetG);
			*(pBuffDst + 2) = *(pBuffSrc + Image::offsetB);
			pBuffSrc += bytesPerPixel;
			pBuffDst += 3;
		}
	}
	return image;
}

void ExitMainLoop()
{
	wxWindow* window = wxDynamicCast(wxApp::GetInstance(), wxApp)->GetTopWindow();
	if (window) window->Close(true);
	if (Error::IsIssued()) {
		String str;
		for (Error* pError : Error::GetErrorOwner()) {
			str += pError->MakeMessage();
			str += "\n";
		}
		wxMessageBox(str.c_str(), "Gurax Script Error", wxICON_ERROR | wxOK);
	}
	wxApp::GetInstance()->ExitMainLoop();
}

}

Gurax_EndModuleScope(wx)
