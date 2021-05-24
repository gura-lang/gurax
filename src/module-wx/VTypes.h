//==============================================================================
// VTypes.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPES_H
#define GURAX_MODULE_WX_VTYPES_H
#include <gurax.h>
#include "VType_AnyButton.h"
#include "VType_App.h"
#include "VType_AppConsole.h"
#include "VType_Button.h"
#include "VType_CommandEvent.h"
#include "VType_Control.h"
#include "VType_Event.h"
#include "VType_EventType.h"
#include "VType_EvtHandler.h"
#include "VType_Frame.h"
#include "VType_Menu.h"
#include "VType_MenuBar.h"
#include "VType_MenuItem.h"
#include "VType_Panel.h"
#include "VType_Point.h"
#include "VType_Size.h"
#include "VType_StatusBar.h"
#include "VType_Validator.h"
#include "VType_Window.h"

Gurax_BeginModuleScope(wx)

void AssignVTypes(Frame& frame);

Gurax_EndModuleScope(wx)

#endif
