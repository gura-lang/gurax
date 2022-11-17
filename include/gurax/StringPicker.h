//==============================================================================
// StringPicker.h
//==============================================================================
#ifndef GURAX_STRINGPICKER_H
#define GURAX_STRINGPICKER_H
#include "Value.h"

namespace Gurax {

//------------------------------------------------------------------------------
// StringPicker
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE StringPicker {
public:
	// Constructor
	StringPicker() = default;
	// Copy constructor/operator
	StringPicker(const StringPicker& src) = delete;
	StringPicker& operator=(const StringPicker& src) = delete;
	// Move constructor/operator
	StringPicker(StringPicker&& src) = delete;
	StringPicker& operator=(StringPicker&& src) noexcept = delete;
	// Destructor
	virtual ~StringPicker() = default;
public:
	virtual const char* Pick() = 0;
};

//------------------------------------------------------------------------------
// StringPicker_StringList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE StringPicker_StringList : public StringPicker {
private:
	StringList::const_iterator _pStr, _pStrEnd;
public:
	StringPicker_StringList(const StringList& strList) :
		_pStr(strList.begin()), _pStrEnd(strList.end()) {}
	virtual const char* Pick() override;
};

//------------------------------------------------------------------------------
// StringPicker_ValueList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE StringPicker_ValueList : public StringPicker {
private:
	String _str;
	ValueList::const_iterator _ppValue, _ppValueEnd;
	const StringStyle& _ss;
public:
	StringPicker_ValueList(const ValueList& valueList, const StringStyle& ss) :
		_ppValue(valueList.begin()), _ppValueEnd(valueList.end()), _ss(ss) {}
	virtual const char* Pick() override;
};

}

#endif
