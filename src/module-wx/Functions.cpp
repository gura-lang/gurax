﻿//==============================================================================
// Functions.cpp
//==============================================================================
#include "stdafx.h"
Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// wx.AboutBox(info as wx.AboutDialogInfo, parent? as wx.Window)
Gurax_DeclareFunctionAlias(AboutBox_gurax, "AboutBox")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("info", VTYPE_wxAboutDialogInfo, ArgOccur::Once, ArgFlag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementFunctionEx(AboutBox_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxAboutDialogInfo& value_info = args_gurax.Pick<Value_wxAboutDialogInfo>();
	const wxAboutDialogInfo& info = value_info.GetEntity();
	wxWindow* parent = args_gurax.IsValid()? args_gurax.Pick<Value_wxWindow>().GetEntityPtr() : nullptr;
	// Function body
	wxAboutBox(info, parent);
	return Gurax::Value::nil();
}

// wx.BeginBusyCursor(cursor? as wx.Cursor)
Gurax_DeclareFunctionAlias(BeginBusyCursor_gurax, "BeginBusyCursor")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cursor", VTYPE_wxCursor, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementFunctionEx(BeginBusyCursor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const wxCursor* cursor = args_gurax.IsValid()? args_gurax.Pick<Value_wxCursor>().GetEntityPtr() : nullptr;
	// Function body
	wxBeginBusyCursor(cursor);
	return Gurax::Value::nil();
}

// wx.Bell()
Gurax_DeclareFunctionAlias(Bell_gurax, "Bell")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementFunctionEx(Bell_gurax, processor_gurax, argument_gurax)
{
	// Function body
	wxBell();
	return Gurax::Value::nil();
}

// wx.DirSelector(message? as String, default_path? as String, style? as Number, pos? as wx.Point, parent? as wx.Window)
Gurax_DeclareFunctionAlias(DirSelector_gurax, "DirSelector")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("message", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("default_path", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementFunctionEx(DirSelector_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool message_validFlag = args_gurax.IsValid();
	wxString message = message_validFlag? wxString(args_gurax.PickString()) : wxDirSelectorPromptStr;
	bool default_path_validFlag = args_gurax.IsValid();
	wxString default_path = default_path_validFlag? wxString(args_gurax.PickString()) : "";
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	wxWindow* parent = args_gurax.IsValid()? args_gurax.Pick<Value_wxWindow>().GetEntityPtr() : nullptr;
	// Function body
	wxString rtn = wxDirSelector(message, default_path, style, pos, parent);
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.EndBusyCursor()
Gurax_DeclareFunctionAlias(EndBusyCursor_gurax, "EndBusyCursor")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementFunctionEx(EndBusyCursor_gurax, processor_gurax, argument_gurax)
{
	// Function body
	wxEndBusyCursor();
	return Gurax::Value::nil();
}

// wx.FileSelector(message as String, default_path? as String, default_filename? as String, default_extension? as String, wildcard? as String, flags? as Number, parent? as wx.Window, x? as Number, y? as Number)
Gurax_DeclareFunctionAlias(FileSelector_gurax, "FileSelector")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("message", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("default_path", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("default_filename", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("default_extension", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("wildcard", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementFunctionEx(FileSelector_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString message(args_gurax.PickString());
	bool default_path_validFlag = args_gurax.IsValid();
	wxString default_path = default_path_validFlag? wxString(args_gurax.PickString()) : "";
	bool default_filename_validFlag = args_gurax.IsValid();
	wxString default_filename = default_filename_validFlag? wxString(args_gurax.PickString()) : "";
	bool default_extension_validFlag = args_gurax.IsValid();
	wxString default_extension = default_extension_validFlag? wxString(args_gurax.PickString()) : "";
	bool wildcard_validFlag = args_gurax.IsValid();
	wxString wildcard = wildcard_validFlag? wxString(args_gurax.PickString()) : wxFileSelectorDefaultWildcardStr;
	bool flags_validFlag = args_gurax.IsValid();
	int flags = flags_validFlag? args_gurax.PickNumber<int>() : 0;
	wxWindow* parent = args_gurax.IsValid()? args_gurax.Pick<Value_wxWindow>().GetEntityPtr() : nullptr;
	bool x_validFlag = args_gurax.IsValid();
	int x = x_validFlag? args_gurax.PickNumber<int>() : wxDefaultCoord;
	bool y_validFlag = args_gurax.IsValid();
	int y = y_validFlag? args_gurax.PickNumber<int>() : wxDefaultCoord;
	// Function body
	wxString rtn = wxFileSelector(message, default_path, default_filename, default_extension, wildcard, flags, parent, x, y);
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.GetBatteryState()
Gurax_DeclareFunctionAlias(GetBatteryState_gurax, "GetBatteryState")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementFunctionEx(GetBatteryState_gurax, processor_gurax, argument_gurax)
{
	// Function body
	wxBatteryState rtn = wxGetBatteryState();
	return new Gurax::Value_Number(rtn);
}

// wx.GetColourFromUser(parent as wx.Window, colInit as wx.Colour, caption? as String, data? as wx.ColourData) {block?}
Gurax_DeclareFunctionAlias(GetColourFromUser_gurax, "GetColourFromUser")
{
	Declare(VTYPE_wxColour, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("colInit", VTYPE_wxColour, ArgOccur::Once, ArgFlag::None);
	DeclareArg("caption", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("data", VTYPE_wxColourData, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementFunctionEx(GetColourFromUser_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	Value_wxColour& value_colInit = args_gurax.Pick<Value_wxColour>();
	const wxColour& colInit = value_colInit.GetEntity();
	bool caption_validFlag = args_gurax.IsValid();
	wxString caption = caption_validFlag? wxString(args_gurax.PickString()) : "";
	wxColourData* data = args_gurax.IsValid()? args_gurax.Pick<Value_wxColourData>().GetEntityPtr() : nullptr;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxColour(wxGetColourFromUser(parent, colInit, caption, data)));
}

// wx.GetFontFromUser(parent as wx.Window, fontInit as wx.Font, caption? as String) {block?}
Gurax_DeclareFunctionAlias(GetFontFromUser_gurax, "GetFontFromUser")
{
	Declare(VTYPE_wxFont, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("fontInit", VTYPE_wxFont, ArgOccur::Once, ArgFlag::None);
	DeclareArg("caption", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementFunctionEx(GetFontFromUser_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	Value_wxFont& value_fontInit = args_gurax.Pick<Value_wxFont>();
	const wxFont& fontInit = value_fontInit.GetEntity();
	bool caption_validFlag = args_gurax.IsValid();
	wxString caption = caption_validFlag? wxString(args_gurax.PickString()) : "";
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxFont(wxGetFontFromUser(parent, fontInit, caption)));
}

// wx.GetKeyCodeName(keyCode as Number)
Gurax_DeclareFunctionAlias(GetKeyCodeName_gurax, "GetKeyCodeName")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("keyCode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(GetKeyCodeName_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int keyCode = args_gurax.PickNumber<int>();
	// Function body
	return new Value_String(Util::GetKeyCodeName(keyCode));
}

// wx.GetKeyState(key as Number)
Gurax_DeclareFunctionAlias(GetKeyState_gurax, "GetKeyState")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("key", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(GetKeyState_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxKeyCode key = args_gurax.PickNumber<wxKeyCode>();
	// Function body
	bool rtn = wxGetKeyState(key);
	return new Gurax::Value_Bool(rtn);
}

// wx.GetLocalTime()
Gurax_DeclareFunctionAlias(GetLocalTime_gurax, "GetLocalTime")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementFunctionEx(GetLocalTime_gurax, processor_gurax, argument_gurax)
{
	// Function body
	long rtn = wxGetLocalTime();
	return new Gurax::Value_Number(rtn);
}

// wx.GetLocalTimeMillis()
Gurax_DeclareFunctionAlias(GetLocalTimeMillis_gurax, "GetLocalTimeMillis")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementFunctionEx(GetLocalTimeMillis_gurax, processor_gurax, argument_gurax)
{
	// Function body
	wxLongLong rtn = wxGetLocalTimeMillis();
	return new Gurax::Value_Number(rtn.GetValue());
}

// wx.GetMousePosition() {block?}
Gurax_DeclareFunctionAlias(GetMousePosition_gurax, "GetMousePosition")
{
	Declare(VTYPE_wxPoint, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementFunctionEx(GetMousePosition_gurax, processor_gurax, argument_gurax)
{
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPoint(wxGetMousePosition()));
}

// wx.GetMouseState() {block?}
Gurax_DeclareFunctionAlias(GetMouseState_gurax, "GetMouseState")
{
	Declare(VTYPE_wxMouseState, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementFunctionEx(GetMouseState_gurax, processor_gurax, argument_gurax)
{
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxMouseState(wxGetMouseState()));
}

// wx.GetNumberFromUser(message as String, prompt as String, caption as String, value as Number, min? as Number, max? as Number, parent? as wx.Window, pos? as wx.Point)
Gurax_DeclareFunctionAlias(GetNumberFromUser_gurax, "GetNumberFromUser")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("message", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("prompt", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("caption", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("min", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("max", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementFunctionEx(GetNumberFromUser_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString message(args_gurax.PickString());
	wxString prompt(args_gurax.PickString());
	wxString caption(args_gurax.PickString());
	long value = args_gurax.PickNumber<long>();
	bool min_validFlag = args_gurax.IsValid();
	long min = min_validFlag? args_gurax.PickNumber<long>() : 0;
	bool max_validFlag = args_gurax.IsValid();
	long max = max_validFlag? args_gurax.PickNumber<long>() : 100;
	wxWindow* parent = args_gurax.IsValid()? args_gurax.Pick<Value_wxWindow>().GetEntityPtr() : nullptr;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	// Function body
	long rtn = wxGetNumberFromUser(message, prompt, caption, value, min, max, parent, pos);
	return new Gurax::Value_Number(rtn);
}

// wx.GetPasswordFromUser(message as String, caption? as String, default_value? as String, parent? as wx.Window, x? as Number, y? as Number, centre? as Bool)
Gurax_DeclareFunctionAlias(GetPasswordFromUser_gurax, "GetPasswordFromUser")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("message", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("caption", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("default_value", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("centre", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementFunctionEx(GetPasswordFromUser_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString message(args_gurax.PickString());
	bool caption_validFlag = args_gurax.IsValid();
	wxString caption = caption_validFlag? wxString(args_gurax.PickString()) : wxGetPasswordFromUserPromptStr;
	bool default_value_validFlag = args_gurax.IsValid();
	wxString default_value = default_value_validFlag? wxString(args_gurax.PickString()) : "";
	wxWindow* parent = args_gurax.IsValid()? args_gurax.Pick<Value_wxWindow>().GetEntityPtr() : nullptr;
	bool x_validFlag = args_gurax.IsValid();
	int x = x_validFlag? args_gurax.PickNumber<int>() : wxDefaultCoord;
	bool y_validFlag = args_gurax.IsValid();
	int y = y_validFlag? args_gurax.PickNumber<int>() : wxDefaultCoord;
	bool centre = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	wxString rtn = wxGetPasswordFromUser(message, caption, default_value, parent, x, y, centre);
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.GetPowerType()
Gurax_DeclareFunctionAlias(GetPowerType_gurax, "GetPowerType")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementFunctionEx(GetPowerType_gurax, processor_gurax, argument_gurax)
{
	// Function body
	wxPowerType rtn = wxGetPowerType();
	return new Gurax::Value_Number(rtn);
}

// wx.GetSingleChoice(message as String, caption as String, aChoices[] as String, parent? as wx.Window, x? as Number, y? as Number, centre? as Bool, width? as Number, height? as Number, initialSelection? as Number)
Gurax_DeclareFunctionAlias(GetSingleChoice_gurax, "GetSingleChoice")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("message", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("caption", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("aChoices", VTYPE_String, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("centre", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("initialSelection", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementFunctionEx(GetSingleChoice_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString message(args_gurax.PickString());
	wxString caption(args_gurax.PickString());
	wxArrayString aChoices = Util::CreateArrayString(args_gurax.PickList());
	wxWindow* parent = args_gurax.IsValid()? args_gurax.Pick<Value_wxWindow>().GetEntityPtr() : nullptr;
	bool x_validFlag = args_gurax.IsValid();
	int x = x_validFlag? args_gurax.PickNumber<int>() : wxDefaultCoord;
	bool y_validFlag = args_gurax.IsValid();
	int y = y_validFlag? args_gurax.PickNumber<int>() : wxDefaultCoord;
	bool centre = args_gurax.IsValid()? args_gurax.PickBool() : true;
	bool width_validFlag = args_gurax.IsValid();
	int width = width_validFlag? args_gurax.PickNumber<int>() : wxCHOICE_WIDTH;
	bool height_validFlag = args_gurax.IsValid();
	int height = height_validFlag? args_gurax.PickNumber<int>() : wxCHOICE_HEIGHT;
	bool initialSelection_validFlag = args_gurax.IsValid();
	int initialSelection = initialSelection_validFlag? args_gurax.PickNumber<int>() : 0;
	// Function body
	wxString rtn = wxGetSingleChoice(message, caption, aChoices, parent, x, y, centre, width, height, initialSelection);
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.GetSingleChoiceIndex(message as String, caption as String, aChoices[] as String, parent? as wx.Window, x? as Number, y? as Number, centre? as Bool, width? as Number, height? as Number, initialSelection? as Number)
Gurax_DeclareFunctionAlias(GetSingleChoiceIndex_gurax, "GetSingleChoiceIndex")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("message", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("caption", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("aChoices", VTYPE_String, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("centre", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("initialSelection", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementFunctionEx(GetSingleChoiceIndex_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString message(args_gurax.PickString());
	wxString caption(args_gurax.PickString());
	wxArrayString aChoices = Util::CreateArrayString(args_gurax.PickList());
	wxWindow* parent = args_gurax.IsValid()? args_gurax.Pick<Value_wxWindow>().GetEntityPtr() : nullptr;
	bool x_validFlag = args_gurax.IsValid();
	int x = x_validFlag? args_gurax.PickNumber<int>() : wxDefaultCoord;
	bool y_validFlag = args_gurax.IsValid();
	int y = y_validFlag? args_gurax.PickNumber<int>() : wxDefaultCoord;
	bool centre = args_gurax.IsValid()? args_gurax.PickBool() : true;
	bool width_validFlag = args_gurax.IsValid();
	int width = width_validFlag? args_gurax.PickNumber<int>() : wxCHOICE_WIDTH;
	bool height_validFlag = args_gurax.IsValid();
	int height = height_validFlag? args_gurax.PickNumber<int>() : wxCHOICE_HEIGHT;
	bool initialSelection_validFlag = args_gurax.IsValid();
	int initialSelection = initialSelection_validFlag? args_gurax.PickNumber<int>() : 0;
	// Function body
	int rtn = wxGetSingleChoiceIndex(message, caption, aChoices, parent, x, y, centre, width, height, initialSelection);
	return new Gurax::Value_Number(rtn);
}

// wx.GetTextFromUser(message as String, caption? as String, default_value? as String, parent? as wx.Window, x? as Number, y? as Number, centre? as Bool)
Gurax_DeclareFunctionAlias(GetTextFromUser_gurax, "GetTextFromUser")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("message", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("caption", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("default_value", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("centre", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementFunctionEx(GetTextFromUser_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString message(args_gurax.PickString());
	bool caption_validFlag = args_gurax.IsValid();
	wxString caption = caption_validFlag? wxString(args_gurax.PickString()) : wxGetTextFromUserPromptStr;
	bool default_value_validFlag = args_gurax.IsValid();
	wxString default_value = default_value_validFlag? wxString(args_gurax.PickString()) : "";
	wxWindow* parent = args_gurax.IsValid()? args_gurax.Pick<Value_wxWindow>().GetEntityPtr() : nullptr;
	bool x_validFlag = args_gurax.IsValid();
	int x = x_validFlag? args_gurax.PickNumber<int>() : wxDefaultCoord;
	bool y_validFlag = args_gurax.IsValid();
	int y = y_validFlag? args_gurax.PickNumber<int>() : wxDefaultCoord;
	bool centre = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	wxString rtn = wxGetTextFromUser(message, caption, default_value, parent, x, y, centre);
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.GetTimeZone()
Gurax_DeclareFunctionAlias(GetTimeZone_gurax, "GetTimeZone")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementFunctionEx(GetTimeZone_gurax, processor_gurax, argument_gurax)
{
	// Function body
	int rtn = wxGetTimeZone();
	return new Gurax::Value_Number(rtn);
}

// wx.GetUTCTime()
Gurax_DeclareFunctionAlias(GetUTCTime_gurax, "GetUTCTime")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementFunctionEx(GetUTCTime_gurax, processor_gurax, argument_gurax)
{
	// Function body
	long rtn = wxGetUTCTime();
	return new Gurax::Value_Number(rtn);
}

// wx.GetUTCTimeMillis()
Gurax_DeclareFunctionAlias(GetUTCTimeMillis_gurax, "GetUTCTimeMillis")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementFunctionEx(GetUTCTimeMillis_gurax, processor_gurax, argument_gurax)
{
	// Function body
	wxLongLong rtn = wxGetUTCTimeMillis();
	return new Gurax::Value_Number(rtn.GetValue());
}

// wx.GetUTCTimeUSec()
Gurax_DeclareFunctionAlias(GetUTCTimeUSec_gurax, "GetUTCTimeUSec")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementFunctionEx(GetUTCTimeUSec_gurax, processor_gurax, argument_gurax)
{
	// Function body
	wxLongLong rtn = wxGetUTCTimeUSec();
	return new Gurax::Value_Number(rtn.GetValue());
}

// wx.ImplementApp(app as wx.AppConsole)
Gurax_DeclareFunctionAlias(ImplementApp_gurax, "ImplementApp")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("app", VTYPE_wxAppConsole, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(ImplementApp_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxAppConsole& value_app = args_gurax.Pick<Value_wxAppConsole>();
	wxAppConsole* app = value_app.GetEntityPtr();
	// Function body
	wxAppConsole::SetInstance(app);
	int argc = 0;
	char* argv[1] = { nullptr };
	::wxEntry(argc, argv);
	return Value::nil();
}

// wx.InfoMessageBox(parent as wx.Window)
Gurax_DeclareFunctionAlias(InfoMessageBox_gurax, "InfoMessageBox")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(InfoMessageBox_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	// Function body
	wxInfoMessageBox(parent);
	return Gurax::Value::nil();
}

// wx.InitAllImageHandlers()
Gurax_DeclareFunctionAlias(InitAllImageHandlers_gurax, "InitAllImageHandlers")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementFunctionEx(InitAllImageHandlers_gurax, processor_gurax, argument_gurax)
{
	// Function body
	wxInitAllImageHandlers();
	return Gurax::Value::nil();
}

// wx.IsBusy()
Gurax_DeclareFunctionAlias(IsBusy_gurax, "IsBusy")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementFunctionEx(IsBusy_gurax, processor_gurax, argument_gurax)
{
	// Function body
	bool rtn = wxIsBusy();
	return new Gurax::Value_Bool(rtn);
}

// wx.LoadFileSelector(what as String, extension as String, default_name? as String, parent? as wx.Window)
Gurax_DeclareFunctionAlias(LoadFileSelector_gurax, "LoadFileSelector")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("what", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("extension", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("default_name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementFunctionEx(LoadFileSelector_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString what(args_gurax.PickString());
	wxString extension(args_gurax.PickString());
	bool default_name_validFlag = args_gurax.IsValid();
	wxString default_name = default_name_validFlag? wxString(args_gurax.PickString()) : "";
	wxWindow* parent = args_gurax.IsValid()? args_gurax.Pick<Value_wxWindow>().GetEntityPtr() : nullptr;
	// Function body
	wxString rtn = wxLoadFileSelector(what, extension, default_name, parent);
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.MessageBox(message as String, caption? as String, style? as Number, parent? as wx.Window, x? as Number, y? as Number)
Gurax_DeclareFunctionAlias(MessageBox_gurax, "MessageBox")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("message", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("caption", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementFunctionEx(MessageBox_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString message(args_gurax.PickString());
	bool caption_validFlag = args_gurax.IsValid();
	wxString caption = caption_validFlag? wxString(args_gurax.PickString()) : wxMessageBoxCaptionStr;
	bool style_validFlag = args_gurax.IsValid();
	int style = style_validFlag? args_gurax.PickNumber<int>() : (wxOK | wxCENTRE);
	wxWindow* parent = args_gurax.IsValid()? args_gurax.Pick<Value_wxWindow>().GetEntityPtr() : nullptr;
	bool x_validFlag = args_gurax.IsValid();
	int x = x_validFlag? args_gurax.PickNumber<int>() : wxDefaultCoord;
	bool y_validFlag = args_gurax.IsValid();
	int y = y_validFlag? args_gurax.PickNumber<int>() : wxDefaultCoord;
	// Function body
	int rtn = wxMessageBox(message, caption, style, parent, x, y);
	return new Gurax::Value_Number(rtn);
}

// wx.MicroSleep(microseconds as Number)
Gurax_DeclareFunctionAlias(MicroSleep_gurax, "MicroSleep")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("microseconds", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(MicroSleep_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned long microseconds = args_gurax.PickNumber<unsigned long>();
	// Function body
	wxMicroSleep(microseconds);
	return Gurax::Value::nil();
}

// wx.MilliSleep(milliseconds as Number)
Gurax_DeclareFunctionAlias(MilliSleep_gurax, "MilliSleep")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("milliseconds", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(MilliSleep_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned long milliseconds = args_gurax.PickNumber<unsigned long>();
	// Function body
	wxMilliSleep(milliseconds);
	return Gurax::Value::nil();
}

// wx.Now()
Gurax_DeclareFunctionAlias(Now_gurax, "Now")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementFunctionEx(Now_gurax, processor_gurax, argument_gurax)
{
	// Function body
	wxString rtn = wxNow();
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.SaveFileSelector(what as String, extension as String, default_name? as String, parent? as wx.Window)
Gurax_DeclareFunctionAlias(SaveFileSelector_gurax, "SaveFileSelector")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("what", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("extension", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("default_name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementFunctionEx(SaveFileSelector_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString what(args_gurax.PickString());
	wxString extension(args_gurax.PickString());
	bool default_name_validFlag = args_gurax.IsValid();
	wxString default_name = default_name_validFlag? wxString(args_gurax.PickString()) : "";
	wxWindow* parent = args_gurax.IsValid()? args_gurax.Pick<Value_wxWindow>().GetEntityPtr() : nullptr;
	// Function body
	wxString rtn = wxSaveFileSelector(what, extension, default_name, parent);
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.Sleep(secs as Number)
Gurax_DeclareFunctionAlias(Sleep_gurax, "Sleep")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("secs", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(Sleep_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int secs = args_gurax.PickNumber<int>();
	// Function body
	wxSleep(secs);
	return Gurax::Value::nil();
}

// wx.T(str as String)
Gurax_DeclareFunctionAlias(T_gurax, "T")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("str", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementFunctionEx(T_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString str(args_gurax.PickString());
	// Function body
	return new Value_String(str.utf8_str().data());
}

//------------------------------------------------------------------------------
// Assignment
//------------------------------------------------------------------------------
void AssignFunctions(Frame& frame)
{
	frame.Assign(Gurax_CreateFunction(AboutBox_gurax));
	frame.Assign(Gurax_CreateFunction(BeginBusyCursor_gurax));
	frame.Assign(Gurax_CreateFunction(Bell_gurax));
	frame.Assign(Gurax_CreateFunction(DirSelector_gurax));
	frame.Assign(Gurax_CreateFunction(EndBusyCursor_gurax));
	frame.Assign(Gurax_CreateFunction(FileSelector_gurax));
	frame.Assign(Gurax_CreateFunction(GetBatteryState_gurax));
	frame.Assign(Gurax_CreateFunction(GetColourFromUser_gurax));
	frame.Assign(Gurax_CreateFunction(GetFontFromUser_gurax));
	frame.Assign(Gurax_CreateFunction(GetKeyCodeName_gurax));
	frame.Assign(Gurax_CreateFunction(GetKeyState_gurax));
	frame.Assign(Gurax_CreateFunction(GetLocalTime_gurax));
	frame.Assign(Gurax_CreateFunction(GetLocalTimeMillis_gurax));
	frame.Assign(Gurax_CreateFunction(GetMousePosition_gurax));
	frame.Assign(Gurax_CreateFunction(GetMouseState_gurax));
	frame.Assign(Gurax_CreateFunction(GetNumberFromUser_gurax));
	frame.Assign(Gurax_CreateFunction(GetPasswordFromUser_gurax));
	frame.Assign(Gurax_CreateFunction(GetPowerType_gurax));
	frame.Assign(Gurax_CreateFunction(GetSingleChoice_gurax));
	frame.Assign(Gurax_CreateFunction(GetSingleChoiceIndex_gurax));
	frame.Assign(Gurax_CreateFunction(GetTextFromUser_gurax));
	frame.Assign(Gurax_CreateFunction(GetTimeZone_gurax));
	frame.Assign(Gurax_CreateFunction(GetUTCTime_gurax));
	frame.Assign(Gurax_CreateFunction(GetUTCTimeMillis_gurax));
	frame.Assign(Gurax_CreateFunction(GetUTCTimeUSec_gurax));
	frame.Assign(Gurax_CreateFunction(ImplementApp_gurax));
	frame.Assign(Gurax_CreateFunction(InfoMessageBox_gurax));
	frame.Assign(Gurax_CreateFunction(InitAllImageHandlers_gurax));
	frame.Assign(Gurax_CreateFunction(IsBusy_gurax));
	frame.Assign(Gurax_CreateFunction(LoadFileSelector_gurax));
	frame.Assign(Gurax_CreateFunction(MessageBox_gurax));
	frame.Assign(Gurax_CreateFunction(MicroSleep_gurax));
	frame.Assign(Gurax_CreateFunction(MilliSleep_gurax));
	frame.Assign(Gurax_CreateFunction(Now_gurax));
	frame.Assign(Gurax_CreateFunction(SaveFileSelector_gurax));
	frame.Assign(Gurax_CreateFunction(Sleep_gurax));
	frame.Assign(Gurax_CreateFunction(T_gurax));
}

Gurax_EndModuleScope(wx)
