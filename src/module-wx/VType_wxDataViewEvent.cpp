//==============================================================================
// VType_wxDataViewEvent.cpp
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(wx.DataViewEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.DataViewEvent, `en)}

${help.ComposeMethodHelp(wx.DataViewEvent, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.DataViewEvent#GetColumn()
Gurax_DeclareMethodAlias(wxDataViewEvent, GetColumn_gurax, "GetColumn")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewEvent, GetColumn_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetColumn();
	return new Gurax::Value_Number(rtn);
}

// wx.DataViewEvent#GetDataViewColumn() {block?}
Gurax_DeclareMethodAlias(wxDataViewEvent, GetDataViewColumn_gurax, "GetDataViewColumn")
{
	Declare(VTYPE_wxDataViewColumn, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewEvent, GetDataViewColumn_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxDataViewColumn(
		pEntity_gurax->GetDataViewColumn()));
}

// wx.DataViewEvent#GetModel() {block?}
Gurax_DeclareMethodAlias(wxDataViewEvent, GetModel_gurax, "GetModel")
{
	Declare(VTYPE_wxDataViewModel, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewEvent, GetModel_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxDataViewModel(
		pEntity_gurax->GetModel()));
}

// wx.DataViewEvent#GetPosition() {block?}
Gurax_DeclareMethodAlias(wxDataViewEvent, GetPosition_gurax, "GetPosition")
{
	Declare(VTYPE_wxPoint, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewEvent, GetPosition_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPoint(
		pEntity_gurax->GetPosition()));
}

// wx.DataViewEvent#GetValue() {block?}
Gurax_DeclareMethodAlias(wxDataViewEvent, GetValue_gurax, "GetValue")
{
	Declare(VTYPE_wxVariant, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewEvent, GetValue_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxVariant(
		pEntity_gurax->GetValue()));
}

// wx.DataViewEvent#IsEditCancelled()
Gurax_DeclareMethodAlias(wxDataViewEvent, IsEditCancelled_gurax, "IsEditCancelled")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewEvent, IsEditCancelled_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsEditCancelled();
	return new Gurax::Value_Bool(rtn);
}

// wx.DataViewEvent#SetColumn(col as Number)
Gurax_DeclareMethodAlias(wxDataViewEvent, SetColumn_gurax, "SetColumn")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("col", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewEvent, SetColumn_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int col = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetColumn(col);
	return Gurax::Value::nil();
}

// wx.DataViewEvent#SetDataViewColumn(col as wx.DataViewColumn)
Gurax_DeclareMethodAlias(wxDataViewEvent, SetDataViewColumn_gurax, "SetDataViewColumn")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("col", VTYPE_wxDataViewColumn, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewEvent, SetDataViewColumn_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDataViewColumn& value_col = args_gurax.Pick<Value_wxDataViewColumn>();
	wxDataViewColumn* col = value_col.GetEntityPtr();
	// Function body
	pEntity_gurax->SetDataViewColumn(col);
	return Gurax::Value::nil();
}

// wx.DataViewEvent#SetModel(model as wx.DataViewModel)
Gurax_DeclareMethodAlias(wxDataViewEvent, SetModel_gurax, "SetModel")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("model", VTYPE_wxDataViewModel, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewEvent, SetModel_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDataViewModel& value_model = args_gurax.Pick<Value_wxDataViewModel>();
	wxDataViewModel* model = value_model.GetEntityPtr();
	// Function body
	pEntity_gurax->SetModel(model);
	return Gurax::Value::nil();
}

// wx.DataViewEvent#SetValue(value as wx.Variant)
Gurax_DeclareMethodAlias(wxDataViewEvent, SetValue_gurax, "SetValue")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("value", VTYPE_wxVariant, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewEvent, SetValue_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxVariant& value_value = args_gurax.Pick<Value_wxVariant>();
	const wxVariant& value = value_value.GetEntity();
	// Function body
	pEntity_gurax->SetValue(value);
	return Gurax::Value::nil();
}

// wx.DataViewEvent#SetDataObject(obj as wx.DataObject)
Gurax_DeclareMethodAlias(wxDataViewEvent, SetDataObject_gurax, "SetDataObject")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("obj", VTYPE_wxDataObject, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewEvent, SetDataObject_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDataObject& value_obj = args_gurax.Pick<Value_wxDataObject>();
	wxDataObject* obj = value_obj.GetEntityPtr();
	// Function body
	pEntity_gurax->SetDataObject(obj);
	return Gurax::Value::nil();
}

// wx.DataViewEvent#GetDataFormat() {block?}
Gurax_DeclareMethodAlias(wxDataViewEvent, GetDataFormat_gurax, "GetDataFormat")
{
	Declare(VTYPE_wxDataFormat, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewEvent, GetDataFormat_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxDataFormat(
		pEntity_gurax->GetDataFormat()));
}

// wx.DataViewEvent#GetDataSize()
Gurax_DeclareMethodAlias(wxDataViewEvent, GetDataSize_gurax, "GetDataSize")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewEvent, GetDataSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	size_t rtn = pEntity_gurax->GetDataSize();
	return new Gurax::Value_Number(rtn);
}

// wx.DataViewEvent#SetDragFlags(flags as Number)
Gurax_DeclareMethodAlias(wxDataViewEvent, SetDragFlags_gurax, "SetDragFlags")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewEvent, SetDragFlags_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int flags = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetDragFlags(flags);
	return Gurax::Value::nil();
}

// wx.DataViewEvent#GetDropEffect()
Gurax_DeclareMethodAlias(wxDataViewEvent, GetDropEffect_gurax, "GetDropEffect")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewEvent, GetDropEffect_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxDragResult rtn = pEntity_gurax->GetDropEffect();
	return new Gurax::Value_Number(rtn);
}

// wx.DataViewEvent#GetCacheFrom()
Gurax_DeclareMethodAlias(wxDataViewEvent, GetCacheFrom_gurax, "GetCacheFrom")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewEvent, GetCacheFrom_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetCacheFrom();
	return new Gurax::Value_Number(rtn);
}

// wx.DataViewEvent#GetCacheTo()
Gurax_DeclareMethodAlias(wxDataViewEvent, GetCacheTo_gurax, "GetCacheTo")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewEvent, GetCacheTo_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetCacheTo();
	return new Gurax::Value_Number(rtn);
}

// wx.DataViewEvent#GetItem() {block?}
Gurax_DeclareMethodAlias(wxDataViewEvent, GetItem_gurax, "GetItem")
{
	Declare(VTYPE_wxDataViewItem, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewEvent, GetItem_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxDataViewItem(
		pEntity_gurax->GetItem()));
}

// wx.DataViewEvent#SetItem(item as wx.DataViewItem)
Gurax_DeclareMethodAlias(wxDataViewEvent, SetItem_gurax, "SetItem")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("item", VTYPE_wxDataViewItem, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewEvent, SetItem_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDataViewItem& value_item = args_gurax.Pick<Value_wxDataViewItem>();
	const wxDataViewItem& item = value_item.GetEntity();
	// Function body
	pEntity_gurax->SetItem(item);
	return Gurax::Value::nil();
}

// wx.DataViewEvent#SetPosition(x as Number, y as Number)
Gurax_DeclareMethodAlias(wxDataViewEvent, SetPosition_gurax, "SetPosition")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewEvent, SetPosition_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int x = args_gurax.PickNumber<int>();
	int y = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetPosition(x, y);
	return Gurax::Value::nil();
}

// wx.DataViewEvent#SetCache(from as Number, to as Number)
Gurax_DeclareMethodAlias(wxDataViewEvent, SetCache_gurax, "SetCache")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("from", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("to", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewEvent, SetCache_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int from = args_gurax.PickNumber<int>();
	int to = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetCache(from, to);
	return Gurax::Value::nil();
}

// wx.DataViewEvent#GetDataObject() {block?}
Gurax_DeclareMethodAlias(wxDataViewEvent, GetDataObject_gurax, "GetDataObject")
{
	Declare(VTYPE_wxDataObject, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewEvent, GetDataObject_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxDataObject(
		pEntity_gurax->GetDataObject()));
}

// wx.DataViewEvent#SetDataFormat(format as wx.DataFormat)
Gurax_DeclareMethodAlias(wxDataViewEvent, SetDataFormat_gurax, "SetDataFormat")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("format", VTYPE_wxDataFormat, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewEvent, SetDataFormat_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDataFormat& value_format = args_gurax.Pick<Value_wxDataFormat>();
	const wxDataFormat& format = value_format.GetEntity();
	// Function body
	pEntity_gurax->SetDataFormat(format);
	return Gurax::Value::nil();
}

// wx.DataViewEvent#SetDataSize(size as Number)
Gurax_DeclareMethodAlias(wxDataViewEvent, SetDataSize_gurax, "SetDataSize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewEvent, SetDataSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t size = args_gurax.PickNumber<size_t>();
	// Function body
	pEntity_gurax->SetDataSize(size);
	return Gurax::Value::nil();
}

// wx.DataViewEvent#SetDataBuffer(buf as Pointer)
Gurax_DeclareMethodAlias(wxDataViewEvent, SetDataBuffer_gurax, "SetDataBuffer")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("buf", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewEvent, SetDataBuffer_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	void* buf = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetWritablePointerC<void>();
	if (!buf) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	pEntity_gurax->SetDataBuffer(buf);
	return Gurax::Value::nil();
}

// wx.DataViewEvent#GetDragFlags()
Gurax_DeclareMethodAlias(wxDataViewEvent, GetDragFlags_gurax, "GetDragFlags")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewEvent, GetDragFlags_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetDragFlags();
	return new Gurax::Value_Number(rtn);
}

// wx.DataViewEvent#SetDropEffect(effect as Number)
Gurax_DeclareMethodAlias(wxDataViewEvent, SetDropEffect_gurax, "SetDropEffect")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("effect", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewEvent, SetDropEffect_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxDragResult effect = args_gurax.PickNumber<wxDragResult>();
	// Function body
	pEntity_gurax->SetDropEffect(effect);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxDataViewEvent
//------------------------------------------------------------------------------
VType_wxDataViewEvent VTYPE_wxDataViewEvent("DataViewEvent");

void VType_wxDataViewEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxNotifyEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxDataViewEvent, GetColumn_gurax));
	Assign(Gurax_CreateMethod(wxDataViewEvent, GetDataViewColumn_gurax));
	Assign(Gurax_CreateMethod(wxDataViewEvent, GetModel_gurax));
	Assign(Gurax_CreateMethod(wxDataViewEvent, GetPosition_gurax));
	Assign(Gurax_CreateMethod(wxDataViewEvent, GetValue_gurax));
	Assign(Gurax_CreateMethod(wxDataViewEvent, IsEditCancelled_gurax));
	Assign(Gurax_CreateMethod(wxDataViewEvent, SetColumn_gurax));
	Assign(Gurax_CreateMethod(wxDataViewEvent, SetDataViewColumn_gurax));
	Assign(Gurax_CreateMethod(wxDataViewEvent, SetModel_gurax));
	Assign(Gurax_CreateMethod(wxDataViewEvent, SetValue_gurax));
	Assign(Gurax_CreateMethod(wxDataViewEvent, SetDataObject_gurax));
	Assign(Gurax_CreateMethod(wxDataViewEvent, GetDataFormat_gurax));
	Assign(Gurax_CreateMethod(wxDataViewEvent, GetDataSize_gurax));
	Assign(Gurax_CreateMethod(wxDataViewEvent, SetDragFlags_gurax));
	Assign(Gurax_CreateMethod(wxDataViewEvent, GetDropEffect_gurax));
	Assign(Gurax_CreateMethod(wxDataViewEvent, GetCacheFrom_gurax));
	Assign(Gurax_CreateMethod(wxDataViewEvent, GetCacheTo_gurax));
	Assign(Gurax_CreateMethod(wxDataViewEvent, GetItem_gurax));
	Assign(Gurax_CreateMethod(wxDataViewEvent, SetItem_gurax));
	Assign(Gurax_CreateMethod(wxDataViewEvent, SetPosition_gurax));
	Assign(Gurax_CreateMethod(wxDataViewEvent, SetCache_gurax));
	Assign(Gurax_CreateMethod(wxDataViewEvent, GetDataObject_gurax));
	Assign(Gurax_CreateMethod(wxDataViewEvent, SetDataFormat_gurax));
	Assign(Gurax_CreateMethod(wxDataViewEvent, SetDataSize_gurax));
	Assign(Gurax_CreateMethod(wxDataViewEvent, SetDataBuffer_gurax));
	Assign(Gurax_CreateMethod(wxDataViewEvent, GetDragFlags_gurax));
	Assign(Gurax_CreateMethod(wxDataViewEvent, SetDropEffect_gurax));
}

//------------------------------------------------------------------------------
// Value_wxDataViewEvent
//------------------------------------------------------------------------------
VType& Value_wxDataViewEvent::vtype = VTYPE_wxDataViewEvent;
EventValueFactoryDeriv<Value_wxDataViewEvent> Value_wxDataViewEvent::eventValueFactory;

String Value_wxDataViewEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.DataViewEvent");
}

Gurax_EndModuleScope(wx)
