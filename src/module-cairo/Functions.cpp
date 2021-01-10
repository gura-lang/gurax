//==============================================================================
// Functions.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(cairo)

// cairo.cairo_version()
Gurax_DeclareFunctionAlias(cairo_version_gurax, "cairo_version")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_version_gurax, processor_gurax, argument_gurax)
{
	// Function body
	int rtn = cairo_version();
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_version_string()
Gurax_DeclareFunctionAlias(cairo_version_string_gurax, "cairo_version_string")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_version_string_gurax, processor_gurax, argument_gurax)
{
	// Function body
	const char* rtn = cairo_version_string();
	return new Gurax::Value_String(rtn);
}

// cairo.cairo_create(target:cairo_surface_t)
Gurax_DeclareFunctionAlias(cairo_create_gurax, "cairo_create")
{
	Declare(VTYPE_cairo_t, Flag::None);
	DeclareArg("target", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_create_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_target = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* target = value_target.GetEntityPtr();
	// Function body
	cairo_t* rtn = cairo_create(target);
	if (!rtn) return Value::nil();
	return new Value_cairo_t(rtn);
}

// cairo.cairo_reference(cr:cairo_t)
Gurax_DeclareFunctionAlias(cairo_reference_gurax, "cairo_reference")
{
	Declare(VTYPE_cairo_t, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_reference_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	cairo_t* rtn = cairo_reference(cr);
	if (!rtn) return Value::nil();
	return new Value_cairo_t(rtn);
}

// cairo.cairo_destroy(cr:cairo_t)
Gurax_DeclareFunctionAlias(cairo_destroy_gurax, "cairo_destroy")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_destroy_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	cairo_destroy(cr);
	return Gurax::Value::nil();
}

// cairo.cairo_get_reference_count(cr:cairo_t)
Gurax_DeclareFunctionAlias(cairo_get_reference_count_gurax, "cairo_get_reference_count")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_get_reference_count_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	unsigned int rtn = cairo_get_reference_count(cr);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_save(cr:cairo_t)
Gurax_DeclareFunctionAlias(cairo_save_gurax, "cairo_save")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_save_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	cairo_save(cr);
	return Gurax::Value::nil();
}

// cairo.cairo_restore(cr:cairo_t)
Gurax_DeclareFunctionAlias(cairo_restore_gurax, "cairo_restore")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_restore_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	cairo_restore(cr);
	return Gurax::Value::nil();
}

// cairo.cairo_push_group(cr:cairo_t)
Gurax_DeclareFunctionAlias(cairo_push_group_gurax, "cairo_push_group")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_push_group_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	cairo_push_group(cr);
	return Gurax::Value::nil();
}

// cairo.cairo_push_group_with_content(cr:cairo_t, content:Number)
Gurax_DeclareFunctionAlias(cairo_push_group_with_content_gurax, "cairo_push_group_with_content")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("content", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_push_group_with_content_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	cairo_content_t content = args_gurax.PickNumber<cairo_content_t>();
	// Function body
	cairo_push_group_with_content(cr, content);
	return Gurax::Value::nil();
}

// cairo.cairo_pop_group(cr:cairo_t)
Gurax_DeclareFunctionAlias(cairo_pop_group_gurax, "cairo_pop_group")
{
	Declare(VTYPE_cairo_pattern_t, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_pop_group_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	cairo_pattern_t* rtn = cairo_pop_group(cr);
	if (!rtn) return Value::nil();
	return new Value_cairo_pattern_t(rtn);
}

// cairo.cairo_pop_group_to_source(cr:cairo_t)
Gurax_DeclareFunctionAlias(cairo_pop_group_to_source_gurax, "cairo_pop_group_to_source")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_pop_group_to_source_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	cairo_pop_group_to_source(cr);
	return Gurax::Value::nil();
}

// cairo.cairo_set_operator(cr:cairo_t, op:Number)
Gurax_DeclareFunctionAlias(cairo_set_operator_gurax, "cairo_set_operator")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("op", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_set_operator_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	cairo_operator_t op = args_gurax.PickNumber<cairo_operator_t>();
	// Function body
	cairo_set_operator(cr, op);
	return Gurax::Value::nil();
}

// cairo.cairo_set_source(cr:cairo_t, source:cairo_pattern_t)
Gurax_DeclareFunctionAlias(cairo_set_source_gurax, "cairo_set_source")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("source", VTYPE_cairo_pattern_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_set_source_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	auto& value_source = args_gurax.Pick<Value_cairo_pattern_t>();
	cairo_pattern_t* source = value_source.GetEntityPtr();
	// Function body
	cairo_set_source(cr, source);
	return Gurax::Value::nil();
}

void AssignFunctions(Frame& frame)
{
	frame.Assign(Gurax_CreateFunction(cairo_version_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_version_string_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_create_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_reference_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_destroy_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_get_reference_count_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_save_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_restore_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_push_group_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_push_group_with_content_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_pop_group_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_pop_group_to_source_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_set_operator_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_set_source_gurax));
}

Gurax_EndModuleScope(cairo)
