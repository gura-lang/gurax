//==============================================================================
// Objects.cpp
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(wx)

void AssignObjects(Frame& frame)
{
	do { // Predefined Objects of wxBrush
		frame.Assign("NullBrush",			new Value_wxBrush(wxNullBrush));
		frame.Assign("BLACK_BRUSH",			new Value_wxBrush(*wxBLACK_BRUSH));
		frame.Assign("BLUE_BRUSH",			new Value_wxBrush(*wxBLUE_BRUSH));
		frame.Assign("CYAN_BRUSH",			new Value_wxBrush(*wxCYAN_BRUSH));
		frame.Assign("GREEN_BRUSH",			new Value_wxBrush(*wxGREEN_BRUSH));
		frame.Assign("YELLOW_BRUSH",		new Value_wxBrush(*wxYELLOW_BRUSH));
		frame.Assign("GREY_BRUSH",			new Value_wxBrush(*wxGREY_BRUSH));
		frame.Assign("LIGHT_GREY_BRUSH",	new Value_wxBrush(*wxLIGHT_GREY_BRUSH));
		frame.Assign("MEDIUM_GREY_BRUSH",	new Value_wxBrush(*wxMEDIUM_GREY_BRUSH));
		frame.Assign("RED_BRUSH",			new Value_wxBrush(*wxRED_BRUSH));
		frame.Assign("TRANSPARENT_BRUSH",	new Value_wxBrush(*wxTRANSPARENT_BRUSH));
		frame.Assign("WHITE_BRUSH",			new Value_wxBrush(*wxWHITE_BRUSH));
	} while (0);
	do { // Predefined Objects of wxColour
		frame.Assign("NullColour",			new Value_wxColour(wxNullColour));
		frame.Assign("TransparentColour",	new Value_wxColour(wxTransparentColour));
		frame.Assign("BLACK",				new Value_wxColour(*wxBLACK));
		frame.Assign("BLUE",				new Value_wxColour(*wxBLUE));
		frame.Assign("CYAN",				new Value_wxColour(*wxCYAN));
		frame.Assign("GREEN",				new Value_wxColour(*wxGREEN));
		frame.Assign("YELLOW",				new Value_wxColour(*wxYELLOW));
		frame.Assign("LIGHT_GREY",			new Value_wxColour(*wxLIGHT_GREY));
		frame.Assign("RED",					new Value_wxColour(*wxRED));
		frame.Assign("WHITE",				new Value_wxColour(*wxWHITE));
	} while (0);
	do { // Predefined Objects of wxCursor
		frame.Assign("NullCursor",			new Value_wxCursor(wxNullCursor));
		frame.Assign("STANDARD_CURSOR",		new Value_wxCursor(*wxSTANDARD_CURSOR));
		frame.Assign("HOURGLASS_CURSOR",	new Value_wxCursor(*wxHOURGLASS_CURSOR));
		frame.Assign("CROSS_CURSOR",		new Value_wxCursor(*wxCROSS_CURSOR));
	} while (0);
	do { // Predefined Objects of wxFont
		frame.Assign("NullFont",			new Value_wxFont(wxNullFont));
		frame.Assign("NORMAL_FONT",			new Value_wxFont(*wxNORMAL_FONT));
		frame.Assign("SMALL_FONT",			new Value_wxFont(*wxSMALL_FONT));
		frame.Assign("ITALIC_FONT",			new Value_wxFont(*wxITALIC_FONT));
		frame.Assign("SWISS_FONT",			new Value_wxFont(*wxSWISS_FONT));
	} while (0);
	do { // Predefined Objects of wxPen
		frame.Assign("NullPen",				new Value_wxPen(wxNullPen));
		frame.Assign("BLACK_DASHED_PEN",	new Value_wxPen(*wxBLACK_DASHED_PEN));
		frame.Assign("BLACK_PEN",			new Value_wxPen(*wxBLACK_PEN));
		frame.Assign("BLUE_PEN",			new Value_wxPen(*wxBLUE_PEN));
		frame.Assign("CYAN_PEN",			new Value_wxPen(*wxCYAN_PEN));
		frame.Assign("GREEN_PEN",			new Value_wxPen(*wxGREEN_PEN));
		frame.Assign("YELLOW_PEN",			new Value_wxPen(*wxYELLOW_PEN));
		frame.Assign("GREY_PEN",			new Value_wxPen(*wxGREY_PEN));
		frame.Assign("LIGHT_GREY_PEN",		new Value_wxPen(*wxLIGHT_GREY_PEN));
		frame.Assign("MEDIUM_GREY_PEN",		new Value_wxPen(*wxMEDIUM_GREY_PEN));
		frame.Assign("RED_PEN",				new Value_wxPen(*wxRED_PEN));
		frame.Assign("TRANSPARENT_PEN",		new Value_wxPen(*wxTRANSPARENT_PEN));
		frame.Assign("WHITE_PEN",			new Value_wxPen(*wxWHITE_PEN));
	} while (0);
	do { // Predefined Objects of wxPoint
		frame.Assign("DefaultPosition", new Value_wxPoint(wxDefaultPosition));
	} while (0);
	do { // Predefined Objects of wxSize
		frame.Assign("DefaultSize", new Value_wxSize(wxDefaultSize));
	} while (0);
	do { // textdlg.h
		frame.Assign("GetTextFromUserPromptStr", new Value_String(wxGetTextFromUserPromptStr));
		frame.Assign("GetPasswordFromUserPromptStr", new Value_String(wxGetPasswordFromUserPromptStr));
	} while (0);
	do {
		frame.Assign("EmptyString", new Value_String(""));
	} while (0);
}

Gurax_EndModuleScope(wx)
