//==============================================================================
// VTypes.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPES_H
#define GURAX_MODULE_WX_VTYPES_H
#include <gurax.h>
#include "VType_wxAnyButton.h"
#include "VType_App.h"
#include "VType_wxAppConsole.h"
#include "VType_Button.h"
#include "VType_CommandEvent.h"
#include "VType_Control.h"
#include "VType_wxEvent.h"
#include "VType_wxEventType.h"
#include "VType_wxEvtHandler.h"
#include "VType_Frame.h"
#include "VType_Menu.h"
#include "VType_MenuBar.h"
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
