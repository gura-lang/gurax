//==============================================================================
// Writer.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(csv)

//------------------------------------------------------------------------------
// Writer
//------------------------------------------------------------------------------
String Writer::_format = "%g";

Writer::Writer(Stream* pStream) : _pStream(pStream)
{
	_str.reserve(2048);
}

bool Writer::PutValue(String& str, const Value& value)
{
	if (value.IsInvalid()) {
		return true;
	} else if (value.IsType(VTYPE_Number)) {
		str.FormatValue(_format.c_str(), value);
	} else if (value.IsType(VTYPE_Complex)) {
		str.FormatValue(_format.c_str(), value);
	} else if (value.IsType(VTYPE_String)) {
		str += '"';
		for (const char* p = Value_String::GetString(value); *p != '\0'; p++) {
			char ch = *p;
			str += ch;
			if (ch == '"') str += ch;
		}
		str += '"';
	} else {
		Error::Issue(ErrorType::TypeError, "can't output in CSV format");
		return false;
	}
	_pStream->Print(str.c_str());
	return true;
}

bool Writer::PutValues(const ValueList& valList)
{
	_str.clear();
	bool firstFlag = true;
	ValueList::const_iterator ppValue = valList.begin();
	if (ppValue == valList.end()) return true;
	if (!PutValue(_str, **ppValue)) return false;
	for ( ; ppValue != valList.end(); ppValue++) {
		_str += ',';
		if (!PutValue(_str, **ppValue)) return false;
	}
	_str += '\n';
	_pStream->Print(_str);
	return !Error::IsIssued();
}

String Writer::ToString(const StringStyle& ss) const
{
	return String().Format("csv.Writer");
}

Gurax_EndModuleScope(csv)
