//==============================================================================
// Functions.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(cairo)

cairo_status_t write_func(void* closure, const unsigned char* data, unsigned int length)
{
	Stream& stream = *reinterpret_cast<Stream*>(closure);
	return stream.Write(data, length)? CAIRO_STATUS_SUCCESS : CAIRO_STATUS_WRITE_ERROR;
}

// cairo.cairo_version()
Gurax_DeclareFunctionAlias(cairo_version_gurax, "cairo_version")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
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
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_version_string_gurax, processor_gurax, argument_gurax)
{
	// Function body
	const char* rtn = cairo_version_string();
	return new Gurax::Value_String(rtn);
}

// cairo.cairo_create(target as cairo_surface_t)
Gurax_DeclareFunctionAlias(cairo_create_gurax, "cairo_create")
{
	Declare(VTYPE_cairo_t, Flag::None);
	DeclareArg("target", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_reference(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_reference_gurax, "cairo_reference")
{
	Declare(VTYPE_cairo_t, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_destroy(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_destroy_gurax, "cairo_destroy")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_get_reference_count(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_get_reference_count_gurax, "cairo_get_reference_count")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_save(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_save_gurax, "cairo_save")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_restore(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_restore_gurax, "cairo_restore")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_push_group(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_push_group_gurax, "cairo_push_group")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_push_group_with_content(cr as cairo_t, content as Number)
Gurax_DeclareFunctionAlias(cairo_push_group_with_content_gurax, "cairo_push_group_with_content")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("content", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_pop_group(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_pop_group_gurax, "cairo_pop_group")
{
	Declare(VTYPE_cairo_pattern_t, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_pop_group_to_source(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_pop_group_to_source_gurax, "cairo_pop_group_to_source")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_set_operator(cr as cairo_t, op as Number)
Gurax_DeclareFunctionAlias(cairo_set_operator_gurax, "cairo_set_operator")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("op", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_set_source(cr as cairo_t, source as cairo_pattern_t)
Gurax_DeclareFunctionAlias(cairo_set_source_gurax, "cairo_set_source")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("source", VTYPE_cairo_pattern_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_set_source_rgb(cr as cairo_t, red as Number, green as Number, blue as Number)
Gurax_DeclareFunctionAlias(cairo_set_source_rgb_gurax, "cairo_set_source_rgb")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_set_source_rgba(cr as cairo_t, red as Number, green as Number, blue as Number, alpha as Number)
Gurax_DeclareFunctionAlias(cairo_set_source_rgba_gurax, "cairo_set_source_rgba")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("alpha", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_set_source_surface(cr as cairo_t, surface as cairo_surface_t, x as Number, y as Number)
Gurax_DeclareFunctionAlias(cairo_set_source_surface_gurax, "cairo_set_source_surface")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_set_tolerance(cr as cairo_t, tolerance as Number)
Gurax_DeclareFunctionAlias(cairo_set_tolerance_gurax, "cairo_set_tolerance")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("tolerance", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_set_antialias(cr as cairo_t, antialias as Number)
Gurax_DeclareFunctionAlias(cairo_set_antialias_gurax, "cairo_set_antialias")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("antialias", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_set_fill_rule(cr as cairo_t, fill_rule as Number)
Gurax_DeclareFunctionAlias(cairo_set_fill_rule_gurax, "cairo_set_fill_rule")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("fill_rule", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_set_line_width(cr as cairo_t, width as Number)
Gurax_DeclareFunctionAlias(cairo_set_line_width_gurax, "cairo_set_line_width")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_set_line_cap(cr as cairo_t, line_cap as Number)
Gurax_DeclareFunctionAlias(cairo_set_line_cap_gurax, "cairo_set_line_cap")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("line_cap", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_set_line_join(cr as cairo_t, line_join as Number)
Gurax_DeclareFunctionAlias(cairo_set_line_join_gurax, "cairo_set_line_join")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("line_join", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_set_dash(cr as cairo_t, dashes[] as Number, offset as Number)
Gurax_DeclareFunctionAlias(cairo_set_dash_gurax, "cairo_set_dash")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dashes", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("offset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_set_dash_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	auto dashes = args_gurax.PickNumList<double>();
	double offset = args_gurax.PickNumber<double>();
	// Function body
	int num_dashes = dashes.sizeT<int>();
	cairo_set_dash(cr, dashes, num_dashes, offset);
	return Value::nil();
}

// cairo.cairo_set_miter_limit(cr as cairo_t, limit as Number)
Gurax_DeclareFunctionAlias(cairo_set_miter_limit_gurax, "cairo_set_miter_limit")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("limit", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_translate(cr as cairo_t, tx as Number, ty as Number)
Gurax_DeclareFunctionAlias(cairo_translate_gurax, "cairo_translate")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("tx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ty", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_scale(cr as cairo_t, sx as Number, sy as Number)
Gurax_DeclareFunctionAlias(cairo_scale_gurax, "cairo_scale")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("sx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("sy", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_rotate(cr as cairo_t, angle as Number)
Gurax_DeclareFunctionAlias(cairo_rotate_gurax, "cairo_rotate")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("angle", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_transform(cr as cairo_t, matrix as cairo_matrix_t)
Gurax_DeclareFunctionAlias(cairo_transform_gurax, "cairo_transform")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("matrix", VTYPE_cairo_matrix_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_set_matrix(cr as cairo_t, matrix as cairo_matrix_t)
Gurax_DeclareFunctionAlias(cairo_set_matrix_gurax, "cairo_set_matrix")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("matrix", VTYPE_cairo_matrix_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_identity_matrix(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_identity_matrix_gurax, "cairo_identity_matrix")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_user_to_device(cr as cairo_t, x as Number, y as Number)
Gurax_DeclareFunctionAlias(cairo_user_to_device_gurax, "cairo_user_to_device")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_user_to_device_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	double x = args_gurax.PickNumber<double>();
	double y = args_gurax.PickNumber<double>();
	// Function body
	cairo_user_to_device(cr, &x, &y);
	return Value_Tuple::Create(new Value_Number(x), new Value_Number(y));
}

// cairo.cairo_user_to_device_distance(cr as cairo_t, dx as Number, dy as Number)
Gurax_DeclareFunctionAlias(cairo_user_to_device_distance_gurax, "cairo_user_to_device_distance")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dy", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_user_to_device_distance_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	double dx = args_gurax.PickNumber<double>();
	double dy = args_gurax.PickNumber<double>();
	// Function body
	cairo_user_to_device_distance(cr, &dx, &dy);
	return Value_Tuple::Create(new Value_Number(dx), new Value_Number(dy));
}

// cairo.cairo_device_to_user(cr as cairo_t, x as Number, y as Number)
Gurax_DeclareFunctionAlias(cairo_device_to_user_gurax, "cairo_device_to_user")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_device_to_user_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	double x = args_gurax.PickNumber<double>();
	double y = args_gurax.PickNumber<double>();
	// Function body
	cairo_device_to_user(cr, &x, &y);
	return Value_Tuple::Create(new Value_Number(x), new Value_Number(y));
}

// cairo.cairo_device_to_user_distance(cr as cairo_t, dx as Number, dy as Number)
Gurax_DeclareFunctionAlias(cairo_device_to_user_distance_gurax, "cairo_device_to_user_distance")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dy", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_device_to_user_distance_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	double dx = args_gurax.PickNumber<double>();
	double dy = args_gurax.PickNumber<double>();
	// Function body
	cairo_device_to_user_distance(cr, &dx, &dy);
	return Value_Tuple::Create(new Value_Number(dx), new Value_Number(dy));
}

// cairo.cairo_new_path(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_new_path_gurax, "cairo_new_path")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_move_to(cr as cairo_t, x as Number, y as Number)
Gurax_DeclareFunctionAlias(cairo_move_to_gurax, "cairo_move_to")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_new_sub_path(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_new_sub_path_gurax, "cairo_new_sub_path")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_line_to(cr as cairo_t, x as Number, y as Number)
Gurax_DeclareFunctionAlias(cairo_line_to_gurax, "cairo_line_to")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_curve_to(cr as cairo_t, x1 as Number, y1 as Number, x2 as Number, y2 as Number, x3 as Number, y3 as Number)
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
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_arc(cr as cairo_t, xc as Number, yc as Number, radius as Number, angle1 as Number, angle2 as Number)
Gurax_DeclareFunctionAlias(cairo_arc_gurax, "cairo_arc")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xc", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("yc", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("radius", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("angle1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("angle2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_arc_negative(cr as cairo_t, xc as Number, yc as Number, radius as Number, angle1 as Number, angle2 as Number)
Gurax_DeclareFunctionAlias(cairo_arc_negative_gurax, "cairo_arc_negative")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xc", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("yc", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("radius", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("angle1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("angle2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_rel_move_to(cr as cairo_t, dx as Number, dy as Number)
Gurax_DeclareFunctionAlias(cairo_rel_move_to_gurax, "cairo_rel_move_to")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dy", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_rel_line_to(cr as cairo_t, dx as Number, dy as Number)
Gurax_DeclareFunctionAlias(cairo_rel_line_to_gurax, "cairo_rel_line_to")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dy", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_rel_curve_to(cr as cairo_t, dx1 as Number, dy1 as Number, dx2 as Number, dy2 as Number, dx3 as Number, dy3 as Number)
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
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_rectangle(cr as cairo_t, x as Number, y as Number, width as Number, height as Number)
Gurax_DeclareFunctionAlias(cairo_rectangle_gurax, "cairo_rectangle")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_close_path(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_close_path_gurax, "cairo_close_path")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_path_extents(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_path_extents_gurax, "cairo_path_extents")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_path_extents_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	double x1, y1, x2, y2;
	cairo_path_extents(cr, &x1, &y1, &x2, &y2);
	return Value_Tuple::Create(new Value_Number(x1), new Value_Number(y1), new Value_Number(x2), new Value_Number(y2));
}

// cairo.cairo_paint(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_paint_gurax, "cairo_paint")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_paint_with_alpha(cr as cairo_t, alpha as Number)
Gurax_DeclareFunctionAlias(cairo_paint_with_alpha_gurax, "cairo_paint_with_alpha")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("alpha", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_mask(cr as cairo_t, pattern as cairo_pattern_t)
Gurax_DeclareFunctionAlias(cairo_mask_gurax, "cairo_mask")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pattern", VTYPE_cairo_pattern_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_mask_surface(cr as cairo_t, surface as cairo_surface_t, surface_x as Number, surface_y as Number)
Gurax_DeclareFunctionAlias(cairo_mask_surface_gurax, "cairo_mask_surface")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("surface_x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("surface_y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_stroke(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_stroke_gurax, "cairo_stroke")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_stroke_preserve(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_stroke_preserve_gurax, "cairo_stroke_preserve")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_fill(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_fill_gurax, "cairo_fill")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_fill_preserve(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_fill_preserve_gurax, "cairo_fill_preserve")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_copy_page(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_copy_page_gurax, "cairo_copy_page")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_show_page(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_show_page_gurax, "cairo_show_page")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_in_stroke(cr as cairo_t, x as Number, y as Number)
Gurax_DeclareFunctionAlias(cairo_in_stroke_gurax, "cairo_in_stroke")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_in_fill(cr as cairo_t, x as Number, y as Number)
Gurax_DeclareFunctionAlias(cairo_in_fill_gurax, "cairo_in_fill")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_in_clip(cr as cairo_t, x as Number, y as Number)
Gurax_DeclareFunctionAlias(cairo_in_clip_gurax, "cairo_in_clip")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_stroke_extents(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_stroke_extents_gurax, "cairo_stroke_extents")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_stroke_extents_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	double x1, y1, x2, y2;
	cairo_stroke_extents(cr, &x1, &y1, &x2, &y2);
	return Value_Tuple::Create(new Value_Number(x1), new Value_Number(y1), new Value_Number(x2), new Value_Number(y2));
}

// cairo.cairo_fill_extents(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_fill_extents_gurax, "cairo_fill_extents")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_fill_extents_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	double x1, y1, x2, y2;
	cairo_fill_extents(cr, &x1, &y1, &x2, &y2);
	return Value_Tuple::Create(new Value_Number(x1), new Value_Number(y1), new Value_Number(x2), new Value_Number(y2));
}

// cairo.cairo_reset_clip(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_reset_clip_gurax, "cairo_reset_clip")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_clip(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_clip_gurax, "cairo_clip")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_clip_preserve(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_clip_preserve_gurax, "cairo_clip_preserve")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_clip_extents(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_clip_extents_gurax, "cairo_clip_extents")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_clip_extents_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	double x1, y1, x2, y2;
	cairo_clip_extents(cr, &x1, &y1, &x2, &y2);
	return Value_Tuple::Create(new Value_Number(x1), new Value_Number(y1), new Value_Number(x2), new Value_Number(y2));
}

// cairo.cairo_copy_clip_rectangle_list(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_copy_clip_rectangle_list_gurax, "cairo_copy_clip_rectangle_list")
{
	Declare(VTYPE_cairo_rectangle_list_t, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_copy_clip_rectangle_list_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	cairo_rectangle_list_t* rtn = cairo_copy_clip_rectangle_list(cr);
	if (!rtn) return Value::nil();
	return new Value_cairo_rectangle_list_t(rtn);
}

// cairo.cairo_rectangle_list_destroy(rectangle_list as cairo_rectangle_list_t)
Gurax_DeclareFunctionAlias(cairo_rectangle_list_destroy_gurax, "cairo_rectangle_list_destroy")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("rectangle_list", VTYPE_cairo_rectangle_list_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_rectangle_list_destroy_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_rectangle_list = args_gurax.Pick<Value_cairo_rectangle_list_t>();
	cairo_rectangle_list_t* rectangle_list = value_rectangle_list.GetEntityPtr();
	// Function body
	cairo_rectangle_list_destroy(rectangle_list);
	return Gurax::Value::nil();
}

// cairo.cairo_tag_begin(cr as cairo_t, tag_name as String, attributes as String)
Gurax_DeclareFunctionAlias(cairo_tag_begin_gurax, "cairo_tag_begin")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("tag_name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("attributes", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_tag_end(cr as cairo_t, tag_name as String)
Gurax_DeclareFunctionAlias(cairo_tag_end_gurax, "cairo_tag_end")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("tag_name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_glyph_allocate(num_glyphs as Number)
Gurax_DeclareFunctionAlias(cairo_glyph_allocate_gurax, "cairo_glyph_allocate")
{
	Declare(VTYPE_cairo_glyph_t, Flag::None);
	DeclareArg("num_glyphs", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_glyph_free(glyphs as cairo_glyph_t)
Gurax_DeclareFunctionAlias(cairo_glyph_free_gurax, "cairo_glyph_free")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("glyphs", VTYPE_cairo_glyph_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_text_cluster_allocate(num_clusters as Number)
Gurax_DeclareFunctionAlias(cairo_text_cluster_allocate_gurax, "cairo_text_cluster_allocate")
{
	Declare(VTYPE_cairo_text_cluster_t, Flag::None);
	DeclareArg("num_clusters", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_text_cluster_free(clusters as cairo_text_cluster_t)
Gurax_DeclareFunctionAlias(cairo_text_cluster_free_gurax, "cairo_text_cluster_free")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("clusters", VTYPE_cairo_text_cluster_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_font_options_create_gurax, processor_gurax, argument_gurax)
{
	// Function body
	cairo_font_options_t* rtn = cairo_font_options_create();
	if (!rtn) return Value::nil();
	return new Value_cairo_font_options_t(rtn);
}

// cairo.cairo_font_options_copy(original as cairo_font_options_t)
Gurax_DeclareFunctionAlias(cairo_font_options_copy_gurax, "cairo_font_options_copy")
{
	Declare(VTYPE_cairo_font_options_t, Flag::None);
	DeclareArg("original", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_font_options_destroy(options as cairo_font_options_t)
Gurax_DeclareFunctionAlias(cairo_font_options_destroy_gurax, "cairo_font_options_destroy")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_font_options_status(options as cairo_font_options_t)
Gurax_DeclareFunctionAlias(cairo_font_options_status_gurax, "cairo_font_options_status")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_font_options_merge(options as cairo_font_options_t, other as cairo_font_options_t)
Gurax_DeclareFunctionAlias(cairo_font_options_merge_gurax, "cairo_font_options_merge")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("other", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_font_options_equal(options as cairo_font_options_t, other as cairo_font_options_t)
Gurax_DeclareFunctionAlias(cairo_font_options_equal_gurax, "cairo_font_options_equal")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("other", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_font_options_hash(options as cairo_font_options_t)
Gurax_DeclareFunctionAlias(cairo_font_options_hash_gurax, "cairo_font_options_hash")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_font_options_set_antialias(options as cairo_font_options_t, antialias as Number)
Gurax_DeclareFunctionAlias(cairo_font_options_set_antialias_gurax, "cairo_font_options_set_antialias")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("antialias", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_font_options_get_antialias(options as cairo_font_options_t)
Gurax_DeclareFunctionAlias(cairo_font_options_get_antialias_gurax, "cairo_font_options_get_antialias")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_font_options_set_subpixel_order(options as cairo_font_options_t, subpixel_order as Number)
Gurax_DeclareFunctionAlias(cairo_font_options_set_subpixel_order_gurax, "cairo_font_options_set_subpixel_order")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("subpixel_order", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_font_options_get_subpixel_order(options as cairo_font_options_t)
Gurax_DeclareFunctionAlias(cairo_font_options_get_subpixel_order_gurax, "cairo_font_options_get_subpixel_order")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_font_options_set_hint_style(options as cairo_font_options_t, hint_style as Number)
Gurax_DeclareFunctionAlias(cairo_font_options_set_hint_style_gurax, "cairo_font_options_set_hint_style")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("hint_style", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_font_options_get_hint_style(options as cairo_font_options_t)
Gurax_DeclareFunctionAlias(cairo_font_options_get_hint_style_gurax, "cairo_font_options_get_hint_style")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_font_options_set_hint_metrics(options as cairo_font_options_t, hint_metrics as Number)
Gurax_DeclareFunctionAlias(cairo_font_options_set_hint_metrics_gurax, "cairo_font_options_set_hint_metrics")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("hint_metrics", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_font_options_get_hint_metrics(options as cairo_font_options_t)
Gurax_DeclareFunctionAlias(cairo_font_options_get_hint_metrics_gurax, "cairo_font_options_get_hint_metrics")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_font_options_get_variations(options as cairo_font_options_t)
Gurax_DeclareFunctionAlias(cairo_font_options_get_variations_gurax, "cairo_font_options_get_variations")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_font_options_set_variations(options as cairo_font_options_t, variations as String)
Gurax_DeclareFunctionAlias(cairo_font_options_set_variations_gurax, "cairo_font_options_set_variations")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("variations", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_select_font_face(cr as cairo_t, family as String, slant as Number, weight as Number)
Gurax_DeclareFunctionAlias(cairo_select_font_face_gurax, "cairo_select_font_face")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("family", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("slant", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("weight", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_set_font_size(cr as cairo_t, size as Number)
Gurax_DeclareFunctionAlias(cairo_set_font_size_gurax, "cairo_set_font_size")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_set_font_matrix(cr as cairo_t, matrix as cairo_matrix_t)
Gurax_DeclareFunctionAlias(cairo_set_font_matrix_gurax, "cairo_set_font_matrix")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("matrix", VTYPE_cairo_matrix_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_get_font_matrix(cr as cairo_t, matrix as cairo_matrix_t)
Gurax_DeclareFunctionAlias(cairo_get_font_matrix_gurax, "cairo_get_font_matrix")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("matrix", VTYPE_cairo_matrix_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_set_font_options(cr as cairo_t, options as cairo_font_options_t)
Gurax_DeclareFunctionAlias(cairo_set_font_options_gurax, "cairo_set_font_options")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_get_font_options(cr as cairo_t, options as cairo_font_options_t)
Gurax_DeclareFunctionAlias(cairo_get_font_options_gurax, "cairo_get_font_options")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_set_font_face(cr as cairo_t, font_face as cairo_font_face_t)
Gurax_DeclareFunctionAlias(cairo_set_font_face_gurax, "cairo_set_font_face")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("font_face", VTYPE_cairo_font_face_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_get_font_face(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_get_font_face_gurax, "cairo_get_font_face")
{
	Declare(VTYPE_cairo_font_face_t, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_set_scaled_font(cr as cairo_t, scaled_font as cairo_scaled_font_t)
Gurax_DeclareFunctionAlias(cairo_set_scaled_font_gurax, "cairo_set_scaled_font")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("scaled_font", VTYPE_cairo_scaled_font_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_get_scaled_font(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_get_scaled_font_gurax, "cairo_get_scaled_font")
{
	Declare(VTYPE_cairo_scaled_font_t, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_show_text(cr as cairo_t, utf8 as String)
Gurax_DeclareFunctionAlias(cairo_show_text_gurax, "cairo_show_text")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("utf8", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_show_glyphs(cr as cairo_t, glyphs as cairo_glyph_t, num_glyphs as Number)
Gurax_DeclareFunctionAlias(cairo_show_glyphs_gurax, "cairo_show_glyphs")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("glyphs", VTYPE_cairo_glyph_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num_glyphs", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_show_text_glyphs(cr as cairo_t, utf8 as String, utf8_len as Number, glyphs as cairo_glyph_t, num_glyphs as Number, clusters as cairo_text_cluster_t, num_clusters as Number, cluster_flags as Number)
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
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_text_path(cr as cairo_t, utf8 as String)
Gurax_DeclareFunctionAlias(cairo_text_path_gurax, "cairo_text_path")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("utf8", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_glyph_path(cr as cairo_t, glyphs as cairo_glyph_t, num_glyphs as Number)
Gurax_DeclareFunctionAlias(cairo_glyph_path_gurax, "cairo_glyph_path")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("glyphs", VTYPE_cairo_glyph_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num_glyphs", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_text_extents(cr as cairo_t, utf8 as String, extents as cairo_text_extents_t)
Gurax_DeclareFunctionAlias(cairo_text_extents_gurax, "cairo_text_extents")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("utf8", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("extents", VTYPE_cairo_text_extents_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_glyph_extents(cr as cairo_t, glyphs as cairo_glyph_t, num_glyphs as Number, extents as cairo_text_extents_t)
Gurax_DeclareFunctionAlias(cairo_glyph_extents_gurax, "cairo_glyph_extents")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("glyphs", VTYPE_cairo_glyph_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num_glyphs", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("extents", VTYPE_cairo_text_extents_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_font_extents(cr as cairo_t, extents as cairo_font_extents_t)
Gurax_DeclareFunctionAlias(cairo_font_extents_gurax, "cairo_font_extents")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("extents", VTYPE_cairo_font_extents_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_font_face_reference(font_face as cairo_font_face_t)
Gurax_DeclareFunctionAlias(cairo_font_face_reference_gurax, "cairo_font_face_reference")
{
	Declare(VTYPE_cairo_font_face_t, Flag::None);
	DeclareArg("font_face", VTYPE_cairo_font_face_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_font_face_destroy(font_face as cairo_font_face_t)
Gurax_DeclareFunctionAlias(cairo_font_face_destroy_gurax, "cairo_font_face_destroy")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("font_face", VTYPE_cairo_font_face_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_font_face_get_reference_count(font_face as cairo_font_face_t)
Gurax_DeclareFunctionAlias(cairo_font_face_get_reference_count_gurax, "cairo_font_face_get_reference_count")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("font_face", VTYPE_cairo_font_face_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_font_face_status(font_face as cairo_font_face_t)
Gurax_DeclareFunctionAlias(cairo_font_face_status_gurax, "cairo_font_face_status")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("font_face", VTYPE_cairo_font_face_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_font_face_get_type(font_face as cairo_font_face_t)
Gurax_DeclareFunctionAlias(cairo_font_face_get_type_gurax, "cairo_font_face_get_type")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("font_face", VTYPE_cairo_font_face_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_scaled_font_create(font_face as cairo_font_face_t, font_matrix as cairo_matrix_t, ctm as cairo_matrix_t, options as cairo_font_options_t)
Gurax_DeclareFunctionAlias(cairo_scaled_font_create_gurax, "cairo_scaled_font_create")
{
	Declare(VTYPE_cairo_scaled_font_t, Flag::None);
	DeclareArg("font_face", VTYPE_cairo_font_face_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("font_matrix", VTYPE_cairo_matrix_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ctm", VTYPE_cairo_matrix_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_scaled_font_reference(scaled_font as cairo_scaled_font_t)
Gurax_DeclareFunctionAlias(cairo_scaled_font_reference_gurax, "cairo_scaled_font_reference")
{
	Declare(VTYPE_cairo_scaled_font_t, Flag::None);
	DeclareArg("scaled_font", VTYPE_cairo_scaled_font_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_scaled_font_destroy(scaled_font as cairo_scaled_font_t)
Gurax_DeclareFunctionAlias(cairo_scaled_font_destroy_gurax, "cairo_scaled_font_destroy")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("scaled_font", VTYPE_cairo_scaled_font_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_scaled_font_get_reference_count(scaled_font as cairo_scaled_font_t)
Gurax_DeclareFunctionAlias(cairo_scaled_font_get_reference_count_gurax, "cairo_scaled_font_get_reference_count")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("scaled_font", VTYPE_cairo_scaled_font_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_scaled_font_status(scaled_font as cairo_scaled_font_t)
Gurax_DeclareFunctionAlias(cairo_scaled_font_status_gurax, "cairo_scaled_font_status")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("scaled_font", VTYPE_cairo_scaled_font_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_scaled_font_get_type(scaled_font as cairo_scaled_font_t)
Gurax_DeclareFunctionAlias(cairo_scaled_font_get_type_gurax, "cairo_scaled_font_get_type")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("scaled_font", VTYPE_cairo_scaled_font_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_scaled_font_extents(scaled_font as cairo_scaled_font_t, extents as cairo_font_extents_t)
Gurax_DeclareFunctionAlias(cairo_scaled_font_extents_gurax, "cairo_scaled_font_extents")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("scaled_font", VTYPE_cairo_scaled_font_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("extents", VTYPE_cairo_font_extents_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_scaled_font_text_extents(scaled_font as cairo_scaled_font_t, utf8 as String, extents as cairo_text_extents_t)
Gurax_DeclareFunctionAlias(cairo_scaled_font_text_extents_gurax, "cairo_scaled_font_text_extents")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("scaled_font", VTYPE_cairo_scaled_font_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("utf8", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("extents", VTYPE_cairo_text_extents_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_scaled_font_glyph_extents(scaled_font as cairo_scaled_font_t, glyphs as cairo_glyph_t, num_glyphs as Number, extents as cairo_text_extents_t)
Gurax_DeclareFunctionAlias(cairo_scaled_font_glyph_extents_gurax, "cairo_scaled_font_glyph_extents")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("scaled_font", VTYPE_cairo_scaled_font_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("glyphs", VTYPE_cairo_glyph_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num_glyphs", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("extents", VTYPE_cairo_text_extents_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_scaled_font_get_font_face(scaled_font as cairo_scaled_font_t)
Gurax_DeclareFunctionAlias(cairo_scaled_font_get_font_face_gurax, "cairo_scaled_font_get_font_face")
{
	Declare(VTYPE_cairo_font_face_t, Flag::None);
	DeclareArg("scaled_font", VTYPE_cairo_scaled_font_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_scaled_font_get_font_matrix(scaled_font as cairo_scaled_font_t, font_matrix as cairo_matrix_t)
Gurax_DeclareFunctionAlias(cairo_scaled_font_get_font_matrix_gurax, "cairo_scaled_font_get_font_matrix")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("scaled_font", VTYPE_cairo_scaled_font_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("font_matrix", VTYPE_cairo_matrix_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_scaled_font_get_ctm(scaled_font as cairo_scaled_font_t, ctm as cairo_matrix_t)
Gurax_DeclareFunctionAlias(cairo_scaled_font_get_ctm_gurax, "cairo_scaled_font_get_ctm")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("scaled_font", VTYPE_cairo_scaled_font_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ctm", VTYPE_cairo_matrix_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_scaled_font_get_scale_matrix(scaled_font as cairo_scaled_font_t, scale_matrix as cairo_matrix_t)
Gurax_DeclareFunctionAlias(cairo_scaled_font_get_scale_matrix_gurax, "cairo_scaled_font_get_scale_matrix")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("scaled_font", VTYPE_cairo_scaled_font_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("scale_matrix", VTYPE_cairo_matrix_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_scaled_font_get_font_options(scaled_font as cairo_scaled_font_t, options as cairo_font_options_t)
Gurax_DeclareFunctionAlias(cairo_scaled_font_get_font_options_gurax, "cairo_scaled_font_get_font_options")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("scaled_font", VTYPE_cairo_scaled_font_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_toy_font_face_create(family as String, slant as Number, weight as Number)
Gurax_DeclareFunctionAlias(cairo_toy_font_face_create_gurax, "cairo_toy_font_face_create")
{
	Declare(VTYPE_cairo_font_face_t, Flag::None);
	DeclareArg("family", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("slant", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("weight", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_toy_font_face_get_family(font_face as cairo_font_face_t)
Gurax_DeclareFunctionAlias(cairo_toy_font_face_get_family_gurax, "cairo_toy_font_face_get_family")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("font_face", VTYPE_cairo_font_face_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_toy_font_face_get_slant(font_face as cairo_font_face_t)
Gurax_DeclareFunctionAlias(cairo_toy_font_face_get_slant_gurax, "cairo_toy_font_face_get_slant")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("font_face", VTYPE_cairo_font_face_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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

// cairo.cairo_toy_font_face_get_weight(font_face as cairo_font_face_t)
Gurax_DeclareFunctionAlias(cairo_toy_font_face_get_weight_gurax, "cairo_toy_font_face_get_weight")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("font_face", VTYPE_cairo_font_face_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
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
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_user_font_face_create_gurax, processor_gurax, argument_gurax)
{
	// Function body
	cairo_font_face_t* rtn = cairo_user_font_face_create();
	if (!rtn) return Value::nil();
	return new Value_cairo_font_face_t(rtn);
}

// cairo.cairo_get_operator(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_get_operator_gurax, "cairo_get_operator")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_get_operator_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	cairo_operator_t rtn = cairo_get_operator(cr);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_get_source(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_get_source_gurax, "cairo_get_source")
{
	Declare(VTYPE_cairo_pattern_t, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_get_source_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	cairo_pattern_t* rtn = cairo_get_source(cr);
	if (!rtn) return Value::nil();
	return new Value_cairo_pattern_t(rtn);
}

// cairo.cairo_get_tolerance(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_get_tolerance_gurax, "cairo_get_tolerance")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_get_tolerance_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	double rtn = cairo_get_tolerance(cr);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_get_antialias(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_get_antialias_gurax, "cairo_get_antialias")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_get_antialias_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	cairo_antialias_t rtn = cairo_get_antialias(cr);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_has_current_point(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_has_current_point_gurax, "cairo_has_current_point")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_has_current_point_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	cairo_bool_t rtn = cairo_has_current_point(cr);
	return new Gurax::Value_Bool(!!rtn);
}

// cairo.cairo_get_current_point(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_get_current_point_gurax, "cairo_get_current_point")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_get_current_point_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	double x, y;
	cairo_get_current_point(cr, &x, &y);
	return Value_Tuple::Create(new Value_Number(x), new Value_Number(y));
}

// cairo.cairo_get_fill_rule(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_get_fill_rule_gurax, "cairo_get_fill_rule")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_get_fill_rule_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	cairo_fill_rule_t rtn = cairo_get_fill_rule(cr);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_get_line_width(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_get_line_width_gurax, "cairo_get_line_width")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_get_line_width_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	double rtn = cairo_get_line_width(cr);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_get_line_cap(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_get_line_cap_gurax, "cairo_get_line_cap")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_get_line_cap_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	cairo_line_cap_t rtn = cairo_get_line_cap(cr);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_get_line_join(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_get_line_join_gurax, "cairo_get_line_join")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_get_line_join_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	cairo_line_join_t rtn = cairo_get_line_join(cr);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_get_miter_limit(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_get_miter_limit_gurax, "cairo_get_miter_limit")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_get_miter_limit_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	double rtn = cairo_get_miter_limit(cr);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_get_dash_count(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_get_dash_count_gurax, "cairo_get_dash_count")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_get_dash_count_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	int rtn = cairo_get_dash_count(cr);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_get_dash(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_get_dash_gurax, "cairo_get_dash")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_get_dash_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	double offset;
	int dash_count = cairo_get_dash_count(cr);
	std::unique_ptr<double []> dashes(new double [dash_count]);
	cairo_get_dash(cr, dashes.get(), &offset);
	return Value_Tuple::Create(Value_List::Create(dashes.get(), dash_count), new Value_Number(offset));
}

// cairo.cairo_get_matrix(cr as cairo_t, matrix as cairo_matrix_t)
Gurax_DeclareFunctionAlias(cairo_get_matrix_gurax, "cairo_get_matrix")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("matrix", VTYPE_cairo_matrix_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_get_matrix_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	auto& value_matrix = args_gurax.Pick<Value_cairo_matrix_t>();
	cairo_matrix_t* matrix = value_matrix.GetEntityPtr();
	// Function body
	cairo_get_matrix(cr, matrix);
	return Gurax::Value::nil();
}

// cairo.cairo_get_target(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_get_target_gurax, "cairo_get_target")
{
	Declare(VTYPE_cairo_surface_t, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_get_target_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	cairo_surface_t* rtn = cairo_get_target(cr);
	if (!rtn) return Value::nil();
	return new Value_cairo_surface_t(rtn);
}

// cairo.cairo_get_group_target(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_get_group_target_gurax, "cairo_get_group_target")
{
	Declare(VTYPE_cairo_surface_t, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_get_group_target_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	cairo_surface_t* rtn = cairo_get_group_target(cr);
	if (!rtn) return Value::nil();
	return new Value_cairo_surface_t(rtn);
}

// cairo.cairo_copy_path(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_copy_path_gurax, "cairo_copy_path")
{
	Declare(VTYPE_cairo_path_t, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_copy_path_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	cairo_path_t* rtn = cairo_copy_path(cr);
	if (!rtn) return Value::nil();
	return new Value_cairo_path_t(rtn);
}

// cairo.cairo_copy_path_flat(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_copy_path_flat_gurax, "cairo_copy_path_flat")
{
	Declare(VTYPE_cairo_path_t, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_copy_path_flat_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	cairo_path_t* rtn = cairo_copy_path_flat(cr);
	if (!rtn) return Value::nil();
	return new Value_cairo_path_t(rtn);
}

// cairo.cairo_append_path(cr as cairo_t, path as cairo_path_t)
Gurax_DeclareFunctionAlias(cairo_append_path_gurax, "cairo_append_path")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("path", VTYPE_cairo_path_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_append_path_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	auto& value_path = args_gurax.Pick<Value_cairo_path_t>();
	const cairo_path_t* path = value_path.GetEntityPtr();
	// Function body
	cairo_append_path(cr, path);
	return Gurax::Value::nil();
}

// cairo.cairo_path_destroy(path as cairo_path_t)
Gurax_DeclareFunctionAlias(cairo_path_destroy_gurax, "cairo_path_destroy")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("path", VTYPE_cairo_path_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_path_destroy_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_path = args_gurax.Pick<Value_cairo_path_t>();
	cairo_path_t* path = value_path.GetEntityPtr();
	// Function body
	cairo_path_destroy(path);
	return Gurax::Value::nil();
}

// cairo.cairo_status(cr as cairo_t)
Gurax_DeclareFunctionAlias(cairo_status_gurax, "cairo_status")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("cr", VTYPE_cairo_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_status_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_cr = args_gurax.Pick<Value_cairo_t>();
	cairo_t* cr = value_cr.GetEntityPtr();
	// Function body
	cairo_status_t rtn = cairo_status(cr);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_status_to_string(status as Number)
Gurax_DeclareFunctionAlias(cairo_status_to_string_gurax, "cairo_status_to_string")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("status", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_status_to_string_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	cairo_status_t status = args_gurax.PickNumber<cairo_status_t>();
	// Function body
	const char* rtn = cairo_status_to_string(status);
	return new Gurax::Value_String(rtn);
}

// cairo.cairo_device_reference(device as cairo_device_t)
Gurax_DeclareFunctionAlias(cairo_device_reference_gurax, "cairo_device_reference")
{
	Declare(VTYPE_cairo_device_t, Flag::None);
	DeclareArg("device", VTYPE_cairo_device_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_device_reference_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_device = args_gurax.Pick<Value_cairo_device_t>();
	cairo_device_t* device = value_device.GetEntityPtr();
	// Function body
	cairo_device_t* rtn = cairo_device_reference(device);
	if (!rtn) return Value::nil();
	return new Value_cairo_device_t(rtn);
}

// cairo.cairo_device_get_type(device as cairo_device_t)
Gurax_DeclareFunctionAlias(cairo_device_get_type_gurax, "cairo_device_get_type")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("device", VTYPE_cairo_device_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_device_get_type_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_device = args_gurax.Pick<Value_cairo_device_t>();
	cairo_device_t* device = value_device.GetEntityPtr();
	// Function body
	cairo_device_type_t rtn = cairo_device_get_type(device);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_device_status(device as cairo_device_t)
Gurax_DeclareFunctionAlias(cairo_device_status_gurax, "cairo_device_status")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("device", VTYPE_cairo_device_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_device_status_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_device = args_gurax.Pick<Value_cairo_device_t>();
	cairo_device_t* device = value_device.GetEntityPtr();
	// Function body
	cairo_status_t rtn = cairo_device_status(device);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_device_acquire(device as cairo_device_t)
Gurax_DeclareFunctionAlias(cairo_device_acquire_gurax, "cairo_device_acquire")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("device", VTYPE_cairo_device_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_device_acquire_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_device = args_gurax.Pick<Value_cairo_device_t>();
	cairo_device_t* device = value_device.GetEntityPtr();
	// Function body
	cairo_status_t rtn = cairo_device_acquire(device);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_device_release(device as cairo_device_t)
Gurax_DeclareFunctionAlias(cairo_device_release_gurax, "cairo_device_release")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("device", VTYPE_cairo_device_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_device_release_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_device = args_gurax.Pick<Value_cairo_device_t>();
	cairo_device_t* device = value_device.GetEntityPtr();
	// Function body
	cairo_device_release(device);
	return Gurax::Value::nil();
}

// cairo.cairo_device_flush(device as cairo_device_t)
Gurax_DeclareFunctionAlias(cairo_device_flush_gurax, "cairo_device_flush")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("device", VTYPE_cairo_device_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_device_flush_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_device = args_gurax.Pick<Value_cairo_device_t>();
	cairo_device_t* device = value_device.GetEntityPtr();
	// Function body
	cairo_device_flush(device);
	return Gurax::Value::nil();
}

// cairo.cairo_device_finish(device as cairo_device_t)
Gurax_DeclareFunctionAlias(cairo_device_finish_gurax, "cairo_device_finish")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("device", VTYPE_cairo_device_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_device_finish_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_device = args_gurax.Pick<Value_cairo_device_t>();
	cairo_device_t* device = value_device.GetEntityPtr();
	// Function body
	cairo_device_finish(device);
	return Gurax::Value::nil();
}

// cairo.cairo_device_destroy(device as cairo_device_t)
Gurax_DeclareFunctionAlias(cairo_device_destroy_gurax, "cairo_device_destroy")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("device", VTYPE_cairo_device_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_device_destroy_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_device = args_gurax.Pick<Value_cairo_device_t>();
	cairo_device_t* device = value_device.GetEntityPtr();
	// Function body
	cairo_device_destroy(device);
	return Gurax::Value::nil();
}

// cairo.cairo_device_get_reference_count(device as cairo_device_t)
Gurax_DeclareFunctionAlias(cairo_device_get_reference_count_gurax, "cairo_device_get_reference_count")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("device", VTYPE_cairo_device_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_device_get_reference_count_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_device = args_gurax.Pick<Value_cairo_device_t>();
	cairo_device_t* device = value_device.GetEntityPtr();
	// Function body
	unsigned int rtn = cairo_device_get_reference_count(device);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_surface_create_similar(other as cairo_surface_t, content as Number, width as Number, height as Number)
Gurax_DeclareFunctionAlias(cairo_surface_create_similar_gurax, "cairo_surface_create_similar")
{
	Declare(VTYPE_cairo_surface_t, Flag::None);
	DeclareArg("other", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("content", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_surface_create_similar_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_other = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* other = value_other.GetEntityPtr();
	cairo_content_t content = args_gurax.PickNumber<cairo_content_t>();
	int width = args_gurax.PickNumber<int>();
	int height = args_gurax.PickNumber<int>();
	// Function body
	cairo_surface_t* rtn = cairo_surface_create_similar(other, content, width, height);
	if (!rtn) return Value::nil();
	return new Value_cairo_surface_t(rtn);
}

// cairo.cairo_surface_create_similar_image(other as cairo_surface_t, format as Number, width as Number, height as Number)
Gurax_DeclareFunctionAlias(cairo_surface_create_similar_image_gurax, "cairo_surface_create_similar_image")
{
	Declare(VTYPE_cairo_surface_t, Flag::None);
	DeclareArg("other", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_surface_create_similar_image_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_other = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* other = value_other.GetEntityPtr();
	cairo_format_t format = args_gurax.PickNumber<cairo_format_t>();
	int width = args_gurax.PickNumber<int>();
	int height = args_gurax.PickNumber<int>();
	// Function body
	cairo_surface_t* rtn = cairo_surface_create_similar_image(other, format, width, height);
	if (!rtn) return Value::nil();
	return new Value_cairo_surface_t(rtn);
}

// cairo.cairo_surface_map_to_image(surface as cairo_surface_t, extents as cairo_rectangle_int_t)
Gurax_DeclareFunctionAlias(cairo_surface_map_to_image_gurax, "cairo_surface_map_to_image")
{
	Declare(VTYPE_cairo_surface_t, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("extents", VTYPE_cairo_rectangle_int_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_surface_map_to_image_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	auto& value_extents = args_gurax.Pick<Value_cairo_rectangle_int_t>();
	const cairo_rectangle_int_t* extents = value_extents.GetEntityPtr();
	// Function body
	cairo_surface_t* rtn = cairo_surface_map_to_image(surface, extents);
	if (!rtn) return Value::nil();
	return new Value_cairo_surface_t(rtn);
}

// cairo.cairo_surface_unmap_image(surface as cairo_surface_t, image as cairo_surface_t)
Gurax_DeclareFunctionAlias(cairo_surface_unmap_image_gurax, "cairo_surface_unmap_image")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("image", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_surface_unmap_image_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	auto& value_image = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* image = value_image.GetEntityPtr();
	// Function body
	cairo_surface_unmap_image(surface, image);
	return Gurax::Value::nil();
}

// cairo.cairo_surface_create_for_rectangle(target as cairo_surface_t, x as Number, y as Number, width as Number, height as Number)
Gurax_DeclareFunctionAlias(cairo_surface_create_for_rectangle_gurax, "cairo_surface_create_for_rectangle")
{
	Declare(VTYPE_cairo_surface_t, Flag::None);
	DeclareArg("target", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_surface_create_for_rectangle_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_target = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* target = value_target.GetEntityPtr();
	double x = args_gurax.PickNumber<double>();
	double y = args_gurax.PickNumber<double>();
	double width = args_gurax.PickNumber<double>();
	double height = args_gurax.PickNumber<double>();
	// Function body
	cairo_surface_t* rtn = cairo_surface_create_for_rectangle(target, x, y, width, height);
	if (!rtn) return Value::nil();
	return new Value_cairo_surface_t(rtn);
}

// cairo.cairo_surface_create_observer(target as cairo_surface_t, mode as Number)
Gurax_DeclareFunctionAlias(cairo_surface_create_observer_gurax, "cairo_surface_create_observer")
{
	Declare(VTYPE_cairo_surface_t, Flag::None);
	DeclareArg("target", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_surface_create_observer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_target = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* target = value_target.GetEntityPtr();
	cairo_surface_observer_mode_t mode = args_gurax.PickNumber<cairo_surface_observer_mode_t>();
	// Function body
	cairo_surface_t* rtn = cairo_surface_create_observer(target, mode);
	if (!rtn) return Value::nil();
	return new Value_cairo_surface_t(rtn);
}

// cairo.cairo_surface_observer_elapsed(surface as cairo_surface_t)
Gurax_DeclareFunctionAlias(cairo_surface_observer_elapsed_gurax, "cairo_surface_observer_elapsed")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_surface_observer_elapsed_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	// Function body
	double rtn = cairo_surface_observer_elapsed(surface);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_device_observer_elapsed(device as cairo_device_t)
Gurax_DeclareFunctionAlias(cairo_device_observer_elapsed_gurax, "cairo_device_observer_elapsed")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("device", VTYPE_cairo_device_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_device_observer_elapsed_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_device = args_gurax.Pick<Value_cairo_device_t>();
	cairo_device_t* device = value_device.GetEntityPtr();
	// Function body
	double rtn = cairo_device_observer_elapsed(device);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_device_observer_paint_elapsed(device as cairo_device_t)
Gurax_DeclareFunctionAlias(cairo_device_observer_paint_elapsed_gurax, "cairo_device_observer_paint_elapsed")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("device", VTYPE_cairo_device_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_device_observer_paint_elapsed_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_device = args_gurax.Pick<Value_cairo_device_t>();
	cairo_device_t* device = value_device.GetEntityPtr();
	// Function body
	double rtn = cairo_device_observer_paint_elapsed(device);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_device_observer_mask_elapsed(device as cairo_device_t)
Gurax_DeclareFunctionAlias(cairo_device_observer_mask_elapsed_gurax, "cairo_device_observer_mask_elapsed")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("device", VTYPE_cairo_device_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_device_observer_mask_elapsed_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_device = args_gurax.Pick<Value_cairo_device_t>();
	cairo_device_t* device = value_device.GetEntityPtr();
	// Function body
	double rtn = cairo_device_observer_mask_elapsed(device);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_device_observer_fill_elapsed(device as cairo_device_t)
Gurax_DeclareFunctionAlias(cairo_device_observer_fill_elapsed_gurax, "cairo_device_observer_fill_elapsed")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("device", VTYPE_cairo_device_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_device_observer_fill_elapsed_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_device = args_gurax.Pick<Value_cairo_device_t>();
	cairo_device_t* device = value_device.GetEntityPtr();
	// Function body
	double rtn = cairo_device_observer_fill_elapsed(device);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_device_observer_stroke_elapsed(device as cairo_device_t)
Gurax_DeclareFunctionAlias(cairo_device_observer_stroke_elapsed_gurax, "cairo_device_observer_stroke_elapsed")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("device", VTYPE_cairo_device_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_device_observer_stroke_elapsed_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_device = args_gurax.Pick<Value_cairo_device_t>();
	cairo_device_t* device = value_device.GetEntityPtr();
	// Function body
	double rtn = cairo_device_observer_stroke_elapsed(device);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_device_observer_glyphs_elapsed(device as cairo_device_t)
Gurax_DeclareFunctionAlias(cairo_device_observer_glyphs_elapsed_gurax, "cairo_device_observer_glyphs_elapsed")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("device", VTYPE_cairo_device_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_device_observer_glyphs_elapsed_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_device = args_gurax.Pick<Value_cairo_device_t>();
	cairo_device_t* device = value_device.GetEntityPtr();
	// Function body
	double rtn = cairo_device_observer_glyphs_elapsed(device);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_surface_reference(surface as cairo_surface_t)
Gurax_DeclareFunctionAlias(cairo_surface_reference_gurax, "cairo_surface_reference")
{
	Declare(VTYPE_cairo_surface_t, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_surface_reference_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	// Function body
	cairo_surface_t* rtn = cairo_surface_reference(surface);
	if (!rtn) return Value::nil();
	return new Value_cairo_surface_t(rtn);
}

// cairo.cairo_surface_finish(surface as cairo_surface_t)
Gurax_DeclareFunctionAlias(cairo_surface_finish_gurax, "cairo_surface_finish")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_surface_finish_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	// Function body
	cairo_surface_finish(surface);
	return Gurax::Value::nil();
}

// cairo.cairo_surface_destroy(surface as cairo_surface_t)
Gurax_DeclareFunctionAlias(cairo_surface_destroy_gurax, "cairo_surface_destroy")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_surface_destroy_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	// Function body
	cairo_surface_destroy(surface);
	return Gurax::Value::nil();
}

// cairo.cairo_surface_get_device(surface as cairo_surface_t)
Gurax_DeclareFunctionAlias(cairo_surface_get_device_gurax, "cairo_surface_get_device")
{
	Declare(VTYPE_cairo_device_t, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_surface_get_device_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	// Function body
	cairo_device_t* rtn = cairo_surface_get_device(surface);
	if (!rtn) return Value::nil();
	return new Value_cairo_device_t(rtn);
}

// cairo.cairo_surface_get_reference_count(surface as cairo_surface_t)
Gurax_DeclareFunctionAlias(cairo_surface_get_reference_count_gurax, "cairo_surface_get_reference_count")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_surface_get_reference_count_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	// Function body
	unsigned int rtn = cairo_surface_get_reference_count(surface);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_surface_status(surface as cairo_surface_t)
Gurax_DeclareFunctionAlias(cairo_surface_status_gurax, "cairo_surface_status")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_surface_status_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	// Function body
	cairo_status_t rtn = cairo_surface_status(surface);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_surface_get_type(surface as cairo_surface_t)
Gurax_DeclareFunctionAlias(cairo_surface_get_type_gurax, "cairo_surface_get_type")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_surface_get_type_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	// Function body
	cairo_surface_type_t rtn = cairo_surface_get_type(surface);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_surface_get_content(surface as cairo_surface_t)
Gurax_DeclareFunctionAlias(cairo_surface_get_content_gurax, "cairo_surface_get_content")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_surface_get_content_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	// Function body
	cairo_content_t rtn = cairo_surface_get_content(surface);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_surface_write_to_png(surface as cairo_surface_t, filename as String)
Gurax_DeclareFunctionAlias(cairo_surface_write_to_png_gurax, "cairo_surface_write_to_png")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("filename", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_surface_write_to_png_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	const char* filename = args_gurax.PickString();
	// Function body
	cairo_status_t rtn = cairo_surface_write_to_png(surface, filename);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_surface_write_to_png_stream(surface as cairo_surface_t, stream:w as Stream)
Gurax_DeclareFunctionAlias(cairo_surface_write_to_png_stream_gurax, "cairo_surface_write_to_png_stream")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamW);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_surface_write_to_png_stream_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	RefPtr<Stream> stream(args_gurax.PickStream().Reference());
	// Function body
	cairo_status_t rtn = cairo_surface_write_to_png_stream(surface, write_func, stream.get());
	return new Value_Number(rtn);
}

// cairo.cairo_surface_get_mime_data(surface as cairo_surface_t, mime_type as String)
Gurax_DeclareFunctionAlias(cairo_surface_get_mime_data_gurax, "cairo_surface_get_mime_data")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mime_type", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_surface_get_mime_data_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	const char* mime_type = args_gurax.PickString();
	// Function body
	const unsigned char* data;
	unsigned long length;
	cairo_surface_get_mime_data(surface, mime_type, &data, &length);
	return new Value_Binary(Binary(data, length));
}

// cairo.cairo_surface_supports_mime_type(surface as cairo_surface_t, mime_type as String)
Gurax_DeclareFunctionAlias(cairo_surface_supports_mime_type_gurax, "cairo_surface_supports_mime_type")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mime_type", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_surface_supports_mime_type_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	const char* mime_type = args_gurax.PickString();
	// Function body
	cairo_bool_t rtn = cairo_surface_supports_mime_type(surface, mime_type);
	return new Gurax::Value_Bool(!!rtn);
}

// cairo.cairo_surface_get_font_options(surface as cairo_surface_t, options as cairo_font_options_t)
Gurax_DeclareFunctionAlias(cairo_surface_get_font_options_gurax, "cairo_surface_get_font_options")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("options", VTYPE_cairo_font_options_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_surface_get_font_options_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	auto& value_options = args_gurax.Pick<Value_cairo_font_options_t>();
	cairo_font_options_t* options = value_options.GetEntityPtr();
	// Function body
	cairo_surface_get_font_options(surface, options);
	return Gurax::Value::nil();
}

// cairo.cairo_surface_flush(surface as cairo_surface_t)
Gurax_DeclareFunctionAlias(cairo_surface_flush_gurax, "cairo_surface_flush")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_surface_flush_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	// Function body
	cairo_surface_flush(surface);
	return Gurax::Value::nil();
}

// cairo.cairo_surface_mark_dirty(surface as cairo_surface_t)
Gurax_DeclareFunctionAlias(cairo_surface_mark_dirty_gurax, "cairo_surface_mark_dirty")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_surface_mark_dirty_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	// Function body
	cairo_surface_mark_dirty(surface);
	return Gurax::Value::nil();
}

// cairo.cairo_surface_mark_dirty_rectangle(surface as cairo_surface_t, x as Number, y as Number, width as Number, height as Number)
Gurax_DeclareFunctionAlias(cairo_surface_mark_dirty_rectangle_gurax, "cairo_surface_mark_dirty_rectangle")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_surface_mark_dirty_rectangle_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	int x = args_gurax.PickNumber<int>();
	int y = args_gurax.PickNumber<int>();
	int width = args_gurax.PickNumber<int>();
	int height = args_gurax.PickNumber<int>();
	// Function body
	cairo_surface_mark_dirty_rectangle(surface, x, y, width, height);
	return Gurax::Value::nil();
}

// cairo.cairo_surface_set_device_scale(surface as cairo_surface_t, x_scale as Number, y_scale as Number)
Gurax_DeclareFunctionAlias(cairo_surface_set_device_scale_gurax, "cairo_surface_set_device_scale")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x_scale", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y_scale", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_surface_set_device_scale_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	double x_scale = args_gurax.PickNumber<double>();
	double y_scale = args_gurax.PickNumber<double>();
	// Function body
	cairo_surface_set_device_scale(surface, x_scale, y_scale);
	return Gurax::Value::nil();
}

// cairo.cairo_surface_get_device_scale(surface as cairo_surface_t)
Gurax_DeclareFunctionAlias(cairo_surface_get_device_scale_gurax, "cairo_surface_get_device_scale")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_surface_get_device_scale_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	// Function body
	double x_scale, y_scale;
	cairo_surface_get_device_scale(surface, &x_scale, &y_scale);
	return Value_Tuple::Create(new Value_Number(x_scale), new Value_Number(y_scale));
}

// cairo.cairo_surface_set_device_offset(surface as cairo_surface_t, x_offset as Number, y_offset as Number)
Gurax_DeclareFunctionAlias(cairo_surface_set_device_offset_gurax, "cairo_surface_set_device_offset")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x_offset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y_offset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_surface_set_device_offset_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	double x_offset = args_gurax.PickNumber<double>();
	double y_offset = args_gurax.PickNumber<double>();
	// Function body
	cairo_surface_set_device_offset(surface, x_offset, y_offset);
	return Gurax::Value::nil();
}

// cairo.cairo_surface_get_device_offset(surface as cairo_surface_t)
Gurax_DeclareFunctionAlias(cairo_surface_get_device_offset_gurax, "cairo_surface_get_device_offset")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_surface_get_device_offset_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	// Function body
	double x_offset, y_offset;
	cairo_surface_get_device_offset(surface, &x_offset, &y_offset);
	return Value_Tuple::Create(new Value_Number(x_offset), new Value_Number(y_offset));
}

// cairo.cairo_surface_set_fallback_resolution(surface as cairo_surface_t, x_pixels_per_inch as Number, y_pixels_per_inch as Number)
Gurax_DeclareFunctionAlias(cairo_surface_set_fallback_resolution_gurax, "cairo_surface_set_fallback_resolution")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x_pixels_per_inch", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y_pixels_per_inch", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_surface_set_fallback_resolution_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	double x_pixels_per_inch = args_gurax.PickNumber<double>();
	double y_pixels_per_inch = args_gurax.PickNumber<double>();
	// Function body
	cairo_surface_set_fallback_resolution(surface, x_pixels_per_inch, y_pixels_per_inch);
	return Gurax::Value::nil();
}

// cairo.cairo_surface_get_fallback_resolution(surface as cairo_surface_t)
Gurax_DeclareFunctionAlias(cairo_surface_get_fallback_resolution_gurax, "cairo_surface_get_fallback_resolution")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_surface_get_fallback_resolution_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	// Function body
	double x_pixels_per_inch, y_pixels_per_inch;
	cairo_surface_get_device_offset(surface, &x_pixels_per_inch, &y_pixels_per_inch);
	return Value_Tuple::Create(new Value_Number(x_pixels_per_inch), new Value_Number(y_pixels_per_inch));
}

// cairo.cairo_surface_copy_page(surface as cairo_surface_t)
Gurax_DeclareFunctionAlias(cairo_surface_copy_page_gurax, "cairo_surface_copy_page")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_surface_copy_page_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	// Function body
	cairo_surface_copy_page(surface);
	return Gurax::Value::nil();
}

// cairo.cairo_surface_show_page(surface as cairo_surface_t)
Gurax_DeclareFunctionAlias(cairo_surface_show_page_gurax, "cairo_surface_show_page")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_surface_show_page_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	// Function body
	cairo_surface_show_page(surface);
	return Gurax::Value::nil();
}

// cairo.cairo_surface_has_show_text_glyphs(surface as cairo_surface_t)
Gurax_DeclareFunctionAlias(cairo_surface_has_show_text_glyphs_gurax, "cairo_surface_has_show_text_glyphs")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_surface_has_show_text_glyphs_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	// Function body
	cairo_bool_t rtn = cairo_surface_has_show_text_glyphs(surface);
	return new Gurax::Value_Bool(!!rtn);
}

// cairo.cairo_image_surface_create(format as Number, width as Number, height as Number)
Gurax_DeclareFunctionAlias(cairo_image_surface_create_gurax, "cairo_image_surface_create")
{
	Declare(VTYPE_cairo_surface_t, Flag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_image_surface_create_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	cairo_format_t format = args_gurax.PickNumber<cairo_format_t>();
	int width = args_gurax.PickNumber<int>();
	int height = args_gurax.PickNumber<int>();
	// Function body
	cairo_surface_t* rtn = cairo_image_surface_create(format, width, height);
	if (!rtn) return Value::nil();
	return new Value_cairo_surface_t(rtn);
}

// cairo.cairo_format_stride_for_width(format as Number, width as Number)
Gurax_DeclareFunctionAlias(cairo_format_stride_for_width_gurax, "cairo_format_stride_for_width")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("format", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_format_stride_for_width_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	cairo_format_t format = args_gurax.PickNumber<cairo_format_t>();
	int width = args_gurax.PickNumber<int>();
	// Function body
	int rtn = cairo_format_stride_for_width(format, width);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_image_surface_get_format(surface as cairo_surface_t)
Gurax_DeclareFunctionAlias(cairo_image_surface_get_format_gurax, "cairo_image_surface_get_format")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_image_surface_get_format_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	// Function body
	cairo_format_t rtn = cairo_image_surface_get_format(surface);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_image_surface_get_width(surface as cairo_surface_t)
Gurax_DeclareFunctionAlias(cairo_image_surface_get_width_gurax, "cairo_image_surface_get_width")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_image_surface_get_width_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	// Function body
	int rtn = cairo_image_surface_get_width(surface);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_image_surface_get_height(surface as cairo_surface_t)
Gurax_DeclareFunctionAlias(cairo_image_surface_get_height_gurax, "cairo_image_surface_get_height")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_image_surface_get_height_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	// Function body
	int rtn = cairo_image_surface_get_height(surface);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_image_surface_get_stride(surface as cairo_surface_t)
Gurax_DeclareFunctionAlias(cairo_image_surface_get_stride_gurax, "cairo_image_surface_get_stride")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_image_surface_get_stride_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	// Function body
	int rtn = cairo_image_surface_get_stride(surface);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_image_surface_create_from_png(filename as String)
Gurax_DeclareFunctionAlias(cairo_image_surface_create_from_png_gurax, "cairo_image_surface_create_from_png")
{
	Declare(VTYPE_cairo_surface_t, Flag::None);
	DeclareArg("filename", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_image_surface_create_from_png_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* filename = args_gurax.PickString();
	// Function body
	cairo_surface_t* rtn = cairo_image_surface_create_from_png(filename);
	if (!rtn) return Value::nil();
	return new Value_cairo_surface_t(rtn);
}

// cairo.cairo_recording_surface_create(content as Number, extents as cairo_rectangle_t)
Gurax_DeclareFunctionAlias(cairo_recording_surface_create_gurax, "cairo_recording_surface_create")
{
	Declare(VTYPE_cairo_surface_t, Flag::None);
	DeclareArg("content", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("extents", VTYPE_cairo_rectangle_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_recording_surface_create_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	cairo_content_t content = args_gurax.PickNumber<cairo_content_t>();
	auto& value_extents = args_gurax.Pick<Value_cairo_rectangle_t>();
	const cairo_rectangle_t* extents = value_extents.GetEntityPtr();
	// Function body
	cairo_surface_t* rtn = cairo_recording_surface_create(content, extents);
	if (!rtn) return Value::nil();
	return new Value_cairo_surface_t(rtn);
}

// cairo.cairo_recording_surface_get_extents(surface as cairo_surface_t, extents as cairo_rectangle_t)
Gurax_DeclareFunctionAlias(cairo_recording_surface_get_extents_gurax, "cairo_recording_surface_get_extents")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("extents", VTYPE_cairo_rectangle_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_recording_surface_get_extents_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	auto& value_extents = args_gurax.Pick<Value_cairo_rectangle_t>();
	cairo_rectangle_t* extents = value_extents.GetEntityPtr();
	// Function body
	cairo_bool_t rtn = cairo_recording_surface_get_extents(surface, extents);
	return new Gurax::Value_Bool(!!rtn);
}

// cairo.cairo_pattern_create_raster_source(user_data as Pointer, content as Number, width as Number, height as Number)
Gurax_DeclareFunctionAlias(cairo_pattern_create_raster_source_gurax, "cairo_pattern_create_raster_source")
{
	Declare(VTYPE_cairo_pattern_t, Flag::None);
	DeclareArg("user_data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("content", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_pattern_create_raster_source_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	void* user_data = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetWritablePointerC<void>();
	if (!user_data) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	cairo_content_t content = args_gurax.PickNumber<cairo_content_t>();
	int width = args_gurax.PickNumber<int>();
	int height = args_gurax.PickNumber<int>();
	// Function body
	cairo_pattern_t* rtn = cairo_pattern_create_raster_source(user_data, content, width, height);
	if (!rtn) return Value::nil();
	return new Value_cairo_pattern_t(rtn);
}

// cairo.cairo_raster_source_pattern_set_callback_data(pattern as cairo_pattern_t, data as Pointer)
Gurax_DeclareFunctionAlias(cairo_raster_source_pattern_set_callback_data_gurax, "cairo_raster_source_pattern_set_callback_data")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pattern", VTYPE_cairo_pattern_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_raster_source_pattern_set_callback_data_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_pattern = args_gurax.Pick<Value_cairo_pattern_t>();
	cairo_pattern_t* pattern = value_pattern.GetEntityPtr();
	void* data = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetWritablePointerC<void>();
	if (!data) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	cairo_raster_source_pattern_set_callback_data(pattern, data);
	return Gurax::Value::nil();
}

// cairo.cairo_pattern_create_rgb(red as Number, green as Number, blue as Number)
Gurax_DeclareFunctionAlias(cairo_pattern_create_rgb_gurax, "cairo_pattern_create_rgb")
{
	Declare(VTYPE_cairo_pattern_t, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_pattern_create_rgb_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	double red = args_gurax.PickNumber<double>();
	double green = args_gurax.PickNumber<double>();
	double blue = args_gurax.PickNumber<double>();
	// Function body
	cairo_pattern_t* rtn = cairo_pattern_create_rgb(red, green, blue);
	if (!rtn) return Value::nil();
	return new Value_cairo_pattern_t(rtn);
}

// cairo.cairo_pattern_create_rgba(red as Number, green as Number, blue as Number, alpha as Number)
Gurax_DeclareFunctionAlias(cairo_pattern_create_rgba_gurax, "cairo_pattern_create_rgba")
{
	Declare(VTYPE_cairo_pattern_t, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("alpha", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_pattern_create_rgba_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	double red = args_gurax.PickNumber<double>();
	double green = args_gurax.PickNumber<double>();
	double blue = args_gurax.PickNumber<double>();
	double alpha = args_gurax.PickNumber<double>();
	// Function body
	cairo_pattern_t* rtn = cairo_pattern_create_rgba(red, green, blue, alpha);
	if (!rtn) return Value::nil();
	return new Value_cairo_pattern_t(rtn);
}

// cairo.cairo_pattern_create_for_surface(surface as cairo_surface_t)
Gurax_DeclareFunctionAlias(cairo_pattern_create_for_surface_gurax, "cairo_pattern_create_for_surface")
{
	Declare(VTYPE_cairo_pattern_t, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_pattern_create_for_surface_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	// Function body
	cairo_pattern_t* rtn = cairo_pattern_create_for_surface(surface);
	if (!rtn) return Value::nil();
	return new Value_cairo_pattern_t(rtn);
}

// cairo.cairo_pattern_create_linear(x0 as Number, y0 as Number, x1 as Number, y1 as Number)
Gurax_DeclareFunctionAlias(cairo_pattern_create_linear_gurax, "cairo_pattern_create_linear")
{
	Declare(VTYPE_cairo_pattern_t, Flag::None);
	DeclareArg("x0", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y0", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_pattern_create_linear_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	double x0 = args_gurax.PickNumber<double>();
	double y0 = args_gurax.PickNumber<double>();
	double x1 = args_gurax.PickNumber<double>();
	double y1 = args_gurax.PickNumber<double>();
	// Function body
	cairo_pattern_t* rtn = cairo_pattern_create_linear(x0, y0, x1, y1);
	if (!rtn) return Value::nil();
	return new Value_cairo_pattern_t(rtn);
}

// cairo.cairo_pattern_create_radial(cx0 as Number, cy0 as Number, radius0 as Number, cx1 as Number, cy1 as Number, radius1 as Number)
Gurax_DeclareFunctionAlias(cairo_pattern_create_radial_gurax, "cairo_pattern_create_radial")
{
	Declare(VTYPE_cairo_pattern_t, Flag::None);
	DeclareArg("cx0", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("cy0", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("radius0", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("cx1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("cy1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("radius1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_pattern_create_radial_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	double cx0 = args_gurax.PickNumber<double>();
	double cy0 = args_gurax.PickNumber<double>();
	double radius0 = args_gurax.PickNumber<double>();
	double cx1 = args_gurax.PickNumber<double>();
	double cy1 = args_gurax.PickNumber<double>();
	double radius1 = args_gurax.PickNumber<double>();
	// Function body
	cairo_pattern_t* rtn = cairo_pattern_create_radial(cx0, cy0, radius0, cx1, cy1, radius1);
	if (!rtn) return Value::nil();
	return new Value_cairo_pattern_t(rtn);
}

// cairo.cairo_pattern_create_mesh()
Gurax_DeclareFunctionAlias(cairo_pattern_create_mesh_gurax, "cairo_pattern_create_mesh")
{
	Declare(VTYPE_cairo_pattern_t, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_pattern_create_mesh_gurax, processor_gurax, argument_gurax)
{
	// Function body
	cairo_pattern_t* rtn = cairo_pattern_create_mesh();
	if (!rtn) return Value::nil();
	return new Value_cairo_pattern_t(rtn);
}

// cairo.cairo_pattern_reference(pattern as cairo_pattern_t)
Gurax_DeclareFunctionAlias(cairo_pattern_reference_gurax, "cairo_pattern_reference")
{
	Declare(VTYPE_cairo_pattern_t, Flag::None);
	DeclareArg("pattern", VTYPE_cairo_pattern_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_pattern_reference_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_pattern = args_gurax.Pick<Value_cairo_pattern_t>();
	cairo_pattern_t* pattern = value_pattern.GetEntityPtr();
	// Function body
	cairo_pattern_t* rtn = cairo_pattern_reference(pattern);
	if (!rtn) return Value::nil();
	return new Value_cairo_pattern_t(rtn);
}

// cairo.cairo_pattern_destroy(pattern as cairo_pattern_t)
Gurax_DeclareFunctionAlias(cairo_pattern_destroy_gurax, "cairo_pattern_destroy")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pattern", VTYPE_cairo_pattern_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_pattern_destroy_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_pattern = args_gurax.Pick<Value_cairo_pattern_t>();
	cairo_pattern_t* pattern = value_pattern.GetEntityPtr();
	// Function body
	cairo_pattern_destroy(pattern);
	return Gurax::Value::nil();
}

// cairo.cairo_pattern_get_reference_count(pattern as cairo_pattern_t)
Gurax_DeclareFunctionAlias(cairo_pattern_get_reference_count_gurax, "cairo_pattern_get_reference_count")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("pattern", VTYPE_cairo_pattern_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_pattern_get_reference_count_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_pattern = args_gurax.Pick<Value_cairo_pattern_t>();
	cairo_pattern_t* pattern = value_pattern.GetEntityPtr();
	// Function body
	unsigned int rtn = cairo_pattern_get_reference_count(pattern);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_pattern_status(pattern as cairo_pattern_t)
Gurax_DeclareFunctionAlias(cairo_pattern_status_gurax, "cairo_pattern_status")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("pattern", VTYPE_cairo_pattern_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_pattern_status_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_pattern = args_gurax.Pick<Value_cairo_pattern_t>();
	cairo_pattern_t* pattern = value_pattern.GetEntityPtr();
	// Function body
	cairo_status_t rtn = cairo_pattern_status(pattern);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_pattern_get_type(pattern as cairo_pattern_t)
Gurax_DeclareFunctionAlias(cairo_pattern_get_type_gurax, "cairo_pattern_get_type")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("pattern", VTYPE_cairo_pattern_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_pattern_get_type_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_pattern = args_gurax.Pick<Value_cairo_pattern_t>();
	cairo_pattern_t* pattern = value_pattern.GetEntityPtr();
	// Function body
	cairo_pattern_type_t rtn = cairo_pattern_get_type(pattern);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_pattern_add_color_stop_rgb(pattern as cairo_pattern_t, offset as Number, red as Number, green as Number, blue as Number)
Gurax_DeclareFunctionAlias(cairo_pattern_add_color_stop_rgb_gurax, "cairo_pattern_add_color_stop_rgb")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pattern", VTYPE_cairo_pattern_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("offset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_pattern_add_color_stop_rgb_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_pattern = args_gurax.Pick<Value_cairo_pattern_t>();
	cairo_pattern_t* pattern = value_pattern.GetEntityPtr();
	double offset = args_gurax.PickNumber<double>();
	double red = args_gurax.PickNumber<double>();
	double green = args_gurax.PickNumber<double>();
	double blue = args_gurax.PickNumber<double>();
	// Function body
	cairo_pattern_add_color_stop_rgb(pattern, offset, red, green, blue);
	return Gurax::Value::nil();
}

// cairo.cairo_pattern_add_color_stop_rgba(pattern as cairo_pattern_t, offset as Number, red as Number, green as Number, blue as Number, alpha as Number)
Gurax_DeclareFunctionAlias(cairo_pattern_add_color_stop_rgba_gurax, "cairo_pattern_add_color_stop_rgba")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pattern", VTYPE_cairo_pattern_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("offset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("alpha", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_pattern_add_color_stop_rgba_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_pattern = args_gurax.Pick<Value_cairo_pattern_t>();
	cairo_pattern_t* pattern = value_pattern.GetEntityPtr();
	double offset = args_gurax.PickNumber<double>();
	double red = args_gurax.PickNumber<double>();
	double green = args_gurax.PickNumber<double>();
	double blue = args_gurax.PickNumber<double>();
	double alpha = args_gurax.PickNumber<double>();
	// Function body
	cairo_pattern_add_color_stop_rgba(pattern, offset, red, green, blue, alpha);
	return Gurax::Value::nil();
}

// cairo.cairo_mesh_pattern_begin_patch(pattern as cairo_pattern_t)
Gurax_DeclareFunctionAlias(cairo_mesh_pattern_begin_patch_gurax, "cairo_mesh_pattern_begin_patch")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pattern", VTYPE_cairo_pattern_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_mesh_pattern_begin_patch_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_pattern = args_gurax.Pick<Value_cairo_pattern_t>();
	cairo_pattern_t* pattern = value_pattern.GetEntityPtr();
	// Function body
	cairo_mesh_pattern_begin_patch(pattern);
	return Gurax::Value::nil();
}

// cairo.cairo_mesh_pattern_end_patch(pattern as cairo_pattern_t)
Gurax_DeclareFunctionAlias(cairo_mesh_pattern_end_patch_gurax, "cairo_mesh_pattern_end_patch")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pattern", VTYPE_cairo_pattern_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_mesh_pattern_end_patch_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_pattern = args_gurax.Pick<Value_cairo_pattern_t>();
	cairo_pattern_t* pattern = value_pattern.GetEntityPtr();
	// Function body
	cairo_mesh_pattern_end_patch(pattern);
	return Gurax::Value::nil();
}

// cairo.cairo_mesh_pattern_curve_to(pattern as cairo_pattern_t, x1 as Number, y1 as Number, x2 as Number, y2 as Number, x3 as Number, y3 as Number)
Gurax_DeclareFunctionAlias(cairo_mesh_pattern_curve_to_gurax, "cairo_mesh_pattern_curve_to")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pattern", VTYPE_cairo_pattern_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x3", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y3", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_mesh_pattern_curve_to_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_pattern = args_gurax.Pick<Value_cairo_pattern_t>();
	cairo_pattern_t* pattern = value_pattern.GetEntityPtr();
	double x1 = args_gurax.PickNumber<double>();
	double y1 = args_gurax.PickNumber<double>();
	double x2 = args_gurax.PickNumber<double>();
	double y2 = args_gurax.PickNumber<double>();
	double x3 = args_gurax.PickNumber<double>();
	double y3 = args_gurax.PickNumber<double>();
	// Function body
	cairo_mesh_pattern_curve_to(pattern, x1, y1, x2, y2, x3, y3);
	return Gurax::Value::nil();
}

// cairo.cairo_mesh_pattern_line_to(pattern as cairo_pattern_t, x as Number, y as Number)
Gurax_DeclareFunctionAlias(cairo_mesh_pattern_line_to_gurax, "cairo_mesh_pattern_line_to")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pattern", VTYPE_cairo_pattern_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_mesh_pattern_line_to_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_pattern = args_gurax.Pick<Value_cairo_pattern_t>();
	cairo_pattern_t* pattern = value_pattern.GetEntityPtr();
	double x = args_gurax.PickNumber<double>();
	double y = args_gurax.PickNumber<double>();
	// Function body
	cairo_mesh_pattern_line_to(pattern, x, y);
	return Gurax::Value::nil();
}

// cairo.cairo_mesh_pattern_move_to(pattern as cairo_pattern_t, x as Number, y as Number)
Gurax_DeclareFunctionAlias(cairo_mesh_pattern_move_to_gurax, "cairo_mesh_pattern_move_to")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pattern", VTYPE_cairo_pattern_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_mesh_pattern_move_to_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_pattern = args_gurax.Pick<Value_cairo_pattern_t>();
	cairo_pattern_t* pattern = value_pattern.GetEntityPtr();
	double x = args_gurax.PickNumber<double>();
	double y = args_gurax.PickNumber<double>();
	// Function body
	cairo_mesh_pattern_move_to(pattern, x, y);
	return Gurax::Value::nil();
}

// cairo.cairo_mesh_pattern_set_control_point(pattern as cairo_pattern_t, point_num as Number, x as Number, y as Number)
Gurax_DeclareFunctionAlias(cairo_mesh_pattern_set_control_point_gurax, "cairo_mesh_pattern_set_control_point")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pattern", VTYPE_cairo_pattern_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("point_num", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_mesh_pattern_set_control_point_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_pattern = args_gurax.Pick<Value_cairo_pattern_t>();
	cairo_pattern_t* pattern = value_pattern.GetEntityPtr();
	unsigned int point_num = args_gurax.PickNumber<unsigned int>();
	double x = args_gurax.PickNumber<double>();
	double y = args_gurax.PickNumber<double>();
	// Function body
	cairo_mesh_pattern_set_control_point(pattern, point_num, x, y);
	return Gurax::Value::nil();
}

// cairo.cairo_mesh_pattern_set_corner_color_rgb(pattern as cairo_pattern_t, corner_num as Number, red as Number, green as Number, blue as Number)
Gurax_DeclareFunctionAlias(cairo_mesh_pattern_set_corner_color_rgb_gurax, "cairo_mesh_pattern_set_corner_color_rgb")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pattern", VTYPE_cairo_pattern_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("corner_num", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_mesh_pattern_set_corner_color_rgb_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_pattern = args_gurax.Pick<Value_cairo_pattern_t>();
	cairo_pattern_t* pattern = value_pattern.GetEntityPtr();
	unsigned int corner_num = args_gurax.PickNumber<unsigned int>();
	double red = args_gurax.PickNumber<double>();
	double green = args_gurax.PickNumber<double>();
	double blue = args_gurax.PickNumber<double>();
	// Function body
	cairo_mesh_pattern_set_corner_color_rgb(pattern, corner_num, red, green, blue);
	return Gurax::Value::nil();
}

// cairo.cairo_mesh_pattern_set_corner_color_rgba(pattern as cairo_pattern_t, corner_num as Number, red as Number, green as Number, blue as Number, alpha as Number)
Gurax_DeclareFunctionAlias(cairo_mesh_pattern_set_corner_color_rgba_gurax, "cairo_mesh_pattern_set_corner_color_rgba")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pattern", VTYPE_cairo_pattern_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("corner_num", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("alpha", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_mesh_pattern_set_corner_color_rgba_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_pattern = args_gurax.Pick<Value_cairo_pattern_t>();
	cairo_pattern_t* pattern = value_pattern.GetEntityPtr();
	unsigned int corner_num = args_gurax.PickNumber<unsigned int>();
	double red = args_gurax.PickNumber<double>();
	double green = args_gurax.PickNumber<double>();
	double blue = args_gurax.PickNumber<double>();
	double alpha = args_gurax.PickNumber<double>();
	// Function body
	cairo_mesh_pattern_set_corner_color_rgba(pattern, corner_num, red, green, blue, alpha);
	return Gurax::Value::nil();
}

// cairo.cairo_pattern_set_matrix(pattern as cairo_pattern_t, matrix as cairo_matrix_t)
Gurax_DeclareFunctionAlias(cairo_pattern_set_matrix_gurax, "cairo_pattern_set_matrix")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pattern", VTYPE_cairo_pattern_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("matrix", VTYPE_cairo_matrix_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_pattern_set_matrix_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_pattern = args_gurax.Pick<Value_cairo_pattern_t>();
	cairo_pattern_t* pattern = value_pattern.GetEntityPtr();
	auto& value_matrix = args_gurax.Pick<Value_cairo_matrix_t>();
	const cairo_matrix_t* matrix = value_matrix.GetEntityPtr();
	// Function body
	cairo_pattern_set_matrix(pattern, matrix);
	return Gurax::Value::nil();
}

// cairo.cairo_pattern_get_matrix(pattern as cairo_pattern_t, matrix as cairo_matrix_t)
Gurax_DeclareFunctionAlias(cairo_pattern_get_matrix_gurax, "cairo_pattern_get_matrix")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pattern", VTYPE_cairo_pattern_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("matrix", VTYPE_cairo_matrix_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_pattern_get_matrix_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_pattern = args_gurax.Pick<Value_cairo_pattern_t>();
	cairo_pattern_t* pattern = value_pattern.GetEntityPtr();
	auto& value_matrix = args_gurax.Pick<Value_cairo_matrix_t>();
	cairo_matrix_t* matrix = value_matrix.GetEntityPtr();
	// Function body
	cairo_pattern_get_matrix(pattern, matrix);
	return Gurax::Value::nil();
}

// cairo.cairo_pattern_set_extend(pattern as cairo_pattern_t, extend as Number)
Gurax_DeclareFunctionAlias(cairo_pattern_set_extend_gurax, "cairo_pattern_set_extend")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pattern", VTYPE_cairo_pattern_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("extend", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_pattern_set_extend_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_pattern = args_gurax.Pick<Value_cairo_pattern_t>();
	cairo_pattern_t* pattern = value_pattern.GetEntityPtr();
	cairo_extend_t extend = args_gurax.PickNumber<cairo_extend_t>();
	// Function body
	cairo_pattern_set_extend(pattern, extend);
	return Gurax::Value::nil();
}

// cairo.cairo_pattern_get_extend(pattern as cairo_pattern_t)
Gurax_DeclareFunctionAlias(cairo_pattern_get_extend_gurax, "cairo_pattern_get_extend")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("pattern", VTYPE_cairo_pattern_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_pattern_get_extend_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_pattern = args_gurax.Pick<Value_cairo_pattern_t>();
	cairo_pattern_t* pattern = value_pattern.GetEntityPtr();
	// Function body
	cairo_extend_t rtn = cairo_pattern_get_extend(pattern);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_pattern_set_filter(pattern as cairo_pattern_t, filter as Number)
Gurax_DeclareFunctionAlias(cairo_pattern_set_filter_gurax, "cairo_pattern_set_filter")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pattern", VTYPE_cairo_pattern_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("filter", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_pattern_set_filter_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_pattern = args_gurax.Pick<Value_cairo_pattern_t>();
	cairo_pattern_t* pattern = value_pattern.GetEntityPtr();
	cairo_filter_t filter = args_gurax.PickNumber<cairo_filter_t>();
	// Function body
	cairo_pattern_set_filter(pattern, filter);
	return Gurax::Value::nil();
}

// cairo.cairo_pattern_get_filter(pattern as cairo_pattern_t)
Gurax_DeclareFunctionAlias(cairo_pattern_get_filter_gurax, "cairo_pattern_get_filter")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("pattern", VTYPE_cairo_pattern_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_pattern_get_filter_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_pattern = args_gurax.Pick<Value_cairo_pattern_t>();
	cairo_pattern_t* pattern = value_pattern.GetEntityPtr();
	// Function body
	cairo_filter_t rtn = cairo_pattern_get_filter(pattern);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_pattern_get_rgba(pattern as cairo_pattern_t)
Gurax_DeclareFunctionAlias(cairo_pattern_get_rgba_gurax, "cairo_pattern_get_rgba")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("pattern", VTYPE_cairo_pattern_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_pattern_get_rgba_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_pattern = args_gurax.Pick<Value_cairo_pattern_t>();
	cairo_pattern_t* pattern = value_pattern.GetEntityPtr();
	// Function body
	double red, green, blue, alpha;
	if (!IsOK(cairo_pattern_get_rgba(pattern, &red, &green, &blue, &alpha))) return Value::nil();
	return Value_Tuple::Create(new Value_Number(red), new Value_Number(green), new Value_Number(blue), new Value_Number(alpha));
}

// cairo.cairo_pattern_get_color_stop_rgba(pattern as cairo_pattern_t, index as Number)
Gurax_DeclareFunctionAlias(cairo_pattern_get_color_stop_rgba_gurax, "cairo_pattern_get_color_stop_rgba")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("pattern", VTYPE_cairo_pattern_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_pattern_get_color_stop_rgba_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_pattern = args_gurax.Pick<Value_cairo_pattern_t>();
	cairo_pattern_t* pattern = value_pattern.GetEntityPtr();
	int index = args_gurax.PickNumber<int>();
	// Function body
	double offset, red, green, blue, alpha;
	if (!IsOK(cairo_pattern_get_color_stop_rgba(pattern, index, &offset, &red, &green, &blue, &alpha))) return Value::nil();
	return Value_Tuple::Create(new Value_Number(offset), new Value_Number(red), new Value_Number(green), new Value_Number(blue), new Value_Number(alpha));
}

// cairo.cairo_mesh_pattern_get_path(pattern as cairo_pattern_t, patch_num as Number)
Gurax_DeclareFunctionAlias(cairo_mesh_pattern_get_path_gurax, "cairo_mesh_pattern_get_path")
{
	Declare(VTYPE_cairo_path_t, Flag::None);
	DeclareArg("pattern", VTYPE_cairo_pattern_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("patch_num", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_mesh_pattern_get_path_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_pattern = args_gurax.Pick<Value_cairo_pattern_t>();
	cairo_pattern_t* pattern = value_pattern.GetEntityPtr();
	unsigned int patch_num = args_gurax.PickNumber<unsigned int>();
	// Function body
	cairo_path_t* rtn = cairo_mesh_pattern_get_path(pattern, patch_num);
	if (!rtn) return Value::nil();
	return new Value_cairo_path_t(rtn);
}

// cairo.cairo_matrix_init(matrix as cairo_matrix_t, xx as Number, yx as Number, xy as Number, yy as Number, x0 as Number, y0 as Number)
Gurax_DeclareFunctionAlias(cairo_matrix_init_gurax, "cairo_matrix_init")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("matrix", VTYPE_cairo_matrix_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("yx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xy", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("yy", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x0", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y0", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_matrix_init_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_matrix = args_gurax.Pick<Value_cairo_matrix_t>();
	cairo_matrix_t* matrix = value_matrix.GetEntityPtr();
	double xx = args_gurax.PickNumber<double>();
	double yx = args_gurax.PickNumber<double>();
	double xy = args_gurax.PickNumber<double>();
	double yy = args_gurax.PickNumber<double>();
	double x0 = args_gurax.PickNumber<double>();
	double y0 = args_gurax.PickNumber<double>();
	// Function body
	cairo_matrix_init(matrix, xx, yx, xy, yy, x0, y0);
	return Gurax::Value::nil();
}

// cairo.cairo_matrix_init_identity(matrix as cairo_matrix_t)
Gurax_DeclareFunctionAlias(cairo_matrix_init_identity_gurax, "cairo_matrix_init_identity")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("matrix", VTYPE_cairo_matrix_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_matrix_init_identity_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_matrix = args_gurax.Pick<Value_cairo_matrix_t>();
	cairo_matrix_t* matrix = value_matrix.GetEntityPtr();
	// Function body
	cairo_matrix_init_identity(matrix);
	return Gurax::Value::nil();
}

// cairo.cairo_matrix_init_translate(matrix as cairo_matrix_t, tx as Number, ty as Number)
Gurax_DeclareFunctionAlias(cairo_matrix_init_translate_gurax, "cairo_matrix_init_translate")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("matrix", VTYPE_cairo_matrix_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("tx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ty", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_matrix_init_translate_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_matrix = args_gurax.Pick<Value_cairo_matrix_t>();
	cairo_matrix_t* matrix = value_matrix.GetEntityPtr();
	double tx = args_gurax.PickNumber<double>();
	double ty = args_gurax.PickNumber<double>();
	// Function body
	cairo_matrix_init_translate(matrix, tx, ty);
	return Gurax::Value::nil();
}

// cairo.cairo_matrix_init_scale(matrix as cairo_matrix_t, sx as Number, sy as Number)
Gurax_DeclareFunctionAlias(cairo_matrix_init_scale_gurax, "cairo_matrix_init_scale")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("matrix", VTYPE_cairo_matrix_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("sx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("sy", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_matrix_init_scale_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_matrix = args_gurax.Pick<Value_cairo_matrix_t>();
	cairo_matrix_t* matrix = value_matrix.GetEntityPtr();
	double sx = args_gurax.PickNumber<double>();
	double sy = args_gurax.PickNumber<double>();
	// Function body
	cairo_matrix_init_scale(matrix, sx, sy);
	return Gurax::Value::nil();
}

// cairo.cairo_matrix_init_rotate(matrix as cairo_matrix_t, radians as Number)
Gurax_DeclareFunctionAlias(cairo_matrix_init_rotate_gurax, "cairo_matrix_init_rotate")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("matrix", VTYPE_cairo_matrix_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("radians", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_matrix_init_rotate_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_matrix = args_gurax.Pick<Value_cairo_matrix_t>();
	cairo_matrix_t* matrix = value_matrix.GetEntityPtr();
	double radians = args_gurax.PickNumber<double>();
	// Function body
	cairo_matrix_init_rotate(matrix, radians);
	return Gurax::Value::nil();
}

// cairo.cairo_matrix_translate(matrix as cairo_matrix_t, tx as Number, ty as Number)
Gurax_DeclareFunctionAlias(cairo_matrix_translate_gurax, "cairo_matrix_translate")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("matrix", VTYPE_cairo_matrix_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("tx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ty", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_matrix_translate_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_matrix = args_gurax.Pick<Value_cairo_matrix_t>();
	cairo_matrix_t* matrix = value_matrix.GetEntityPtr();
	double tx = args_gurax.PickNumber<double>();
	double ty = args_gurax.PickNumber<double>();
	// Function body
	cairo_matrix_translate(matrix, tx, ty);
	return Gurax::Value::nil();
}

// cairo.cairo_matrix_scale(matrix as cairo_matrix_t, sx as Number, sy as Number)
Gurax_DeclareFunctionAlias(cairo_matrix_scale_gurax, "cairo_matrix_scale")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("matrix", VTYPE_cairo_matrix_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("sx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("sy", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_matrix_scale_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_matrix = args_gurax.Pick<Value_cairo_matrix_t>();
	cairo_matrix_t* matrix = value_matrix.GetEntityPtr();
	double sx = args_gurax.PickNumber<double>();
	double sy = args_gurax.PickNumber<double>();
	// Function body
	cairo_matrix_scale(matrix, sx, sy);
	return Gurax::Value::nil();
}

// cairo.cairo_matrix_rotate(matrix as cairo_matrix_t, radians as Number)
Gurax_DeclareFunctionAlias(cairo_matrix_rotate_gurax, "cairo_matrix_rotate")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("matrix", VTYPE_cairo_matrix_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("radians", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_matrix_rotate_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_matrix = args_gurax.Pick<Value_cairo_matrix_t>();
	cairo_matrix_t* matrix = value_matrix.GetEntityPtr();
	double radians = args_gurax.PickNumber<double>();
	// Function body
	cairo_matrix_rotate(matrix, radians);
	return Gurax::Value::nil();
}

// cairo.cairo_matrix_invert(matrix as cairo_matrix_t)
Gurax_DeclareFunctionAlias(cairo_matrix_invert_gurax, "cairo_matrix_invert")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("matrix", VTYPE_cairo_matrix_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_matrix_invert_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_matrix = args_gurax.Pick<Value_cairo_matrix_t>();
	cairo_matrix_t* matrix = value_matrix.GetEntityPtr();
	// Function body
	cairo_status_t rtn = cairo_matrix_invert(matrix);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_matrix_multiply(result as cairo_matrix_t, a as cairo_matrix_t, b as cairo_matrix_t)
Gurax_DeclareFunctionAlias(cairo_matrix_multiply_gurax, "cairo_matrix_multiply")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("result", VTYPE_cairo_matrix_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("a", VTYPE_cairo_matrix_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("b", VTYPE_cairo_matrix_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_matrix_multiply_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_result = args_gurax.Pick<Value_cairo_matrix_t>();
	cairo_matrix_t* result = value_result.GetEntityPtr();
	auto& value_a = args_gurax.Pick<Value_cairo_matrix_t>();
	const cairo_matrix_t* a = value_a.GetEntityPtr();
	auto& value_b = args_gurax.Pick<Value_cairo_matrix_t>();
	const cairo_matrix_t* b = value_b.GetEntityPtr();
	// Function body
	cairo_matrix_multiply(result, a, b);
	return Gurax::Value::nil();
}

// cairo.cairo_matrix_transform_distance(matrix as cairo_matrix_t, dx as Number, dy as Number)
Gurax_DeclareFunctionAlias(cairo_matrix_transform_distance_gurax, "cairo_matrix_transform_distance")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("matrix", VTYPE_cairo_matrix_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dy", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_matrix_transform_distance_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_matrix = args_gurax.Pick<Value_cairo_matrix_t>();
	const cairo_matrix_t* matrix = value_matrix.GetEntityPtr();
	double dx = args_gurax.PickNumber<double>();
	double dy = args_gurax.PickNumber<double>();
	// Function body
	cairo_matrix_transform_distance(matrix, &dx, &dy);
	return Value_Tuple::Create(new Value_Number(dx), new Value_Number(dy));
}

// cairo.cairo_matrix_transform_point(matrix as cairo_matrix_t, x as Number, y as Number)
Gurax_DeclareFunctionAlias(cairo_matrix_transform_point_gurax, "cairo_matrix_transform_point")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("matrix", VTYPE_cairo_matrix_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_matrix_transform_point_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_matrix = args_gurax.Pick<Value_cairo_matrix_t>();
	const cairo_matrix_t* matrix = value_matrix.GetEntityPtr();
	double x = args_gurax.PickNumber<double>();
	double y = args_gurax.PickNumber<double>();
	// Function body
	cairo_matrix_transform_distance(matrix, &x, &y);
	return Value_Tuple::Create(new Value_Number(x), new Value_Number(y));
}

// cairo.cairo_region_create()
Gurax_DeclareFunctionAlias(cairo_region_create_gurax, "cairo_region_create")
{
	Declare(VTYPE_cairo_region_t, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_region_create_gurax, processor_gurax, argument_gurax)
{
	// Function body
	cairo_region_t* rtn = cairo_region_create();
	if (!rtn) return Value::nil();
	return new Value_cairo_region_t(rtn);
}

// cairo.cairo_region_create_rectangle(rectangle as cairo_rectangle_int_t)
Gurax_DeclareFunctionAlias(cairo_region_create_rectangle_gurax, "cairo_region_create_rectangle")
{
	Declare(VTYPE_cairo_region_t, Flag::None);
	DeclareArg("rectangle", VTYPE_cairo_rectangle_int_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_region_create_rectangle_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_rectangle = args_gurax.Pick<Value_cairo_rectangle_int_t>();
	const cairo_rectangle_int_t* rectangle = value_rectangle.GetEntityPtr();
	// Function body
	cairo_region_t* rtn = cairo_region_create_rectangle(rectangle);
	if (!rtn) return Value::nil();
	return new Value_cairo_region_t(rtn);
}

// cairo.cairo_region_create_rectangles(rects as cairo_rectangle_int_t, count as Number)
Gurax_DeclareFunctionAlias(cairo_region_create_rectangles_gurax, "cairo_region_create_rectangles")
{
	Declare(VTYPE_cairo_region_t, Flag::None);
	DeclareArg("rects", VTYPE_cairo_rectangle_int_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_region_create_rectangles_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_rects = args_gurax.Pick<Value_cairo_rectangle_int_t>();
	const cairo_rectangle_int_t* rects = value_rects.GetEntityPtr();
	int count = args_gurax.PickNumber<int>();
	// Function body
	cairo_region_t* rtn = cairo_region_create_rectangles(rects, count);
	if (!rtn) return Value::nil();
	return new Value_cairo_region_t(rtn);
}

// cairo.cairo_region_copy(original as cairo_region_t)
Gurax_DeclareFunctionAlias(cairo_region_copy_gurax, "cairo_region_copy")
{
	Declare(VTYPE_cairo_region_t, Flag::None);
	DeclareArg("original", VTYPE_cairo_region_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_region_copy_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_original = args_gurax.Pick<Value_cairo_region_t>();
	const cairo_region_t* original = value_original.GetEntityPtr();
	// Function body
	cairo_region_t* rtn = cairo_region_copy(original);
	if (!rtn) return Value::nil();
	return new Value_cairo_region_t(rtn);
}

// cairo.cairo_region_reference(region as cairo_region_t)
Gurax_DeclareFunctionAlias(cairo_region_reference_gurax, "cairo_region_reference")
{
	Declare(VTYPE_cairo_region_t, Flag::None);
	DeclareArg("region", VTYPE_cairo_region_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_region_reference_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_region = args_gurax.Pick<Value_cairo_region_t>();
	cairo_region_t* region = value_region.GetEntityPtr();
	// Function body
	cairo_region_t* rtn = cairo_region_reference(region);
	if (!rtn) return Value::nil();
	return new Value_cairo_region_t(rtn);
}

// cairo.cairo_region_destroy(region as cairo_region_t)
Gurax_DeclareFunctionAlias(cairo_region_destroy_gurax, "cairo_region_destroy")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("region", VTYPE_cairo_region_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_region_destroy_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_region = args_gurax.Pick<Value_cairo_region_t>();
	cairo_region_t* region = value_region.GetEntityPtr();
	// Function body
	cairo_region_destroy(region);
	return Gurax::Value::nil();
}

// cairo.cairo_region_equal(a as cairo_region_t, b as cairo_region_t)
Gurax_DeclareFunctionAlias(cairo_region_equal_gurax, "cairo_region_equal")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("a", VTYPE_cairo_region_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("b", VTYPE_cairo_region_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_region_equal_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_a = args_gurax.Pick<Value_cairo_region_t>();
	const cairo_region_t* a = value_a.GetEntityPtr();
	auto& value_b = args_gurax.Pick<Value_cairo_region_t>();
	const cairo_region_t* b = value_b.GetEntityPtr();
	// Function body
	cairo_bool_t rtn = cairo_region_equal(a, b);
	return new Gurax::Value_Bool(!!rtn);
}

// cairo.cairo_region_status(region as cairo_region_t)
Gurax_DeclareFunctionAlias(cairo_region_status_gurax, "cairo_region_status")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("region", VTYPE_cairo_region_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_region_status_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_region = args_gurax.Pick<Value_cairo_region_t>();
	const cairo_region_t* region = value_region.GetEntityPtr();
	// Function body
	cairo_status_t rtn = cairo_region_status(region);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_region_get_extents(region as cairo_region_t, extents as cairo_rectangle_int_t)
Gurax_DeclareFunctionAlias(cairo_region_get_extents_gurax, "cairo_region_get_extents")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("region", VTYPE_cairo_region_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("extents", VTYPE_cairo_rectangle_int_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_region_get_extents_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_region = args_gurax.Pick<Value_cairo_region_t>();
	const cairo_region_t* region = value_region.GetEntityPtr();
	auto& value_extents = args_gurax.Pick<Value_cairo_rectangle_int_t>();
	cairo_rectangle_int_t* extents = value_extents.GetEntityPtr();
	// Function body
	cairo_region_get_extents(region, extents);
	return Gurax::Value::nil();
}

// cairo.cairo_region_num_rectangles(region as cairo_region_t)
Gurax_DeclareFunctionAlias(cairo_region_num_rectangles_gurax, "cairo_region_num_rectangles")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("region", VTYPE_cairo_region_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_region_num_rectangles_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_region = args_gurax.Pick<Value_cairo_region_t>();
	const cairo_region_t* region = value_region.GetEntityPtr();
	// Function body
	int rtn = cairo_region_num_rectangles(region);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_region_get_rectangle(region as cairo_region_t, nth as Number, rectangle as cairo_rectangle_int_t)
Gurax_DeclareFunctionAlias(cairo_region_get_rectangle_gurax, "cairo_region_get_rectangle")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("region", VTYPE_cairo_region_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("nth", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rectangle", VTYPE_cairo_rectangle_int_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_region_get_rectangle_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_region = args_gurax.Pick<Value_cairo_region_t>();
	const cairo_region_t* region = value_region.GetEntityPtr();
	int nth = args_gurax.PickNumber<int>();
	auto& value_rectangle = args_gurax.Pick<Value_cairo_rectangle_int_t>();
	cairo_rectangle_int_t* rectangle = value_rectangle.GetEntityPtr();
	// Function body
	cairo_region_get_rectangle(region, nth, rectangle);
	return Gurax::Value::nil();
}

// cairo.cairo_region_is_empty(region as cairo_region_t)
Gurax_DeclareFunctionAlias(cairo_region_is_empty_gurax, "cairo_region_is_empty")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("region", VTYPE_cairo_region_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_region_is_empty_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_region = args_gurax.Pick<Value_cairo_region_t>();
	const cairo_region_t* region = value_region.GetEntityPtr();
	// Function body
	cairo_bool_t rtn = cairo_region_is_empty(region);
	return new Gurax::Value_Bool(!!rtn);
}

// cairo.cairo_region_contains_rectangle(region as cairo_region_t, rectangle as cairo_rectangle_int_t)
Gurax_DeclareFunctionAlias(cairo_region_contains_rectangle_gurax, "cairo_region_contains_rectangle")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("region", VTYPE_cairo_region_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rectangle", VTYPE_cairo_rectangle_int_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_region_contains_rectangle_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_region = args_gurax.Pick<Value_cairo_region_t>();
	const cairo_region_t* region = value_region.GetEntityPtr();
	auto& value_rectangle = args_gurax.Pick<Value_cairo_rectangle_int_t>();
	const cairo_rectangle_int_t* rectangle = value_rectangle.GetEntityPtr();
	// Function body
	cairo_region_overlap_t rtn = cairo_region_contains_rectangle(region, rectangle);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_region_contains_point(region as cairo_region_t, x as Number, y as Number)
Gurax_DeclareFunctionAlias(cairo_region_contains_point_gurax, "cairo_region_contains_point")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("region", VTYPE_cairo_region_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_region_contains_point_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_region = args_gurax.Pick<Value_cairo_region_t>();
	const cairo_region_t* region = value_region.GetEntityPtr();
	int x = args_gurax.PickNumber<int>();
	int y = args_gurax.PickNumber<int>();
	// Function body
	cairo_bool_t rtn = cairo_region_contains_point(region, x, y);
	return new Gurax::Value_Bool(!!rtn);
}

// cairo.cairo_region_translate(region as cairo_region_t, dx as Number, dy as Number)
Gurax_DeclareFunctionAlias(cairo_region_translate_gurax, "cairo_region_translate")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("region", VTYPE_cairo_region_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dy", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_region_translate_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_region = args_gurax.Pick<Value_cairo_region_t>();
	cairo_region_t* region = value_region.GetEntityPtr();
	int dx = args_gurax.PickNumber<int>();
	int dy = args_gurax.PickNumber<int>();
	// Function body
	cairo_region_translate(region, dx, dy);
	return Gurax::Value::nil();
}

// cairo.cairo_region_subtract(dst as cairo_region_t, other as cairo_region_t)
Gurax_DeclareFunctionAlias(cairo_region_subtract_gurax, "cairo_region_subtract")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("dst", VTYPE_cairo_region_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("other", VTYPE_cairo_region_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_region_subtract_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_dst = args_gurax.Pick<Value_cairo_region_t>();
	cairo_region_t* dst = value_dst.GetEntityPtr();
	auto& value_other = args_gurax.Pick<Value_cairo_region_t>();
	const cairo_region_t* other = value_other.GetEntityPtr();
	// Function body
	cairo_status_t rtn = cairo_region_subtract(dst, other);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_region_subtract_rectangle(dst as cairo_region_t, rectangle as cairo_rectangle_int_t)
Gurax_DeclareFunctionAlias(cairo_region_subtract_rectangle_gurax, "cairo_region_subtract_rectangle")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("dst", VTYPE_cairo_region_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rectangle", VTYPE_cairo_rectangle_int_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_region_subtract_rectangle_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_dst = args_gurax.Pick<Value_cairo_region_t>();
	cairo_region_t* dst = value_dst.GetEntityPtr();
	auto& value_rectangle = args_gurax.Pick<Value_cairo_rectangle_int_t>();
	const cairo_rectangle_int_t* rectangle = value_rectangle.GetEntityPtr();
	// Function body
	cairo_status_t rtn = cairo_region_subtract_rectangle(dst, rectangle);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_region_intersect(dst as cairo_region_t, other as cairo_region_t)
Gurax_DeclareFunctionAlias(cairo_region_intersect_gurax, "cairo_region_intersect")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("dst", VTYPE_cairo_region_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("other", VTYPE_cairo_region_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_region_intersect_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_dst = args_gurax.Pick<Value_cairo_region_t>();
	cairo_region_t* dst = value_dst.GetEntityPtr();
	auto& value_other = args_gurax.Pick<Value_cairo_region_t>();
	const cairo_region_t* other = value_other.GetEntityPtr();
	// Function body
	cairo_status_t rtn = cairo_region_intersect(dst, other);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_region_intersect_rectangle(dst as cairo_region_t, rectangle as cairo_rectangle_int_t)
Gurax_DeclareFunctionAlias(cairo_region_intersect_rectangle_gurax, "cairo_region_intersect_rectangle")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("dst", VTYPE_cairo_region_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rectangle", VTYPE_cairo_rectangle_int_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_region_intersect_rectangle_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_dst = args_gurax.Pick<Value_cairo_region_t>();
	cairo_region_t* dst = value_dst.GetEntityPtr();
	auto& value_rectangle = args_gurax.Pick<Value_cairo_rectangle_int_t>();
	const cairo_rectangle_int_t* rectangle = value_rectangle.GetEntityPtr();
	// Function body
	cairo_status_t rtn = cairo_region_intersect_rectangle(dst, rectangle);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_region_union(dst as cairo_region_t, other as cairo_region_t)
Gurax_DeclareFunctionAlias(cairo_region_union_gurax, "cairo_region_union")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("dst", VTYPE_cairo_region_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("other", VTYPE_cairo_region_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_region_union_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_dst = args_gurax.Pick<Value_cairo_region_t>();
	cairo_region_t* dst = value_dst.GetEntityPtr();
	auto& value_other = args_gurax.Pick<Value_cairo_region_t>();
	const cairo_region_t* other = value_other.GetEntityPtr();
	// Function body
	cairo_status_t rtn = cairo_region_union(dst, other);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_region_union_rectangle(dst as cairo_region_t, rectangle as cairo_rectangle_int_t)
Gurax_DeclareFunctionAlias(cairo_region_union_rectangle_gurax, "cairo_region_union_rectangle")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("dst", VTYPE_cairo_region_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rectangle", VTYPE_cairo_rectangle_int_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_region_union_rectangle_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_dst = args_gurax.Pick<Value_cairo_region_t>();
	cairo_region_t* dst = value_dst.GetEntityPtr();
	auto& value_rectangle = args_gurax.Pick<Value_cairo_rectangle_int_t>();
	const cairo_rectangle_int_t* rectangle = value_rectangle.GetEntityPtr();
	// Function body
	cairo_status_t rtn = cairo_region_union_rectangle(dst, rectangle);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_region_xor(dst as cairo_region_t, other as cairo_region_t)
Gurax_DeclareFunctionAlias(cairo_region_xor_gurax, "cairo_region_xor")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("dst", VTYPE_cairo_region_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("other", VTYPE_cairo_region_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_region_xor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_dst = args_gurax.Pick<Value_cairo_region_t>();
	cairo_region_t* dst = value_dst.GetEntityPtr();
	auto& value_other = args_gurax.Pick<Value_cairo_region_t>();
	const cairo_region_t* other = value_other.GetEntityPtr();
	// Function body
	cairo_status_t rtn = cairo_region_xor(dst, other);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_region_xor_rectangle(dst as cairo_region_t, rectangle as cairo_rectangle_int_t)
Gurax_DeclareFunctionAlias(cairo_region_xor_rectangle_gurax, "cairo_region_xor_rectangle")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("dst", VTYPE_cairo_region_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rectangle", VTYPE_cairo_rectangle_int_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_region_xor_rectangle_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_dst = args_gurax.Pick<Value_cairo_region_t>();
	cairo_region_t* dst = value_dst.GetEntityPtr();
	auto& value_rectangle = args_gurax.Pick<Value_cairo_rectangle_int_t>();
	const cairo_rectangle_int_t* rectangle = value_rectangle.GetEntityPtr();
	// Function body
	cairo_status_t rtn = cairo_region_xor_rectangle(dst, rectangle);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_debug_reset_static_data()
Gurax_DeclareFunctionAlias(cairo_debug_reset_static_data_gurax, "cairo_debug_reset_static_data")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_debug_reset_static_data_gurax, processor_gurax, argument_gurax)
{
	// Function body
	cairo_debug_reset_static_data();
	return Gurax::Value::nil();
}

// cairo.cairo_pdf_surface_create(filename as String, width_in_points as Number, height_in_points as Number)
Gurax_DeclareFunctionAlias(cairo_pdf_surface_create_gurax, "cairo_pdf_surface_create")
{
	Declare(VTYPE_cairo_surface_t, Flag::None);
	DeclareArg("filename", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width_in_points", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height_in_points", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_pdf_surface_create_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* filename = args_gurax.PickString();
	double width_in_points = args_gurax.PickNumber<double>();
	double height_in_points = args_gurax.PickNumber<double>();
	// Function body
	cairo_surface_t* rtn = cairo_pdf_surface_create(filename, width_in_points, height_in_points);
	if (!rtn) return Value::nil();
	return new Value_cairo_surface_t(rtn);
}

// cairo.cairo_pdf_surface_create_for_stream(stream:w as Stream, width_in_points as Number, height_in_points as Number)
Gurax_DeclareFunctionAlias(cairo_pdf_surface_create_for_stream_gurax, "cairo_pdf_surface_create_for_stream")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamW);
	DeclareArg("width_in_points", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height_in_points", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_pdf_surface_create_for_stream_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	RefPtr<Stream> stream(args_gurax.PickStream().Reference());
	double width_in_points = args_gurax.PickNumber<double>();
	double height_in_points = args_gurax.PickNumber<double>();
	// Function body
	cairo_surface_t* surface = cairo_pdf_surface_create_for_stream(write_func, stream.get(), width_in_points, height_in_points);
	return new Value_cairo_surface_t(surface, stream.release());
}

// cairo.cairo_pdf_surface_restrict_to_version(surface as cairo_surface_t, version as Number)
Gurax_DeclareFunctionAlias(cairo_pdf_surface_restrict_to_version_gurax, "cairo_pdf_surface_restrict_to_version")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("version", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_pdf_surface_restrict_to_version_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	cairo_pdf_version_t version = args_gurax.PickNumber<cairo_pdf_version_t>();
	// Function body
	cairo_pdf_surface_restrict_to_version(surface, version);
	return Gurax::Value::nil();
}

// cairo.cairo_pdf_get_versions()
Gurax_DeclareFunctionAlias(cairo_pdf_get_versions_gurax, "cairo_pdf_get_versions")
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_pdf_get_versions_gurax, processor_gurax, argument_gurax)
{
	// Function body
	const cairo_pdf_version_t* versions;
	int num_version;
	cairo_pdf_get_versions(&versions, &num_version);
	return Value_List::Create(reinterpret_cast<const int*>(versions), num_version);
}

// cairo.cairo_pdf_version_to_string(version as Number)
Gurax_DeclareFunctionAlias(cairo_pdf_version_to_string_gurax, "cairo_pdf_version_to_string")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("version", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_pdf_version_to_string_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	cairo_pdf_version_t version = args_gurax.PickNumber<cairo_pdf_version_t>();
	// Function body
	const char* rtn = cairo_pdf_version_to_string(version);
	return new Gurax::Value_String(rtn);
}

// cairo.cairo_pdf_surface_set_size(surface as cairo_surface_t, width_in_points as Number, height_in_points as Number)
Gurax_DeclareFunctionAlias(cairo_pdf_surface_set_size_gurax, "cairo_pdf_surface_set_size")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width_in_points", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height_in_points", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_pdf_surface_set_size_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	double width_in_points = args_gurax.PickNumber<double>();
	double height_in_points = args_gurax.PickNumber<double>();
	// Function body
	cairo_pdf_surface_set_size(surface, width_in_points, height_in_points);
	return Gurax::Value::nil();
}

// cairo.cairo_pdf_surface_add_outline(surface as cairo_surface_t, parent_id as Number, utf8 as String, link_attribs as String, flags as Number)
Gurax_DeclareFunctionAlias(cairo_pdf_surface_add_outline_gurax, "cairo_pdf_surface_add_outline")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("parent_id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("utf8", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("link_attribs", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_pdf_surface_add_outline_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	int parent_id = args_gurax.PickNumber<int>();
	const char* utf8 = args_gurax.PickString();
	const char* link_attribs = args_gurax.PickString();
	cairo_pdf_outline_flags_t flags = args_gurax.PickNumber<cairo_pdf_outline_flags_t>();
	// Function body
	int rtn = cairo_pdf_surface_add_outline(surface, parent_id, utf8, link_attribs, flags);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_pdf_surface_set_metadata(surface as cairo_surface_t, metadata as Number, utf8 as String)
Gurax_DeclareFunctionAlias(cairo_pdf_surface_set_metadata_gurax, "cairo_pdf_surface_set_metadata")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("metadata", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("utf8", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_pdf_surface_set_metadata_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	cairo_pdf_metadata_t metadata = args_gurax.PickNumber<cairo_pdf_metadata_t>();
	const char* utf8 = args_gurax.PickString();
	// Function body
	cairo_pdf_surface_set_metadata(surface, metadata, utf8);
	return Gurax::Value::nil();
}

// cairo.cairo_pdf_surface_set_page_label(surface as cairo_surface_t, utf8 as String)
Gurax_DeclareFunctionAlias(cairo_pdf_surface_set_page_label_gurax, "cairo_pdf_surface_set_page_label")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("utf8", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_pdf_surface_set_page_label_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	const char* utf8 = args_gurax.PickString();
	// Function body
	cairo_pdf_surface_set_page_label(surface, utf8);
	return Gurax::Value::nil();
}

// cairo.cairo_pdf_surface_set_thumbnail_size(surface as cairo_surface_t, width as Number, height as Number)
Gurax_DeclareFunctionAlias(cairo_pdf_surface_set_thumbnail_size_gurax, "cairo_pdf_surface_set_thumbnail_size")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_pdf_surface_set_thumbnail_size_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	int width = args_gurax.PickNumber<int>();
	int height = args_gurax.PickNumber<int>();
	// Function body
	cairo_pdf_surface_set_thumbnail_size(surface, width, height);
	return Gurax::Value::nil();
}

// cairo.cairo_ps_surface_create(filename as String, width_in_points as Number, height_in_points as Number)
Gurax_DeclareFunctionAlias(cairo_ps_surface_create_gurax, "cairo_ps_surface_create")
{
	Declare(VTYPE_cairo_surface_t, Flag::None);
	DeclareArg("filename", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width_in_points", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height_in_points", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_ps_surface_create_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* filename = args_gurax.PickString();
	double width_in_points = args_gurax.PickNumber<double>();
	double height_in_points = args_gurax.PickNumber<double>();
	// Function body
	cairo_surface_t* rtn = cairo_ps_surface_create(filename, width_in_points, height_in_points);
	if (!rtn) return Value::nil();
	return new Value_cairo_surface_t(rtn);
}

// cairo.cairo_ps_surface_create_for_stream(stream:w as Stream, width_in_points as Number, height_in_points as Number)
Gurax_DeclareFunctionAlias(cairo_ps_surface_create_for_stream_gurax, "cairo_ps_surface_create_for_stream")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamW);
	DeclareArg("width_in_points", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height_in_points", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_ps_surface_create_for_stream_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	RefPtr<Stream> stream(args_gurax.PickStream().Reference());
	double width_in_points = args_gurax.PickNumber<double>();
	double height_in_points = args_gurax.PickNumber<double>();
	// Function body
	cairo_surface_t* surface = cairo_ps_surface_create_for_stream(write_func, stream.get(), width_in_points, height_in_points);
	return new Value_cairo_surface_t(surface, stream.release());
}

// cairo.cairo_ps_surface_restrict_to_level(surface as cairo_surface_t, level as Number)
Gurax_DeclareFunctionAlias(cairo_ps_surface_restrict_to_level_gurax, "cairo_ps_surface_restrict_to_level")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_ps_surface_restrict_to_level_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	cairo_ps_level_t level = args_gurax.PickNumber<cairo_ps_level_t>();
	// Function body
	cairo_ps_surface_restrict_to_level(surface, level);
	return Gurax::Value::nil();
}

// cairo.cairo_ps_level_to_string(level as Number)
Gurax_DeclareFunctionAlias(cairo_ps_level_to_string_gurax, "cairo_ps_level_to_string")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_ps_level_to_string_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	cairo_ps_level_t level = args_gurax.PickNumber<cairo_ps_level_t>();
	// Function body
	const char* rtn = cairo_ps_level_to_string(level);
	return new Gurax::Value_String(rtn);
}

// cairo.cairo_ps_surface_set_eps(surface as cairo_surface_t, eps as Bool)
Gurax_DeclareFunctionAlias(cairo_ps_surface_set_eps_gurax, "cairo_ps_surface_set_eps")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("eps", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_ps_surface_set_eps_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	cairo_bool_t eps = static_cast<cairo_bool_t>(args_gurax.PickBool());
	// Function body
	cairo_ps_surface_set_eps(surface, eps);
	return Gurax::Value::nil();
}

// cairo.cairo_ps_surface_get_eps(surface as cairo_surface_t)
Gurax_DeclareFunctionAlias(cairo_ps_surface_get_eps_gurax, "cairo_ps_surface_get_eps")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_ps_surface_get_eps_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	// Function body
	cairo_bool_t rtn = cairo_ps_surface_get_eps(surface);
	return new Gurax::Value_Bool(!!rtn);
}

// cairo.cairo_ps_surface_set_size(surface as cairo_surface_t, width_in_points as Number, height_in_points as Number)
Gurax_DeclareFunctionAlias(cairo_ps_surface_set_size_gurax, "cairo_ps_surface_set_size")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width_in_points", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height_in_points", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_ps_surface_set_size_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	double width_in_points = args_gurax.PickNumber<double>();
	double height_in_points = args_gurax.PickNumber<double>();
	// Function body
	cairo_ps_surface_set_size(surface, width_in_points, height_in_points);
	return Gurax::Value::nil();
}

// cairo.cairo_ps_surface_dsc_comment(surface as cairo_surface_t, comment as String)
Gurax_DeclareFunctionAlias(cairo_ps_surface_dsc_comment_gurax, "cairo_ps_surface_dsc_comment")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("comment", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_ps_surface_dsc_comment_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	const char* comment = args_gurax.PickString();
	// Function body
	cairo_ps_surface_dsc_comment(surface, comment);
	return Gurax::Value::nil();
}

// cairo.cairo_ps_surface_dsc_begin_setup(surface as cairo_surface_t)
Gurax_DeclareFunctionAlias(cairo_ps_surface_dsc_begin_setup_gurax, "cairo_ps_surface_dsc_begin_setup")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_ps_surface_dsc_begin_setup_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	// Function body
	cairo_ps_surface_dsc_begin_setup(surface);
	return Gurax::Value::nil();
}

// cairo.cairo_ps_surface_dsc_begin_page_setup(surface as cairo_surface_t)
Gurax_DeclareFunctionAlias(cairo_ps_surface_dsc_begin_page_setup_gurax, "cairo_ps_surface_dsc_begin_page_setup")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_ps_surface_dsc_begin_page_setup_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	// Function body
	cairo_ps_surface_dsc_begin_page_setup(surface);
	return Gurax::Value::nil();
}

// cairo.cairo_script_create(filename as String)
Gurax_DeclareFunctionAlias(cairo_script_create_gurax, "cairo_script_create")
{
	Declare(VTYPE_cairo_device_t, Flag::None);
	DeclareArg("filename", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_script_create_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* filename = args_gurax.PickString();
	// Function body
	cairo_device_t* rtn = cairo_script_create(filename);
	if (!rtn) return Value::nil();
	return new Value_cairo_device_t(rtn);
}

// cairo.cairo_script_create_for_stream(stream:w as Stream)
Gurax_DeclareFunctionAlias(cairo_script_create_for_stream_gurax, "cairo_script_create_for_stream")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamW);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_script_create_for_stream_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	RefPtr<Stream> stream(args_gurax.PickStream().Reference());
	// Function body
	cairo_device_t* device = cairo_script_create_for_stream(write_func, stream.get());
	return new Value_cairo_device_t(device, stream.release());
}

// cairo.cairo_script_write_comment(script as cairo_device_t, comment as String, len as Number)
Gurax_DeclareFunctionAlias(cairo_script_write_comment_gurax, "cairo_script_write_comment")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("script", VTYPE_cairo_device_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("comment", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("len", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_script_write_comment_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_script = args_gurax.Pick<Value_cairo_device_t>();
	cairo_device_t* script = value_script.GetEntityPtr();
	const char* comment = args_gurax.PickString();
	int len = args_gurax.PickNumber<int>();
	// Function body
	cairo_script_write_comment(script, comment, len);
	return Gurax::Value::nil();
}

// cairo.cairo_script_set_mode(script as cairo_device_t, mode as Number)
Gurax_DeclareFunctionAlias(cairo_script_set_mode_gurax, "cairo_script_set_mode")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("script", VTYPE_cairo_device_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_script_set_mode_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_script = args_gurax.Pick<Value_cairo_device_t>();
	cairo_device_t* script = value_script.GetEntityPtr();
	cairo_script_mode_t mode = args_gurax.PickNumber<cairo_script_mode_t>();
	// Function body
	cairo_script_set_mode(script, mode);
	return Gurax::Value::nil();
}

// cairo.cairo_script_get_mode(script as cairo_device_t)
Gurax_DeclareFunctionAlias(cairo_script_get_mode_gurax, "cairo_script_get_mode")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("script", VTYPE_cairo_device_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_script_get_mode_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_script = args_gurax.Pick<Value_cairo_device_t>();
	cairo_device_t* script = value_script.GetEntityPtr();
	// Function body
	cairo_script_mode_t rtn = cairo_script_get_mode(script);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_script_surface_create(script as cairo_device_t, content as Number, width as Number, height as Number)
Gurax_DeclareFunctionAlias(cairo_script_surface_create_gurax, "cairo_script_surface_create")
{
	Declare(VTYPE_cairo_surface_t, Flag::None);
	DeclareArg("script", VTYPE_cairo_device_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("content", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_script_surface_create_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_script = args_gurax.Pick<Value_cairo_device_t>();
	cairo_device_t* script = value_script.GetEntityPtr();
	cairo_content_t content = args_gurax.PickNumber<cairo_content_t>();
	double width = args_gurax.PickNumber<double>();
	double height = args_gurax.PickNumber<double>();
	// Function body
	cairo_surface_t* rtn = cairo_script_surface_create(script, content, width, height);
	if (!rtn) return Value::nil();
	return new Value_cairo_surface_t(rtn);
}

// cairo.cairo_script_surface_create_for_target(script as cairo_device_t, target as cairo_surface_t)
Gurax_DeclareFunctionAlias(cairo_script_surface_create_for_target_gurax, "cairo_script_surface_create_for_target")
{
	Declare(VTYPE_cairo_surface_t, Flag::None);
	DeclareArg("script", VTYPE_cairo_device_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("target", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_script_surface_create_for_target_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_script = args_gurax.Pick<Value_cairo_device_t>();
	cairo_device_t* script = value_script.GetEntityPtr();
	auto& value_target = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* target = value_target.GetEntityPtr();
	// Function body
	cairo_surface_t* rtn = cairo_script_surface_create_for_target(script, target);
	if (!rtn) return Value::nil();
	return new Value_cairo_surface_t(rtn);
}

// cairo.cairo_script_from_recording_surface(script as cairo_device_t, recording_surface as cairo_surface_t)
Gurax_DeclareFunctionAlias(cairo_script_from_recording_surface_gurax, "cairo_script_from_recording_surface")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("script", VTYPE_cairo_device_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("recording_surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_script_from_recording_surface_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_script = args_gurax.Pick<Value_cairo_device_t>();
	cairo_device_t* script = value_script.GetEntityPtr();
	auto& value_recording_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* recording_surface = value_recording_surface.GetEntityPtr();
	// Function body
	cairo_status_t rtn = cairo_script_from_recording_surface(script, recording_surface);
	return new Gurax::Value_Number(rtn);
}

// cairo.cairo_svg_surface_create(filename as String, width_in_points as Number, height_in_points as Number)
Gurax_DeclareFunctionAlias(cairo_svg_surface_create_gurax, "cairo_svg_surface_create")
{
	Declare(VTYPE_cairo_surface_t, Flag::None);
	DeclareArg("filename", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width_in_points", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height_in_points", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_svg_surface_create_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* filename = args_gurax.PickString();
	double width_in_points = args_gurax.PickNumber<double>();
	double height_in_points = args_gurax.PickNumber<double>();
	// Function body
	cairo_surface_t* rtn = cairo_svg_surface_create(filename, width_in_points, height_in_points);
	if (!rtn) return Value::nil();
	return new Value_cairo_surface_t(rtn);
}

// cairo.cairo_svg_surface_create_for_stream(stream:w as Stream, width_in_points as Number, height_in_points as Number)
Gurax_DeclareFunctionAlias(cairo_svg_surface_create_for_stream_gurax, "cairo_svg_surface_create_for_stream")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamW);
	DeclareArg("width_in_points", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height_in_points", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_svg_surface_create_for_stream_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	RefPtr<Stream> stream(args_gurax.PickStream().Reference());
	double width_in_points = args_gurax.PickNumber<double>();
	double height_in_points = args_gurax.PickNumber<double>();
	// Function body
	cairo_surface_t* surface = cairo_svg_surface_create_for_stream(write_func, stream.get(), width_in_points, height_in_points);
	return new Value_cairo_surface_t(surface, stream.release());
}

// cairo.cairo_svg_surface_restrict_to_version(surface as cairo_surface_t, version as Number)
Gurax_DeclareFunctionAlias(cairo_svg_surface_restrict_to_version_gurax, "cairo_svg_surface_restrict_to_version")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("version", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_svg_surface_restrict_to_version_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	cairo_svg_version_t version = args_gurax.PickNumber<cairo_svg_version_t>();
	// Function body
	cairo_svg_surface_restrict_to_version(surface, version);
	return Gurax::Value::nil();
}

// cairo.cairo_svg_get_versions()
Gurax_DeclareFunctionAlias(cairo_svg_get_versions_gurax, "cairo_svg_get_versions")
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_svg_get_versions_gurax, processor_gurax, argument_gurax)
{
	// Function body
	const cairo_svg_version_t* versions;
	int num_version;
	cairo_svg_get_versions(&versions, &num_version);
	return Value_List::Create(reinterpret_cast<const int*>(versions), num_version);
}

// cairo.cairo_svg_version_to_string(version as Number)
Gurax_DeclareFunctionAlias(cairo_svg_version_to_string_gurax, "cairo_svg_version_to_string")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("version", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_svg_version_to_string_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	cairo_svg_version_t version = args_gurax.PickNumber<cairo_svg_version_t>();
	// Function body
	const char* rtn = cairo_svg_version_to_string(version);
	return new Gurax::Value_String(rtn);
}

// cairo.cairo_svg_surface_set_document_unit(surface as cairo_surface_t, unit as Number)
Gurax_DeclareFunctionAlias(cairo_svg_surface_set_document_unit_gurax, "cairo_svg_surface_set_document_unit")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	DeclareArg("unit", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_svg_surface_set_document_unit_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	cairo_svg_unit_t unit = args_gurax.PickNumber<cairo_svg_unit_t>();
	// Function body
	cairo_svg_surface_set_document_unit(surface, unit);
	return Gurax::Value::nil();
}

// cairo.cairo_svg_surface_get_document_unit(surface as cairo_surface_t)
Gurax_DeclareFunctionAlias(cairo_svg_surface_get_document_unit_gurax, "cairo_svg_surface_get_document_unit")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("surface", VTYPE_cairo_surface_t, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementFunctionEx(cairo_svg_surface_get_document_unit_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_surface = args_gurax.Pick<Value_cairo_surface_t>();
	cairo_surface_t* surface = value_surface.GetEntityPtr();
	// Function body
	cairo_svg_unit_t rtn = cairo_svg_surface_get_document_unit(surface);
	return new Gurax::Value_Number(rtn);
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
	frame.Assign(Gurax_CreateFunction(cairo_set_dash_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_set_miter_limit_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_translate_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_scale_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_rotate_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_transform_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_set_matrix_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_identity_matrix_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_user_to_device_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_user_to_device_distance_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_device_to_user_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_device_to_user_distance_gurax));
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
	frame.Assign(Gurax_CreateFunction(cairo_path_extents_gurax));
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
	frame.Assign(Gurax_CreateFunction(cairo_stroke_extents_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_fill_extents_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_reset_clip_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_clip_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_clip_preserve_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_clip_extents_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_copy_clip_rectangle_list_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_rectangle_list_destroy_gurax));
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
	frame.Assign(Gurax_CreateFunction(cairo_get_operator_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_get_source_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_get_tolerance_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_get_antialias_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_has_current_point_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_get_current_point_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_get_fill_rule_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_get_line_width_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_get_line_cap_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_get_line_join_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_get_miter_limit_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_get_dash_count_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_get_dash_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_get_matrix_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_get_target_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_get_group_target_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_copy_path_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_copy_path_flat_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_append_path_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_path_destroy_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_status_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_status_to_string_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_device_reference_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_device_get_type_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_device_status_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_device_acquire_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_device_release_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_device_flush_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_device_finish_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_device_destroy_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_device_get_reference_count_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_surface_create_similar_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_surface_create_similar_image_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_surface_map_to_image_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_surface_unmap_image_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_surface_create_for_rectangle_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_surface_create_observer_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_surface_observer_elapsed_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_device_observer_elapsed_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_device_observer_paint_elapsed_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_device_observer_mask_elapsed_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_device_observer_fill_elapsed_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_device_observer_stroke_elapsed_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_device_observer_glyphs_elapsed_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_surface_reference_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_surface_finish_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_surface_destroy_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_surface_get_device_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_surface_get_reference_count_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_surface_status_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_surface_get_type_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_surface_get_content_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_surface_write_to_png_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_surface_write_to_png_stream_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_surface_get_mime_data_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_surface_supports_mime_type_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_surface_get_font_options_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_surface_flush_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_surface_mark_dirty_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_surface_mark_dirty_rectangle_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_surface_set_device_scale_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_surface_get_device_scale_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_surface_set_device_offset_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_surface_get_device_offset_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_surface_set_fallback_resolution_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_surface_get_fallback_resolution_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_surface_copy_page_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_surface_show_page_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_surface_has_show_text_glyphs_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_image_surface_create_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_format_stride_for_width_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_image_surface_get_format_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_image_surface_get_width_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_image_surface_get_height_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_image_surface_get_stride_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_image_surface_create_from_png_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_recording_surface_create_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_recording_surface_get_extents_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_pattern_create_raster_source_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_raster_source_pattern_set_callback_data_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_pattern_create_rgb_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_pattern_create_rgba_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_pattern_create_for_surface_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_pattern_create_linear_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_pattern_create_radial_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_pattern_create_mesh_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_pattern_reference_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_pattern_destroy_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_pattern_get_reference_count_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_pattern_status_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_pattern_get_type_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_pattern_add_color_stop_rgb_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_pattern_add_color_stop_rgba_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_mesh_pattern_begin_patch_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_mesh_pattern_end_patch_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_mesh_pattern_curve_to_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_mesh_pattern_line_to_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_mesh_pattern_move_to_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_mesh_pattern_set_control_point_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_mesh_pattern_set_corner_color_rgb_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_mesh_pattern_set_corner_color_rgba_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_pattern_set_matrix_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_pattern_get_matrix_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_pattern_set_extend_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_pattern_get_extend_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_pattern_set_filter_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_pattern_get_filter_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_pattern_get_rgba_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_pattern_get_color_stop_rgba_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_mesh_pattern_get_path_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_matrix_init_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_matrix_init_identity_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_matrix_init_translate_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_matrix_init_scale_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_matrix_init_rotate_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_matrix_translate_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_matrix_scale_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_matrix_rotate_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_matrix_invert_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_matrix_multiply_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_matrix_transform_distance_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_matrix_transform_point_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_region_create_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_region_create_rectangle_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_region_create_rectangles_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_region_copy_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_region_reference_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_region_destroy_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_region_equal_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_region_status_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_region_get_extents_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_region_num_rectangles_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_region_get_rectangle_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_region_is_empty_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_region_contains_rectangle_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_region_contains_point_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_region_translate_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_region_subtract_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_region_subtract_rectangle_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_region_intersect_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_region_intersect_rectangle_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_region_union_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_region_union_rectangle_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_region_xor_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_region_xor_rectangle_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_debug_reset_static_data_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_pdf_surface_create_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_pdf_surface_create_for_stream_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_pdf_surface_restrict_to_version_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_pdf_get_versions_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_pdf_version_to_string_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_pdf_surface_set_size_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_pdf_surface_add_outline_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_pdf_surface_set_metadata_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_pdf_surface_set_page_label_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_pdf_surface_set_thumbnail_size_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_ps_surface_create_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_ps_surface_create_for_stream_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_ps_surface_restrict_to_level_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_ps_level_to_string_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_ps_surface_set_eps_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_ps_surface_get_eps_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_ps_surface_set_size_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_ps_surface_dsc_comment_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_ps_surface_dsc_begin_setup_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_ps_surface_dsc_begin_page_setup_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_script_create_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_script_create_for_stream_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_script_write_comment_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_script_set_mode_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_script_get_mode_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_script_surface_create_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_script_surface_create_for_target_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_script_from_recording_surface_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_svg_surface_create_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_svg_surface_create_for_stream_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_svg_surface_restrict_to_version_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_svg_get_versions_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_svg_version_to_string_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_svg_surface_set_document_unit_gurax));
	frame.Assign(Gurax_CreateFunction(cairo_svg_surface_get_document_unit_gurax));
}

Gurax_EndModuleScope(cairo)
