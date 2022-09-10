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
	bool rtn = true;
	bool eatNextChar = true;
	for (;;) {
		if (eatNextChar) {
			while ((ch = NextChar(sig)) == '\r') ;
			if (sig.IsSignalled()) return false;
		}
		eatNextChar = true;
		if (stat == Stat::LineTop) {
			if (ch == '\0') {
				rtn = false;
				break;
			}
			eatNextChar = false;
			stat = Stat::FieldTop;
		} else if (stat == Stat::FieldTop) {
			field.clear();
			if (ch == '"') {
				stat = Stat::Quoted;
			} else if (ch == '\n' || ch == '\0') {
				valList.push_back(Value(field));
				break;
			} else {
				eatNextChar = false;
				stat = Stat::Field;
			}
		} else if (stat == Stat::Field) {
			if (ch == ',') {
				valList.push_back(Value(field));
				stat = Stat::FieldTop;
			} else if (ch == '\n' || ch == '\0') {
				valList.push_back(Value(field));
				break;
			} else {
				field.push_back(ch);
			}
		} else if (stat == Stat::Quoted) {
			if (ch == '"') {
				stat = Stat::QuotedEnd;
			} else if (ch == '\0') {
				valList.push_back(Value(field));
				break;
			} else {
				field.push_back(ch);
			}
		} else if (stat == Stat::QuotedEnd) {
			if (ch == '"') {
				field.push_back(ch);
				stat = Stat::Quoted;
			} else if (ch == '\0') {
				valList.push_back(Value(field));
				break;
			} else {
				eatNextChar = false;
				stat = Stat::Field;
			}
		}
	}
	return rtn;
}

String Reader::ToString(const StringStyle& ss) const
{
	return String().Format("csv.Reader");
}

Gurax_EndModuleScope(csv)
