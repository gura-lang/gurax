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

// cairo.cairo_set_source_rgb(cr:cairo_t, red:Number, green:Number, blue:Number)
Gurax_DeclareFunctionAlias(cairo_set_source_rgb_gurax, "cairo_set_source_rgb")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_set_source_rgb_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	double red = args_gurax.PickNumber<double>();
	double green = args_gurax.PickNumber<double>();
	double blue = args_gurax.PickNumber<double>();
	// Function body
	cairo_set_source_rgb(cr, red, green, blue);
	return Gurax::Value::nil();
}

// cairo.cairo_set_source_rgba(cr:cairo_t, red:Number, green:Number, blue:Number, alpha:Number)
Gurax_DeclareFunctionAlias(cairo_set_source_rgba_gurax, "cairo_set_source_rgba")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("alpha", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_set_source_rgba_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	double red = args_gurax.PickNumber<double>();
	double green = args_gurax.PickNumber<double>();
	double blue = args_gurax.PickNumber<double>();
	double alpha = args_gurax.PickNumber<double>();
	// Function body
	cairo_set_source_rgba(cr, red, green, blue, alpha);
	return Gurax::Value::nil();
}

// cairo.cairo_set_source_surface(cr:cairo_t, surface:cairo_surface_t, x:Number, y:Number)
Gurax_DeclareFunctionAlias(cairo_set_source_surface_gurax, "cairo_set_source_surface")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_set_source_surface_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	double x = args_gurax.PickNumber<double>();
	double y = args_gurax.PickNumber<double>();
	// Function body
	cairo_set_source_surface(cr, surface, x, y);
	return Gurax::Value::nil();
}

// cairo.cairo_set_tolerance(cr:cairo_t, tolerance:Number)
Gurax_DeclareFunctionAlias(cairo_set_tolerance_gurax, "cairo_set_tolerance")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("tolerance", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_set_tolerance_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	double tolerance = args_gurax.PickNumber<double>();
	// Function body
	cairo_set_tolerance(cr, tolerance);
	return Gurax::Value::nil();
}

// cairo.cairo_set_antialias(cr:cairo_t, antialias:Number)
Gurax_DeclareFunctionAlias(cairo_set_antialias_gurax, "cairo_set_antialias")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("antialias", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_set_antialias_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	cairo_antialias_t antialias = args_gurax.PickNumber<cairo_antialias_t>();
	// Function body
	cairo_set_antialias(cr, antialias);
	return Gurax::Value::nil();
}

// cairo.cairo_set_fill_rule(cr:cairo_t, fill_rule:Number)
Gurax_DeclareFunctionAlias(cairo_set_fill_rule_gurax, "cairo_set_fill_rule")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("fill_rule", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_set_fill_rule_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	cairo_fill_rule_t fill_rule = args_gurax.PickNumber<cairo_fill_rule_t>();
	// Function body
	cairo_set_fill_rule(cr, fill_rule);
	return Gurax::Value::nil();
}

// cairo.cairo_set_line_width(cr:cairo_t, width:Number)
Gurax_DeclareFunctionAlias(cairo_set_line_width_gurax, "cairo_set_line_width")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_set_line_width_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	double width = args_gurax.PickNumber<double>();
	// Function body
	cairo_set_line_width(cr, width);
	return Gurax::Value::nil();
}

// cairo.cairo_set_line_cap(cr:cairo_t, line_cap:Number)
Gurax_DeclareFunctionAlias(cairo_set_line_cap_gurax, "cairo_set_line_cap")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("line_cap", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_set_line_cap_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	cairo_line_cap_t line_cap = args_gurax.PickNumber<cairo_line_cap_t>();
	// Function body
	cairo_set_line_cap(cr, line_cap);
	return Gurax::Value::nil();
}

// cairo.cairo_set_line_join(cr:cairo_t, line_join:Number)
Gurax_DeclareFunctionAlias(cairo_set_line_join_gurax, "cairo_set_line_join")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("line_join", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_set_line_join_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	cairo_line_join_t line_join = args_gurax.PickNumber<cairo_line_join_t>();
	// Function body
	cairo_set_line_join(cr, line_join);
	return Gurax::Value::nil();
}

// cairo.cairo_set_miter_limit(cr:cairo_t, limit:Number)
Gurax_DeclareFunctionAlias(cairo_set_miter_limit_gurax, "cairo_set_miter_limit")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("limit", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_set_miter_limit_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	double limit = args_gurax.PickNumber<double>();
	// Function body
	cairo_set_miter_limit(cr, limit);
	return Gurax::Value::nil();
}

// cairo.cairo_translate(cr:cairo_t, tx:Number, ty:Number)
Gurax_DeclareFunctionAlias(cairo_translate_gurax, "cairo_translate")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("tx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ty", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_translate_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	double tx = args_gurax.PickNumber<double>();
	double ty = args_gurax.PickNumber<double>();
	// Function body
	cairo_translate(cr, tx, ty);
	return Gurax::Value::nil();
}

// cairo.cairo_scale(cr:cairo_t, sx:Number, sy:Number)
Gurax_DeclareFunctionAlias(cairo_scale_gurax, "cairo_scale")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("sx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("sy", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_scale_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	double sx = args_gurax.PickNumber<double>();
	double sy = args_gurax.PickNumber<double>();
	// Function body
	cairo_scale(cr, sx, sy);
	return Gurax::Value::nil();
}

// cairo.cairo_rotate(cr:cairo_t, angle:Number)
Gurax_DeclareFunctionAlias(cairo_rotate_gurax, "cairo_rotate")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("angle", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_rotate_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	double angle = args_gurax.PickNumber<double>();
	// Function body
	cairo_rotate(cr, angle);
	return Gurax::Value::nil();
}

// cairo.cairo_identity_matrix(cr:cairo_t)
Gurax_DeclareFunctionAlias(cairo_identity_matrix_gurax, "cairo_identity_matrix")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_identity_matrix_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	cairo_identity_matrix(cr);
	return Gurax::Value::nil();
}

// cairo.cairo_new_path(cr:cairo_t)
Gurax_DeclareFunctionAlias(cairo_new_path_gurax, "cairo_new_path")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_new_path_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	cairo_new_path(cr);
	return Gurax::Value::nil();
}

// cairo.cairo_move_to(cr:cairo_t, x:Number, y:Number)
Gurax_DeclareFunctionAlias(cairo_move_to_gurax, "cairo_move_to")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_move_to_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	double x = args_gurax.PickNumber<double>();
	double y = args_gurax.PickNumber<double>();
	// Function body
	cairo_move_to(cr, x, y);
	return Gurax::Value::nil();
}

// cairo.cairo_new_sub_path(cr:cairo_t)
Gurax_DeclareFunctionAlias(cairo_new_sub_path_gurax, "cairo_new_sub_path")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_new_sub_path_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	cairo_new_sub_path(cr);
	return Gurax::Value::nil();
}

// cairo.cairo_line_to(cr:cairo_t, x:Number, y:Number)
Gurax_DeclareFunctionAlias(cairo_line_to_gurax, "cairo_line_to")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_line_to_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	double x = args_gurax.PickNumber<double>();
	double y = args_gurax.PickNumber<double>();
	// Function body
	cairo_line_to(cr, x, y);
	return Gurax::Value::nil();
}

// cairo.cairo_curve_to(cr:cairo_t, x1:Number, y1:Number, x2:Number, y2:Number, x3:Number, y3:Number)
Gurax_DeclareFunctionAlias(cairo_curve_to_gurax, "cairo_curve_to")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x3", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y3", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_curve_to_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	double x1 = args_gurax.PickNumber<double>();
	double y1 = args_gurax.PickNumber<double>();
	double x2 = args_gurax.PickNumber<double>();
	double y2 = args_gurax.PickNumber<double>();
	double x3 = args_gurax.PickNumber<double>();
	double y3 = args_gurax.PickNumber<double>();
	// Function body
	cairo_curve_to(cr, x1, y1, x2, y2, x3, y3);
	return Gurax::Value::nil();
}

// cairo.cairo_arc(cr:cairo_t, xc:Number, yc:Number, radius:Number, angle1:Number, angle2:Number)
Gurax_DeclareFunctionAlias(cairo_arc_gurax, "cairo_arc")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xc", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("yc", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("radius", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("angle1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("angle2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_arc_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	double xc = args_gurax.PickNumber<double>();
	double yc = args_gurax.PickNumber<double>();
	double radius = args_gurax.PickNumber<double>();
	double angle1 = args_gurax.PickNumber<double>();
	double angle2 = args_gurax.PickNumber<double>();
	// Function body
	cairo_arc(cr, xc, yc, radius, angle1, angle2);
	return Gurax::Value::nil();
}

// cairo.cairo_arc_negative(cr:cairo_t, xc:Number, yc:Number, radius:Number, angle1:Number, angle2:Number)
Gurax_DeclareFunctionAlias(cairo_arc_negative_gurax, "cairo_arc_negative")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xc", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("yc", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("radius", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("angle1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("angle2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_arc_negative_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	double xc = args_gurax.PickNumber<double>();
	double yc = args_gurax.PickNumber<double>();
	double radius = args_gurax.PickNumber<double>();
	double angle1 = args_gurax.PickNumber<double>();
	double angle2 = args_gurax.PickNumber<double>();
	// Function body
	cairo_arc_negative(cr, xc, yc, radius, angle1, angle2);
	return Gurax::Value::nil();
}

// cairo.cairo_rel_move_to(cr:cairo_t, dx:Number, dy:Number)
Gurax_DeclareFunctionAlias(cairo_rel_move_to_gurax, "cairo_rel_move_to")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dy", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_rel_move_to_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	double dx = args_gurax.PickNumber<double>();
	double dy = args_gurax.PickNumber<double>();
	// Function body
	cairo_rel_move_to(cr, dx, dy);
	return Gurax::Value::nil();
}

// cairo.cairo_rel_line_to(cr:cairo_t, dx:Number, dy:Number)
Gurax_DeclareFunctionAlias(cairo_rel_line_to_gurax, "cairo_rel_line_to")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dy", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_rel_line_to_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	double dx = args_gurax.PickNumber<double>();
	double dy = args_gurax.PickNumber<double>();
	// Function body
	cairo_rel_line_to(cr, dx, dy);
	return Gurax::Value::nil();
}

// cairo.cairo_rel_curve_to(cr:cairo_t, dx1:Number, dy1:Number, dx2:Number, dy2:Number, dx3:Number, dy3:Number)
Gurax_DeclareFunctionAlias(cairo_rel_curve_to_gurax, "cairo_rel_curve_to")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dx1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dy1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dx2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dy2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dx3", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dy3", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_rel_curve_to_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	double dx1 = args_gurax.PickNumber<double>();
	double dy1 = args_gurax.PickNumber<double>();
	double dx2 = args_gurax.PickNumber<double>();
	double dy2 = args_gurax.PickNumber<double>();
	double dx3 = args_gurax.PickNumber<double>();
	double dy3 = args_gurax.PickNumber<double>();
	// Function body
	cairo_rel_curve_to(cr, dx1, dy1, dx2, dy2, dx3, dy3);
	return Gurax::Value::nil();
}

// cairo.cairo_rectangle(cr:cairo_t, x:Number, y:Number, width:Number, height:Number)
Gurax_DeclareFunctionAlias(cairo_rectangle_gurax, "cairo_rectangle")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_rectangle_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	double x = args_gurax.PickNumber<double>();
	double y = args_gurax.PickNumber<double>();
	double width = args_gurax.PickNumber<double>();
	double height = args_gurax.PickNumber<double>();
	// Function body
	cairo_rectangle(cr, x, y, width, height);
	return Gurax::Value::nil();
}

// cairo.cairo_close_path(cr:cairo_t)
Gurax_DeclareFunctionAlias(cairo_close_path_gurax, "cairo_close_path")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_close_path_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	cairo_close_path(cr);
	return Gurax::Value::nil();
}

// cairo.cairo_paint(cr:cairo_t)
Gurax_DeclareFunctionAlias(cairo_paint_gurax, "cairo_paint")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_paint_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	cairo_paint(cr);
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
	frame.Assign(Gurax_CreateFunction(cairo_set_source_rgb_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_set_source_rgba_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_set_source_surface_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_set_tolerance_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_set_antialias_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_set_fill_rule_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_set_line_width_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_set_line_cap_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_set_line_join_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_set_miter_limit_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_translate_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_scale_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_rotate_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_identity_matrix_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_new_path_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_move_to_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_new_sub_path_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_line_to_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_curve_to_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_arc_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_arc_negative_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_rel_move_to_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_rel_line_to_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_rel_curve_to_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_rectangle_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_close_path_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_paint_gurax));
}

Gurax_EndModuleScope(cairo)
