//==============================================================================
// VType_Frame.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//------------------------------------------------------------------------------
// Implementation of class method
//------------------------------------------------------------------------------
// Frame.Current() {block?}
Gurax_DeclareClassMethod(Frame, Current)
{
	Declare(VTYPE_Frame, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Returns a `Frame` instance of the current scope.\n");
}

Gurax_ImplementClassMethod(Frame, Current)
{
	// Arguments
	ArgPicker args(argument);
	// Function body
	RefPtr<Value> pValueRtn(new Value_Frame(processor.GetFrameCur().Reference()));
	return argument.ReturnValue(processor, pValueRtn.release());
}

// Frame.Where(symbol:Symbol) {block?}
Gurax_DeclareClassMethod(Frame, Where)
{
	Declare(VTYPE_Frame, Flag::None);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Searches a value in the current environment and returns a `Frame` instance where it's found.\n"
		"If the symbol is not found, it returns `nil`.\n");
}

Gurax_ImplementClassMethod(Frame, Where)
{
	// Arguments
	ArgPicker args(argument);
	const Symbol* pSymbol = args.PickSymbol();
	// Function body
	Frame* pFrameSrc = nullptr;
	RefPtr<Value> pValue(processor.GetFrameCur().DoRetrieve(pSymbol, &pFrameSrc));
	RefPtr<Value> pValueRtn(Value::nil());
	if (pValue) pValueRtn.reset(new Value_Frame(pFrameSrc->Reference()));
	return argument.ReturnValue(processor, pValueRtn.release());
}

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// Frame#Print():void
Gurax_DeclareMethod(Frame, Print)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Prints the frame's information.");
}

Gurax_ImplementMethod(Frame, Print)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	valueThis.GetFrame().PrintTree(Basement::Inst.GetStreamCOut());
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// Frame#id
Gurax_DeclareProperty_R(Frame, id)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Frame, id)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(String().Format("#%p", &valueThis.GetFrame()));
}

// Frame#local
Gurax_DeclareProperty_R(Frame, local)
{
	Declare(VTYPE_Frame, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Frame, local)
{
	auto& valueThis = GetValueThis(valueTarget);
	Frame* pFrame = valueThis.GetFrame().DoGetFrameLocal();
	if (!pFrame) return Value::nil();
	return new Value_Frame(pFrame->Reference());
}

// Frame#outer
Gurax_DeclareProperty_R(Frame, outer)
{
	Declare(VTYPE_Frame, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Frame, outer)
{
	auto& valueThis = GetValueThis(valueTarget);
	Frame* pFrame = valueThis.GetFrame().GetFrameOuter();
	if (!pFrame) return Value::nil();
	return new Value_Frame(pFrame->Reference());
}

// Frame#typeName
Gurax_DeclareProperty_R(Frame, typeName)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Frame, typeName)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetFrame().GetTypeName());
}

//------------------------------------------------------------------------------
// VType_Frame
//------------------------------------------------------------------------------
VType_Frame VTYPE_Frame("Frame");

void VType_Frame::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of class method
	Assign(Gurax_CreateClassMethod(Frame, Current));
	Assign(Gurax_CreateClassMethod(Frame, Where));
	// Assignment of class method
	Assign(Gurax_CreateMethod(Frame, Print));
	// Assignment of property
	Assign(Gurax_CreateProperty(Frame, id));
	Assign(Gurax_CreateProperty(Frame, outer));
	Assign(Gurax_CreateProperty(Frame, typeName));
}

//------------------------------------------------------------------------------
// Value_Frame
//------------------------------------------------------------------------------
VType& Value_Frame::vtype = VTYPE_Frame;

}
