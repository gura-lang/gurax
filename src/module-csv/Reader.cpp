//==============================================================================
// Reader.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(csv)

//------------------------------------------------------------------------------
// Reader
//------------------------------------------------------------------------------
Reader::Reader(Stream* pStream) : _pStream(pStream)
{
	_field.reserve(2048);
}

bool Reader::ReadLine(ValueOwner& valueOwner)
{
	Stat stat = Stat::LineTop;
	char ch = '\0';
	bool contFlag = true;
	bool eatNextChar = true;
	while (contFlag) {
		if (eatNextChar) {
			while ((ch = GetStream().GetChar()) == '\r') ;
			if (Error::IsIssued()) return false;
		}
		eatNextChar = true;
		switch (stat) {
		case Stat::LineTop:
			if (ch == '\0') {
				return false;
			} else if (ch == '\n') {
				contFlag = false;
			} else {
				eatNextChar = false;
				stat = Stat::FieldTop;
			}
			break;
		case Stat::FieldTop:
			_field.clear();
			if (ch == '"') {
				stat = Stat::Quoted;
			} else if (ch == '\n' || ch == '\0') {
				valueOwner.push_back(new Value_String(_field));
				contFlag = false;
			} else {
				eatNextChar = false;
				stat = Stat::Field;
			}
			break;
		case Stat::Field:
			if (ch == ',') {
				valueOwner.push_back(new Value_String(_field));
				stat = Stat::FieldTop;
			} else if (ch == '\n' || ch == '\0') {
				valueOwner.push_back(new Value_String(_field));
				contFlag = false;
			} else {
				_field.push_back(ch);
			}
			break;
		case Stat::Quoted:
			if (ch == '"') {
				stat = Stat::QuotedEnd;
			} else if (ch == '\0') {
				valueOwner.push_back(new Value_String(_field));
				contFlag = false;
			} else {
				_field.push_back(ch);
			}
			break;
		case Stat::QuotedEnd:
			if (ch == '"') {
				_field.push_back(ch);
				stat = Stat::Quoted;
			} else if (ch == '\0') {
				valueOwner.push_back(new Value_String(_field));
				contFlag = false;
			} else {
				eatNextChar = false;
				stat = Stat::Field;
			}
			break;
		default:
			break;
		}
	}
	return true;
}

String Reader::ToString(const StringStyle& ss) const
{
	return String().Format("csv.Reader:%s", _pStream->GetName());
}

//------------------------------------------------------------------------------
// Iterator_ReadLine
//------------------------------------------------------------------------------
Value* Iterator_ReadLine::DoNextValue()
{
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	if (!_pReader->ReadLine(*pValueOwner)) return nullptr;
	if (_asListFlag) {
		return new Value_List(VTYPE_String, pValueOwner.release());
	} else {
		return new Value_Tuple(pValueOwner.release());
	}
}

String Iterator_ReadLine::ToString(const StringStyle& ss) const
{
	return String().Format("csv.ReadLine:%s", _pReader->GetStream().GetName());
}

Gurax_EndModuleScope(csv)
