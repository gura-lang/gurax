//==============================================================================
// Writer.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(csv)

//------------------------------------------------------------------------------
// Writer
//------------------------------------------------------------------------------
bool Writer::PutValue(const Value& value)
{
#if 0
	String str;
	if (value.IsInvalid()) {
		return true;
	} else if (value.IsType<VTYPE_Number>()) {
		str = Formatter::FormatValueList(_format.c_str(), ValueList(value));
	} else if (value.IsType<VTYPE_Complex>()) {
		str = Formatter::FormatValueList(_format.c_str(), ValueList(value));
	} else if (value.IsType<VTYPE_String>()) {
		str += '"';
		for (const char *p = value.GetString(); *p != '\0'; p++) {
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
#endif
	return true;
}

bool Writer::PutValues(const ValueList& valList)
{
	bool firstFlag = true;
	for (Value* pValue : valList) {
		if (firstFlag) {
			_pStream->PutChar(',');
			if (Error::IsIssued()) return false;
			firstFlag = false;
		}
		if (!PutValue(*pValue)) return false;
	}
	_pStream->PutChar('\n');
	return !Error::IsIssued();
}

String Writer::ToString(const StringStyle& ss) const
{
	return String().Format("csv.Writer");
}

Gurax_EndModuleScope(csv)
