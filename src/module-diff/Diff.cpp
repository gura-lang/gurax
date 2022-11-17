//==============================================================================
// Diff.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(diff)

//------------------------------------------------------------------------------
// Diff
//------------------------------------------------------------------------------
bool Diff::Compose(Value& value1, Value& value2)
{
	if (!FeedValue(_context.A, value1) || !FeedValue(_context.B, value2)) return false;
	_context.init();
	_context.onHuge();
	_context.compose();
	return true;
}

bool Diff::FeedValue(Sequence& seq, Value& value)
{
	bool rtn = true;
	if (value.IsType(VTYPE_String)) {
		FeedString(seq, Value_String::GetString(value));
	} else if (value.IsType(VTYPE_Stream)) {
		rtn = FeedStream(seq, Value_Stream::GetStream(value));
	} else if (value.IsType(VTYPE_Binary)) {
		RefPtr<Stream> pStream(new Stream_Binary(
			Stream::Flag::Readable, Value_Binary::GetBinaryReferable(value).Reference()));
		rtn = FeedStream(seq, *pStream);
	} else if (value.IsType(VTYPE_Iterator)) {
		rtn = FeedIterator(seq, Value_Iterator::GetIterator(value));
	} else if (value.IsType(VTYPE_List)) {
		FeedList(seq, Value_List::GetValueOwner(value));
	} else {
		Error::Issue(ErrorType::TypeError, "invalid value type");
		rtn = false;
	}
	return rtn;
}

void Diff::FeedString(Sequence& seq, const char* src)
{
	String str;
	for (const char* p = src; *p != '\0'; p++) {
		char ch = *p;
		if (ch == '\n') {
			seq.push_back(str);
			str.clear();
		} else {
			str += ch;
		}
	}
	if (!str.empty()) seq.push_back(str);
}

bool Diff::FeedStream(Sequence& seq, Stream& src)
{
	bool includeEOLFlag = false;
	for (;;) {
		String str;
		if (!src.ReadLine(str, includeEOLFlag)) break;
		seq.push_back(str);
	}
	return !Error::IsIssued();
}

bool Diff::FeedIterator(Sequence& seq, Iterator& iter)
{
	for (;;) {
		RefPtr<Value> pValue(iter.NextValue());
		if (!pValue) break;
		seq.push_back(pValue->ToString());
	}
	return !Error::IsIssued();
}

void Diff::FeedList(Sequence& seq, const ValueList& valList)
{
	for (const Value* pValue : valList) {
		seq.push_back(pValue->ToString());
	}
}

String Diff::ToString(const StringStyle& ss) const
{
	return "diff.Diff";
}

Gurax_EndModuleScope(diff)
