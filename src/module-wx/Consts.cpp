//==============================================================================
// Consts.cpp
//==============================================================================
#include "stdafx.h"

#define Gurax_AssignWxValue(name) frame.Assign(#name, new Value_Number(wx##name))

Gurax_BeginModuleScope(wx)

void AssignConsts(Frame& frame)
{
    Gurax_AssignWxValue(ID_ANY);
    Gurax_AssignWxValue(ID_LOWEST);
    Gurax_AssignWxValue(ID_OPEN);
    Gurax_AssignWxValue(ID_CLOSE);
    Gurax_AssignWxValue(ID_NEW);
    Gurax_AssignWxValue(ID_SAVE);
    Gurax_AssignWxValue(ID_SAVEAS);
    Gurax_AssignWxValue(ID_REVERT);
    Gurax_AssignWxValue(ID_EXIT);
    Gurax_AssignWxValue(ID_UNDO);
    Gurax_AssignWxValue(ID_REDO);
    Gurax_AssignWxValue(ID_HELP);
    Gurax_AssignWxValue(ID_PRINT);
    Gurax_AssignWxValue(ID_PRINT_SETUP);
    Gurax_AssignWxValue(ID_PAGE_SETUP);
    Gurax_AssignWxValue(ID_PREVIEW);
    Gurax_AssignWxValue(ID_ABOUT);
    Gurax_AssignWxValue(ID_HELP_CONTENTS);
    Gurax_AssignWxValue(ID_HELP_INDEX);
    Gurax_AssignWxValue(ID_HELP_SEARCH);
    Gurax_AssignWxValue(ID_HELP_COMMANDS);
    Gurax_AssignWxValue(ID_HELP_PROCEDURES);
    Gurax_AssignWxValue(ID_HELP_CONTEXT);
    Gurax_AssignWxValue(ID_CLOSE_ALL);
    Gurax_AssignWxValue(ID_PREFERENCES);
    Gurax_AssignWxValue(ID_EDIT);
    Gurax_AssignWxValue(ID_CUT);
    Gurax_AssignWxValue(ID_COPY);
    Gurax_AssignWxValue(ID_PASTE);
    Gurax_AssignWxValue(ID_CLEAR);
    Gurax_AssignWxValue(ID_FIND);
    Gurax_AssignWxValue(ID_DUPLICATE);
    Gurax_AssignWxValue(ID_SELECTALL);
    Gurax_AssignWxValue(ID_DELETE);
    Gurax_AssignWxValue(ID_REPLACE);
    Gurax_AssignWxValue(ID_REPLACE_ALL);
    Gurax_AssignWxValue(ID_PROPERTIES);
    Gurax_AssignWxValue(ID_VIEW_DETAILS);
    Gurax_AssignWxValue(ID_VIEW_LARGEICONS);
    Gurax_AssignWxValue(ID_VIEW_SMALLICONS);
    Gurax_AssignWxValue(ID_VIEW_LIST);
    Gurax_AssignWxValue(ID_VIEW_SORTDATE);
    Gurax_AssignWxValue(ID_VIEW_SORTNAME);
    Gurax_AssignWxValue(ID_VIEW_SORTSIZE);
    Gurax_AssignWxValue(ID_VIEW_SORTTYPE);
    Gurax_AssignWxValue(ID_FILE);
    Gurax_AssignWxValue(ID_FILE1);
    Gurax_AssignWxValue(ID_FILE2);
    Gurax_AssignWxValue(ID_FILE3);
    Gurax_AssignWxValue(ID_FILE4);
    Gurax_AssignWxValue(ID_FILE5);
    Gurax_AssignWxValue(ID_FILE6);
    Gurax_AssignWxValue(ID_FILE7);
    Gurax_AssignWxValue(ID_FILE8);
    Gurax_AssignWxValue(ID_FILE9);
    // Standard button IDs
    Gurax_AssignWxValue(ID_OK);
    Gurax_AssignWxValue(ID_CANCEL);
    Gurax_AssignWxValue(ID_APPLY);
    Gurax_AssignWxValue(ID_YES);
    Gurax_AssignWxValue(ID_NO);
    Gurax_AssignWxValue(ID_STATIC);
    Gurax_AssignWxValue(ID_FORWARD);
    Gurax_AssignWxValue(ID_BACKWARD);
    Gurax_AssignWxValue(ID_DEFAULT);
    Gurax_AssignWxValue(ID_MORE);
    Gurax_AssignWxValue(ID_SETUP);
    Gurax_AssignWxValue(ID_RESET);
    Gurax_AssignWxValue(ID_CONTEXT_HELP);
    Gurax_AssignWxValue(ID_YESTOALL);
    Gurax_AssignWxValue(ID_NOTOALL);
    Gurax_AssignWxValue(ID_ABORT);
    Gurax_AssignWxValue(ID_RETRY);
    Gurax_AssignWxValue(ID_IGNORE);
    Gurax_AssignWxValue(ID_ADD);
    Gurax_AssignWxValue(ID_REMOVE);
    Gurax_AssignWxValue(ID_UP);
    Gurax_AssignWxValue(ID_DOWN);
    Gurax_AssignWxValue(ID_HOME);
    Gurax_AssignWxValue(ID_REFRESH);
    Gurax_AssignWxValue(ID_STOP);
    Gurax_AssignWxValue(ID_INDEX);
    Gurax_AssignWxValue(ID_BOLD);
    Gurax_AssignWxValue(ID_ITALIC);
    Gurax_AssignWxValue(ID_JUSTIFY_CENTER);
    Gurax_AssignWxValue(ID_JUSTIFY_FILL);
    Gurax_AssignWxValue(ID_JUSTIFY_RIGHT);
    Gurax_AssignWxValue(ID_JUSTIFY_LEFT);
    Gurax_AssignWxValue(ID_UNDERLINE);
    Gurax_AssignWxValue(ID_INDENT);
    Gurax_AssignWxValue(ID_UNINDENT);
    Gurax_AssignWxValue(ID_ZOOM_100);
    Gurax_AssignWxValue(ID_ZOOM_FIT);
    Gurax_AssignWxValue(ID_ZOOM_IN);
    Gurax_AssignWxValue(ID_ZOOM_OUT);
    Gurax_AssignWxValue(ID_UNDELETE);
    Gurax_AssignWxValue(ID_REVERT_TO_SAVED);
    // System menu IDs (used by wxUniv):
    Gurax_AssignWxValue(ID_SYSTEM_MENU);
    Gurax_AssignWxValue(ID_CLOSE_FRAME);
    Gurax_AssignWxValue(ID_MOVE_FRAME);
    Gurax_AssignWxValue(ID_RESIZE_FRAME);
    Gurax_AssignWxValue(ID_MAXIMIZE_FRAME);
    Gurax_AssignWxValue(ID_ICONIZE_FRAME);
    Gurax_AssignWxValue(ID_RESTORE_FRAME);
    // IDs used by generic file dialog (13 consecutive starting from this value)
    Gurax_AssignWxValue(ID_FILEDLGG);
	Gurax_AssignWxValue(ID_HIGHEST);

	Gurax_AssignWxValue(OK);
	Gurax_AssignWxValue(ICON_INFORMATION);

	Gurax_AssignWxValue(VERTICAL);
	Gurax_AssignWxValue(HORIZONTAL);
    // wx.Sizer
    Gurax_AssignWxValue(TOP);
    Gurax_AssignWxValue(BOTTOM);
    Gurax_AssignWxValue(LEFT);
    Gurax_AssignWxValue(RIGHT);
    Gurax_AssignWxValue(ALL);
    Gurax_AssignWxValue(EXPAND);
    Gurax_AssignWxValue(SHAPED);
    Gurax_AssignWxValue(FIXED_MINSIZE);
    Gurax_AssignWxValue(RESERVE_SPACE_EVEN_IF_HIDDEN);
    Gurax_AssignWxValue(ALIGN_CENTER);
    Gurax_AssignWxValue(ALIGN_CENTRE);
    Gurax_AssignWxValue(ALIGN_LEFT);
    Gurax_AssignWxValue(ALIGN_RIGHT);
    Gurax_AssignWxValue(ALIGN_TOP);
    Gurax_AssignWxValue(ALIGN_BOTTOM);
    Gurax_AssignWxValue(ALIGN_CENTER_VERTICAL);
    Gurax_AssignWxValue(ALIGN_CENTRE_VERTICAL);
    Gurax_AssignWxValue(ALIGN_CENTER_HORIZONTAL);
    Gurax_AssignWxValue(ALIGN_CENTRE_HORIZONTAL);

}

Gurax_EndModuleScope(wx)
