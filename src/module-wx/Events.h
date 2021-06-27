//==============================================================================
// Events.h
//==============================================================================
#ifndef GURAX_MODULE_WX_EVENTS_H
#define GURAX_MODULE_WX_EVENTS_H
#include <gurax.h>

Gurax_BeginModuleScope(wx)

void AssignEvents(Frame& frame);
const Value& LookupEventType(wxEventType eventType);

Gurax_EndModuleScope(wx)

#endif
