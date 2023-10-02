﻿//==============================================================================
// Events.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// Assignment
//------------------------------------------------------------------------------
void AssignEvents(Frame& frame)
{
	Gurax_AssignEvent(EVT_ACTIVATE,								wxActivateEvent);
	Gurax_AssignEvent(EVT_ACTIVATE_APP,							wxActivateEvent);
	Gurax_AssignEvent(EVT_AUITOOLBAR_BEGIN_DRAG,				wxAuiToolBarEvent);
	Gurax_AssignEvent(EVT_AUITOOLBAR_MIDDLE_CLICK,				wxAuiToolBarEvent);
	Gurax_AssignEvent(EVT_AUITOOLBAR_OVERFLOW_CLICK,			wxAuiToolBarEvent);
	Gurax_AssignEvent(EVT_AUITOOLBAR_RIGHT_CLICK,				wxAuiToolBarEvent);
	Gurax_AssignEvent(EVT_AUITOOLBAR_TOOL_DROPDOWN,				wxAuiToolBarEvent);
	Gurax_AssignEvent(EVT_AUX1_DCLICK,							wxMouseEvent);
	Gurax_AssignEvent(EVT_AUX1_DOWN,							wxMouseEvent);
	Gurax_AssignEvent(EVT_AUX1_UP,								wxMouseEvent);
	Gurax_AssignEvent(EVT_AUX2_DCLICK,							wxMouseEvent);
	Gurax_AssignEvent(EVT_AUX2_DOWN,							wxMouseEvent);
	Gurax_AssignEvent(EVT_AUX2_UP,								wxMouseEvent);
	Gurax_AssignEvent(EVT_BUTTON,								wxCommandEvent);
	Gurax_AssignEvent(EVT_CALCULATE_LAYOUT,						wxCalculateLayoutEvent);
	Gurax_AssignEvent(EVT_CHAR,									wxKeyEvent);
	Gurax_AssignEvent(EVT_CHAR_HOOK,							wxKeyEvent);
	Gurax_AssignEvent(EVT_CHECKBOX,								wxCommandEvent);
	Gurax_AssignEvent(EVT_CHECKLISTBOX,							wxCommandEvent);
	Gurax_AssignEvent(EVT_CHECKLISTBOX,							wxCommandEvent);
	Gurax_AssignEvent(EVT_CHILD_FOCUS,							wxChildFocusEvent);
	Gurax_AssignEvent(EVT_CHOICE,								wxCommandEvent);
	Gurax_AssignEvent(EVT_CHOICE,								wxCommandEvent);
	Gurax_AssignEvent(EVT_CHOICEBOOK_PAGE_CHANGED,				wxBookCtrlEvent);
	Gurax_AssignEvent(EVT_CHOICEBOOK_PAGE_CHANGING,				wxBookCtrlEvent);
	Gurax_AssignEvent(EVT_COLLAPSIBLEHEADER_CHANGED,			wxCommandEvent);
	Gurax_AssignEvent(EVT_COLLAPSIBLEPANE_CHANGED,				wxCollapsiblePaneEvent);
	Gurax_AssignEvent(EVT_COLOURPICKER_CHANGED,					wxColourPickerEvent);
	Gurax_AssignEvent(EVT_COMBOBOX,								wxCommandEvent);
	Gurax_AssignEvent(EVT_COMBOBOX_CLOSEUP,						wxCommandEvent);
	Gurax_AssignEvent(EVT_COMBOBOX_DROPDOWN,					wxCommandEvent);
	Gurax_AssignEvent(EVT_COMMAND_BUTTON_CLICKED,				wxCommandEvent);
	Gurax_AssignEvent(EVT_COMMAND_ENTER,						wxCommandEvent);
	Gurax_AssignEvent(EVT_COMMAND_KILL_FOCUS,					wxCommandEvent);
	Gurax_AssignEvent(EVT_COMMAND_LEFT_CLICK,					wxCommandEvent);
	Gurax_AssignEvent(EVT_COMMAND_LEFT_DCLICK,					wxCommandEvent);
	Gurax_AssignEvent(EVT_COMMAND_RIGHT_CLICK,					wxCommandEvent);
	Gurax_AssignEvent(EVT_COMMAND_RIGHT_DCLICK,					wxCommandEvent);
	Gurax_AssignEvent(EVT_COMMAND_SET_FOCUS,					wxCommandEvent);
	Gurax_AssignEvent(EVT_CONTEXT_MENU,							wxContextMenuEvent);
	Gurax_AssignEvent(EVT_CONTEXT_MENU,							wxCommandEvent);
	Gurax_AssignEvent(EVT_DATAVIEW_CACHE_HINT,					wxDataViewEvent);
	Gurax_AssignEvent(EVT_DATAVIEW_COLUMN_HEADER_CLICK,			wxDataViewEvent);
	Gurax_AssignEvent(EVT_DATAVIEW_COLUMN_HEADER_RIGHT_CLICK,	wxDataViewEvent);
	Gurax_AssignEvent(EVT_DATAVIEW_COLUMN_REORDERED,			wxDataViewEvent);
	Gurax_AssignEvent(EVT_DATAVIEW_COLUMN_SORTED,				wxDataViewEvent);
	Gurax_AssignEvent(EVT_DATAVIEW_ITEM_ACTIVATED,				wxDataViewEvent);
	Gurax_AssignEvent(EVT_DATAVIEW_ITEM_BEGIN_DRAG,				wxDataViewEvent);
	Gurax_AssignEvent(EVT_DATAVIEW_ITEM_COLLAPSED,				wxDataViewEvent);
	Gurax_AssignEvent(EVT_DATAVIEW_ITEM_COLLAPSING,				wxDataViewEvent);
	Gurax_AssignEvent(EVT_DATAVIEW_ITEM_CONTEXT_MENU,			wxDataViewEvent);
	Gurax_AssignEvent(EVT_DATAVIEW_ITEM_DROP,					wxDataViewEvent);
	Gurax_AssignEvent(EVT_DATAVIEW_ITEM_DROP_POSSIBLE,			wxDataViewEvent);
	Gurax_AssignEvent(EVT_DATAVIEW_ITEM_EDITING_DONE,			wxDataViewEvent);
	Gurax_AssignEvent(EVT_DATAVIEW_ITEM_EDITING_STARTED,		wxDataViewEvent);
	Gurax_AssignEvent(EVT_DATAVIEW_ITEM_EXPANDED,				wxDataViewEvent);
	Gurax_AssignEvent(EVT_DATAVIEW_ITEM_EXPANDING,				wxDataViewEvent);
	Gurax_AssignEvent(EVT_DATAVIEW_ITEM_VALUE_CHANGED,			wxDataViewEvent);
	Gurax_AssignEvent(EVT_DATAVIEW_SELECTION_CHANGED,			wxDataViewEvent);
	Gurax_AssignEvent(EVT_DATE_CHANGED,							wxDateEvent);
	Gurax_AssignEvent(EVT_DIALUP_CONNECTED,						wxDialUpEvent);
	Gurax_AssignEvent(EVT_DIALUP_DISCONNECTED,					wxDialUpEvent);
	Gurax_AssignEvent(EVT_DIRPICKER_CHANGED,					wxFileDirPickerEvent);
	Gurax_AssignEvent(EVT_DROP_FILES,							wxDropFilesEvent);
	Gurax_AssignEvent(EVT_END_PROCESS,							wxProcessEvent);
	Gurax_AssignEvent(EVT_END_SESSION,							wxCloseEvent);
	Gurax_AssignEvent(EVT_ENTER_WINDOW,							wxMouseEvent);
	Gurax_AssignEvent(EVT_ERASE_BACKGROUND,						wxEraseEvent);
	Gurax_AssignEvent(EVT_FILECTRL_FILEACTIVATED,				wxFileCtrlEvent);
	Gurax_AssignEvent(EVT_FILECTRL_FILTERCHANGED,				wxFileCtrlEvent);
	Gurax_AssignEvent(EVT_FILECTRL_FOLDERCHANGED,				wxFileCtrlEvent);
	Gurax_AssignEvent(EVT_FILECTRL_SELECTIONCHANGED,			wxFileCtrlEvent);
	Gurax_AssignEvent(EVT_FILEPICKER_CHANGED,					wxFileDirPickerEvent);
	Gurax_AssignEvent(EVT_FONTPICKER_CHANGED,					wxFontPickerEvent);
	Gurax_AssignEvent(EVT_GRID_CELL_CHANGED,					wxGridEvent);
	Gurax_AssignEvent(EVT_GRID_CELL_CHANGING,					wxGridEvent);
	Gurax_AssignEvent(EVT_GRID_CELL_LEFT_CLICK,					wxGridEvent);
	Gurax_AssignEvent(EVT_GRID_CELL_LEFT_DCLICK,				wxGridEvent);
	Gurax_AssignEvent(EVT_GRID_CELL_RIGHT_CLICK,				wxGridEvent);
	Gurax_AssignEvent(EVT_GRID_CELL_RIGHT_DCLICK,				wxGridEvent);
	Gurax_AssignEvent(EVT_GRID_COL_MOVE,						wxGridEvent);
	Gurax_AssignEvent(EVT_GRID_COL_SORT,						wxGridEvent);
	Gurax_AssignEvent(EVT_GRID_EDITOR_HIDDEN,					wxGridEvent);
	Gurax_AssignEvent(EVT_GRID_EDITOR_SHOWN,					wxGridEvent);
	Gurax_AssignEvent(EVT_GRID_LABEL_LEFT_CLICK,				wxGridEvent);
	Gurax_AssignEvent(EVT_GRID_LABEL_LEFT_DCLICK,				wxGridEvent);
	Gurax_AssignEvent(EVT_GRID_LABEL_RIGHT_CLICK,				wxGridEvent);
	Gurax_AssignEvent(EVT_GRID_LABEL_RIGHT_DCLICK,				wxGridEvent);
	Gurax_AssignEvent(EVT_GRID_SELECT_CELL,						wxGridEvent);
	Gurax_AssignEvent(EVT_GRID_TABBING,							wxGridEvent);
	Gurax_AssignEvent(EVT_HEADER_BEGIN_REORDER,					wxHeaderCtrlEvent);
	Gurax_AssignEvent(EVT_HEADER_BEGIN_RESIZE,					wxHeaderCtrlEvent);
	Gurax_AssignEvent(EVT_HEADER_CLICK,							wxHeaderCtrlEvent);
	Gurax_AssignEvent(EVT_HEADER_DCLICK,						wxHeaderCtrlEvent);
	Gurax_AssignEvent(EVT_HEADER_DRAGGING_CANCELLED,			wxHeaderCtrlEvent);
	Gurax_AssignEvent(EVT_HEADER_END_REORDER,					wxHeaderCtrlEvent);
	Gurax_AssignEvent(EVT_HEADER_END_RESIZE,					wxHeaderCtrlEvent);
	Gurax_AssignEvent(EVT_HEADER_MIDDLE_CLICK,					wxHeaderCtrlEvent);
	Gurax_AssignEvent(EVT_HEADER_MIDDLE_DCLICK,					wxHeaderCtrlEvent);
	Gurax_AssignEvent(EVT_HEADER_RESIZING,						wxHeaderCtrlEvent);
	Gurax_AssignEvent(EVT_HEADER_RIGHT_CLICK,					wxHeaderCtrlEvent);
	Gurax_AssignEvent(EVT_HEADER_RIGHT_DCLICK,					wxHeaderCtrlEvent);
	Gurax_AssignEvent(EVT_HEADER_SEPARATOR_DCLICK,				wxHeaderCtrlEvent);
	Gurax_AssignEvent(EVT_HELP,									wxHelpEvent);
	Gurax_AssignEvent(EVT_HIBERNATE,							wxActivateEvent);
	Gurax_AssignEvent(EVT_HTML_CELL_CLICKED,					wxHtmlCellEvent);
	Gurax_AssignEvent(EVT_HTML_CELL_HOVER,						wxHtmlCellEvent);
	Gurax_AssignEvent(EVT_HTML_LINK_CLICKED,					wxHtmlLinkEvent);
	Gurax_AssignEvent(EVT_HYPERLINK,							wxHyperlinkEvent);
	Gurax_AssignEvent(EVT_ICONIZE,								wxIconizeEvent);
	Gurax_AssignEvent(EVT_IDLE,									wxIdleEvent);
	Gurax_AssignEvent(EVT_INIT_DIALOG,							wxInitDialogEvent);
	Gurax_AssignEvent(EVT_JOY_BUTTON_DOWN,						wxJoystickEvent);
	Gurax_AssignEvent(EVT_JOY_BUTTON_UP,						wxJoystickEvent);
	Gurax_AssignEvent(EVT_JOY_MOVE,								wxJoystickEvent);
	Gurax_AssignEvent(EVT_JOY_ZMOVE,							wxJoystickEvent);
	Gurax_AssignEvent(EVT_KEY_DOWN,								wxKeyEvent);
	Gurax_AssignEvent(EVT_KEY_UP,								wxKeyEvent);
	Gurax_AssignEvent(EVT_KILL_FOCUS,							wxFocusEvent);
	Gurax_AssignEvent(EVT_LEAVE_WINDOW,							wxMouseEvent);
	Gurax_AssignEvent(EVT_LEFT_DCLICK,							wxMouseEvent);
	Gurax_AssignEvent(EVT_LEFT_DOWN,							wxMouseEvent);
	Gurax_AssignEvent(EVT_LEFT_UP,								wxMouseEvent);
	Gurax_AssignEvent(EVT_LISTBOOK_PAGE_CHANGED,				wxBookCtrlEvent);
	Gurax_AssignEvent(EVT_LISTBOOK_PAGE_CHANGING,				wxBookCtrlEvent);
	Gurax_AssignEvent(EVT_LISTBOX,								wxCommandEvent);
	Gurax_AssignEvent(EVT_LISTBOX_DCLICK,						wxCommandEvent);
	Gurax_AssignEvent(EVT_LIST_BEGIN_DRAG,						wxListEvent);
	Gurax_AssignEvent(EVT_LIST_BEGIN_LABEL_EDIT,				wxListEvent);
	Gurax_AssignEvent(EVT_LIST_BEGIN_RDRAG,						wxListEvent);
	Gurax_AssignEvent(EVT_LIST_CACHE_HINT,						wxListEvent);
	Gurax_AssignEvent(EVT_LIST_COL_BEGIN_DRAG,					wxListEvent);
	Gurax_AssignEvent(EVT_LIST_COL_CLICK,						wxListEvent);
	Gurax_AssignEvent(EVT_LIST_COL_DRAGGING,					wxListEvent);
	Gurax_AssignEvent(EVT_LIST_COL_END_DRAG,					wxListEvent);
	Gurax_AssignEvent(EVT_LIST_COL_RIGHT_CLICK,					wxListEvent);
	Gurax_AssignEvent(EVT_LIST_DELETE_ALL_ITEMS,				wxListEvent);
	Gurax_AssignEvent(EVT_LIST_DELETE_ITEM,						wxListEvent);
	Gurax_AssignEvent(EVT_LIST_END_LABEL_EDIT,					wxListEvent);
	Gurax_AssignEvent(EVT_LIST_INSERT_ITEM,						wxListEvent);
	Gurax_AssignEvent(EVT_LIST_ITEM_ACTIVATED,					wxListEvent);
	Gurax_AssignEvent(EVT_LIST_ITEM_DESELECTED,					wxListEvent);
	Gurax_AssignEvent(EVT_LIST_ITEM_FOCUSED,					wxListEvent);
	Gurax_AssignEvent(EVT_LIST_ITEM_MIDDLE_CLICK,				wxListEvent);
	Gurax_AssignEvent(EVT_LIST_ITEM_RIGHT_CLICK,				wxListEvent);
	Gurax_AssignEvent(EVT_LIST_ITEM_SELECTED,					wxListEvent);
	Gurax_AssignEvent(EVT_LIST_KEY_DOWN,						wxListEvent);
	Gurax_AssignEvent(EVT_MAXIMIZE,								wxMaximizeEvent);
	Gurax_AssignEvent(EVT_MENU,									wxCommandEvent);
	Gurax_AssignEvent(EVT_MENU_CLOSE,							wxMenuEvent);
	Gurax_AssignEvent(EVT_MENU_HIGHLIGHT,						wxMenuEvent);
	Gurax_AssignEvent(EVT_MENU_OPEN,							wxMenuEvent);
	Gurax_AssignEvent(EVT_MIDDLE_DCLICK,						wxMouseEvent);
	Gurax_AssignEvent(EVT_MIDDLE_DOWN,							wxMouseEvent);
	Gurax_AssignEvent(EVT_MIDDLE_UP,							wxMouseEvent);
	Gurax_AssignEvent(EVT_MOTION,								wxMouseEvent);
	Gurax_AssignEvent(EVT_MOUSEWHEEL,							wxMouseEvent);
	Gurax_AssignEvent(EVT_MOUSE_CAPTURE_CHANGED,				wxMouseCaptureChangedEvent);
	Gurax_AssignEvent(EVT_MOUSE_CAPTURE_LOST,					wxMouseCaptureLostEvent);
	Gurax_AssignEvent(EVT_MOVE,									wxMoveEvent);
	Gurax_AssignEvent(EVT_MOVE_END,								wxMoveEvent);
	Gurax_AssignEvent(EVT_MOVE_START,							wxMoveEvent);
	Gurax_AssignEvent(EVT_MOVING,								wxMoveEvent);
	Gurax_AssignEvent(EVT_NAVIGATION_KEY,						wxNavigationKeyEvent);
	Gurax_AssignEvent(EVT_NOTEBOOK_PAGE_CHANGED,				wxBookCtrlEvent);
	Gurax_AssignEvent(EVT_NOTEBOOK_PAGE_CHANGING,				wxBookCtrlEvent);
	Gurax_AssignEvent(EVT_PAINT,								wxPaintEvent);
	Gurax_AssignEvent(EVT_PG_CHANGED,							wxPropertyGridEvent);
	Gurax_AssignEvent(EVT_PG_CHANGING,							wxPropertyGridEvent);
	Gurax_AssignEvent(EVT_PG_COL_BEGIN_DRAG,					wxPropertyGridEvent);
	Gurax_AssignEvent(EVT_PG_COL_DRAGGING,						wxPropertyGridEvent);
	Gurax_AssignEvent(EVT_PG_COL_END_DRAG,						wxPropertyGridEvent);
	Gurax_AssignEvent(EVT_PG_DOUBLE_CLICK,						wxPropertyGridEvent);
	Gurax_AssignEvent(EVT_PG_HIGHLIGHTED,						wxPropertyGridEvent);
	Gurax_AssignEvent(EVT_PG_ITEM_COLLAPSED,					wxPropertyGridEvent);
	Gurax_AssignEvent(EVT_PG_ITEM_EXPANDED,						wxPropertyGridEvent);
	Gurax_AssignEvent(EVT_PG_LABEL_EDIT_BEGIN,					wxPropertyGridEvent);
	Gurax_AssignEvent(EVT_PG_LABEL_EDIT_ENDING,					wxPropertyGridEvent);
	Gurax_AssignEvent(EVT_PG_RIGHT_CLICK,						wxPropertyGridEvent);
	Gurax_AssignEvent(EVT_PG_SELECTED,							wxPropertyGridEvent);
	Gurax_AssignEvent(EVT_POWER_RESUME,							wxPowerEvent);
	Gurax_AssignEvent(EVT_POWER_SUSPENDED,						wxPowerEvent);
	Gurax_AssignEvent(EVT_POWER_SUSPENDING,						wxPowerEvent);
	Gurax_AssignEvent(EVT_POWER_SUSPEND_CANCEL,					wxPowerEvent);
	Gurax_AssignEvent(EVT_QUERY_END_SESSION,					wxCloseEvent);
	Gurax_AssignEvent(EVT_QUERY_LAYOUT_INFO,					wxQueryLayoutInfoEvent);
	Gurax_AssignEvent(EVT_RADIOBOX,								wxCommandEvent);
	Gurax_AssignEvent(EVT_RADIOBUTTON,							wxCommandEvent);
	Gurax_AssignEvent(EVT_RIBBONBAR_HELP_CLICK,					wxRibbonBarEvent);
	Gurax_AssignEvent(EVT_RIBBONBAR_PAGE_CHANGED,				wxRibbonBarEvent);
	Gurax_AssignEvent(EVT_RIBBONBAR_PAGE_CHANGING,				wxRibbonBarEvent);
	Gurax_AssignEvent(EVT_RIBBONBAR_TAB_LEFT_DCLICK,			wxRibbonBarEvent);
	Gurax_AssignEvent(EVT_RIBBONBAR_TAB_MIDDLE_DOWN,			wxRibbonBarEvent);
	Gurax_AssignEvent(EVT_RIBBONBAR_TAB_MIDDLE_UP,				wxRibbonBarEvent);
	Gurax_AssignEvent(EVT_RIBBONBAR_TAB_RIGHT_DOWN,				wxRibbonBarEvent);
	Gurax_AssignEvent(EVT_RIBBONBAR_TAB_RIGHT_UP,				wxRibbonBarEvent);
	Gurax_AssignEvent(EVT_RIBBONBAR_TOGGLED,					wxRibbonBarEvent);
	Gurax_AssignEvent(EVT_RIBBONBUTTONBAR_CLICKED,				wxRibbonButtonBarEvent);
	Gurax_AssignEvent(EVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED,		wxRibbonButtonBarEvent);
	Gurax_AssignEvent(EVT_RIGHT_DCLICK,							wxMouseEvent);
	Gurax_AssignEvent(EVT_RIGHT_DOWN,							wxMouseEvent);
	Gurax_AssignEvent(EVT_RIGHT_UP,								wxMouseEvent);
	Gurax_AssignEvent(EVT_SASH_DRAGGED,							wxSashEvent);
	Gurax_AssignEvent(EVT_SCROLLBAR,							wxCommandEvent);
	Gurax_AssignEvent(EVT_SCROLLWIN_BOTTOM,						wxScrollWinEvent);
	Gurax_AssignEvent(EVT_SCROLLWIN_LINEDOWN,					wxScrollWinEvent);
	Gurax_AssignEvent(EVT_SCROLLWIN_LINEUP,						wxScrollWinEvent);
	Gurax_AssignEvent(EVT_SCROLLWIN_PAGEDOWN,					wxScrollWinEvent);
	Gurax_AssignEvent(EVT_SCROLLWIN_PAGEUP,						wxScrollWinEvent);
	Gurax_AssignEvent(EVT_SCROLLWIN_THUMBRELEASE,				wxScrollWinEvent);
	Gurax_AssignEvent(EVT_SCROLLWIN_THUMBTRACK,					wxScrollWinEvent);
	Gurax_AssignEvent(EVT_SCROLLWIN_TOP,						wxScrollWinEvent);
	Gurax_AssignEvent(EVT_SCROLL_BOTTOM,						wxScrollEvent);
	Gurax_AssignEvent(EVT_SCROLL_CHANGED,						wxScrollEvent);
	Gurax_AssignEvent(EVT_SCROLL_LINEDOWN,						wxScrollEvent);
	Gurax_AssignEvent(EVT_SCROLL_LINEUP,						wxScrollEvent);
	Gurax_AssignEvent(EVT_SCROLL_PAGEDOWN,						wxScrollEvent);
	Gurax_AssignEvent(EVT_SCROLL_PAGEUP,						wxScrollEvent);
	Gurax_AssignEvent(EVT_SCROLL_THUMBRELEASE,					wxScrollEvent);
	Gurax_AssignEvent(EVT_SCROLL_THUMBTRACK,					wxScrollEvent);
	Gurax_AssignEvent(EVT_SCROLL_TOP,							wxScrollEvent);
	Gurax_AssignEvent(EVT_SET_CURSOR,							wxSetCursorEvent);
	Gurax_AssignEvent(EVT_SET_FOCUS,							wxFocusEvent);
	Gurax_AssignEvent(EVT_SHOW,									wxShowEvent);
	Gurax_AssignEvent(EVT_SIZE,									wxSizeEvent);
	Gurax_AssignEvent(EVT_SLIDER,								wxCommandEvent);
	Gurax_AssignEvent(EVT_SOCKET,								wxSocketEvent);
	Gurax_AssignEvent(EVT_SPIN,									wxSpinEvent);
	Gurax_AssignEvent(EVT_SPIN,									wxSpinEvent);
	Gurax_AssignEvent(EVT_SPINCTRL,								wxSpinEvent);
	Gurax_AssignEvent(EVT_SPIN_DOWN,							wxSpinEvent);
	Gurax_AssignEvent(EVT_SPIN_DOWN,							wxSpinEvent);
	Gurax_AssignEvent(EVT_SPIN_UP,								wxSpinEvent);
	Gurax_AssignEvent(EVT_SPIN_UP,								wxSpinEvent);
	Gurax_AssignEvent(EVT_SPLITTER_SASH_POS_CHANGED,			wxSplitterEvent);
	Gurax_AssignEvent(EVT_SPLITTER_SASH_POS_CHANGING,			wxSplitterEvent);
	Gurax_AssignEvent(EVT_SPLITTER_UNSPLIT,						wxSplitterEvent);
	Gurax_AssignEvent(EVT_STC_AUTOCOMP_CANCELLED,				wxStyledTextEvent);
	Gurax_AssignEvent(EVT_STC_AUTOCOMP_CHAR_DELETED,			wxStyledTextEvent);
	Gurax_AssignEvent(EVT_STC_AUTOCOMP_SELECTION,				wxStyledTextEvent);
	Gurax_AssignEvent(EVT_STC_CALLTIP_CLICK,					wxStyledTextEvent);
	Gurax_AssignEvent(EVT_STC_CHANGE,							wxStyledTextEvent);
	Gurax_AssignEvent(EVT_STC_CHARADDED,						wxStyledTextEvent);
	Gurax_AssignEvent(EVT_STC_DOUBLECLICK,						wxStyledTextEvent);
	Gurax_AssignEvent(EVT_STC_DO_DROP,							wxStyledTextEvent);
	Gurax_AssignEvent(EVT_STC_DRAG_OVER,						wxStyledTextEvent);
	Gurax_AssignEvent(EVT_STC_DWELLEND,							wxStyledTextEvent);
	Gurax_AssignEvent(EVT_STC_DWELLSTART,						wxStyledTextEvent);
	Gurax_AssignEvent(EVT_STC_HOTSPOT_CLICK,					wxStyledTextEvent);
	Gurax_AssignEvent(EVT_STC_HOTSPOT_DCLICK,					wxStyledTextEvent);
	Gurax_AssignEvent(EVT_STC_HOTSPOT_RELEASE_CLICK,			wxStyledTextEvent);
	Gurax_AssignEvent(EVT_STC_INDICATOR_CLICK,					wxStyledTextEvent);
	Gurax_AssignEvent(EVT_STC_INDICATOR_RELEASE,				wxStyledTextEvent);
	Gurax_AssignEvent(EVT_STC_KEY,								wxStyledTextEvent);
	Gurax_AssignEvent(EVT_STC_MACRORECORD,						wxStyledTextEvent);
	Gurax_AssignEvent(EVT_STC_MARGINCLICK,						wxStyledTextEvent);
	Gurax_AssignEvent(EVT_STC_MODIFIED,							wxStyledTextEvent);
	Gurax_AssignEvent(EVT_STC_NEEDSHOWN,						wxStyledTextEvent);
	Gurax_AssignEvent(EVT_STC_PAINTED,							wxStyledTextEvent);
	Gurax_AssignEvent(EVT_STC_ROMODIFYATTEMPT,					wxStyledTextEvent);
	Gurax_AssignEvent(EVT_STC_SAVEPOINTLEFT,					wxStyledTextEvent);
	Gurax_AssignEvent(EVT_STC_SAVEPOINTREACHED,					wxStyledTextEvent);
	Gurax_AssignEvent(EVT_STC_START_DRAG,						wxStyledTextEvent);
	Gurax_AssignEvent(EVT_STC_STYLENEEDED,						wxStyledTextEvent);
	Gurax_AssignEvent(EVT_STC_UPDATEUI,							wxStyledTextEvent);
	Gurax_AssignEvent(EVT_STC_URIDROPPED,						wxStyledTextEvent);
	Gurax_AssignEvent(EVT_STC_USERLISTSELECTION,				wxStyledTextEvent);
	Gurax_AssignEvent(EVT_STC_ZOOM,								wxStyledTextEvent);
	Gurax_AssignEvent(EVT_SYS_COLOUR_CHANGED,					wxSysColourChangedEvent);
	Gurax_AssignEvent(EVT_TEXT,									wxCommandEvent);
	Gurax_AssignEvent(EVT_TEXT_ENTER,							wxCommandEvent);
	Gurax_AssignEvent(EVT_TEXT_MAXLEN,							wxCommandEvent);
	Gurax_AssignEvent(EVT_TIMER,								wxTimerEvent);
	Gurax_AssignEvent(EVT_TIME_CHANGED,							wxDateEvent);
	Gurax_AssignEvent(EVT_TOOL,									wxCommandEvent);
	Gurax_AssignEvent(EVT_TOOLBOOK_PAGE_CHANGED,				wxBookCtrlEvent);
	Gurax_AssignEvent(EVT_TOOLBOOK_PAGE_CHANGING,				wxBookCtrlEvent);
	Gurax_AssignEvent(EVT_TOOL_ENTER,							wxCommandEvent);
	Gurax_AssignEvent(EVT_TOOL_RCLICKED,						wxCommandEvent);
	Gurax_AssignEvent(EVT_TREEBOOK_NODE_COLLAPSED,				wxBookCtrlEvent);
	Gurax_AssignEvent(EVT_TREEBOOK_NODE_EXPANDED,				wxBookCtrlEvent);
	Gurax_AssignEvent(EVT_TREEBOOK_PAGE_CHANGED,				wxBookCtrlEvent);
	Gurax_AssignEvent(EVT_TREEBOOK_PAGE_CHANGING,				wxBookCtrlEvent);
	Gurax_AssignEvent(EVT_TREELIST_COLUMN_SORTED,				wxTreeListEvent);
	Gurax_AssignEvent(EVT_TREELIST_ITEM_ACTIVATED,				wxTreeListEvent);
	Gurax_AssignEvent(EVT_TREELIST_ITEM_CHECKED,				wxTreeListEvent);
	Gurax_AssignEvent(EVT_TREELIST_ITEM_CONTEXT_MENU,			wxTreeListEvent);
	Gurax_AssignEvent(EVT_TREELIST_ITEM_EXPANDED,				wxTreeListEvent);
	Gurax_AssignEvent(EVT_TREELIST_ITEM_EXPANDING,				wxTreeListEvent);
	Gurax_AssignEvent(EVT_TREELIST_SELECTION_CHANGED,			wxTreeListEvent);
	Gurax_AssignEvent(EVT_TREE_BEGIN_DRAG,						wxTreeEvent);
	Gurax_AssignEvent(EVT_TREE_BEGIN_LABEL_EDIT,				wxTreeEvent);
	Gurax_AssignEvent(EVT_TREE_BEGIN_RDRAG,						wxTreeEvent);
	Gurax_AssignEvent(EVT_TREE_DELETE_ITEM,						wxTreeEvent);
	Gurax_AssignEvent(EVT_TREE_END_DRAG,						wxTreeEvent);
	Gurax_AssignEvent(EVT_TREE_END_LABEL_EDIT,					wxTreeEvent);
	Gurax_AssignEvent(EVT_TREE_GET_INFO,						wxTreeEvent);
	Gurax_AssignEvent(EVT_TREE_ITEM_ACTIVATED,					wxTreeEvent);
	Gurax_AssignEvent(EVT_TREE_ITEM_COLLAPSED,					wxTreeEvent);
	Gurax_AssignEvent(EVT_TREE_ITEM_COLLAPSING,					wxTreeEvent);
	Gurax_AssignEvent(EVT_TREE_ITEM_EXPANDED,					wxTreeEvent);
	Gurax_AssignEvent(EVT_TREE_ITEM_EXPANDING,					wxTreeEvent);
	Gurax_AssignEvent(EVT_TREE_ITEM_GETTOOLTIP,					wxTreeEvent);
	Gurax_AssignEvent(EVT_TREE_ITEM_MENU,						wxTreeEvent);
	Gurax_AssignEvent(EVT_TREE_ITEM_MIDDLE_CLICK,				wxTreeEvent);
	Gurax_AssignEvent(EVT_TREE_ITEM_RIGHT_CLICK,				wxTreeEvent);
	Gurax_AssignEvent(EVT_TREE_KEY_DOWN,						wxTreeEvent);
	Gurax_AssignEvent(EVT_TREE_SEL_CHANGED,						wxTreeEvent);
	Gurax_AssignEvent(EVT_TREE_SEL_CHANGING,					wxTreeEvent);
	Gurax_AssignEvent(EVT_TREE_SET_INFO,						wxTreeEvent);
	Gurax_AssignEvent(EVT_TREE_STATE_IMAGE_CLICK,				wxTreeEvent);
	Gurax_AssignEvent(EVT_UPDATE_UI,							wxUpdateUIEvent);
	Gurax_AssignEvent(EVT_WIZARD_BEFORE_PAGE_CHANGED,			wxWizardEvent);
	Gurax_AssignEvent(EVT_WIZARD_BEFORE_PAGE_CHANGED,			wxWizardEvent);
	Gurax_AssignEvent(EVT_WIZARD_CANCEL,						wxWizardEvent);
	Gurax_AssignEvent(EVT_WIZARD_CANCEL,						wxWizardEvent);
	Gurax_AssignEvent(EVT_WIZARD_FINISHED,						wxWizardEvent);
	Gurax_AssignEvent(EVT_WIZARD_FINISHED,						wxWizardEvent);
	Gurax_AssignEvent(EVT_WIZARD_HELP,							wxWizardEvent);
	Gurax_AssignEvent(EVT_WIZARD_HELP,							wxWizardEvent);
	Gurax_AssignEvent(EVT_WIZARD_PAGE_CHANGED,					wxWizardEvent);
	Gurax_AssignEvent(EVT_WIZARD_PAGE_CHANGED,					wxWizardEvent);
	Gurax_AssignEvent(EVT_WIZARD_PAGE_CHANGING,					wxWizardEvent);
	Gurax_AssignEvent(EVT_WIZARD_PAGE_CHANGING,					wxWizardEvent);
	Gurax_AssignEvent(EVT_WIZARD_PAGE_SHOWN,					wxWizardEvent);
	Gurax_AssignEvent(EVT_WIZARD_PAGE_SHOWN,					wxWizardEvent);
}

Gurax_EndModuleScope(wx)
