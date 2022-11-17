//==============================================================================
// Writer.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(csv)

//------------------------------------------------------------------------------
// Writer
//------------------------------------------------------------------------------
const char* Writer::_formatForNumberDefault = "%g";

Writer::Writer(Stream* pStream) : _pStream(pStream), _formatForNumber(_formatForNumberDefault)
{
	_str.reserve(2048);
}

bool Writer::PutValue(String& str, const Value& value)
{
	if (value.IsInvalid()) {
		return true;
	} else if (value.IsType(VTYPE_Number)) {
		str.FormatValue(GetFormatForNumber(), value);
	} else if (value.IsType(VTYPE_Complex)) {
		str.FormatValue(GetFormatForNumber(), value);
	} else if (value.IsType(VTYPE_String)) {
		str += '"';
		for (const char* p = Value_String::GetString(value); *p != '\0'; p++) {
			char ch = *p;
			str += ch;
			if (ch == '"') str += '"';
		}
		str += '"';
	} else {
		Error::Issue(ErrorType::TypeError, "can't output in CSV format");
		return false;
	}
	return true;
}

bool Writer::PutValues(const ValueList& valList, bool appendEOLFlag)
{
	_str.clear();
	ValueList::const_iterator ppValue = valList.begin();
	if (ppValue != valList.end()) {
		if (!PutValue(_str, **ppValue)) return false;
		ppValue++;
		for ( ; ppValue != valList.end(); ppValue++) {
			_str += ',';
			if (!PutValue(_str, **ppValue)) return false;
		}
	}
	if (appendEOLFlag) _str += '\n';
	_pStream->Print(_str);
	return !Error::IsIssued();
}

String Writer::ToString(const StringStyle& ss) const
{
	return String().Format("csv.Writer:%s", _pStream->GetName());
}

Gurax_EndModuleScope(csv)
