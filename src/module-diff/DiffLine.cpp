//==============================================================================
// DiffLine.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(diff)

//------------------------------------------------------------------------------
// DiffLine
//------------------------------------------------------------------------------
bool DiffLine::Compose(Value& value1, Value& value2)
{
	if (!FeedValue(_diff.A, value1) || !FeedValue(_diff.B, value2)) return false;
	_diff.init();
	_diff.onHuge();
	_diff.compose();
	_diff.composeUnifiedHunks();
	return true;
}

void DiffLine::PrintHunks(Stream& stream) const
{
	for (const Hunk& hunk : _diff.uniHunks) PrintHunk(stream, hunk);
}

void DiffLine::PrintHunk(Stream& stream, const Hunk& hunk)
{
	stream.Printf("@@ -%d,%d +%d,%d @@\n", hunk.a, hunk.b, hunk.c, hunk.d);
	for (const SesElem& sesElem : hunk.common[0]) {
		stream.Printf(" %s\n", sesElem.first.c_str());
	}
	for (const SesElem& sesElem : hunk.change) {
		stream.Printf("%s%s\n",
			(sesElem.second.type == dtl::SES_ADD)? SES_MARK_ADD :
			(sesElem.second.type == dtl::SES_DELETE)? SES_MARK_DELETE :
			(sesElem.second.type == dtl::SES_COMMON)? SES_MARK_COMMON : "?",
			sesElem.first.c_str());
	}
	for (const SesElem& sesElem : hunk.common[1]) {
		stream.Printf(" %s\n", sesElem.first.c_str());
	}
}

bool DiffLine::FeedValue(Sequence& seq, Value& value)
{
	bool rtn = true;
	if (value.IsType(VTYPE_String)) {
		FeedString(seq, Value_String::GetString(value));
	} else if (value.IsType(VTYPE_Stream)) {
		rtn = FeedStream(seq, Value_Stream::GetStream(value));
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

void DiffLine::FeedString(Sequence& seq, const char* src)
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

bool DiffLine::FeedStream(Sequence& seq, Stream& src)
{
	bool includeEOLFlag = false;
	for (;;) {
		String str;
		if (!src.ReadLine(str, includeEOLFlag)) break;
		seq.push_back(str);
	}
	return !Error::IsIssued();
}

bool DiffLine::FeedIterator(Sequence& seq, Iterator& iter)
{
	do {
		RefPtr<Value> pValue(iter.NextValue());
		seq.push_back(pValue->ToString(StringStyle::AsValue));
	} while (0);
	return !Error::IsIssued();
}

void DiffLine::FeedList(Sequence& seq, const ValueList& valList)
{
	for (const Value* pValue : valList) {
		seq.push_back(pValue->ToString(StringStyle::AsValue));
	}
}

String DiffLine::ToString(const StringStyle& ss) const
{
	return "diff.DiffLine";
}

Gurax_EndModuleScope(diff)
