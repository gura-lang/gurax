//==============================================================================
// module-wx.cpp
//==============================================================================
#include "stdafx.h"

#define Gurax_AssignWxValue(name) frame.Assign(#name, new Value_Number(wx##name))

class MyApp: public wxApp
{
public:
    virtual bool OnInit();
};
class MyFrame: public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();
};
enum
{
    ID_Hello = 1
};
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(ID_Hello,   MyFrame::OnHello)
    EVT_MENU(wxID_EXIT,  MyFrame::OnExit)
    EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
wxEND_EVENT_TABLE()
//wxIMPLEMENT_APP(MyApp);
bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame( "Hello World", wxPoint(50, 50), wxSize(450, 340) );
    frame->Show( true );
    return true;
}
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" );
    menuBar->Append( menuHelp, "&Help" );
    SetMenuBar( menuBar );
    CreateStatusBar();
    SetStatusText( "Welcome to wxWidgets!" );
}
void MyFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox( "This is a wxWidgets' Hello world sample",
                  "About Hello World", wxOK | wxICON_INFORMATION );
}
void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}

Gurax_BeginModule(wx)

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
}

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// wx.Test()
Gurax_DeclareFunction(Test)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(Test)
{
	int argc = 0;
	char *argv[1] = { nullptr };
	wxApp::SetInstance(new MyApp());
	::wxEntry(argc, argv);
    return Value::nil();
}

// wx.ImplementApp(app:wx.App)
Gurax_DeclareFunction(ImplementApp)
{
	Declare(VTYPE_Nil, Flag::None);
    DeclareArg("app", VTYPE_App, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(ImplementApp)
{
    // Argument
    ArgPicker args(argument);
    auto pEntity = Value_App::GetEntity(args.PickValue());
    // Function Body
	wxApp::SetInstance(pEntity);
	int argc = 0;
	char *argv[1] = { nullptr };
	::wxEntry(argc, argv);
    return Value::nil();
}

//------------------------------------------------------------------------------
// Entries
//------------------------------------------------------------------------------
Gurax_ModuleValidate()
{
	return Version::CheckCoreVersion(GURAX_VERSION, nullptr);
}

Gurax_ModulePrepare()
{
	// Assignment of VType
    Assign(VTYPE_App);
    Assign(VTYPE_AppConsole);
    Assign(VTYPE_Control);
    Assign(VTYPE_Event);
    Assign(VTYPE_EvtHandler);
    Assign(VTYPE_Frame);
    Assign(VTYPE_Menu);
    Assign(VTYPE_MenuBar);
    Assign(VTYPE_MenuItem);
    Assign(VTYPE_Point);
    Assign(VTYPE_Size);
    Assign(VTYPE_StatusBar);
    Assign(VTYPE_Window);
	// Assignment of constant
    AssignConsts(GetFrame());
	// Assignment of function
	Assign(Gurax_CreateFunction(Test));
	Assign(Gurax_CreateFunction(ImplementApp));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(wx)

#if defined(__WXMSW__)
WXDLLIMPEXP_BASE void wxSetInstance(HINSTANCE hInst);

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD dwReason, LPVOID lpvReserved)
{
	// This is necessary to load resources correctly.
	::wxSetInstance(hInst);
	return TRUE;
}
#endif
