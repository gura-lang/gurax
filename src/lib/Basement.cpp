//==============================================================================
// Basement.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Basement
//------------------------------------------------------------------------------
Basement Basement::Inst;

Basement::Basement() : _pFrame(new Frame_Basement()), _ps1(">>> "), _ps2("... ")
{
	_pathList.push_back(".");
}

void Basement::Initialize(int argc, char** argv)
{
	_argc = argc;
	_argv = argv;
	Frame& frame = GetFrame();
	PrepareVType(frame);
	PrepareValue(frame);
	Statements::AssignToBasement(frame);
	Functions::AssignToBasement(frame);
	SetStreamCIn(Stream::CIn->Reference());
	SetStreamCOut(Stream::COut->Reference());
	SetStreamCErr(Stream::CErr->Reference());
	frame.Assign(Module_codecs::Create(frame.Reference()));
	frame.Assign(Module_fs::Create(frame.Reference()));
	frame.Assign(Module_math::Create(frame.Reference()));
	frame.Assign(Module_os::Create(frame.Reference()));
	frame.Assign(Module_path::Create(frame.Reference()));
	frame.Assign(Module_re::Create(frame.Reference()));
	frame.Assign(Module_sys::Create(frame.Reference()));
}

void Basement::PrepareVType(Frame& frame)
{
	VTYPE_Object.Prepare(frame);
	VTYPE_Any.Prepare(frame);
	VTYPE_ArgMapper.Prepare(frame);
	VTYPE_ArgMapper_Multiple.Prepare(frame);
	VTYPE_ArgSlot.Prepare(frame);
	VTYPE_Argument.Prepare(frame);
	VTYPE_Attribute.Prepare(frame);
	VTYPE_Binary.Prepare(frame);
	VTYPE_Bool.Prepare(frame);
	VTYPE_DateTime.Prepare(frame);
	VTYPE_Dict.Prepare(frame);
	VTYPE_Error.Prepare(frame);
	VTYPE_ErrorType.Prepare(frame);
	VTYPE_Expr.Prepare(frame);
	VTYPE_Frame.Prepare(frame);
	VTYPE_Function.Prepare(frame);
	VTYPE_Iterator.Prepare(frame);
	VTYPE_VType.Prepare(frame);
	VTYPE_List.Prepare(frame);
	VTYPE_Member.Prepare(frame);
	VTYPE_Module.Prepare(frame);
	VTYPE_Nil.Prepare(frame);
	VTYPE_Number.Prepare(frame);
	VTYPE_PropHandler.Prepare(frame);
	VTYPE_PUnit.Prepare(frame);
	VTYPE_Quote.Prepare(frame);
	VTYPE_Random.Prepare(frame);
	VTYPE_Stream.Prepare(frame);
	VTYPE_String.Prepare(frame);
	VTYPE_StringPtr.Prepare(frame);
	VTYPE_Symbol.Prepare(frame);
	VTYPE_Template.Prepare(frame);
	VTYPE_TimeDelta.Prepare(frame);
	VTYPE_Undefined.Prepare(frame);
}

void Basement::PrepareValue(Frame& frame)
{
	Value::CreateConstant();
	frame.Assign("nil",		Value::nil());
	frame.Assign("false",	Value::false_());
	frame.Assign("true",	Value::true_());
}

}
