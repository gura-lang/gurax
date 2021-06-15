//==============================================================================
// VTypes.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPES_H
#define GURAX_MODULE_WX_VTYPES_H
#include <gurax.h>
#include "VType_wxApp.h"
#include "VType_wxEventType.h"
#include "VType_wxAnyButton.h"
#include "VType_wxAppConsole.h"
#include "VType_wxButton.h"
#include "VType_wxCommandEvent.h"
#include "VType_wxControl.h"
#include "VType_wxEvent.h"
#include "VType_wxEvtHandler.h"
#include "VType_wxFrame.h"
#include "VType_wxMenu.h"
#include "VType_wxMenuBar.h"
#include "VType_wxMenuItem.h"
#include "VType_wxObject.h"
#include "VType_wxPanel.h"
#include "VType_wxPoint.h"
#include "VType_wxSize.h"
#include "VType_wxStatusBar.h"
#include "VType_wxValidator.h"
#include "VType_wxWindow.h"

Gurax_BeginModuleScope(wx)

void AssignVTypes(Frame& frame);

Gurax_EndModuleScope(wx)

#endif
