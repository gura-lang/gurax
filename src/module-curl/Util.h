//==============================================================================
// Util.h
//==============================================================================
#ifndef GURAX_MODULE_CURL_UTIL_H
#define GURAX_MODULE_CURL_UTIL_H
#include <gurax.h>

Gurax_BeginModuleScope(curl)

curl_slist* CreateSListFromIterator(Iterator& iter);
curl_slist* CreateSListFromValueList(const ValueList& values);
ValueOwner* CreateValueOwnerFromSList(const curl_slist* slist);

Gurax_EndModuleScope(curl)

#endif
