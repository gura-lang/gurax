//==============================================================================
// Functions.cpp
//==============================================================================
#include "stdafx.h"

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

Gurax_BeginModuleScope(wx)

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
	auto app = Value_App::GetEntity(args.PickValue());
	// Function Body
	wxApp::SetInstance(app);
	int argc = 0;
	char *argv[1] = { nullptr };
	::wxEntry(argc, argv);
	return Value::nil();
}

// wx.MessageBox(message as String, caption? as String, style? as Number, parent? as wx.Window, x? as Number, y? as Number)
Gurax_DeclareFunctionAlias(MessageBox_, "MessageBox")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("message", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("caption", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("parent", VTYPE_Window, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(MessageBox_)
{
	// Arguments
	ArgPicker args(argument);
	const char* message = args.PickString();
	const char* caption = args.IsValid()? args.PickString() : wxMessageBoxCaptionStr;
	int style = args.IsValid()? args.PickNumber<int>() : (wxOK | wxCENTRE);
	wxWindow* parent = args.IsValid()? args.Pick<Value_Window>().GetEntity() : nullptr;
	int x = args.IsValid()? args.PickNumber<int>() : wxDefaultCoord;
	int y = args.IsValid()? args.PickNumber<int>() : wxDefaultCoord;
	// Function body
	int rtn = wxMessageBox(message, caption, style, parent, x, y);
	return new Value_Number(rtn);
}

//------------------------------------------------------------------------------
// Assignment
//------------------------------------------------------------------------------
void AssignFunctions(Frame& frame)
{
	frame.Assign(Gurax_CreateFunction(Test));
	frame.Assign(Gurax_CreateFunction(ImplementApp));
	frame.Assign(Gurax_CreateFunction(MessageBox_));
}

Gurax_EndModuleScope(wx)
