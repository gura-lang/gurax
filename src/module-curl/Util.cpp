//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(curl)

curl_slist* CreateSListFromValueList(const ValueList& values)
{
	curl_slist* slist = nullptr;
	for (const Value* pValue : values) {
		slist = curl_slist_append(slist, Value_String::GetString(*pValue));
	}
	return slist;
}

ValueOwner* CreateValueOwnerFromSList(const curl_slist* slist)
{
	RefPtr<ValueOwner> pValues(new ValueOwner());
	for ( ; slist; slist = slist->next) {
		pValues->push_back(new Value_String(slist->data));
	}
	return pValues.release();
}

Gurax_EndModuleScope(curl)
