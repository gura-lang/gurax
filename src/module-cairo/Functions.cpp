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

// cairo.cairo_transform(cr:cairo_t, matrix:cairo_matrix_t)
Gurax_DeclareFunctionAlias(cairo_transform_gurax, "cairo_transform")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("matrix", VTYPE_cairo_matrix_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_transform_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	auto& value_matrix = args_gurax.Pick<Value_cairo_matrix_t>();
	const cairo_matrix_t* matrix = value_matrix.GetEntityPtr();
	// Function body
	cairo_transform(cr, matrix);
	return Gurax::Value::nil();
}

// cairo.cairo_set_matrix(cr:cairo_t, matrix:cairo_matrix_t)
Gurax_DeclareFunctionAlias(cairo_set_matrix_gurax, "cairo_set_matrix")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("matrix", VTYPE_cairo_matrix_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_set_matrix_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	auto& value_matrix = args_gurax.Pick<Value_cairo_matrix_t>();
	const cairo_matrix_t* matrix = value_matrix.GetEntityPtr();
	// Function body
	cairo_set_matrix(cr, matrix);
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

// cairo.cairo_paint_with_alpha(cr:cairo_t, alpha:Number)
Gurax_DeclareFunctionAlias(cairo_paint_with_alpha_gurax, "cairo_paint_with_alpha")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("alpha", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_paint_with_alpha_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	double alpha = args_gurax.PickNumber<double>();
	// Function body
	cairo_paint_with_alpha(cr, alpha);
	return Gurax::Value::nil();
}

// cairo.cairo_mask(cr:cairo_t, pattern:cairo_pattern_t)
Gurax_DeclareFunctionAlias(cairo_mask_gurax, "cairo_mask")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pattern", VTYPE_cairo_pattern_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_mask_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	auto& value_pattern = args_gurax.Pick<Value_cairo_pattern_t>();
	cairo_pattern_t* pattern = value_pattern.GetEntityPtr();
	// Function body
	cairo_mask(cr, pattern);
	return Gurax::Value::nil();
}

// cairo.cairo_mask_surface(cr:cairo_t, surface:cairo_surface_t, surface_x:Number, surface_y:Number)
Gurax_DeclareFunctionAlias(cairo_mask_surface_gurax, "cairo_mask_surface")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("surface_x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("surface_y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_mask_surface_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	double surface_x = args_gurax.PickNumber<double>();
	double surface_y = args_gurax.PickNumber<double>();
	// Function body
	cairo_mask_surface(cr, surface, surface_x, surface_y);
	return Gurax::Value::nil();
}

// cairo.cairo_stroke(cr:cairo_t)
Gurax_DeclareFunctionAlias(cairo_stroke_gurax, "cairo_stroke")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_stroke_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	cairo_stroke(cr);
	return Gurax::Value::nil();
}

// cairo.cairo_stroke_preserve(cr:cairo_t)
Gurax_DeclareFunctionAlias(cairo_stroke_preserve_gurax, "cairo_stroke_preserve")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_stroke_preserve_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	cairo_stroke_preserve(cr);
	return Gurax::Value::nil();
}

// cairo.cairo_fill(cr:cairo_t)
Gurax_DeclareFunctionAlias(cairo_fill_gurax, "cairo_fill")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_fill_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	cairo_fill(cr);
	return Gurax::Value::nil();
}

// cairo.cairo_fill_preserve(cr:cairo_t)
Gurax_DeclareFunctionAlias(cairo_fill_preserve_gurax, "cairo_fill_preserve")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_fill_preserve_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	cairo_fill_preserve(cr);
	return Gurax::Value::nil();
}

// cairo.cairo_copy_page(cr:cairo_t)
Gurax_DeclareFunctionAlias(cairo_copy_page_gurax, "cairo_copy_page")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_copy_page_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	cairo_copy_page(cr);
	return Gurax::Value::nil();
}

// cairo.cairo_show_page(cr:cairo_t)
Gurax_DeclareFunctionAlias(cairo_show_page_gurax, "cairo_show_page")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_show_page_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	cairo_show_page(cr);
	return Gurax::Value::nil();
}

// cairo.cairo_in_stroke(cr:cairo_t, x:Number, y:Number)
Gurax_DeclareFunctionAlias(cairo_in_stroke_gurax, "cairo_in_stroke")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_in_stroke_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	double x = args_gurax.PickNumber<double>();
	double y = args_gurax.PickNumber<double>();
	// Function body
	cairo_bool_t rtn = cairo_in_stroke(cr, x, y);
	return new Gurax::Value_Bool(!!rtn);
}

// cairo.cairo_in_fill(cr:cairo_t, x:Number, y:Number)
Gurax_DeclareFunctionAlias(cairo_in_fill_gurax, "cairo_in_fill")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_in_fill_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	double x = args_gurax.PickNumber<double>();
	double y = args_gurax.PickNumber<double>();
	// Function body
	cairo_bool_t rtn = cairo_in_fill(cr, x, y);
	return new Gurax::Value_Bool(!!rtn);
}

// cairo.cairo_in_clip(cr:cairo_t, x:Number, y:Number)
Gurax_DeclareFunctionAlias(cairo_in_clip_gurax, "cairo_in_clip")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_in_clip_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	double x = args_gurax.PickNumber<double>();
	double y = args_gurax.PickNumber<double>();
	// Function body
	cairo_bool_t rtn = cairo_in_clip(cr, x, y);
	return new Gurax::Value_Bool(!!rtn);
}

// cairo.cairo_reset_clip(cr:cairo_t)
Gurax_DeclareFunctionAlias(cairo_reset_clip_gurax, "cairo_reset_clip")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_reset_clip_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	cairo_reset_clip(cr);
	return Gurax::Value::nil();
}

// cairo.cairo_clip(cr:cairo_t)
Gurax_DeclareFunctionAlias(cairo_clip_gurax, "cairo_clip")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_clip_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	cairo_clip(cr);
	return Gurax::Value::nil();
}

// cairo.cairo_clip_preserve(cr:cairo_t)
Gurax_DeclareFunctionAlias(cairo_clip_preserve_gurax, "cairo_clip_preserve")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_clip_preserve_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	cairo_clip_preserve(cr);
	return Gurax::Value::nil();
}

// cairo.cairo_tag_begin(cr:cairo_t, tag_name:String, attributes:String)
Gurax_DeclareFunctionAlias(cairo_tag_begin_gurax, "cairo_tag_begin")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("tag_name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("attributes", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_tag_begin_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	const char* tag_name = args_gurax.PickString();
	const char* attributes = args_gurax.PickString();
	// Function body
	cairo_tag_begin(cr, tag_name, attributes);
	return Gurax::Value::nil();
}

// cairo.cairo_tag_end(cr:cairo_t, tag_name:String)
Gurax_DeclareFunctionAlias(cairo_tag_end_gurax, "cairo_tag_end")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("tag_name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_tag_end_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	const char* tag_name = args_gurax.PickString();
	// Function body
	cairo_tag_end(cr, tag_name);
	return Gurax::Value::nil();
}

// cairo.cairo_glyph_allocate(num_glyphs:Number)
Gurax_DeclareFunctionAlias(cairo_glyph_allocate_gurax, "cairo_glyph_allocate")
{
	Declare(VTYPE_cairo_glyph_t, Flag::None);
	DeclareArg("num_glyphs", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_glyph_allocate_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int num_glyphs = args_gurax.PickNumber<int>();
	// Function body
	cairo_glyph_t* rtn = cairo_glyph_allocate(num_glyphs);
	if (!rtn) return Value::nil();
	return new Value_cairo_glyph_t(rtn);
}

// cairo.cairo_glyph_free(glyphs:cairo_glyph_t)
Gurax_DeclareFunctionAlias(cairo_glyph_free_gurax, "cairo_glyph_free")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("glyphs", VTYPE_cairo_glyph_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_glyph_free_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_glyphs = args_gurax.Pick<Value_cairo_glyph_t>();
	cairo_glyph_t* glyphs = value_glyphs.GetEntityPtr();
	// Function body
	cairo_glyph_free(glyphs);
	return Gurax::Value::nil();
}

// cairo.cairo_text_cluster_allocate(num_clusters:Number)
Gurax_DeclareFunctionAlias(cairo_text_cluster_allocate_gurax, "cairo_text_cluster_allocate")
{
	Declare(VTYPE_cairo_text_cluster_t, Flag::None);
	DeclareArg("num_clusters", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_text_cluster_allocate_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int num_clusters = args_gurax.PickNumber<int>();
	// Function body
	cairo_text_cluster_t* rtn = cairo_text_cluster_allocate(num_clusters);
	if (!rtn) return Value::nil();
	return new Value_cairo_text_cluster_t(rtn);
}

// cairo.cairo_text_cluster_free(clusters:cairo_text_cluster_t)
Gurax_DeclareFunctionAlias(cairo_text_cluster_free_gurax, "cairo_text_cluster_free")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("clusters", VTYPE_cairo_text_cluster_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_text_cluster_free_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_clusters = args_gurax.Pick<Value_cairo_text_cluster_t>();
	cairo_text_cluster_t* clusters = value_clusters.GetEntityPtr();
	// Function body
	cairo_text_cluster_free(clusters);
	return Gurax::Value::nil();
}

// cairo.cairo_font_options_create()
Gurax_DeclareFunctionAlias(cairo_font_options_create_gurax, "cairo_font_options_create")
{
	Declare(VTYPE_cairo_font_options_t, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_font_options_create_gurax, processor_gurax, argument_gurax)
{
	// Function body
	cairo_font_options_t* rtn = cairo_font_options_create();
	if (!rtn) return Value::nil();
	return new Value_cairo_font_options_t(rtn);
}

// cairo.cairo_font_options_copy(original:cairo_font_options_t)
Gurax_DeclareFunctionAlias(cairo_font_options_copy_gurax, "cairo_font_options_copy")
{
	Declare(VTYPE_cairo_font_options_t, Flag::None);
	DeclareArg("original", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_font_options_copy_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_original = args_gurax.Pick<Value_cairo_font_options_t>();
	const cairo_font_options_t* original = value_original.GetEntityPtr();
	// Function body
	cairo_font_options_t* rtn = cairo_font_options_copy(original);
	if (!rtn) return Value::nil();
	return new Value_cairo_font_options_t(rtn);
}

// cairo.cairo_font_options_destroy(options:cairo_font_options_t)
Gurax_DeclareFunctionAlias(cairo_font_options_destroy_gurax, "cairo_font_options_destroy")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_font_options_destroy_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_options = args_gurax.Pick<Value_cairo_font_options_t>();
	cairo_font_options_t* options = value_options.GetEntityPtr();
	// Function body
	cairo_font_options_destroy(options);
	return Gurax::Value::nil();
}

// cairo.cairo_font_options_status(options:cairo_font_options_t)
Gurax_DeclareFunctionAlias(cairo_font_options_status_gurax, "cairo_font_options_status")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_font_options_status_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_options = args_gurax.Pick<Value_cairo_font_options_t>();
	cairo_font_options_t* options = value_options.GetEntityPtr();
	// Function body
	cairo_status_t rtn = cairo_font_options_status(options);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_font_options_merge(options:cairo_font_options_t, other:cairo_font_options_t)
Gurax_DeclareFunctionAlias(cairo_font_options_merge_gurax, "cairo_font_options_merge")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("other", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_font_options_merge_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_options = args_gurax.Pick<Value_cairo_font_options_t>();
	cairo_font_options_t* options = value_options.GetEntityPtr();
	auto& value_other = args_gurax.Pick<Value_cairo_font_options_t>();
	const cairo_font_options_t* other = value_other.GetEntityPtr();
	// Function body
	cairo_font_options_merge(options, other);
	return Gurax::Value::nil();
}

// cairo.cairo_font_options_equal(options:cairo_font_options_t, other:cairo_font_options_t)
Gurax_DeclareFunctionAlias(cairo_font_options_equal_gurax, "cairo_font_options_equal")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("other", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_font_options_equal_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_options = args_gurax.Pick<Value_cairo_font_options_t>();
	const cairo_font_options_t* options = value_options.GetEntityPtr();
	auto& value_other = args_gurax.Pick<Value_cairo_font_options_t>();
	const cairo_font_options_t* other = value_other.GetEntityPtr();
	// Function body
	cairo_bool_t rtn = cairo_font_options_equal(options, other);
	return new Gurax::Value_Bool(!!rtn);
}

// cairo.cairo_font_options_hash(options:cairo_font_options_t)
Gurax_DeclareFunctionAlias(cairo_font_options_hash_gurax, "cairo_font_options_hash")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_font_options_hash_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_options = args_gurax.Pick<Value_cairo_font_options_t>();
	const cairo_font_options_t* options = value_options.GetEntityPtr();
	// Function body
	unsigned long rtn = cairo_font_options_hash(options);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_font_options_set_antialias(options:cairo_font_options_t, antialias:Number)
Gurax_DeclareFunctionAlias(cairo_font_options_set_antialias_gurax, "cairo_font_options_set_antialias")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("antialias", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_font_options_set_antialias_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_options = args_gurax.Pick<Value_cairo_font_options_t>();
	cairo_font_options_t* options = value_options.GetEntityPtr();
	cairo_antialias_t antialias = args_gurax.PickNumber<cairo_antialias_t>();
	// Function body
	cairo_font_options_set_antialias(options, antialias);
	return Gurax::Value::nil();
}

// cairo.cairo_font_options_get_antialias(options:cairo_font_options_t)
Gurax_DeclareFunctionAlias(cairo_font_options_get_antialias_gurax, "cairo_font_options_get_antialias")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_font_options_get_antialias_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_options = args_gurax.Pick<Value_cairo_font_options_t>();
	const cairo_font_options_t* options = value_options.GetEntityPtr();
	// Function body
	cairo_antialias_t rtn = cairo_font_options_get_antialias(options);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_font_options_set_subpixel_order(options:cairo_font_options_t, subpixel_order:Number)
Gurax_DeclareFunctionAlias(cairo_font_options_set_subpixel_order_gurax, "cairo_font_options_set_subpixel_order")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("subpixel_order", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_font_options_set_subpixel_order_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_options = args_gurax.Pick<Value_cairo_font_options_t>();
	cairo_font_options_t* options = value_options.GetEntityPtr();
	cairo_subpixel_order_t subpixel_order = args_gurax.PickNumber<cairo_subpixel_order_t>();
	// Function body
	cairo_font_options_set_subpixel_order(options, subpixel_order);
	return Gurax::Value::nil();
}

// cairo.cairo_font_options_get_subpixel_order(options:cairo_font_options_t)
Gurax_DeclareFunctionAlias(cairo_font_options_get_subpixel_order_gurax, "cairo_font_options_get_subpixel_order")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_font_options_get_subpixel_order_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_options = args_gurax.Pick<Value_cairo_font_options_t>();
	const cairo_font_options_t* options = value_options.GetEntityPtr();
	// Function body
	cairo_subpixel_order_t rtn = cairo_font_options_get_subpixel_order(options);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_font_options_set_hint_style(options:cairo_font_options_t, hint_style:Number)
Gurax_DeclareFunctionAlias(cairo_font_options_set_hint_style_gurax, "cairo_font_options_set_hint_style")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("hint_style", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_font_options_set_hint_style_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_options = args_gurax.Pick<Value_cairo_font_options_t>();
	cairo_font_options_t* options = value_options.GetEntityPtr();
	cairo_hint_style_t hint_style = args_gurax.PickNumber<cairo_hint_style_t>();
	// Function body
	cairo_font_options_set_hint_style(options, hint_style);
	return Gurax::Value::nil();
}

// cairo.cairo_font_options_get_hint_style(options:cairo_font_options_t)
Gurax_DeclareFunctionAlias(cairo_font_options_get_hint_style_gurax, "cairo_font_options_get_hint_style")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_font_options_get_hint_style_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_options = args_gurax.Pick<Value_cairo_font_options_t>();
	const cairo_font_options_t* options = value_options.GetEntityPtr();
	// Function body
	cairo_hint_style_t rtn = cairo_font_options_get_hint_style(options);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_font_options_set_hint_metrics(options:cairo_font_options_t, hint_metrics:Number)
Gurax_DeclareFunctionAlias(cairo_font_options_set_hint_metrics_gurax, "cairo_font_options_set_hint_metrics")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("hint_metrics", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_font_options_set_hint_metrics_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_options = args_gurax.Pick<Value_cairo_font_options_t>();
	cairo_font_options_t* options = value_options.GetEntityPtr();
	cairo_hint_metrics_t hint_metrics = args_gurax.PickNumber<cairo_hint_metrics_t>();
	// Function body
	cairo_font_options_set_hint_metrics(options, hint_metrics);
	return Gurax::Value::nil();
}

// cairo.cairo_font_options_get_hint_metrics(options:cairo_font_options_t)
Gurax_DeclareFunctionAlias(cairo_font_options_get_hint_metrics_gurax, "cairo_font_options_get_hint_metrics")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_font_options_get_hint_metrics_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_options = args_gurax.Pick<Value_cairo_font_options_t>();
	const cairo_font_options_t* options = value_options.GetEntityPtr();
	// Function body
	cairo_hint_metrics_t rtn = cairo_font_options_get_hint_metrics(options);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_font_options_get_variations(options:cairo_font_options_t)
Gurax_DeclareFunctionAlias(cairo_font_options_get_variations_gurax, "cairo_font_options_get_variations")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_font_options_get_variations_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_options = args_gurax.Pick<Value_cairo_font_options_t>();
	cairo_font_options_t* options = value_options.GetEntityPtr();
	// Function body
	const char* rtn = cairo_font_options_get_variations(options);
	return new Gurax::Value_String(rtn);
}

// cairo.cairo_font_options_set_variations(options:cairo_font_options_t, variations:String)
Gurax_DeclareFunctionAlias(cairo_font_options_set_variations_gurax, "cairo_font_options_set_variations")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("variations", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_font_options_set_variations_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_options = args_gurax.Pick<Value_cairo_font_options_t>();
	cairo_font_options_t* options = value_options.GetEntityPtr();
	const char* variations = args_gurax.PickString();
	// Function body
	cairo_font_options_set_variations(options, variations);
	return Gurax::Value::nil();
}

// cairo.cairo_select_font_face(cr:cairo_t, family:String, slant:Number, weight:Number)
Gurax_DeclareFunctionAlias(cairo_select_font_face_gurax, "cairo_select_font_face")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("family", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("slant", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("weight", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_select_font_face_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	const char* family = args_gurax.PickString();
	cairo_font_slant_t slant = args_gurax.PickNumber<cairo_font_slant_t>();
	cairo_font_weight_t weight = args_gurax.PickNumber<cairo_font_weight_t>();
	// Function body
	cairo_select_font_face(cr, family, slant, weight);
	return Gurax::Value::nil();
}

// cairo.cairo_set_font_size(cr:cairo_t, size:Number)
Gurax_DeclareFunctionAlias(cairo_set_font_size_gurax, "cairo_set_font_size")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_set_font_size_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	double size = args_gurax.PickNumber<double>();
	// Function body
	cairo_set_font_size(cr, size);
	return Gurax::Value::nil();
}

// cairo.cairo_set_font_matrix(cr:cairo_t, matrix:cairo_matrix_t)
Gurax_DeclareFunctionAlias(cairo_set_font_matrix_gurax, "cairo_set_font_matrix")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("matrix", VTYPE_cairo_matrix_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_set_font_matrix_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	auto& value_matrix = args_gurax.Pick<Value_cairo_matrix_t>();
	const cairo_matrix_t* matrix = value_matrix.GetEntityPtr();
	// Function body
	cairo_set_font_matrix(cr, matrix);
	return Gurax::Value::nil();
}

// cairo.cairo_get_font_matrix(cr:cairo_t, matrix:cairo_matrix_t)
Gurax_DeclareFunctionAlias(cairo_get_font_matrix_gurax, "cairo_get_font_matrix")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("matrix", VTYPE_cairo_matrix_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_get_font_matrix_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	auto& value_matrix = args_gurax.Pick<Value_cairo_matrix_t>();
	cairo_matrix_t* matrix = value_matrix.GetEntityPtr();
	// Function body
	cairo_get_font_matrix(cr, matrix);
	return Gurax::Value::nil();
}

// cairo.cairo_set_font_options(cr:cairo_t, options:cairo_font_options_t)
Gurax_DeclareFunctionAlias(cairo_set_font_options_gurax, "cairo_set_font_options")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_set_font_options_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	auto& value_options = args_gurax.Pick<Value_cairo_font_options_t>();
	const cairo_font_options_t* options = value_options.GetEntityPtr();
	// Function body
	cairo_set_font_options(cr, options);
	return Gurax::Value::nil();
}

// cairo.cairo_get_font_options(cr:cairo_t, options:cairo_font_options_t)
Gurax_DeclareFunctionAlias(cairo_get_font_options_gurax, "cairo_get_font_options")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_get_font_options_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	auto& value_options = args_gurax.Pick<Value_cairo_font_options_t>();
	cairo_font_options_t* options = value_options.GetEntityPtr();
	// Function body
	cairo_get_font_options(cr, options);
	return Gurax::Value::nil();
}

// cairo.cairo_set_font_face(cr:cairo_t, font_face:cairo_font_face_t)
Gurax_DeclareFunctionAlias(cairo_set_font_face_gurax, "cairo_set_font_face")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("font_face", VTYPE_cairo_font_face_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_set_font_face_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	auto& value_font_face = args_gurax.Pick<Value_cairo_font_face_t>();
	cairo_font_face_t* font_face = value_font_face.GetEntityPtr();
	// Function body
	cairo_set_font_face(cr, font_face);
	return Gurax::Value::nil();
}

// cairo.cairo_get_font_face(cr:cairo_t)
Gurax_DeclareFunctionAlias(cairo_get_font_face_gurax, "cairo_get_font_face")
{
	Declare(VTYPE_cairo_font_face_t, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_get_font_face_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	cairo_font_face_t* rtn = cairo_get_font_face(cr);
	if (!rtn) return Value::nil();
	return new Value_cairo_font_face_t(rtn);
}

// cairo.cairo_set_scaled_font(cr:cairo_t, scaled_font:cairo_scaled_font_t)
Gurax_DeclareFunctionAlias(cairo_set_scaled_font_gurax, "cairo_set_scaled_font")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("scaled_font", VTYPE_cairo_scaled_font_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_set_scaled_font_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	auto& value_scaled_font = args_gurax.Pick<Value_cairo_scaled_font_t>();
	const cairo_scaled_font_t* scaled_font = value_scaled_font.GetEntityPtr();
	// Function body
	cairo_set_scaled_font(cr, scaled_font);
	return Gurax::Value::nil();
}

// cairo.cairo_get_scaled_font(cr:cairo_t)
Gurax_DeclareFunctionAlias(cairo_get_scaled_font_gurax, "cairo_get_scaled_font")
{
	Declare(VTYPE_cairo_scaled_font_t, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_get_scaled_font_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	cairo_scaled_font_t* rtn = cairo_get_scaled_font(cr);
	if (!rtn) return Value::nil();
	return new Value_cairo_scaled_font_t(rtn);
}

// cairo.cairo_show_text(cr:cairo_t, utf8:String)
Gurax_DeclareFunctionAlias(cairo_show_text_gurax, "cairo_show_text")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("utf8", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_show_text_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	const char* utf8 = args_gurax.PickString();
	// Function body
	cairo_show_text(cr, utf8);
	return Gurax::Value::nil();
}

// cairo.cairo_show_glyphs(cr:cairo_t, glyphs:cairo_glyph_t, num_glyphs:Number)
Gurax_DeclareFunctionAlias(cairo_show_glyphs_gurax, "cairo_show_glyphs")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("glyphs", VTYPE_cairo_glyph_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num_glyphs", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_show_glyphs_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	auto& value_glyphs = args_gurax.Pick<Value_cairo_glyph_t>();
	const cairo_glyph_t* glyphs = value_glyphs.GetEntityPtr();
	int num_glyphs = args_gurax.PickNumber<int>();
	// Function body
	cairo_show_glyphs(cr, glyphs, num_glyphs);
	return Gurax::Value::nil();
}

// cairo.cairo_show_text_glyphs(cr:cairo_t, utf8:String, utf8_len:Number, glyphs:cairo_glyph_t, num_glyphs:Number, clusters:cairo_text_cluster_t, num_clusters:Number, cluster_flags:Number)
Gurax_DeclareFunctionAlias(cairo_show_text_glyphs_gurax, "cairo_show_text_glyphs")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("utf8", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("utf8_len", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("glyphs", VTYPE_cairo_glyph_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num_glyphs", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("clusters", VTYPE_cairo_text_cluster_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num_clusters", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("cluster_flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_show_text_glyphs_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	const char* utf8 = args_gurax.PickString();
	int utf8_len = args_gurax.PickNumber<int>();
	auto& value_glyphs = args_gurax.Pick<Value_cairo_glyph_t>();
	const cairo_glyph_t* glyphs = value_glyphs.GetEntityPtr();
	int num_glyphs = args_gurax.PickNumber<int>();
	auto& value_clusters = args_gurax.Pick<Value_cairo_text_cluster_t>();
	const cairo_text_cluster_t* clusters = value_clusters.GetEntityPtr();
	int num_clusters = args_gurax.PickNumber<int>();
	cairo_text_cluster_flags_t cluster_flags = args_gurax.PickNumber<cairo_text_cluster_flags_t>();
	// Function body
	cairo_show_text_glyphs(cr, utf8, utf8_len, glyphs, num_glyphs, clusters, num_clusters, cluster_flags);
	return Gurax::Value::nil();
}

// cairo.cairo_text_path(cr:cairo_t, utf8:String)
Gurax_DeclareFunctionAlias(cairo_text_path_gurax, "cairo_text_path")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("utf8", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_text_path_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	const char* utf8 = args_gurax.PickString();
	// Function body
	cairo_text_path(cr, utf8);
	return Gurax::Value::nil();
}

// cairo.cairo_glyph_path(cr:cairo_t, glyphs:cairo_glyph_t, num_glyphs:Number)
Gurax_DeclareFunctionAlias(cairo_glyph_path_gurax, "cairo_glyph_path")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("glyphs", VTYPE_cairo_glyph_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num_glyphs", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_glyph_path_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	auto& value_glyphs = args_gurax.Pick<Value_cairo_glyph_t>();
	const cairo_glyph_t* glyphs = value_glyphs.GetEntityPtr();
	int num_glyphs = args_gurax.PickNumber<int>();
	// Function body
	cairo_glyph_path(cr, glyphs, num_glyphs);
	return Gurax::Value::nil();
}

// cairo.cairo_text_extents(cr:cairo_t, utf8:String, extents:cairo_text_extents_t)
Gurax_DeclareFunctionAlias(cairo_text_extents_gurax, "cairo_text_extents")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("utf8", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("extents", VTYPE_cairo_text_extents_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_text_extents_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	const char* utf8 = args_gurax.PickString();
	auto& value_extents = args_gurax.Pick<Value_cairo_text_extents_t>();
	cairo_text_extents_t* extents = value_extents.GetEntityPtr();
	// Function body
	cairo_text_extents(cr, utf8, extents);
	return Gurax::Value::nil();
}

// cairo.cairo_glyph_extents(cr:cairo_t, glyphs:cairo_glyph_t, num_glyphs:Number, extents:cairo_text_extents_t)
Gurax_DeclareFunctionAlias(cairo_glyph_extents_gurax, "cairo_glyph_extents")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("glyphs", VTYPE_cairo_glyph_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num_glyphs", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("extents", VTYPE_cairo_text_extents_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_glyph_extents_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	auto& value_glyphs = args_gurax.Pick<Value_cairo_glyph_t>();
	const cairo_glyph_t* glyphs = value_glyphs.GetEntityPtr();
	int num_glyphs = args_gurax.PickNumber<int>();
	auto& value_extents = args_gurax.Pick<Value_cairo_text_extents_t>();
	cairo_text_extents_t* extents = value_extents.GetEntityPtr();
	// Function body
	cairo_glyph_extents(cr, glyphs, num_glyphs, extents);
	return Gurax::Value::nil();
}

// cairo.cairo_font_extents(cr:cairo_t, extents:cairo_font_extents_t)
Gurax_DeclareFunctionAlias(cairo_font_extents_gurax, "cairo_font_extents")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("extents", VTYPE_cairo_font_extents_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_font_extents_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	auto& value_extents = args_gurax.Pick<Value_cairo_font_extents_t>();
	cairo_font_extents_t* extents = value_extents.GetEntityPtr();
	// Function body
	cairo_font_extents(cr, extents);
	return Gurax::Value::nil();
}

// cairo.cairo_font_face_reference(font_face:cairo_font_face_t)
Gurax_DeclareFunctionAlias(cairo_font_face_reference_gurax, "cairo_font_face_reference")
{
	Declare(VTYPE_cairo_font_face_t, Flag::None);
	DeclareArg("font_face", VTYPE_cairo_font_face_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_font_face_reference_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_font_face = args_gurax.Pick<Value_cairo_font_face_t>();
	cairo_font_face_t* font_face = value_font_face.GetEntityPtr();
	// Function body
	cairo_font_face_t* rtn = cairo_font_face_reference(font_face);
	if (!rtn) return Value::nil();
	return new Value_cairo_font_face_t(rtn);
}

// cairo.cairo_font_face_destroy(font_face:cairo_font_face_t)
Gurax_DeclareFunctionAlias(cairo_font_face_destroy_gurax, "cairo_font_face_destroy")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("font_face", VTYPE_cairo_font_face_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_font_face_destroy_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_font_face = args_gurax.Pick<Value_cairo_font_face_t>();
	cairo_font_face_t* font_face = value_font_face.GetEntityPtr();
	// Function body
	cairo_font_face_destroy(font_face);
	return Gurax::Value::nil();
}

// cairo.cairo_font_face_get_reference_count(font_face:cairo_font_face_t)
Gurax_DeclareFunctionAlias(cairo_font_face_get_reference_count_gurax, "cairo_font_face_get_reference_count")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("font_face", VTYPE_cairo_font_face_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_font_face_get_reference_count_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_font_face = args_gurax.Pick<Value_cairo_font_face_t>();
	cairo_font_face_t* font_face = value_font_face.GetEntityPtr();
	// Function body
	unsigned int rtn = cairo_font_face_get_reference_count(font_face);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_font_face_status(font_face:cairo_font_face_t)
Gurax_DeclareFunctionAlias(cairo_font_face_status_gurax, "cairo_font_face_status")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("font_face", VTYPE_cairo_font_face_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_font_face_status_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_font_face = args_gurax.Pick<Value_cairo_font_face_t>();
	cairo_font_face_t* font_face = value_font_face.GetEntityPtr();
	// Function body
	cairo_status_t rtn = cairo_font_face_status(font_face);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_font_face_get_type(font_face:cairo_font_face_t)
Gurax_DeclareFunctionAlias(cairo_font_face_get_type_gurax, "cairo_font_face_get_type")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("font_face", VTYPE_cairo_font_face_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_font_face_get_type_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_font_face = args_gurax.Pick<Value_cairo_font_face_t>();
	cairo_font_face_t* font_face = value_font_face.GetEntityPtr();
	// Function body
	cairo_font_type_t rtn = cairo_font_face_get_type(font_face);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_scaled_font_create(font_face:cairo_font_face_t, font_matrix:cairo_matrix_t, ctm:cairo_matrix_t, options:cairo_font_options_t)
Gurax_DeclareFunctionAlias(cairo_scaled_font_create_gurax, "cairo_scaled_font_create")
{
	Declare(VTYPE_cairo_scaled_font_t, Flag::None);
	DeclareArg("font_face", VTYPE_cairo_font_face_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("font_matrix", VTYPE_cairo_matrix_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ctm", VTYPE_cairo_matrix_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_scaled_font_create_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_font_face = args_gurax.Pick<Value_cairo_font_face_t>();
	cairo_font_face_t* font_face = value_font_face.GetEntityPtr();
	auto& value_font_matrix = args_gurax.Pick<Value_cairo_matrix_t>();
	const cairo_matrix_t* font_matrix = value_font_matrix.GetEntityPtr();
	auto& value_ctm = args_gurax.Pick<Value_cairo_matrix_t>();
	const cairo_matrix_t* ctm = value_ctm.GetEntityPtr();
	auto& value_options = args_gurax.Pick<Value_cairo_font_options_t>();
	const cairo_font_options_t* options = value_options.GetEntityPtr();
	// Function body
	cairo_scaled_font_t* rtn = cairo_scaled_font_create(font_face, font_matrix, ctm, options);
	if (!rtn) return Value::nil();
	return new Value_cairo_scaled_font_t(rtn);
}

// cairo.cairo_scaled_font_reference(scaled_font:cairo_scaled_font_t)
Gurax_DeclareFunctionAlias(cairo_scaled_font_reference_gurax, "cairo_scaled_font_reference")
{
	Declare(VTYPE_cairo_scaled_font_t, Flag::None);
	DeclareArg("scaled_font", VTYPE_cairo_scaled_font_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_scaled_font_reference_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_scaled_font = args_gurax.Pick<Value_cairo_scaled_font_t>();
	cairo_scaled_font_t* scaled_font = value_scaled_font.GetEntityPtr();
	// Function body
	cairo_scaled_font_t* rtn = cairo_scaled_font_reference(scaled_font);
	if (!rtn) return Value::nil();
	return new Value_cairo_scaled_font_t(rtn);
}

// cairo.cairo_scaled_font_destroy(scaled_font:cairo_scaled_font_t)
Gurax_DeclareFunctionAlias(cairo_scaled_font_destroy_gurax, "cairo_scaled_font_destroy")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("scaled_font", VTYPE_cairo_scaled_font_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_scaled_font_destroy_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_scaled_font = args_gurax.Pick<Value_cairo_scaled_font_t>();
	cairo_scaled_font_t* scaled_font = value_scaled_font.GetEntityPtr();
	// Function body
	cairo_scaled_font_destroy(scaled_font);
	return Gurax::Value::nil();
}

// cairo.cairo_scaled_font_get_reference_count(scaled_font:cairo_scaled_font_t)
Gurax_DeclareFunctionAlias(cairo_scaled_font_get_reference_count_gurax, "cairo_scaled_font_get_reference_count")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("scaled_font", VTYPE_cairo_scaled_font_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_scaled_font_get_reference_count_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_scaled_font = args_gurax.Pick<Value_cairo_scaled_font_t>();
	cairo_scaled_font_t* scaled_font = value_scaled_font.GetEntityPtr();
	// Function body
	unsigned int rtn = cairo_scaled_font_get_reference_count(scaled_font);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_scaled_font_status(scaled_font:cairo_scaled_font_t)
Gurax_DeclareFunctionAlias(cairo_scaled_font_status_gurax, "cairo_scaled_font_status")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("scaled_font", VTYPE_cairo_scaled_font_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_scaled_font_status_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_scaled_font = args_gurax.Pick<Value_cairo_scaled_font_t>();
	cairo_scaled_font_t* scaled_font = value_scaled_font.GetEntityPtr();
	// Function body
	cairo_status_t rtn = cairo_scaled_font_status(scaled_font);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_scaled_font_get_type(scaled_font:cairo_scaled_font_t)
Gurax_DeclareFunctionAlias(cairo_scaled_font_get_type_gurax, "cairo_scaled_font_get_type")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("scaled_font", VTYPE_cairo_scaled_font_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_scaled_font_get_type_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_scaled_font = args_gurax.Pick<Value_cairo_scaled_font_t>();
	cairo_scaled_font_t* scaled_font = value_scaled_font.GetEntityPtr();
	// Function body
	cairo_font_type_t rtn = cairo_scaled_font_get_type(scaled_font);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_scaled_font_extents(scaled_font:cairo_scaled_font_t, extents:cairo_font_extents_t)
Gurax_DeclareFunctionAlias(cairo_scaled_font_extents_gurax, "cairo_scaled_font_extents")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("scaled_font", VTYPE_cairo_scaled_font_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("extents", VTYPE_cairo_font_extents_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_scaled_font_extents_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_scaled_font = args_gurax.Pick<Value_cairo_scaled_font_t>();
	cairo_scaled_font_t* scaled_font = value_scaled_font.GetEntityPtr();
	auto& value_extents = args_gurax.Pick<Value_cairo_font_extents_t>();
	cairo_font_extents_t* extents = value_extents.GetEntityPtr();
	// Function body
	cairo_scaled_font_extents(scaled_font, extents);
	return Gurax::Value::nil();
}

// cairo.cairo_scaled_font_text_extents(scaled_font:cairo_scaled_font_t, utf8:String, extents:cairo_text_extents_t)
Gurax_DeclareFunctionAlias(cairo_scaled_font_text_extents_gurax, "cairo_scaled_font_text_extents")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("scaled_font", VTYPE_cairo_scaled_font_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("utf8", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("extents", VTYPE_cairo_text_extents_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_scaled_font_text_extents_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_scaled_font = args_gurax.Pick<Value_cairo_scaled_font_t>();
	cairo_scaled_font_t* scaled_font = value_scaled_font.GetEntityPtr();
	const char* utf8 = args_gurax.PickString();
	auto& value_extents = args_gurax.Pick<Value_cairo_text_extents_t>();
	cairo_text_extents_t* extents = value_extents.GetEntityPtr();
	// Function body
	cairo_scaled_font_text_extents(scaled_font, utf8, extents);
	return Gurax::Value::nil();
}

// cairo.cairo_scaled_font_glyph_extents(scaled_font:cairo_scaled_font_t, glyphs:cairo_glyph_t, num_glyphs:Number, extents:cairo_text_extents_t)
Gurax_DeclareFunctionAlias(cairo_scaled_font_glyph_extents_gurax, "cairo_scaled_font_glyph_extents")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("scaled_font", VTYPE_cairo_scaled_font_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("glyphs", VTYPE_cairo_glyph_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num_glyphs", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("extents", VTYPE_cairo_text_extents_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_scaled_font_glyph_extents_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_scaled_font = args_gurax.Pick<Value_cairo_scaled_font_t>();
	cairo_scaled_font_t* scaled_font = value_scaled_font.GetEntityPtr();
	auto& value_glyphs = args_gurax.Pick<Value_cairo_glyph_t>();
	const cairo_glyph_t* glyphs = value_glyphs.GetEntityPtr();
	int num_glyphs = args_gurax.PickNumber<int>();
	auto& value_extents = args_gurax.Pick<Value_cairo_text_extents_t>();
	cairo_text_extents_t* extents = value_extents.GetEntityPtr();
	// Function body
	cairo_scaled_font_glyph_extents(scaled_font, glyphs, num_glyphs, extents);
	return Gurax::Value::nil();
}

// cairo.cairo_scaled_font_get_font_face(scaled_font:cairo_scaled_font_t)
Gurax_DeclareFunctionAlias(cairo_scaled_font_get_font_face_gurax, "cairo_scaled_font_get_font_face")
{
	Declare(VTYPE_cairo_font_face_t, Flag::None);
	DeclareArg("scaled_font", VTYPE_cairo_scaled_font_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_scaled_font_get_font_face_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_scaled_font = args_gurax.Pick<Value_cairo_scaled_font_t>();
	cairo_scaled_font_t* scaled_font = value_scaled_font.GetEntityPtr();
	// Function body
	cairo_font_face_t* rtn = cairo_scaled_font_get_font_face(scaled_font);
	if (!rtn) return Value::nil();
	return new Value_cairo_font_face_t(rtn);
}

// cairo.cairo_scaled_font_get_font_matrix(scaled_font:cairo_scaled_font_t, font_matrix:cairo_matrix_t)
Gurax_DeclareFunctionAlias(cairo_scaled_font_get_font_matrix_gurax, "cairo_scaled_font_get_font_matrix")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("scaled_font", VTYPE_cairo_scaled_font_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("font_matrix", VTYPE_cairo_matrix_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_scaled_font_get_font_matrix_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_scaled_font = args_gurax.Pick<Value_cairo_scaled_font_t>();
	cairo_scaled_font_t* scaled_font = value_scaled_font.GetEntityPtr();
	auto& value_font_matrix = args_gurax.Pick<Value_cairo_matrix_t>();
	cairo_matrix_t* font_matrix = value_font_matrix.GetEntityPtr();
	// Function body
	cairo_scaled_font_get_font_matrix(scaled_font, font_matrix);
	return Gurax::Value::nil();
}

// cairo.cairo_scaled_font_get_ctm(scaled_font:cairo_scaled_font_t, ctm:cairo_matrix_t)
Gurax_DeclareFunctionAlias(cairo_scaled_font_get_ctm_gurax, "cairo_scaled_font_get_ctm")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("scaled_font", VTYPE_cairo_scaled_font_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ctm", VTYPE_cairo_matrix_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_scaled_font_get_ctm_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_scaled_font = args_gurax.Pick<Value_cairo_scaled_font_t>();
	cairo_scaled_font_t* scaled_font = value_scaled_font.GetEntityPtr();
	auto& value_ctm = args_gurax.Pick<Value_cairo_matrix_t>();
	cairo_matrix_t* ctm = value_ctm.GetEntityPtr();
	// Function body
	cairo_scaled_font_get_ctm(scaled_font, ctm);
	return Gurax::Value::nil();
}

// cairo.cairo_scaled_font_get_scale_matrix(scaled_font:cairo_scaled_font_t, scale_matrix:cairo_matrix_t)
Gurax_DeclareFunctionAlias(cairo_scaled_font_get_scale_matrix_gurax, "cairo_scaled_font_get_scale_matrix")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("scaled_font", VTYPE_cairo_scaled_font_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("scale_matrix", VTYPE_cairo_matrix_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_scaled_font_get_scale_matrix_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_scaled_font = args_gurax.Pick<Value_cairo_scaled_font_t>();
	cairo_scaled_font_t* scaled_font = value_scaled_font.GetEntityPtr();
	auto& value_scale_matrix = args_gurax.Pick<Value_cairo_matrix_t>();
	cairo_matrix_t* scale_matrix = value_scale_matrix.GetEntityPtr();
	// Function body
	cairo_scaled_font_get_scale_matrix(scaled_font, scale_matrix);
	return Gurax::Value::nil();
}

// cairo.cairo_scaled_font_get_font_options(scaled_font:cairo_scaled_font_t, options:cairo_font_options_t)
Gurax_DeclareFunctionAlias(cairo_scaled_font_get_font_options_gurax, "cairo_scaled_font_get_font_options")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("scaled_font", VTYPE_cairo_scaled_font_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_scaled_font_get_font_options_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_scaled_font = args_gurax.Pick<Value_cairo_scaled_font_t>();
	cairo_scaled_font_t* scaled_font = value_scaled_font.GetEntityPtr();
	auto& value_options = args_gurax.Pick<Value_cairo_font_options_t>();
	cairo_font_options_t* options = value_options.GetEntityPtr();
	// Function body
	cairo_scaled_font_get_font_options(scaled_font, options);
	return Gurax::Value::nil();
}

// cairo.cairo_toy_font_face_create(family:String, slant:Number, weight:Number)
Gurax_DeclareFunctionAlias(cairo_toy_font_face_create_gurax, "cairo_toy_font_face_create")
{
	Declare(VTYPE_cairo_font_face_t, Flag::None);
	DeclareArg("family", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("slant", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("weight", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_toy_font_face_create_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* family = args_gurax.PickString();
	cairo_font_slant_t slant = args_gurax.PickNumber<cairo_font_slant_t>();
	cairo_font_weight_t weight = args_gurax.PickNumber<cairo_font_weight_t>();
	// Function body
	cairo_font_face_t* rtn = cairo_toy_font_face_create(family, slant, weight);
	if (!rtn) return Value::nil();
	return new Value_cairo_font_face_t(rtn);
}

// cairo.cairo_toy_font_face_get_family(font_face:cairo_font_face_t)
Gurax_DeclareFunctionAlias(cairo_toy_font_face_get_family_gurax, "cairo_toy_font_face_get_family")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("font_face", VTYPE_cairo_font_face_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_toy_font_face_get_family_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_font_face = args_gurax.Pick<Value_cairo_font_face_t>();
	cairo_font_face_t* font_face = value_font_face.GetEntityPtr();
	// Function body
	const char* rtn = cairo_toy_font_face_get_family(font_face);
	return new Gurax::Value_String(rtn);
}

// cairo.cairo_toy_font_face_get_slant(font_face:cairo_font_face_t)
Gurax_DeclareFunctionAlias(cairo_toy_font_face_get_slant_gurax, "cairo_toy_font_face_get_slant")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("font_face", VTYPE_cairo_font_face_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_toy_font_face_get_slant_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_font_face = args_gurax.Pick<Value_cairo_font_face_t>();
	cairo_font_face_t* font_face = value_font_face.GetEntityPtr();
	// Function body
	cairo_font_slant_t rtn = cairo_toy_font_face_get_slant(font_face);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_toy_font_face_get_weight(font_face:cairo_font_face_t)
Gurax_DeclareFunctionAlias(cairo_toy_font_face_get_weight_gurax, "cairo_toy_font_face_get_weight")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("font_face", VTYPE_cairo_font_face_t, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_toy_font_face_get_weight_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_font_face = args_gurax.Pick<Value_cairo_font_face_t>();
	cairo_font_face_t* font_face = value_font_face.GetEntityPtr();
	// Function body
	cairo_font_weight_t rtn = cairo_toy_font_face_get_weight(font_face);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_user_font_face_create()
Gurax_DeclareFunctionAlias(cairo_user_font_face_create_gurax, "cairo_user_font_face_create")
{
	Declare(VTYPE_cairo_font_face_t, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(cairo_user_font_face_create_gurax, processor_gurax, argument_gurax)
{
	// Function body
	cairo_font_face_t* rtn = cairo_user_font_face_create();
	if (!rtn) return Value::nil();
	return new Value_cairo_font_face_t(rtn);
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
	frame.Assign(Gurax_CreateFunction(cairo_transform_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_set_matrix_gurax));
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
	frame.Assign(Gurax_CreateFunction(cairo_paint_with_alpha_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_mask_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_mask_surface_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_stroke_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_stroke_preserve_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_fill_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_fill_preserve_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_copy_page_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_show_page_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_in_stroke_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_in_fill_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_in_clip_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_reset_clip_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_clip_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_clip_preserve_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_tag_begin_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_tag_end_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_glyph_allocate_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_glyph_free_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_text_cluster_allocate_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_text_cluster_free_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_font_options_create_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_font_options_copy_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_font_options_destroy_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_font_options_status_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_font_options_merge_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_font_options_equal_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_font_options_hash_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_font_options_set_antialias_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_font_options_get_antialias_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_font_options_set_subpixel_order_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_font_options_get_subpixel_order_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_font_options_set_hint_style_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_font_options_get_hint_style_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_font_options_set_hint_metrics_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_font_options_get_hint_metrics_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_font_options_get_variations_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_font_options_set_variations_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_select_font_face_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_set_font_size_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_set_font_matrix_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_get_font_matrix_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_set_font_options_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_get_font_options_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_set_font_face_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_get_font_face_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_set_scaled_font_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_get_scaled_font_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_show_text_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_show_glyphs_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_show_text_glyphs_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_text_path_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_glyph_path_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_text_extents_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_glyph_extents_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_font_extents_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_font_face_reference_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_font_face_destroy_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_font_face_get_reference_count_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_font_face_status_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_font_face_get_type_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_scaled_font_create_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_scaled_font_reference_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_scaled_font_destroy_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_scaled_font_get_reference_count_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_scaled_font_status_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_scaled_font_get_type_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_scaled_font_extents_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_scaled_font_text_extents_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_scaled_font_glyph_extents_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_scaled_font_get_font_face_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_scaled_font_get_font_matrix_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_scaled_font_get_ctm_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_scaled_font_get_scale_matrix_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_scaled_font_get_font_options_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_toy_font_face_create_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_toy_font_face_get_family_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_toy_font_face_get_slant_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_toy_font_face_get_weight_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_user_font_face_create_gurax));
}

Gurax_EndModuleScope(cairo)
